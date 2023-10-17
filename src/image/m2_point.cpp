#include <m2_point.h>

namespace m2 {


/*****************************************************************************
  Point member functions
 *****************************************************************************/

/**
 * @fn Point::Point()

    Constructs a null point, i.e. with coordinates (0, 0)

 * @sa isNull()
*/

/**
 * @fn Point::Point(int xpos, int ypos)

    Constructs a point with the given coordinates (\a xpos, \a ypos).

 * @sa setX(), setY()
*/

/**
 * @fn bool Point::isNull() const

    Returns \c true if both the x and y coordinates are set to 0,
    otherwise returns \c false.
*/

/**
 * @fn int Point::x() const

    Returns the x coordinate of this point.

 * @sa setX(), rx()
*/

/**
 * @fn int Point::y() const

    Returns the y coordinate of this point.

 * @sa setY(), ry()
*/

/**
 * @fn void Point::setX(int x)

    Sets the x coordinate of this point to the given \a x coordinate.

 * @sa x(), setY()
*/

/**
 * @fn void Point::setY(int y)

    Sets the y coordinate of this point to the given \a y coordinate.

 * @sa y(), setX()
*/

/**
 * @fn Point::transposed() const

    Returns a point with x and y coordinates exchanged:
    \code
    Point{1, 2}.transposed() // {2, 1}
    \endcode

 * @sa x(), y(), setX(), setY()
*/

/**
 * @fn int &Point::rx()

    Returns a reference to the x coordinate of this point.

    Using a reference makes it possible to directly manipulate x.

 * @sa x(), setX()
*/

/**
 * @fn int &Point::ry()

    Returns a reference to the y coordinate of this point.

    Using a reference makes it possible to directly manipulate y.

 * @sa y(), setY()
*/


/**
 * @fn Point &Point::operator+=(const Point &point)

    Adds the given \a point to this point and returns a reference to
    this point.

 * @sa operator-=()
*/

/**
 * @fn Point &Point::operator-=(const Point &point)

    Subtracts the given \a point from this point and returns a
    reference to this point.

 * @sa operator+=()
*/

/**
 * @fn Point &Point::operator*=(float factor)

    Multiplies this point's coordinates by the given \a factor, and
    returns a reference to this point.

    Note that the result is rounded to the nearest integer as points are held as
    integers. Use PointF for floating point accuracy.

 * @sa operator/=()
*/

/**
 * @fn Point &Point::operator*=(double factor)

    Multiplies this point's coordinates by the given \a factor, and
    returns a reference to this point.

    Note that the result is rounded to the nearest integer as points are held as
    integers. Use PointF for floating point accuracy.

 * @sa operator/=()
*/

/**
 * @fn Point &Point::operator*=(int factor)

    Multiplies this point's coordinates by the given \a factor, and
    returns a reference to this point.

 * @sa operator/=()
*/

/**
 * @fn static int Point::dotProduct(const Point &p1, const Point &p2)

    Returns the dot product of \a p1 and \a p2.
*/

/**
 * @fn bool Point::operator==(const Point &p1, const Point &p2)

    Returns \c true if \a p1 and \a p2 are equal; otherwise returns
    false.
*/

/**
 * @fn bool Point::operator!=(const Point &p1, const Point &p2)

    Returns \c true if \a p1 and \a p2 are not equal; otherwise returns \c false.
*/

/**
 * @fn Point Point::operator+(const Point &p1, const Point &p2)

    Returns a Point object that is the sum of the given points, \a p1
    and \a p2; each component is added separately.

 * @sa Point::operator+=()
*/

/**
 * @fn Point Point::operator-(const Point &p1, const Point &p2)

    Returns a Point object that is formed by subtracting \a p2 from
    \a p1; each component is subtracted separately.

 * @sa Point::operator-=()
*/

/**
 * @fn Point Point::operator*(const Point &point, float factor)

    Returns a copy of the given \a point multiplied by the given \a factor.

    Note that the result is rounded to the nearest integer as points
    are held as integers. Use PointF for floating point accuracy.

 * @sa Point::operator*=()
*/

/**
 * @fn Point Point::operator*(const Point &point, double factor)

    Returns a copy of the given \a point multiplied by the given \a factor.

    Note that the result is rounded to the nearest integer as points
    are held as integers. Use PointF for floating point accuracy.

 * @sa Point::operator*=()
*/

/**
 * @fn Point Point::operator*(const Point &point, int factor)

    Returns a copy of the given \a point multiplied by the given \a factor.

 * @sa Point::operator*=()
*/

/**
 * @fn Point Point::operator*(float factor, const Point &point)
    \overload

    Returns a copy of the given \a point multiplied by the given \a factor.

    Note that the result is rounded to the nearest integer as points
    are held as integers. Use PointF for floating point accuracy.

 * @sa Point::operator*=()
*/

/**
 * @fn Point Point::operator*(double factor, const Point &point)
    \overload

    Returns a copy of the given \a point multiplied by the given \a factor.

    Note that the result is rounded to the nearest integer as points
    are held as integers. Use PointF for floating point accuracy.

 * @sa Point::operator*=()
*/

/**
 * @fn Point Point::operator*(int factor, const Point &point)
    \overload

    Returns a copy of the given \a point multiplied by the given \a factor.

 * @sa Point::operator*=()
*/

/**
 * @fn Point Point::operator+(const Point &point)

    Returns \a point unmodified.
*/

/**
 * @fn Point Point::operator-(const Point &point)
    \overload

    Returns a Point object that is formed by changing the sign of
    both components of the given \a point.

    Equivalent to \c{Point(0,0) - point}.
*/

/**
 * @fn Point &Point::operator/=(double divisor)
    \overload

    Divides both x and y by the given \a divisor, and returns a reference to this
    point.

    Note that the result is rounded to the nearest integer as points are held as
    integers. Use PointF for floating point accuracy.

 * @sa operator*=()
*/

/**
 * @fn const Point Point::operator/(const Point &point, double divisor)

    Returns the Point formed by dividing both components of the given \a point
    by the given \a divisor.

    Note that the result is rounded to the nearest integer as points are held as
    integers. Use PointF for floating point accuracy.

 * @sa Point::operator/=()
*/

/**
 * @fn Point::toPointF() const

    Returns this point as a point with floating point accuracy.

 * @sa PointF::toPoint()
*/

/*****************************************************************************
  PointF member functions
 *****************************************************************************/


/**
 * @fn PointF::PointF()

    Constructs a null point, i.e. with coordinates (0.0, 0.0)

 * @sa isNull()
*/

/**
 * @fn PointF::PointF(const Point &point)

    Constructs a copy of the given \a point.

 * @sa toPoint(), Point::toPointF()
*/

/**
 * @fn PointF::PointF(double xpos, double ypos)

    Constructs a point with the given coordinates (\a xpos, \a ypos).

 * @sa setX(), setY()
*/

/**
 * @fn bool PointF::isNull() const

    Returns \c true if both the x and y coordinates are set to 0.0 (ignoring
    the sign); otherwise returns \c false.
*/


/**
 * @fn double PointF::manhattanLength() const

    Returns the sum of the absolute values of x() and y(),
    traditionally known as the "Manhattan length" of the vector from
    the origin to the point.

 * @sa Point::manhattanLength()
*/

/**
 * @fn double PointF::x() const

    Returns the x coordinate of this point.

 * @sa setX(), rx()
*/

/**
 * @fn double PointF::y() const

    Returns the y coordinate of this point.

 * @sa setY(), ry()
*/

/**
 * @fn void PointF::setX(double x)

    Sets the x coordinate of this point to the given finite \a x coordinate.

 * @sa x(), setY()
*/

/**
 * @fn void PointF::setY(double y)

    Sets the y coordinate of this point to the given finite \a y coordinate.

 * @sa y(), setX()
*/

/**
 * @fn PointF::transposed() const

    Returns a point with x and y coordinates exchanged:
    \code
    PointF{1.0, 2.0}.transposed() // {2.0, 1.0}
    \endcode

 * @sa x(), y(), setX(), setY()
*/

/**
 * @fn double& PointF::rx()

    Returns a reference to the x coordinate of this point.

    Using a reference makes it possible to directly manipulate x.

 * @sa x(), setX()
*/

/**
 * @fn double& PointF::ry()

    Returns a reference to the y coordinate of this point.

    Using a reference makes it possible to directly manipulate y.

 * @sa y(), setY()
*/

/**
 * @fn PointF& PointF::operator+=(const PointF &point)

    Adds the given \a point to this point and returns a reference to
    this point.

 * @sa operator-=()
*/

/**
 * @fn PointF& PointF::operator-=(const PointF &point)

    Subtracts the given \a point from this point and returns a reference
    to this point.

 * @sa operator+=()
*/

/**
 * @fn PointF& PointF::operator*=(double factor)

    Multiplies this point's coordinates by the given finite \a factor, and
    returns a reference to this point.

 * @sa operator/=()
*/

/**
 * @fn PointF& PointF::operator/=(double divisor)

    Divides both x and y by the given \a divisor, and returns a reference
    to this point. For example:

    The \a divisor must not be zero or NaN.

 * @sa operator*=()
*/

/**
 * @fn PointF PointF::operator+(const PointF &p1, const PointF &p2)

    Returns a PointF object that is the sum of the given points, \a p1
    and \a p2; each component is added separately.

 * @sa PointF::operator+=()
*/

/**
 * @fn PointF PointF::operator-(const PointF &p1, const PointF &p2)

    Returns a PointF object that is formed by subtracting \a p2 from \a p1;
    each component is subtracted separately.

 * @sa PointF::operator-=()
*/

/**
 * @fn PointF PointF::operator*(const PointF &point, double factor)

    Returns a copy of the given \a point, multiplied by the given finite \a factor.

 * @sa PointF::operator*=()
*/

/**
 * @fn PointF PointF::operator*(double factor, const PointF &point)

    \overload

    Returns a copy of the given \a point, multiplied by the given finite \a factor.
*/

/**
 * @fn PointF PointF::operator+(const PointF &point)

    Returns \a point unmodified.
*/

/**
 * @fn PointF PointF::operator-(const PointF &point)
    \overload

    Returns a PointF object that is formed by changing the sign of
    each component of the given \a point.

    Equivalent to \c {PointF(0,0) - point}.
*/

/**
 * @fn PointF PointF::operator/(const PointF &point, double divisor)

    Returns the PointF object formed by dividing each component of
    the given \a point by the given \a divisor.

    The \a divisor must not be zero or NaN.

 * @sa PointF::operator/=()
*/

/**
 * @fn Point PointF::toPoint() const

    Rounds the coordinates of this point to the nearest integer, and
    returns a Point object with the rounded coordinates.

 * @sa PointF(), Point::toPointF()
*/

/**
 * @fn static double PointF::dotProduct(const PointF &p1, const PointF &p2)

    Returns the dot product of \a p1 and \a p2.
*/

/**
 * @fn bool PointF::operator==(const PointF &p1, const PointF &p2)

    Returns \c true if \a p1 is approximately equal to \a p2; otherwise
    returns \c false.

    \warning This function does not check for strict equality; instead,
    it uses a fuzzy comparison to compare the points' coordinates.

 * @sa qFuzzyCompare
*/

/**
 * @fn bool PointF::operator!=(const PointF &p1, const PointF &p2);

    Returns \c true if \a p1 is sufficiently different from \a p2;
    otherwise returns \c false.

 * @sa qFuzzyCompare
*/

}// namespace m2
