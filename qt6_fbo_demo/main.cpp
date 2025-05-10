#include <QApplication>
#include <QDebug>
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>
#include <QPainter>
#include <QResizeEvent>
#include <QSurfaceFormat>
#include <QWidget>
#include <QWindow>

class FBOWidget : public QWidget
{
public:
    FBOWidget(QWidget *parent = nullptr)
        : QWidget(parent)
        , m_fbo(nullptr)
        , m_context(nullptr)
        , m_surface(nullptr)
        , m_fboImage(nullptr)
    {
        // Do not use WA_PaintOnScreen as we want to use QPainter
        setAttribute(Qt::WA_NoSystemBackground);
        setAutoFillBackground(false);

        // Set up OpenGL context
        m_context = new QOpenGLContext(this);
        QSurfaceFormat format;
        format.setRenderableType(QSurfaceFormat::OpenGL);
        format.setVersion(3, 3); // Use OpenGL 3.3 Core
        format.setProfile(QSurfaceFormat::CoreProfile);
        m_context->setFormat(format);

        if (!m_context->create()) {
            qCritical() << "Failed to create OpenGL context";
            return;
        }

        // Create offscreen surface for the OpenGL context
        m_surface = new QOffscreenSurface();
        m_surface->setFormat(m_context->format());
        m_surface->create();

        if (!m_surface->isValid()) {
            qCritical() << "Failed to create offscreen surface";
            return;
        }

        // Set a reasonable minimum size
        resize(400, 400);
    }

    ~FBOWidget()
    {
        if (m_context && m_surface && m_context->makeCurrent(m_surface)) {
            delete m_fbo;
            m_context->doneCurrent();
        }
        delete m_fboImage;
        delete m_context;
        delete m_surface;
    }

protected:
    void resizeEvent(QResizeEvent *event) override
    {
        // Recreate FBO on resize with DPR scaling
        if (m_context && m_surface && m_context->makeCurrent(m_surface)) {
            delete m_fbo;
            // Create FBO at device pixel size
            QSize fboSize = size() * devicePixelRatio();
            m_fbo = new QOpenGLFramebufferObject(fboSize, QOpenGLFramebufferObject::NoAttachment);

            // Make sure to update the image next time we paint
            delete m_fboImage;
            m_fboImage = nullptr;

            m_context->doneCurrent();
        }
        QWidget::resizeEvent(event);
    }

    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);

        if (!m_context || !m_surface)
            return;

        // Initialize FBO if it does not exist yet
        if (!m_fbo && m_context->makeCurrent(m_surface)) {
            QSize fboSize = size() * devicePixelRatio();
            m_fbo = new QOpenGLFramebufferObject(fboSize, QOpenGLFramebufferObject::NoAttachment);
            m_context->doneCurrent();
        }

        if (!m_fbo)
            return;

        // Only render to FBO if we need to update the image
        if (!m_fboImage) {
            if (m_context->makeCurrent(m_surface)) {
                QOpenGLFunctions *f = m_context->functions();

                // Bind FBO
                m_fbo->bind();

                // Clear with a background color
                f->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                f->glClear(GL_COLOR_BUFFER_BIT);

                // Draw using QPainter on the OpenGL paint device
                {
                    // Create a paint device for the FBO
                    QOpenGLPaintDevice device(m_fbo->size());

                    QPainter painter(&device);
                    painter.setRenderHint(QPainter::Antialiasing);

                    // Calculate positions based on device pixels
                    int deviceWidth = width() * devicePixelRatio();
                    int deviceHeight = height() * devicePixelRatio();
                    int radius = qMin(deviceWidth, deviceHeight) / 3;
                    QPoint center(deviceWidth / 2, deviceHeight / 2);

                    // Set font size in device pixels
                    QFont font("Arial", 16 * devicePixelRatio(), QFont::Bold);
                    painter.setFont(font);

                    // Draw text above the circle
                    painter.setPen(Qt::white);
                    QString text = "Qt6 FBO Demo";
                    QFontMetrics fm(font);
                    int textWidth = fm.horizontalAdvance(text);
                    int textHeight = fm.height();
                    painter.drawText(center.x() - textWidth / 2,
                                     center.y() - radius - textHeight,
                                     text);

                    // Draw a circle in the center
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(QColor(0, 120, 215));
                    painter.drawEllipse(center, radius, radius);

                    // End painting on OpenGL device
                    painter.end();
                }

                // Release FBO
                m_fbo->release();

                // Store the rendered image with correct DPR
                delete m_fboImage;
                m_fboImage = new QImage(m_fbo->toImage());
                m_fboImage->setDevicePixelRatio(devicePixelRatio());

                m_context->doneCurrent();
            }
        }

        // Draw the image to fill the widget
        if (m_fboImage) {
            QPainter widgetPainter(this);
            widgetPainter.setRenderHint(QPainter::SmoothPixmapTransform);
            widgetPainter.drawImage(rect(), *m_fboImage, m_fboImage->rect());
        }
    }

private:
    QOpenGLFramebufferObject *m_fbo;
    QOpenGLContext *m_context;
    QOffscreenSurface *m_surface;
    QImage *m_fboImage; // Cache the rendered image
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Set default surface format for the application
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(16);
    QSurfaceFormat::setDefaultFormat(format);

    FBOWidget widget;
    widget.setWindowTitle("Qt6 FBO Demo");
    widget.show();

    return app.exec();
}
