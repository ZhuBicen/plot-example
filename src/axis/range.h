/* modified 2022-11-06T12:45:56, size 5280 */

class QCP_LIB_DECL QCPRange
{
public:
  double lower, upper;
  
  QCPRange();
  QCPRange(double lower, double upper);
  
  bool operator==(const QCPRange& other) const { return lower == other.lower && upper == other.upper; }
  bool operator!=(const QCPRange& other) const { return !(*this == other); }
  
  QCPRange &operator+=(const double& value) { lower+=value; upper+=value; return *this; }
  QCPRange &operator-=(const double& value) { lower-=value; upper-=value; return *this; }
  QCPRange &operator*=(const double& value) { lower*=value; upper*=value; return *this; }
  QCPRange &operator/=(const double& value) { lower/=value; upper/=value; return *this; }
  friend inline const QCPRange operator+(const QCPRange&, double);
  friend inline const QCPRange operator+(double, const QCPRange&);
  friend inline const QCPRange operator-(const QCPRange& range, double value);
  friend inline const QCPRange operator*(const QCPRange& range, double value);
  friend inline const QCPRange operator*(double value, const QCPRange& range);
  friend inline const QCPRange operator/(const QCPRange& range, double value);
  
  double size() const { return upper-lower; }
  double center() const { return (upper+lower)*0.5; }
  void normalize() { if (lower > upper) qSwap(lower, upper); }
  void expand(const QCPRange &otherRange);
  void expand(double includeCoord);
  QCPRange expanded(const QCPRange &otherRange) const;
  QCPRange expanded(double includeCoord) const;
  QCPRange bounded(double lowerBound, double upperBound) const;
  QCPRange sanitizedForLogScale() const;
  QCPRange sanitizedForLinScale() const;
  bool contains(double value) const { return value >= lower && value <= upper; }
  
  static bool validRange(double lower, double upper);
  static bool validRange(const QCPRange &range);
  static const double minRange;
  static const double maxRange;
  
};
Q_DECLARE_TYPEINFO(QCPRange, Q_MOVABLE_TYPE);

/*! \relates QCPRange

  Prints \a range in a human readable format to the qDebug output.
*/
inline QDebug operator<< (QDebug d, const QCPRange &range)
{
    d.nospace() << "QCPRange(" << range.lower << ", " << range.upper << ")";
    return d.space();
}

/*!
  Adds \a value to both boundaries of the range.
*/
inline const QCPRange operator+(const QCPRange& range, double value)
{
  QCPRange result(range);
  result += value;
  return result;
}

/*!
  Adds \a value to both boundaries of the range.
*/
inline const QCPRange operator+(double value, const QCPRange& range)
{
  QCPRange result(range);
  result += value;
  return result;
}

/*!
  Subtracts \a value from both boundaries of the range.
*/
inline const QCPRange operator-(const QCPRange& range, double value)
{
  QCPRange result(range);
  result -= value;
  return result;
}

/*!
  Multiplies both boundaries of the range by \a value.
*/
inline const QCPRange operator*(const QCPRange& range, double value)
{
  QCPRange result(range);
  result *= value;
  return result;
}

/*!
  Multiplies both boundaries of the range by \a value.
*/
inline const QCPRange operator*(double value, const QCPRange& range)
{
  QCPRange result(range);
  result *= value;
  return result;
}

/*!
  Divides both boundaries of the range by \a value.
*/
inline const QCPRange operator/(const QCPRange& range, double value)
{
  QCPRange result(range);
  result /= value;
  return result;
}

/* end of 'src/axis/range.h' */


/* including file 'src/selection.h'        */