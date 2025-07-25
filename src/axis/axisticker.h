#pragma once
#include "src/global.h"
#include "src/axis/range.h"

class QCP_LIB_DECL QCPAxisTicker
{
  Q_GADGET
public:
  /*!
    Defines the strategies that the axis ticker may follow when choosing the size of the tick step.
    
    \see setTickStepStrategy
  */
  enum TickStepStrategy
  {
    tssReadability    ///< A nicely readable tick step is prioritized over matching the requested number of ticks (see \ref setTickCount)
    ,tssMeetTickCount ///< Less readable tick steps are allowed which in turn facilitates getting closer to the requested tick count
  };
  Q_ENUMS(TickStepStrategy)
  
  QCPAxisTicker();
  virtual ~QCPAxisTicker();
  
  // getters:
  TickStepStrategy tickStepStrategy() const { return mTickStepStrategy; }
  int tickCount() const { return mTickCount; }
  double tickOrigin() const { return mTickOrigin; }
  
  // setters:
  void setTickStepStrategy(TickStepStrategy strategy);
  void setTickCount(int count);
  void setTickOrigin(double origin);
  
  // introduced virtual methods:
  virtual void generate(const QCPRange &range, const QLocale &locale, QChar formatChar, int precision, QVector<double> &ticks, QVector<double> *subTicks, QVector<QString> *tickLabels);
  
protected:
  // property members:
  TickStepStrategy mTickStepStrategy;
  int mTickCount;
  double mTickOrigin;
  
  // introduced virtual methods:
  virtual double getTickStep(const QCPRange &range);
  virtual int getSubTickCount(double tickStep);
  virtual QString getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision);
  virtual QVector<double> createTickVector(double tickStep, const QCPRange &range);
  virtual QVector<double> createSubTickVector(int subTickCount, const QVector<double> &ticks);
  virtual QVector<QString> createLabelVector(const QVector<double> &ticks, const QLocale &locale, QChar formatChar, int precision);
  
  // non-virtual methods:
  void trimTicks(const QCPRange &range, QVector<double> &ticks, bool keepOneOutlier) const;
  double pickClosest(double target, const QVector<double> &candidates) const;
  double getMantissa(double input, double *magnitude=nullptr) const;
  double cleanMantissa(double input) const;
  
private:
  Q_DISABLE_COPY(QCPAxisTicker)
  
};
Q_DECLARE_METATYPE(QCPAxisTicker::TickStepStrategy)
Q_DECLARE_METATYPE(QSharedPointer<QCPAxisTicker>)

/* end of 'src/axis/axisticker.h' */


/* including file 'src/axis/axistickerdatetime.h' */
