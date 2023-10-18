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
    Line() noexcept;
    Line(const Point &pt1, const Point &pt2) noexcept;
    Line(int x1, int y1, int x2, int y2) noexcept;

    bool isNull() const noexcept;

    Point p1() const noexcept;
    Point p2() const noexcept;

    int x1() const noexcept;
    int y1() const noexcept;

    int x2() const noexcept;
    int y2() const noexcept;

    int dx() const noexcept;
    int dy() const noexcept;

    void translate(const Point &p) noexcept;
    void translate(int dx, int dy) noexcept;

    [[nodiscard]] Line translated(const Point &p) const noexcept;
    [[nodiscard]] Line translated(int dx, int dy) const noexcept;

    [[nodiscard]] Point center() const noexcept;

    void setP1(const Point &p1) noexcept;
    void setP2(const Point &p2) noexcept;
    void setPoints(const Point &p1, const Point &p2) noexcept;
    void setLine(int x1, int y1, int x2, int y2) noexcept;

    bool operator==(const Line &d) const noexcept;
    bool operator!=(const Line &d) const noexcept { return !(*this == d); }

    [[nodiscard]] LineF toLineF() const noexcept;

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

    LineF() noexcept;
    LineF(const PointF &pt1, const PointF &pt2) noexcept;
    LineF(double x1, double y1, double x2, double y2) noexcept;
    LineF(const Line &line) noexcept : pt1(line.p1()), pt2(line.p2()) {}

    [[nodiscard]] static LineF fromPolar(double length, double angle);

    constexpr bool isNull() const noexcept;

    PointF p1() const noexcept;
    PointF p2() const noexcept;

    double x1() const noexcept;
    double y1() const noexcept;

    double x2() const noexcept;
    double y2() const noexcept;

    double dx() const noexcept;
    double dy() const noexcept;

    double length() const noexcept;
    void setLength(double len) noexcept;

    double angle() const noexcept;
    void setAngle(double angle) noexcept;

    double angleTo(const LineF &l) const noexcept;

    [[nodiscard]] LineF unitVector() const noexcept;
    [[nodiscard]] LineF normalVector() const noexcept;

    IntersectionType
    intersects(const LineF &l,
               PointF *intersectionPoint = nullptr) const noexcept;

    PointF pointAt(double t) const noexcept;
    void translate(const PointF &p) noexcept;
    void translate(double dx, double dy) noexcept;

    [[nodiscard]] LineF translated(const PointF &p) const noexcept;
    [[nodiscard]] LineF translated(double dx, double dy) const noexcept;

    [[nodiscard]] PointF center() const;

    void setP1(const PointF &p1) noexcept;
    void setP2(const PointF &p2) noexcept;
    void setPoints(const PointF &p1, const PointF &p2) noexcept;
    void setLine(double x1, double y1, double x2, double y2) noexcept;

    bool operator==(const LineF &d) const noexcept;
    bool operator!=(const LineF &d) const noexcept { return !(*this == d); }

    constexpr Line toLine() const noexcept;

private:
    PointF pt1, pt2;
};

}// namespace m2

#endif//M2_LINE_H_