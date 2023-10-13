#include <m2_polygon.h>
#include <m2_rect.h>

namespace m2 {

/****************************************************************************
Polygon functions
****************************************************************************/

/**
 * @brief Construct a new Polygon:: Polygon object
 * 
 */
Polygon::Polygon() {}

/**
 * @brief Construct a new Polygon:: Polygon object
 * 
 * @param v 
 */
Polygon::Polygon(const std::vector<Point> &v) {}

/**
 * @brief Construct a new Polygon:: Polygon object
 * 
 * @param v 
 */
Polygon::Polygon(std::vector<Point> &&v) noexcept {}

/**
 * @brief Construct a new Polygon:: Polygon object
 * 
 * @param r 
 * @param closed 
 */
Polygon::Polygon(const Rect &r, bool closed) {}

/**
 * @brief Construct a new Polygon:: Polygon object
 * 
 * @param nPoints 
 * @param points 
 */
Polygon::Polygon(int nPoints, const int *points) {}

/**
 * @brief 
 * 
 * @param other 
 */
void Polygon::swap(Polygon &other) noexcept {}

/**
 * @brief 
 * 
 * @param dx 
 * @param dy 
 */
void Polygon::translate(int dx, int dy) {}

/**
 * @brief 
 * 
 * @param offset 
 */
void Polygon::translate(const Point &offset) {}

/**
 * @brief 
 * 
 * @param dx 
 * @param dy 
 * @return Polygon 
 */
Polygon Polygon::translated(int dx, int dy) const { Polygon(); }

/**
 * @brief 
 * 
 * @param offset 
 * @return Polygon 
 */
Polygon Polygon::translated(const Point &offset) const { return Polygon(); }

/**
 * @brief 
 * 
 * @return Rect 
 */
Rect Polygon::boundingRect() const { return Rect(); }

/**
 * @brief 
 * 
 * @param i 
 * @param x 
 * @param y 
 */
void Polygon::point(int i, int *x, int *y) const {}

/**
 * @brief 
 * 
 * @param i 
 * @return Point 
 */
Point Polygon::point(int i) const { return Point(); }

/**
 * @brief 
 * 
 * @param index 
 * @param x 
 * @param y 
 */
void Polygon::setPoint(int index, int x, int y) {}

/**
 * @brief 
 * 
 * @param index 
 * @param p 
 */
void Polygon::setPoint(int index, const Point &p) {}

/**
 * @brief 
 * 
 * @param nPoints 
 * @param points 
 */
void Polygon::setPoints(int nPoints, const int *points) {}

/**
 * @brief 
 * 
 * @param nPoints 
 * @param firstx 
 * @param firsty 
 * @param ... 
 */
void Polygon::setPoints(int nPoints, int firstx, int firsty, ...) {}

/**
 * @brief 
 * 
 * @param index 
 * @param nPoints 
 * @param points 
 */
void Polygon::putPoints(int index, int nPoints, const int *points) {}

/**
 * @brief 
 * 
 * @param index 
 * @param nPoints 
 * @param firstx 
 * @param firsty 
 * @param ... 
 */
void Polygon::putPoints(int index, int nPoints, int firstx, int firsty, ...) {}

/**
 * @brief 
 * 
 * @param index 
 * @param nPoints 
 * @param from 
 * @param fromIndex 
 */
void Polygon::putPoints(int index, int nPoints, const Polygon &from,
                        int fromIndex = 0)
{
}

/**
 * @brief 
 * 
 * @param pt 
 * @param fillRule 
 * @return true 
 * @return false 
 */
bool Polygon::containsPoint(const Point &pt, FillRule fillRule) const
{
    return false;
}

/**
 * @brief 
 * 
 * @param r 
 * @return Polygon 
 */
Polygon Polygon::united(const Polygon &r) const { return Polygon(); }

/**
 * @brief 
 * 
 * @param r 
 * @return Polygon 
 */
Polygon Polygon::intersected(const Polygon &r) const { return Polygon(); }

/**
 * @brief 
 * 
 * @param r 
 * @return Polygon 
 */
Polygon Polygon::subtracted(const Polygon &r) const { return Polygon(); }

/**
 * @brief 
 * 
 * @param r 
 * @return true 
 * @return false 
 */
bool Polygon::intersects(const Polygon &r) const { return false; }

/**
 * @brief 
 * 
 * @return PolygonF 
 */
PolygonF Polygon::toPolygonF() const { return PolygonF(); }

/****************************************************************************
PolygonF functions
****************************************************************************/

/**
 * @brief Construct a new Polygon F:: Polygon F object
 * 
 * @param v 
 */
PolygonF::PolygonF(const std::vector<PointF> &v) {}

/**
 * @brief Construct a new Polygon F:: Polygon F object
 * 
 * @param v 
 */
PolygonF::PolygonF(std::vector<PointF> &&v) noexcept {}

/**
 * @brief Construct a new Polygon F:: Polygon F object
 * 
 * @param r 
 */
PolygonF::PolygonF(const RectF &r) {}

/**
 * @brief Construct a new Polygon F:: Polygon F object
 * 
 * @param a 
 */
PolygonF::PolygonF(const Polygon &a) {}

/**
 * @brief 
 * 
 * @param other 
 */
void PolygonF::swap(PolygonF &other) {}

/**
 * @brief 
 * 
 * @param dx 
 * @param dy 
 */
void PolygonF::translate(double dx, double dy) {}

/**
 * @brief 
 * 
 * @param offset 
 */
void PolygonF::translate(const PointF &offset) {}

/**
 * @brief 
 * 
 * @param dx 
 * @param dy 
 * @return PolygonF 
 */
PolygonF PolygonF::translated(double dx, double dy) const { return PolygonF(); }

/**
 * @brief 
 * 
 * @param offset 
 * @return PolygonF 
 */
PolygonF PolygonF::translated(const PointF &offset) const {}

/**
 * @brief 
 * 
 * @return Polygon 
 */
Polygon PolygonF::toPolygon() const {}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool PolygonF::isClosed() const { return false; }

/**
 * @brief 
 * 
 * @return RectF 
 */
RectF PolygonF::boundingRect() const { return RectF(); }

/**
 * @brief 
 * 
 * @param pt 
 * @param fillRule 
 * @return true 
 * @return false 
 */
bool PolygonF::containsPoint(const PointF &pt, FillRule fillRule) const
{
    return false;
}

/**
 * @brief 
 * 
 * @param r 
 * @return PolygonF 
 */
PolygonF PolygonF::united(const PolygonF &r) const { return PolygonF(); }

/**
 * @brief 
 * 
 * @param r 
 * @return PolygonF 
 */
PolygonF PolygonF::intersected(const PolygonF &r) const { return PolygonF(); }

/**
 * @brief 
 * 
 * @param r 
 * @return PolygonF 
 */
PolygonF PolygonF::subtracted(const PolygonF &r) const { return PolygonF(); }

/**
 * @brief 
 * 
 * @param r 
 * @return true 
 * @return false 
 */
bool PolygonF::intersects(const PolygonF &r) const { return false; }

}// namespace m2
