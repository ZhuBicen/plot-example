#pragma once
#include "src/global.h"
/* modified 2022-11-06T12:45:56, size 8569 */

class QCP_LIB_DECL QCPDataRange
{
public:
  QCPDataRange();
  QCPDataRange(int begin, int end);
  
  bool operator==(const QCPDataRange& other) const { return mBegin == other.mBegin && mEnd == other.mEnd; }
  bool operator!=(const QCPDataRange& other) const { return !(*this == other); }
  
  // getters:
  int begin() const { return mBegin; }
  int end() const { return mEnd; }
  int size() const { return mEnd-mBegin; }
  int length() const { return size(); }
  
  // setters:
  void setBegin(int begin) { mBegin = begin; }
  void setEnd(int end)  { mEnd = end; }
  
  // non-property methods:
  bool isValid() const { return (mEnd >= mBegin) && (mBegin >= 0); }
  bool isEmpty() const { return length() == 0; }
  QCPDataRange bounded(const QCPDataRange &other) const;
  QCPDataRange expanded(const QCPDataRange &other) const;
  QCPDataRange intersection(const QCPDataRange &other) const;
  QCPDataRange adjusted(int changeBegin, int changeEnd) const { return QCPDataRange(mBegin+changeBegin, mEnd+changeEnd); }
  bool intersects(const QCPDataRange &other) const;
  bool contains(const QCPDataRange &other) const;
  
private:
  // property members:
  int mBegin, mEnd;

};
Q_DECLARE_TYPEINFO(QCPDataRange, Q_MOVABLE_TYPE);


class QCP_LIB_DECL QCPDataSelection
{
public:
  explicit QCPDataSelection();
  explicit QCPDataSelection(const QCPDataRange &range);
  
  bool operator==(const QCPDataSelection& other) const;
  bool operator!=(const QCPDataSelection& other) const { return !(*this == other); }
  QCPDataSelection &operator+=(const QCPDataSelection& other);
  QCPDataSelection &operator+=(const QCPDataRange& other);
  QCPDataSelection &operator-=(const QCPDataSelection& other);
  QCPDataSelection &operator-=(const QCPDataRange& other);
  friend inline const QCPDataSelection operator+(const QCPDataSelection& a, const QCPDataSelection& b);
  friend inline const QCPDataSelection operator+(const QCPDataRange& a, const QCPDataSelection& b);
  friend inline const QCPDataSelection operator+(const QCPDataSelection& a, const QCPDataRange& b);
  friend inline const QCPDataSelection operator+(const QCPDataRange& a, const QCPDataRange& b);
  friend inline const QCPDataSelection operator-(const QCPDataSelection& a, const QCPDataSelection& b);
  friend inline const QCPDataSelection operator-(const QCPDataRange& a, const QCPDataSelection& b);
  friend inline const QCPDataSelection operator-(const QCPDataSelection& a, const QCPDataRange& b);
  friend inline const QCPDataSelection operator-(const QCPDataRange& a, const QCPDataRange& b);
  
  // getters:
  int dataRangeCount() const { return mDataRanges.size(); }
  int dataPointCount() const;
  QCPDataRange dataRange(int index=0) const;
  QList<QCPDataRange> dataRanges() const { return mDataRanges; }
  QCPDataRange span() const;
  
  // non-property methods:
  void addDataRange(const QCPDataRange &dataRange, bool simplify=true);
  void clear();
  bool isEmpty() const { return mDataRanges.isEmpty(); }
  void simplify();
  void enforceType(QCP::SelectionType type);
  bool contains(const QCPDataSelection &other) const;
  QCPDataSelection intersection(const QCPDataRange &other) const;
  QCPDataSelection intersection(const QCPDataSelection &other) const;
  QCPDataSelection inverse(const QCPDataRange &outerRange) const;
  
private:
  // property members:
  QList<QCPDataRange> mDataRanges;
  
  inline static bool lessThanDataRangeBegin(const QCPDataRange &a, const QCPDataRange &b) { return a.begin() < b.begin(); }
};
Q_DECLARE_METATYPE(QCPDataSelection)


/*!
  Return a \ref QCPDataSelection with the data points in \a a joined with the data points in \a b.
  The resulting data selection is already simplified (see \ref QCPDataSelection::simplify).
*/
inline const QCPDataSelection operator+(const QCPDataSelection& a, const QCPDataSelection& b)
{
  QCPDataSelection result(a);
  result += b;
  return result;
}

/*!
  Return a \ref QCPDataSelection with the data points in \a a joined with the data points in \a b.
  The resulting data selection is already simplified (see \ref QCPDataSelection::simplify).
*/
inline const QCPDataSelection operator+(const QCPDataRange& a, const QCPDataSelection& b)
{
  QCPDataSelection result(a);
  result += b;
  return result;
}

/*!
  Return a \ref QCPDataSelection with the data points in \a a joined with the data points in \a b.
  The resulting data selection is already simplified (see \ref QCPDataSelection::simplify).
*/
inline const QCPDataSelection operator+(const QCPDataSelection& a, const QCPDataRange& b)
{
  QCPDataSelection result(a);
  result += b;
  return result;
}

/*!
  Return a \ref QCPDataSelection with the data points in \a a joined with the data points in \a b.
  The resulting data selection is already simplified (see \ref QCPDataSelection::simplify).
*/
inline const QCPDataSelection operator+(const QCPDataRange& a, const QCPDataRange& b)
{
  QCPDataSelection result(a);
  result += b;
  return result;
}

/*!
  Return a \ref QCPDataSelection with the data points which are in \a a but not in \a b.
*/
inline const QCPDataSelection operator-(const QCPDataSelection& a, const QCPDataSelection& b)
{
  QCPDataSelection result(a);
  result -= b;
  return result;
}

/*!
  Return a \ref QCPDataSelection with the data points which are in \a a but not in \a b.
*/
inline const QCPDataSelection operator-(const QCPDataRange& a, const QCPDataSelection& b)
{
  QCPDataSelection result(a);
  result -= b;
  return result;
}

/*!
  Return a \ref QCPDataSelection with the data points which are in \a a but not in \a b.
*/
inline const QCPDataSelection operator-(const QCPDataSelection& a, const QCPDataRange& b)
{
  QCPDataSelection result(a);
  result -= b;
  return result;
}

/*!
  Return a \ref QCPDataSelection with the data points which are in \a a but not in \a b.
*/
inline const QCPDataSelection operator-(const QCPDataRange& a, const QCPDataRange& b)
{
  QCPDataSelection result(a);
  result -= b;
  return result;
}

/*! \relates QCPDataRange

  Prints \a dataRange in a human readable format to the qDebug output.
*/
inline QDebug operator<< (QDebug d, const QCPDataRange &dataRange)
{
  d.nospace() << "QCPDataRange(" << dataRange.begin() << ", " << dataRange.end() << ")";
  return d;
}

/*! \relates QCPDataSelection

  Prints \a selection in a human readable format to the qDebug output.
*/
inline QDebug operator<< (QDebug d, const QCPDataSelection &selection)
{
    d.nospace() << "QCPDataSelection(";
    for (int i=0; i<selection.dataRangeCount(); ++i)
    {
      if (i != 0)
        d << ", ";
      d << selection.dataRange(i);
    }
    d << ")";
    return d;
}



/* end of 'src/selection.h' */


/* including file 'src/selectionrect.h'    */