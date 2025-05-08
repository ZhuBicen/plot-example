#pragma once
#include "src/global.h"
#include "src/axis/axisticker.h"
#include "src/axis/range.h"

/* modified 2022-11-06T12:45:56, size 2594   */

class QCP_LIB_DECL QCPAxisTickerLog : public QCPAxisTicker
{
public:
  QCPAxisTickerLog();
  
  // getters:
  double logBase() const { return mLogBase; }
  int subTickCount() const { return mSubTickCount; }
  
  // setters:
  void setLogBase(double base);
  void setSubTickCount(int subTicks);
  
protected:
  // property members:
  double mLogBase;
  int mSubTickCount;
  
  // non-property members:
  double mLogBaseLnInv;
  
  // reimplemented virtual methods:
  virtual int getSubTickCount(double tickStep) Q_DECL_OVERRIDE;
  virtual QVector<double> createTickVector(double tickStep, const QCPRange &range) Q_DECL_OVERRIDE;
};

/* end of 'src/axis/axistickerlog.h' */


/* including file 'src/axis/axis.h'         */
