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

#ifndef M2_LINE_H_
#define M2_LINE_H_

#include <m2_point.h>

namespace m2 {

class LineF;
class Line
{
public:
    constexpr inline Line();
    constexpr inline Line(const Point &pt1, const Point &pt2);
    constexpr inline Line(int x1, int y1, int x2, int y2);

    constexpr inline bool isNull() const;

    constexpr inline Point p1() const;
    constexpr inline Point p2() const;

    constexpr inline int x1() const;
    constexpr inline int y1() const;

    constexpr inline int x2() const;
    constexpr inline int y2() const;

    constexpr inline int dx() const;
    constexpr inline int dy() const;

    inline void translate(const Point &p);
    inline void translate(int dx, int dy);

    [[nodiscard]] constexpr inline Line translated(const Point &p) const;
    [[nodiscard]] constexpr inline Line translated(int dx, int dy) const;

    [[nodiscard]] constexpr inline Point center() const;

    inline void setP1(const Point &p1);
    inline void setP2(const Point &p2);
    inline void setPoints(const Point &p1, const Point &p2);
    inline void setLine(int x1, int y1, int x2, int y2);

    constexpr inline bool operator==(const Line &d) const noexcept;
    constexpr inline bool operator!=(const Line &d) const noexcept { return !(*this == d); }

    [[nodiscard]] constexpr inline LineF toLineF() const noexcept;

private:
    Point pt1, pt2;
};

class LineF
{
public:
    enum IntersectionType
    {
        NoIntersection,
        BoundedIntersection,
        UnboundedIntersection
    };
    using IntersectType = IntersectionType;

    constexpr inline LineF();
    constexpr inline LineF(const PointF &pt1, const PointF &pt2);
    constexpr inline LineF(double x1, double y1, double x2, double y2);
    constexpr inline LineF(const Line &line) : pt1(line.p1()), pt2(line.p2()) {}

    [[nodiscard]] static LineF fromPolar(double length, double angle);

    constexpr bool isNull() const;

    constexpr inline PointF p1() const;
    constexpr inline PointF p2() const;

    constexpr inline double x1() const;
    constexpr inline double y1() const;

    constexpr inline double x2() const;
    constexpr inline double y2() const;

    constexpr inline double dx() const;
    constexpr inline double dy() const;

    double length() const;
    void setLength(double len);

    double angle() const;
    void setAngle(double angle);

    double angleTo(const LineF &l) const;

    [[nodiscard]] LineF unitVector() const;
    [[nodiscard]] constexpr inline LineF normalVector() const;

    IntersectionType intersects(const LineF &l, PointF *intersectionPoint = nullptr) const;

    constexpr inline PointF pointAt(double t) const;
    inline void translate(const PointF &p);
    inline void translate(double dx, double dy);

    [[nodiscard]] constexpr inline LineF translated(const PointF &p) const;
    [[nodiscard]] constexpr inline LineF translated(double dx, double dy) const;

    [[nodiscard]] constexpr inline PointF center() const;

    inline void setP1(const PointF &p1);
    inline void setP2(const PointF &p2);
    inline void setPoints(const PointF &p1, const PointF &p2);
    inline void setLine(double x1, double y1, double x2, double y2);

    constexpr inline bool operator==(const LineF &d) const;
    constexpr inline bool operator!=(const LineF &d) const { return !(*this == d); }

