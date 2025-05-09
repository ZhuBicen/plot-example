#include "glwidget.h"
#include <QColor>
#include <QOpenGLContext>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_fbo(nullptr)
    , m_paintDevice(nullptr)
    , m_rotation(0.0f)
{
    // Set up animation timer to update the scene
    m_animationTimer.setInterval(16); // approximately 60 FPS
    connect(&m_animationTimer, &QTimer::timeout, this, &GLWidget::updateAnimation);
    m_animationTimer.start();
}

GLWidget::~GLWidget()
{
    // Make sure the context is current before cleaning up resources
    makeCurrent();
    cleanupGL();
    doneCurrent();
}

void GLWidget::initializeGL()
{
    // Initialize OpenGL functions
    initializeOpenGLFunctions();
    
    // Set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Create the framebuffer object (will be properly sized in resizeGL)
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4); // Enable multisampling for better quality
    
    m_fbo = new QOpenGLFramebufferObject(width(), height(), format);
    
    // Create paint device for the FBO
    m_paintDevice = new QOpenGLPaintDevice(m_fbo->size());
    
    // Check if FBO creation was successful
    if (!m_fbo->isValid()) {
        qWarning("Failed to create FBO!");
    }
}

void GLWidget::resizeGL(int w, int h)
{
    // Account for high DPI displays
    qreal devicePixelRatio = window()->devicePixelRatio();
    
    // Width and height in device pixels
    int deviceWidth = w * devicePixelRatio;
    int deviceHeight = h * devicePixelRatio;
    
    // Resize viewport to match device pixels
    // This ensures the viewport starts at (0,0) and fills the entire widget
    glViewport(0, 0, deviceWidth, deviceHeight);
    
    // Clean up old resources
    if (m_paintDevice) {
        delete m_paintDevice;
        m_paintDevice = nullptr;
    }
    
    if (m_fbo) {
        delete m_fbo;
        m_fbo = nullptr;
    }
    
    // Create new FBO with updated size in device pixels
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(16); // Enable multisampling for better quality
    
    m_fbo = new QOpenGLFramebufferObject(deviceWidth, deviceHeight, format);
    
    // Create new paint device for the FBO with correct device pixel ratio
    m_paintDevice = new QOpenGLPaintDevice(QSize(deviceWidth, deviceHeight));
    m_paintDevice->setDevicePixelRatio(3);
}

void GLWidget::paintGL()
{
    if (!m_fbo || !m_fbo->isValid())
        return;
    
    // Account for high DPI displays
    qreal devicePixelRatio = window()->devicePixelRatio();
    
    // Make sure the viewport is correctly set for the default framebuffer
    glViewport(0, 0, width() * devicePixelRatio, height() * devicePixelRatio);
    
    qDebug() << width() << height() << devicePixelRatio;
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Render content into the FBO
    renderContent();
    
    // For the blit operation, we need to ensure that:
    // 1. We're using device pixels as coordinates
    // 2. Both rects match in size to avoid stretching
    
    // Target is the default framebuffer (screen) at device pixel coordinates
    // This ensures we blit to the entire window
    QRect targetRect(0, 0, width() * devicePixelRatio, height() * devicePixelRatio);
    
    // Source is the FBO at its native coordinates
    QRect sourceRect(0, 0, m_fbo->width(), m_fbo->height());
    
    // Use blitFramebuffer for efficient copy from FBO to default framebuffer
    // Pass nullptr as the target FBO to indicate the default framebuffer
    QOpenGLFramebufferObject::blitFramebuffer(nullptr, targetRect, 
                                             m_fbo, sourceRect);
}

void GLWidget::renderContent()
{
    if (!m_fbo || !m_paintDevice)
        return;
    
    // Get FBO dimensions
    int fboWidth = m_fbo->width();
    int fboHeight = m_fbo->height();
    
    // Set viewport to FBO size to ensure we're rendering to the entire FBO
    glViewport(0, 0, fboWidth, fboHeight);
    
    // Bind the FBO to render into it
    m_fbo->bind();
    
    // Clear the FBO with a background color
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Create a painter that paints directly to the FBO through the paint device
    QPainter painter(m_paintDevice);
    
    // Set up painter with anti-aliasing
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // Get the device pixel ratio
    qreal devicePixelRatio = window()->devicePixelRatio();
    qreal w = m_fbo->width() / devicePixelRatio;
    qreal h = m_fbo->height() / devicePixelRatio;

    qDebug() << "FBO" << fboWidth << fboHeight;
    qDebug() << "opengal Paint device size" << m_paintDevice->size();
    // Draw background - ensure it fills the entire FBO
    painter.fillRect(0, 0, w, h, QColor(48, 60, 80));
    
    // Save painter state before transformations
    painter.save();
    
    // Center and rotate - use FBO dimensions for centering
    painter.translate(w/2, h/2);
    painter.rotate(m_rotation);
    
    // Size relative to the viewport/FBO
    const int points = 8;
    // Make the star size proportional to the smaller dimension of the window
    // and make it larger (40% of width/height) to be more visible
    const int radius = qMin(w, h) * 0.4;
    const int innerRadius = radius / 2;
    
    QPolygonF star;
    for (int i = 0; i < 2 * points; ++i) {
        double r = (i % 2 == 0) ? radius : innerRadius;
        double angle = i * M_PI / points;
        star << QPointF(r * cos(angle), r * sin(angle));
    }
    
    QLinearGradient gradient(QPointF(-radius, -radius), QPointF(radius, radius));
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(0.25, Qt::yellow);
    gradient.setColorAt(0.5, Qt::green);
    gradient.setColorAt(0.75, Qt::blue);
    gradient.setColorAt(1, Qt::magenta);
    
    // Use a pen width proportional to the star size for better visibility
    painter.setPen(QPen(Qt::white, radius * 0.01));
    painter.setBrush(gradient);
    painter.drawPolygon(star);
    
    // Draw some additional shapes - central circle
    painter.drawEllipse(QPointF(0, 0), innerRadius / 2, innerRadius / 2);
    
    // Restore painter state
    painter.restore();
    
    // Draw some text with properly scaled font size
    // Scale font size based on window dimension for better visibility
    QFont font = painter.font();
    font.setPointSize(qMax(12, qMin(fboWidth, fboHeight) / 30));
    painter.setFont(font);
    painter.setPen(Qt::white);
    
    // Draw title text at the top
    painter.drawText(20, 40, "QOpenGLFramebufferObject Demo");
    
    // Draw information text at the bottom
    QString infoText = QString("Rotation: %1°").arg(static_cast<int>(m_rotation));
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(infoText);
    painter.drawText(fboWidth - textWidth - 20, fboHeight - 20, infoText);
    
    // End painting
    painter.end();
    
    // Release the FBO
    m_fbo->release();
}

void GLWidget::updateAnimation()
{
    // Update rotation angle for animation
    m_rotation += 1.0f;
    if (m_rotation >= 360.0f) {
        m_rotation -= 360.0f;
    }
    
    // Request a redraw
    update();
}

void GLWidget::cleanupGL()
{
    // Clean up the FBO
    if (m_fbo) {
        delete m_fbo;
        m_fbo = nullptr;
    }
    
    // Clean up the paint device
    if (m_paintDevice) {
        delete m_paintDevice;
        m_paintDevice = nullptr;
    }
}
