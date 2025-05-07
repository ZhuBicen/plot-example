#pragma once
#include "src/global.h"
/* modified 2022-11-06T12:45:56, size 3137        */

class QCP_LIB_DECL QCPItemStraightLine : public QCPAbstractItem
{
  Q_OBJECT
  /// \cond INCLUDE_QPROPERTIES
  Q_PROPERTY(QPen pen READ pen WRITE setPen)
  Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
  /// \endcond
public:
  explicit QCPItemStraightLine(QCustomPlot *parentPlot);
  virtual ~QCPItemStraightLine() Q_DECL_OVERRIDE;
  
  // getters:
  QPen pen() const { return mPen; }
  QPen selectedPen() const { return mSelectedPen; }
  
  // setters;
  void setPen(const QPen &pen);
  void setSelectedPen(const QPen &pen);
  
  // reimplemented virtual methods:
  virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=nullptr) const Q_DECL_OVERRIDE;
  
  QCPItemPosition * const point1;
  QCPItemPosition * const point2;
  
protected:
  // property members:
  QPen mPen, mSelectedPen;
  
  // reimplemented virtual methods:
  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  
  // non-virtual methods:
  QLineF getRectClippedStraightLine(const QCPVector2D &base, const QCPVector2D &vec, const QRect &rect) const;
  QPen mainPen() const;
};

/* end of 'src/items/item-straightline.h' */


/* including file 'src/items/item-line.h'  */