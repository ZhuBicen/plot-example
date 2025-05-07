/* modified 2022-11-06T12:45:56, size 4988 */

class QCP_LIB_DECL QCPVector2D
{
public:
  QCPVector2D();
  QCPVector2D(double x, double y);
  QCPVector2D(const QPoint &point);
  QCPVector2D(const QPointF &point);
  
  // getters:
  double x() const { return mX; }
  double y() const { return mY; }
  double &rx() { return mX; }
  double &ry() { return mY; }
  
  // setters:
  void setX(double x) { mX = x; }
  void setY(double y) { mY = y; }
  
  // non-virtual methods:
  double length() const { return qSqrt(mX*mX+mY*mY); }
  double lengthSquared() const { return mX*mX+mY*mY; }
  double angle() const { return qAtan2(mY, mX); }
  QPoint toPoint() const { return QPoint(int(mX), int(mY)); }
  QPointF toPointF() const { return QPointF(mX, mY); }
  
  bool isNull() const { return qIsNull(mX) && qIsNull(mY); }
  void normalize();
  QCPVector2D normalized() const;
  QCPVector2D perpendicular() const { return QCPVector2D(-mY, mX); }
  double dot(const QCPVector2D &vec) const { return mX*vec.mX+mY*vec.mY; }
  double distanceSquaredToLine(const QCPVector2D &start, const QCPVector2D &end) const;
  double distanceSquaredToLine(const QLineF &line) const;
  double distanceToStraightLine(const QCPVector2D &base, const QCPVector2D &direction) const;
  
  QCPVector2D &operator*=(double factor);
  QCPVector2D &operator/=(double divisor);
  QCPVector2D &operator+=(const QCPVector2D &vector);
  QCPVector2D &operator-=(const QCPVector2D &vector);
  
private:
  // property members:
  double mX, mY;
  
  friend inline const QCPVector2D operator*(double factor, const QCPVector2D &vec);
  friend inline const QCPVector2D operator*(const QCPVector2D &vec, double factor);
  friend inline const QCPVector2D operator/(const QCPVector2D &vec, double divisor);
  friend inline const QCPVector2D operator+(const QCPVector2D &vec1, const QCPVector2D &vec2);
  friend inline const QCPVector2D operator-(const QCPVector2D &vec1, const QCPVector2D &vec2);
  friend inline const QCPVector2D operator-(const QCPVector2D &vec);
};
Q_DECLARE_TYPEINFO(QCPVector2D, Q_MOVABLE_TYPE);

inline const QCPVector2D operator*(double factor, const QCPVector2D &vec) { return QCPVector2D(vec.mX*factor, vec.mY*factor); }
inline const QCPVector2D operator*(const QCPVector2D &vec, double factor) { return QCPVector2D(vec.mX*factor, vec.mY*factor); }
inline const QCPVector2D operator/(const QCPVector2D &vec, double divisor) { return QCPVector2D(vec.mX/divisor, vec.mY/divisor); }
inline const QCPVector2D operator+(const QCPVector2D &vec1, const QCPVector2D &vec2) { return QCPVector2D(vec1.mX+vec2.mX, vec1.mY+vec2.mY); }
inline const QCPVector2D operator-(const QCPVector2D &vec1, const QCPVector2D &vec2) { return QCPVector2D(vec1.mX-vec2.mX, vec1.mY-vec2.mY); }
inline const QCPVector2D operator-(const QCPVector2D &vec) { return QCPVector2D(-vec.mX, -vec.mY); }

/*! \relates QCPVector2D

  Prints \a vec in a human readable format to the qDebug output.
*/
inline QDebug operator<< (QDebug d, const QCPVector2D &vec)
{
    d.nospace() << "QCPVector2D(" << vec.x() << ", " << vec.y() << ")";
    return d.space();
}

/* end of 'src/vector2d.h' */


/* including file 'src/painter.h'          */