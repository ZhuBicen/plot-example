#pragma once
#include "src/global.h"
#include "src/vector2d.h"

class QCP_LIB_DECL QCPLineEnding
{
  Q_GADGET
public:
  /*!
    Defines the type of ending decoration for line-like items, e.g. an arrow.
    
    \image html QCPLineEnding.png
    
    The width and length of these decorations can be controlled with the functions \ref setWidth
    and \ref setLength. Some decorations like \ref esDisc, \ref esSquare, \ref esDiamond and \ref esBar only
    support a width, the length property is ignored.
    
    \see QCPItemLine::setHead, QCPItemLine::setTail, QCPItemCurve::setHead, QCPItemCurve::setTail, QCPAxis::setLowerEnding, QCPAxis::setUpperEnding
  */
  enum EndingStyle { esNone          ///< No ending decoration
                     ,esFlatArrow    ///< A filled arrow head with a straight/flat back (a triangle)
                     ,esSpikeArrow   ///< A filled arrow head with an indented back
                     ,esLineArrow    ///< A non-filled arrow head with open back
                     ,esDisc         ///< A filled circle
                     ,esSquare       ///< A filled square
                     ,esDiamond      ///< A filled diamond (45 degrees rotated square)
                     ,esBar          ///< A bar perpendicular to the line
                     ,esHalfBar      ///< A bar perpendicular to the line, pointing out to only one side (to which side can be changed with \ref setInverted)
                     ,esSkewedBar    ///< A bar that is skewed (skew controllable via \ref setLength)
                   };
  Q_ENUMS(EndingStyle)
  
  QCPLineEnding();
  QCPLineEnding(EndingStyle style, double width=8, double length=10, bool inverted=false);
  
  // getters:
  EndingStyle style() const { return mStyle; }
  double width() const { return mWidth; }
  double length() const { return mLength; }
  bool inverted() const { return mInverted; }
  
  // setters:
  void setStyle(EndingStyle style);
  void setWidth(double width);
  void setLength(double length);
  void setInverted(bool inverted);
  
  // non-property methods:
  double boundingDistance() const;
  double realLength() const;
  void draw(QCPPainter *painter, const QCPVector2D &pos, const QCPVector2D &dir) const;
  void draw(QCPPainter *painter, const QCPVector2D &pos, double angle) const;
  
protected:
  // property members:
  EndingStyle mStyle;
  double mWidth, mLength;
  bool mInverted;
};
Q_DECLARE_TYPEINFO(QCPLineEnding, Q_MOVABLE_TYPE);
Q_DECLARE_METATYPE(QCPLineEnding::EndingStyle)

/* end of 'src/lineending.h' */


/* including file 'src/axis/labelpainter.h' */