    constexpr Line toLine() const;

private:
    PointF pt1, pt2;
};

/*******************************************************************************
 * class Line inline members
 *******************************************************************************/

constexpr inline Line::Line() {}

constexpr inline Line::Line(const Point &pt1_, const Point &pt2_) : pt1(pt1_), pt2(pt2_) {}

constexpr inline Line::Line(int x1pos, int y1pos, int x2pos, int y2pos) : pt1(Point(x1pos, y1pos)), pt2(Point(x2pos, y2pos)) {}

constexpr inline bool Line::isNull() const
{
    return pt1 == pt2;
}

constexpr inline int Line::x1() const
{
    return pt1.x();
}

constexpr inline int Line::y1() const
{
    return pt1.y();
}

constexpr inline int Line::x2() const
{
    return pt2.x();
}

constexpr inline int Line::y2() const
{
    return pt2.y();
}

constexpr inline Point Line::p1() const
{
    return pt1;
}

constexpr inline Point Line::p2() const
{
    return pt2;
}

constexpr inline int Line::dx() const
{
    return pt2.x() - pt1.x();
}

constexpr inline int Line::dy() const
{
    return pt2.y() - pt1.y();
}

inline void Line::translate(const Point &point)
{
    pt1 += point;
    pt2 += point;
}

inline void Line::translate(int adx, int ady)
{
    this->translate(Point(adx, ady));
}

constexpr inline Line Line::translated(const Point &p) const
{
    return Line(pt1 + p, pt2 + p);
}

constexpr inline Line Line::translated(int adx, int ady) const
{
    return translated(Point(adx, ady));
}

constexpr inline Point Line::center() const
{
    return Point(int((int64_t(pt1.x()) + pt2.x()) / 2), int((int64_t(pt1.y()) + pt2.y()) / 2));
}

inline void Line::setP1(const Point &aP1)
{
    pt1 = aP1;
}

inline void Line::setP2(const Point &aP2)
{
    pt2 = aP2;
}

inline void Line::setPoints(const Point &aP1, const Point &aP2)
{
    pt1 = aP1;
    pt2 = aP2;
}

inline void Line::setLine(int aX1, int aY1, int aX2, int aY2)
{
    pt1 = Point(aX1, aY1);
    pt2 = Point(aX2, aY2);
}

constexpr inline bool Line::operator==(const Line &d) const noexcept
{
    return pt1 == d.pt1 && pt2 == d.pt2;
}


/*******************************************************************************
 * class LineF inline members
 *******************************************************************************/

constexpr inline LineF::LineF()
{
}

constexpr inline LineF::LineF(const PointF &apt1, const PointF &apt2)
    : pt1(apt1), pt2(apt2)
{
}

constexpr inline LineF::LineF(double x1pos, double y1pos, double x2pos, double y2pos)
    : pt1(x1pos, y1pos), pt2(x2pos, y2pos)
{
}

constexpr inline double LineF::x1() const
{
    return pt1.x();
}

constexpr inline double LineF::y1() const
{
    return pt1.y();
}

constexpr inline double LineF::x2() const
{
    return pt2.x();
}

constexpr inline double LineF::y2() const
{
    return pt2.y();
}

constexpr inline bool LineF::isNull() const
{
    return qFuzzyCompare(pt1.x(), pt2.x()) && qFuzzyCompare(pt1.y(), pt2.y());
}

constexpr inline PointF LineF::p1() const
{
    return pt1;
}

constexpr inline PointF LineF::p2() const
{
    return pt2;
}

constexpr inline double LineF::dx() const
{
    return pt2.x() - pt1.x();
}

constexpr inline double LineF::dy() const
{
    return pt2.y() - pt1.y();
}

constexpr inline LineF LineF::normalVector() const
{
    return LineF(p1(), p1() + PointF(dy(), -dx()));
}

inline void LineF::translate(const PointF &point)
{
    pt1 += point;
    pt2 += point;
}

inline void LineF::translate(double adx, double ady)
{
    this->translate(PointF(adx, ady));
}

constexpr inline LineF LineF::translated(const PointF &p) const
{
    return LineF(pt1 + p, pt2 + p);
}

constexpr inline LineF LineF::translated(double adx, double ady) const
{
    return translated(PointF(adx, ady));
}

constexpr inline PointF LineF::center() const
{
    return PointF(0.5 * pt1.x() + 0.5 * pt2.x(), 0.5 * pt1.y() + 0.5 * pt2.y());
}

inline void LineF::setLength(double len)
{
    assert(std::isfinite(len));
    const double oldLength = length();
    assert(std::isfinite(oldLength));
    if (oldLength > 0)
        pt2 = PointF(pt1.x() + len * (dx() / oldLength), pt1.y() + len * (dy() / oldLength));
}

constexpr inline PointF LineF::pointAt(double t) const
{
    return PointF(pt1.x() + (pt2.x() - pt1.x()) * t, pt1.y() + (pt2.y() - pt1.y()) * t);
}

constexpr inline LineF Line::toLineF() const noexcept { return *this; }

constexpr inline Line LineF::toLine() const
{
    return Line(pt1.toPoint(), pt2.toPoint());
}

inline void LineF::setP1(const PointF &aP1)
{
    pt1 = aP1;
}

inline void LineF::setP2(const PointF &aP2)
{
    pt2 = aP2;
}

inline void LineF::setPoints(const PointF &aP1, const PointF &aP2)
{
    pt1 = aP1;
    pt2 = aP2;
}

inline void LineF::setLine(double aX1, double aY1, double aX2, double aY2)
{
    pt1 = PointF(aX1, aY1);
    pt2 = PointF(aX2, aY2);
}

constexpr inline bool LineF::operator==(const LineF &d) const
{
    return pt1 == d.pt1 && pt2 == d.pt2;
}

}// namespace m2

#endif//M2_LINE_H_