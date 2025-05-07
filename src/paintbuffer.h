#pragma once
#include "src/global.h"
/* modified 2022-11-06T12:45:56, size 5006 */

class QCP_LIB_DECL QCPAbstractPaintBuffer
{
public:
  explicit QCPAbstractPaintBuffer(const QSize &size, double devicePixelRatio);
  virtual ~QCPAbstractPaintBuffer();
  
  // getters:
  QSize size() const { return mSize; }
  bool invalidated() const { return mInvalidated; }
  double devicePixelRatio() const { return mDevicePixelRatio; }
  
  // setters:
  void setSize(const QSize &size);
  void setInvalidated(bool invalidated=true);
  void setDevicePixelRatio(double ratio);
  
  // introduced virtual methods:
  virtual QCPPainter *startPainting() = 0;
  virtual void donePainting() {}
  virtual void draw(QCPPainter *painter) const = 0;
  virtual void clear(const QColor &color) = 0;
  
protected:
  // property members:
  QSize mSize;
  double mDevicePixelRatio;
  
  // non-property members:
  bool mInvalidated;
  
  // introduced virtual methods:
  virtual void reallocateBuffer() = 0;
};


class QCP_LIB_DECL QCPPaintBufferPixmap : public QCPAbstractPaintBuffer
{
public:
  explicit QCPPaintBufferPixmap(const QSize &size, double devicePixelRatio);
  virtual ~QCPPaintBufferPixmap() Q_DECL_OVERRIDE;
  
  // reimplemented virtual methods:
  virtual QCPPainter *startPainting() Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) const Q_DECL_OVERRIDE;
  void clear(const QColor &color) Q_DECL_OVERRIDE;
  
protected:
  // non-property members:
  QPixmap mBuffer;
  
  // reimplemented virtual methods:
  virtual void reallocateBuffer() Q_DECL_OVERRIDE;
};


#ifdef QCP_OPENGL_PBUFFER
class QCP_LIB_DECL QCPPaintBufferGlPbuffer : public QCPAbstractPaintBuffer
{
public:
  explicit QCPPaintBufferGlPbuffer(const QSize &size, double devicePixelRatio, int multisamples);
  virtual ~QCPPaintBufferGlPbuffer() Q_DECL_OVERRIDE;
  
  // reimplemented virtual methods:
  virtual QCPPainter *startPainting() Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) const Q_DECL_OVERRIDE;
  void clear(const QColor &color) Q_DECL_OVERRIDE;
  
protected:
  // non-property members:
  QGLPixelBuffer *mGlPBuffer;
  int mMultisamples;
  
  // reimplemented virtual methods:
  virtual void reallocateBuffer() Q_DECL_OVERRIDE;
};
#endif // QCP_OPENGL_PBUFFER


#ifdef QCP_OPENGL_FBO
class QCP_LIB_DECL QCPPaintBufferGlFbo : public QCPAbstractPaintBuffer
{
public:
  explicit QCPPaintBufferGlFbo(const QSize &size, double devicePixelRatio, QWeakPointer<QOpenGLContext> glContext, QWeakPointer<QOpenGLPaintDevice> glPaintDevice);
  virtual ~QCPPaintBufferGlFbo() Q_DECL_OVERRIDE;
  
  // reimplemented virtual methods:
  virtual QCPPainter *startPainting() Q_DECL_OVERRIDE;
  virtual void donePainting() Q_DECL_OVERRIDE;
  virtual void draw(QCPPainter *painter) const Q_DECL_OVERRIDE;
  void clear(const QColor &color) Q_DECL_OVERRIDE;
  
protected:
  // non-property members:
  QWeakPointer<QOpenGLContext> mGlContext;
  QWeakPointer<QOpenGLPaintDevice> mGlPaintDevice;
  QOpenGLFramebufferObject *mGlFrameBuffer;
  
  // reimplemented virtual methods:
  virtual void reallocateBuffer() Q_DECL_OVERRIDE;
};
#endif // QCP_OPENGL_FBO

/* end of 'src/paintbuffer.h' */


/* including file 'src/layer.h'            */