/****************************************************************************
**
** Copyright (C) 2023 MerlotRain
** Github:https://github.com/MerlotRain
**
** M2 is a cross platform C++basic library that encapsulates commonly 
** used C++ classes and functional modules, shields system functions from 
** the outside, and provides a unified interface.
**
** $M2_BEGIN_LICENSE:MIT$
** Permission is hereby granted, free of charge, to any person obtaining a 
** copy of this software and associated documentation files (the “Software”), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
** DEALINGS IN THE SOFTWARE.
** 
** $M2_END_LICENSE$
**
****************************************************************************/

#ifndef M2_POLYGON_H_
#define M2_POLYGON_H_

#include <list>
#include <m2_point.h>

namespace m2 {

class Rect;
class RectF;
class PolygonF;

enum FillRule
{
    OddEvenFill,
    WindingFill
};

class Polygon : public std::vector<Point>
{
public:
    Polygon() = default;
    Polygon(const std::vector<Point> &v);
    Polygon(std::vector<Point> &&v) noexcept;
    Polygon(const Rect &r, bool closed = false);
    Polygon(int nPoints, const int *points);
    void swap(Polygon &other) noexcept;

    void translate(int dx, int dy);
    void translate(const Point &offset);

    [[nodiscard]] Polygon translated(int dx, int dy) const;
    [[nodiscard]] inline Polygon translated(const Point &offset) const;

    Rect boundingRect() const;

    void point(int i, int *x, int *y) const;
    Point point(int i) const;
    void setPoint(int index, int x, int y);
    inline void setPoint(int index, const Point &p);
    void setPoints(int nPoints, const int *points);
    void setPoints(int nPoints, int firstx, int firsty, ...);
    void putPoints(int index, int nPoints, const int *points);
    void putPoints(int index, int nPoints, int firstx, int firsty, ...);
    void putPoints(int index, int nPoints, const Polygon &from,
                   int fromIndex = 0);

    bool containsPoint(const Point &pt, FillRule fillRule) const;

    [[nodiscard]] Polygon united(const Polygon &r) const;
    [[nodiscard]] Polygon intersected(const Polygon &r) const;
    [[nodiscard]] Polygon subtracted(const Polygon &r) const;

    bool intersects(const Polygon &r) const;

    [[nodiscard]] inline PolygonF toPolygonF() const;
};

class PolygonF : public std::vector<PointF>
{
public:
    PolygonF() = default;
    PolygonF(const std::vector<PointF> &v);
    PolygonF(std::vector<PointF> &&v) noexcept;
    PolygonF(const RectF &r);
    PolygonF(const Polygon &a);
    inline void swap(PolygonF &other);

    inline void translate(double dx, double dy);
    void translate(const PointF &offset);

    inline PolygonF translated(double dx, double dy) const;
    [[nodiscard]] PolygonF translated(const PointF &offset) const;

    Polygon toPolygon() const;

    bool isClosed() const;
    RectF boundingRect() const;
    bool containsPoint(const PointF &pt, FillRule fillRule) const;

    [[nodiscard]] PolygonF united(const PolygonF &r) const;
    [[nodiscard]] PolygonF intersected(const PolygonF &r) const;
    [[nodiscard]] PolygonF subtracted(const PolygonF &r) const;

    bool intersects(const PolygonF &r) const;
};


inline void Polygon::setPoint(int index, const Point &pt)
{
    setPoint(index, pt.x(), pt.y());
}

inline Point Polygon::point(int index) const { return at(index); }

inline void Polygon::translate(const Point &offset)
{
    translate(offset.x(), offset.y());
}

inline Polygon Polygon::translated(const Point &offset) const
{
    return translated(offset.x(), offset.y());
}

inline void PolygonF::translate(double dx, double dy)
{
    translate(PointF(dx, dy));
}

inline PolygonF PolygonF::translated(double dx, double dy) const
{
    return translated(PointF(dx, dy));
}

}// namespace m2

#endif//M2_POLYGON_H_