#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include <QOpenGLPaintDevice>
#include <QPainter>
#include <QTimer>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = nullptr);
    ~GLWidget() override;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private slots:
    void updateAnimation();

private:
    void renderContent();
    void cleanupGL();

    QOpenGLFramebufferObject *m_fbo;
    QOpenGLPaintDevice *m_paintDevice;
    QTimer m_animationTimer;
    float m_rotation;
};

#endif // GLWIDGET_H
