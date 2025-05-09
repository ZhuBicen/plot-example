#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "glwidget.h"

int main(int argc, char *argv[])
{
    // Set up high-quality OpenGL format
    QSurfaceFormat format;
    format.setVersion(3, 3);           // Use OpenGL 3.3 core profile
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(4);              // Anti-aliasing
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
    
    QApplication app(argc, argv);
    
    // Create main window
    QMainWindow window;
    window.setWindowTitle("Qt6 OpenGLFramebufferObject Demo");
    window.resize(800, 600);
    
    // Create and set our custom OpenGL widget as the central widget
    GLWidget *glWidget = new GLWidget(&window);
    window.setCentralWidget(glWidget);
    
    window.show();
    
    return app.exec();
}
