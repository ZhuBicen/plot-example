/* modified 2022-11-06T12:45:56, size 3308     */

class QCP_LIB_DECL QCPAxisTickerFixed : public QCPAxisTicker
{
  Q_GADGET
public:
  /*!
    Defines how the axis ticker may modify the specified tick step (\ref setTickStep) in order to
    control the number of ticks in the axis range.
    
    \see setScaleStrategy
  */
  enum ScaleStrategy { ssNone      ///< Modifications are not allowed, the specified tick step is absolutely fixed. This might cause a high tick density and overlapping labels if the axis range is zoomed out.
                       ,ssMultiples ///< An integer multiple of the specified tick step is allowed. The used factor follows the base class properties of \ref setTickStepStrategy and \ref setTickCount.
                       ,ssPowers    ///< An integer power of the specified tick step is allowed.
                     };
  Q_ENUMS(ScaleStrategy)
  
  QCPAxisTickerFixed();
  
  // getters:
  double tickStep() const { return mTickStep; }
  ScaleStrategy scaleStrategy() const { return mScaleStrategy; }
  
  // setters:
  void setTickStep(double step);
  void setScaleStrategy(ScaleStrategy strategy);
  
protected:
  // property members:
  double mTickStep;
  ScaleStrategy mScaleStrategy;
  
  // reimplemented virtual methods:
  virtual double getTickStep(const QCPRange &range) Q_DECL_OVERRIDE;
};
Q_DECLARE_METATYPE(QCPAxisTickerFixed::ScaleStrategy)

/* end of 'src/axis/axistickerfixed.h' */


/* including file 'src/axis/axistickertext.h' */