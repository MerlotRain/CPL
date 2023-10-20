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

#ifndef M2_POINT_H_
#define M2_POINT_H_

#include <m2_math.h>
#include <preconfig.h>

namespace m2 {

class PointF;
class LIBM2_EXPORT Point
{
public:
    Point() noexcept;
    Point(int xpos, int ypos) noexcept;

    inline bool isValid() const noexcept;
    bool isNull() const noexcept;

    int x() const noexcept;
    int y() const noexcept;
    void setX(int x) noexcept;
    void setY(int y) noexcept;

    int manhattanLength() const;

    Point transposed() const noexcept { return {yp, xp}; }

    int &rx() noexcept;
    int &ry() noexcept;

    Point &operator+=(const Point &p);
    Point &operator-=(const Point &p);

    Point &operator*=(float factor);
    Point &operator*=(double factor);
    Point &operator*=(int factor);

    Point &operator/=(double divisor);
    PointF project(double distance, double azimuth, double inclination);
    static inline int dotProduct(const Point &p1, const Point &p2)
    {
        return p1.xp * p2.xp + p1.yp * p2.yp;
    }

    friend bool operator==(const Point &p1, const Point &p2) noexcept
    {
        return p1.xp == p2.xp && p1.yp == p2.yp;
    }
    friend bool operator!=(const Point &p1, const Point &p2) noexcept
    {
        return p1.xp != p2.xp || p1.yp != p2.yp;
    }
    friend Point operator+(const Point &p1, const Point &p2) noexcept
    {
        return Point(p1.xp + p2.xp, p1.yp + p2.yp);
    }
    friend Point operator-(const Point &p1, const Point &p2) noexcept
    {
        return Point(p1.xp - p2.xp, p1.yp - p2.yp);
    }
    friend Point operator*(const Point &p, float factor)
    {
        return Point(qRound(p.xp * factor), qRound(p.yp * factor));
    }
    friend Point operator*(const Point &p, double factor)
    {
        return Point(qRound(p.xp * factor), qRound(p.yp * factor));
    }
    friend Point operator*(const Point &p, int factor) noexcept
    {
        return Point(p.xp * factor, p.yp * factor);
    }
    friend Point operator*(float factor, const Point &p)
    {
        return Point(qRound(p.xp * factor), qRound(p.yp * factor));
    }
    friend Point operator*(double factor, const Point &p)
    {
        return Point(qRound(p.xp * factor), qRound(p.yp * factor));
    }
    friend Point operator*(int factor, const Point &p) noexcept
    {
        return Point(p.xp * factor, p.yp * factor);
    }
    friend Point operator+(const Point &p) noexcept { return p; }
    friend Point operator-(const Point &p) noexcept
    {
        return Point(-p.xp, -p.yp);
    }
    friend Point operator/(const Point &p, double c)
    {
        return Point(qRound(p.xp / c), qRound(p.yp / c));
    }

    [[nodiscard]] PointF toPointF() const noexcept;

private:
    int xp;
    int yp;
};

class LIBM2_EXPORT PointF
{
public:
    PointF() noexcept;
    PointF(const Point &p) noexcept;
    PointF(double xpos, double ypos) noexcept;

    double manhattanLength() const;
    double distance(const PointF &other) const;
    double azimuth(const PointF &other) const;

    inline bool isNull() const noexcept;
    inline bool isValid() const noexcept;

    double x() const noexcept;
    double y() const noexcept;
    void setX(double x) noexcept;
    void setY(double y) noexcept;

    PointF offset(double x, double y) const noexcept;
    PointF transposed() const noexcept { return {yp, xp}; }

    double &rx() noexcept;
    double &ry() noexcept;

    PointF &operator+=(const PointF &p);
    PointF &operator-=(const PointF &p);
    PointF &operator*=(double c);
    PointF &operator/=(double c);

    PointF project(double distance, double azimuth) const;
    static inline double dotProduct(const PointF &p1, const PointF &p2)
    {
        return p1.xp * p2.xp + p1.yp * p2.yp;
    }

    friend bool operator==(const PointF &p1, const PointF &p2)
    {
        return ((!p1.xp || !p2.xp) ? qFuzzyIsNull(p1.xp - p2.xp)
                                   : qFuzzyCompare(p1.xp, p2.xp)) &&
               ((!p1.yp || !p2.yp) ? qFuzzyIsNull(p1.yp - p2.yp)
                                   : qFuzzyCompare(p1.yp, p2.yp));
    }
    friend bool operator!=(const PointF &p1, const PointF &p2)
    {
        return !(p1 == p2);
    }
    friend PointF operator+(const PointF &p1, const PointF &p2)
    {
        return PointF(p1.xp + p2.xp, p1.yp + p2.yp);
    }
    friend PointF operator-(const PointF &p1, const PointF &p2)
    {
        return PointF(p1.xp - p2.xp, p1.yp - p2.yp);
    }
    friend PointF operator*(const PointF &p, double c)
    {
        return PointF(p.xp * c, p.yp * c);
    }
    friend PointF operator*(double c, const PointF &p)
    {
        return PointF(p.xp * c, p.yp * c);
    }
    friend PointF operator+(const PointF &p) { return p; }
    friend PointF operator-(const PointF &p) { return PointF(-p.xp, -p.yp); }
    friend PointF operator/(const PointF &p, double divisor)
    {
        assert(divisor < 0 || divisor > 0);
        return PointF(p.xp / divisor, p.yp / divisor);
    }
    Point toPoint() const;

private:
    double xp;
    double yp;
};
typedef std::vector<PointF> PointSequence;

}// namespace m2

#endif//M2_POINT_H_