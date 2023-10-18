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
Polygon::Polygon(const std::vector<Point> &v) : std::vector<Point>(v) {}

/**
 * @brief Construct a new Polygon:: Polygon object
 * 
 * @param v 
 */
Polygon::Polygon(std::vector<Point> &&v) noexcept
    : std::vector<Point>(std::move(v))
{
}

/**
 * @brief Construct a new Polygon:: Polygon object
 * 
 * @param r 
 * @param closed 
 */
Polygon::Polygon(const Rect &r, bool closed)
{
    reserve(closed ? 5 : 4);
    std::vector<int> x;
    (*this).push_back(Point(r.x(), r.y()));
    (*this).push_back(Point(r.x() + r.width(), r.y()));
    (*this).push_back(Point(r.x() + r.width(), r.y() + r.height()));
    (*this).push_back(Point(r.x(), r.y() + r.height()));
    if (closed) (*this).push_back(Point(r.left(), r.top()));
}

/**
 * @brief Construct a new Polygon:: Polygon object
 * 
 * @param nPoints 
 * @param points 
 */
Polygon::Polygon(int nPoints, const int *points) { setPoints(nPoints, points); }

/**
 * @brief 
 * 
 * @param other 
 */
void Polygon::swap(Polygon &other) noexcept { std::vector<Point>::swap(other); }

/**
 * @brief 
 * 
 * @param dx 
 * @param dy 
 */
void Polygon::translate(int dx, int dy)
{
    if (dx == 0 && dy == 0) return;

    Point *p = data();
    int i = size();
    Point pt(dx, dy);
    while (i--)
    {
        *p += pt;
        ++p;
    }
}

/**
 * @brief 
 * 
 * @param offset 
 */
void Polygon::translate(const Point &offset)
{
    translate(offset.x(), offset.y());
}

/**
 * @brief 
 * 
 * @param dx 
 * @param dy 
 * @return Polygon 
 */
Polygon Polygon::translated(int dx, int dy) const
{
    Polygon copy(*this);
    copy.translate(dx, dy);
    return copy;
}

/**
 * @brief 
 * 
 * @param offset 
 * @return Polygon 
 */
Polygon Polygon::translated(const Point &offset) const
{
    return translated(offset.x(), offset.y());
}

/**
 * @brief 
 * 
 * @return Rect 
 */
Rect Polygon::boundingRect() const
{
    const Point *pd = data();
    const Point *pe = pd + size();
    if (pd == pe) return Rect(0, 0, 0, 0);
    int minx, maxx, miny, maxy;
    minx = maxx = pd->x();
    miny = maxy = pd->y();
    ++pd;
    for (; pd != pe; ++pd)
    {
        if (pd->x() < minx) minx = pd->x();
        else if (pd->x() > maxx)
            maxx = pd->x();
        if (pd->y() < miny) miny = pd->y();
        else if (pd->y() > maxy)
            maxy = pd->y();
    }
    return Rect(Point(minx, miny), Point(maxx, maxy));
}

/**
 * @brief 
 * 
 * @param index 
 * @param x 
 * @param y 
 */
void Polygon::point(int index, int *x, int *y) const
{
    Point p = at(index);
    if (x) *x = (int) p.x();
    if (y) *y = (int) p.y();
}

/**
 * @brief 
 * 
 * @param i 
 * @return Point 
 */
Point Polygon::point(int i) const { return at(i); }

/**
 * @brief 
 * 
 * @param index 
 * @param x 
 * @param y 
 */
void Polygon::setPoint(int index, int x, int y)
{
    (*this)[index] = Point(x, y);
}

/**
 * @brief 
 * 
 * @param index 
 * @param p 
 */
void Polygon::setPoint(int index, const Point &p)
{
    setPoint(index, p.x(), p.y());
}

/**
 * @brief 
 * 
 * @param nPoints 
 * @param points 
 */
void Polygon::setPoints(int nPoints, const int *points)
{
    resize(nPoints);
    int i = 0;
    while (nPoints--)
    {
        setPoint(i++, *points, *(points + 1));
        points += 2;
    }
}

/**
 * @brief 
 * 
 * @param nPoints 
 * @param firstx 
 * @param firsty 
 * @param ... 
 */
void Polygon::setPoints(int nPoints, int firstx, int firsty, ...)
{
    va_list ap;
    resize(nPoints);
    setPoint(0, firstx, firsty);
    int i = 0, x, y;
    va_start(ap, firsty);
    while (--nPoints)
    {
        x = va_arg(ap, int);
        y = va_arg(ap, int);
        setPoint(++i, x, y);
    }
    va_end(ap);
}

/**
 * @brief 
 * 
 * @param index 
 * @param nPoints 
 * @param points 
 */
void Polygon::putPoints(int index, int nPoints, const int *points)
{
    if (index + nPoints > size()) resize(index + nPoints);
    int i = index;
    while (nPoints--)
    {
        setPoint(i++, *points, *(points + 1));
        points += 2;
    }
}

/**
 * @brief 
 * 
 * @param index 
 * @param nPoints 
 * @param firstx 
 * @param firsty 
 * @param ... 
 */
void Polygon::putPoints(int index, int nPoints, int firstx, int firsty, ...)
{
    va_list ap;
    if (index + nPoints > size()) resize(index + nPoints);
    if (nPoints <= 0) return;
    setPoint(index, firstx, firsty);
    int i = index, x, y;
    va_start(ap, firsty);
    while (--nPoints)
    {
        x = va_arg(ap, int);
        y = va_arg(ap, int);
        setPoint(++i, x, y);
    }
    va_end(ap);
}

/**
 * @brief 
 * 
 * @param index 
 * @param nPoints 
 * @param from 
 * @param fromIndex 
 */
void Polygon::putPoints(int index, int nPoints, const Polygon &from,
                        int fromIndex)
{
    if (index + nPoints > size()) resize(index + nPoints);
    if (nPoints <= 0) return;
    int n = 0;
    while (n < nPoints)
    {
        setPoint(index + n, from[fromIndex + n]);
        ++n;
    }
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
PolygonF Polygon::toPolygonF() const { return PolygonF(*this); }

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
