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
class M2_API Point
{
public:
    constexpr Point() noexcept;
    constexpr Point(int xpos, int ypos) noexcept;

    inline bool isValid() const noexcept;
    constexpr inline bool isNull() const noexcept;

    constexpr inline int x() const noexcept;
    constexpr inline int y() const noexcept;
    constexpr inline void setX(int x) noexcept;
    constexpr inline void setY(int y) noexcept;

    constexpr inline int manhattanLength() const;

    constexpr Point transposed() const noexcept { return {yp, xp}; }

    constexpr inline int &rx() noexcept;
    constexpr inline int &ry() noexcept;

    constexpr inline Point &operator+=(const Point &p);
    constexpr inline Point &operator-=(const Point &p);

    constexpr inline Point &operator*=(float factor);
    constexpr inline Point &operator*=(double factor);
    constexpr inline Point &operator*=(int factor);

    constexpr inline Point &operator/=(double divisor);
    PointF project(double distance, double azimuth, double inclination);
    constexpr static inline int dotProduct(const Point &p1, const Point &p2)
    {
        return p1.xp * p2.xp + p1.yp * p2.yp;
    }

    friend constexpr inline bool operator==(const Point &p1,
                                            const Point &p2) noexcept
    {
        return p1.xp == p2.xp && p1.yp == p2.yp;
    }
    friend constexpr inline bool operator!=(const Point &p1,
                                            const Point &p2) noexcept
    {
        return p1.xp != p2.xp || p1.yp != p2.yp;
    }
    friend constexpr inline Point operator+(const Point &p1,
                                            const Point &p2) noexcept
    {
        return Point(p1.xp + p2.xp, p1.yp + p2.yp);
    }
    friend constexpr inline Point operator-(const Point &p1,
                                            const Point &p2) noexcept
    {
        return Point(p1.xp - p2.xp, p1.yp - p2.yp);
    }
    friend constexpr inline Point operator*(const Point &p, float factor)
    {
        return Point(qRound(p.xp * factor), qRound(p.yp * factor));
    }
    friend constexpr inline Point operator*(const Point &p, double factor)
    {
        return Point(qRound(p.xp * factor), qRound(p.yp * factor));
    }
    friend constexpr inline Point operator*(const Point &p, int factor) noexcept
    {
        return Point(p.xp * factor, p.yp * factor);
    }
    friend constexpr inline Point operator*(float factor, const Point &p)
    {
        return Point(qRound(p.xp * factor), qRound(p.yp * factor));
    }
    friend constexpr inline Point operator*(double factor, const Point &p)
    {
        return Point(qRound(p.xp * factor), qRound(p.yp * factor));
    }
    friend constexpr inline Point operator*(int factor, const Point &p) noexcept
    {
        return Point(p.xp * factor, p.yp * factor);
    }
    friend constexpr inline Point operator+(const Point &p) noexcept
    {
        return p;
    }
    friend constexpr inline Point operator-(const Point &p) noexcept
    {
        return Point(-p.xp, -p.yp);
    }
    friend constexpr inline Point operator/(const Point &p, double c)
    {
        return Point(qRound(p.xp / c), qRound(p.yp / c));
    }

    [[nodiscard]] constexpr inline PointF toPointF() const noexcept;

private:
    int xp;
    int yp;
};

class M2_API PointF
{
public:
    constexpr PointF() noexcept;
    constexpr PointF(const Point &p) noexcept;
    constexpr PointF(double xpos, double ypos) noexcept;

    constexpr inline double manhattanLength() const;
    constexpr inline double distance(const PointF &other) const;
    constexpr inline double azimuth(const PointF &other) const;

    inline bool isNull() const noexcept;
    inline bool isValid() const noexcept;

    constexpr inline double x() const noexcept;
    constexpr inline double y() const noexcept;
    constexpr inline void setX(double x) noexcept;
    constexpr inline void setY(double y) noexcept;

    constexpr PointF transposed() const noexcept { return {yp, xp}; }

    constexpr inline double &rx() noexcept;
    constexpr inline double &ry() noexcept;

    constexpr inline PointF &operator+=(const PointF &p);
    constexpr inline PointF &operator-=(const PointF &p);
    constexpr inline PointF &operator*=(double c);
    constexpr inline PointF &operator/=(double c);

    PointF project(double distance, double azimuth) const;
    constexpr static inline double dotProduct(const PointF &p1,
                                              const PointF &p2)
    {
        return p1.xp * p2.xp + p1.yp * p2.yp;
    }

    friend constexpr inline bool operator==(const PointF &p1, const PointF &p2)
    {
        return ((!p1.xp || !p2.xp) ? qFuzzyIsNull(p1.xp - p2.xp)
                                   : qFuzzyCompare(p1.xp, p2.xp)) &&
               ((!p1.yp || !p2.yp) ? qFuzzyIsNull(p1.yp - p2.yp)
                                   : qFuzzyCompare(p1.yp, p2.yp));
    }
    friend constexpr inline bool operator!=(const PointF &p1, const PointF &p2)
    {
        return !(p1 == p2);
    }
    friend constexpr inline PointF operator+(const PointF &p1, const PointF &p2)
    {
        return PointF(p1.xp + p2.xp, p1.yp + p2.yp);
    }
    friend constexpr inline PointF operator-(const PointF &p1, const PointF &p2)
    {
        return PointF(p1.xp - p2.xp, p1.yp - p2.yp);
    }
    friend constexpr inline PointF operator*(const PointF &p, double c)
    {
        return PointF(p.xp * c, p.yp * c);
    }
    friend constexpr inline PointF operator*(double c, const PointF &p)
    {
        return PointF(p.xp * c, p.yp * c);
    }
    friend constexpr inline PointF operator+(const PointF &p) { return p; }
    friend constexpr inline PointF operator-(const PointF &p)
    {
        return PointF(-p.xp, -p.yp);
    }
    friend constexpr inline PointF operator/(const PointF &p, double divisor)
    {
        assert(divisor < 0 || divisor > 0);
        return PointF(p.xp / divisor, p.yp / divisor);
    }
    constexpr Point toPoint() const;

private:
    double xp;
    double yp;
};
typedef std::vector<PointF> PointSequence;

/*****************************************************************************
  Point inline functions
 *****************************************************************************/

constexpr inline Point::Point() noexcept : xp(0), yp(0) {}

constexpr inline Point::Point(int xpos, int ypos) noexcept : xp(xpos), yp(ypos)
{
}

inline bool Point::isValid() const noexcept
{
    return std::isfinite(xp) || std::isfinite(yp);
}

constexpr inline bool Point::isNull() const noexcept
{
    return xp == 0 && yp == 0;
}

constexpr inline int Point::x() const noexcept { return xp; }

constexpr inline int Point::y() const noexcept { return yp; }

constexpr inline void Point::setX(int xpos) noexcept { xp = xpos; }

constexpr inline void Point::setY(int ypos) noexcept { yp = ypos; }

inline int constexpr Point::manhattanLength() const
{
    return qAbs(x()) + qAbs(y());
}

constexpr inline int &Point::rx() noexcept { return xp; }

constexpr inline int &Point::ry() noexcept { return yp; }

constexpr inline Point &Point::operator+=(const Point &p)
{
    xp += p.xp;
    yp += p.yp;
    return *this;
}

constexpr inline Point &Point::operator-=(const Point &p)
{
    xp -= p.xp;
    yp -= p.yp;
    return *this;
}

constexpr inline Point &Point::operator*=(float factor)
{
    xp = qRound(xp * factor);
    yp = qRound(yp * factor);
    return *this;
}

constexpr inline Point &Point::operator*=(double factor)
{
    xp = qRound(xp * factor);
    yp = qRound(yp * factor);
    return *this;
}

constexpr inline Point &Point::operator*=(int factor)
{
    xp = xp * factor;
    yp = yp * factor;
    return *this;
}

constexpr inline Point &Point::operator/=(double c)
{
    xp = qRound(xp / c);
    yp = qRound(yp / c);
    return *this;
}

/*****************************************************************************
  PointF inline functions
 *****************************************************************************/

constexpr inline PointF::PointF() noexcept : xp(0), yp(0) {}

constexpr inline PointF::PointF(double xpos, double ypos) noexcept
    : xp(xpos), yp(ypos)
{
}

constexpr inline PointF::PointF(const Point &p) noexcept : xp(p.x()), yp(p.y())
{
}

constexpr inline double PointF::manhattanLength() const
{
    return qAbs(x()) + qAbs(y());
}

inline constexpr double PointF::distance(const PointF &other) const
{
    return std::sqrt((xp - other.x()) * (xp - other.x()) +
                     (yp - other.y()) * (yp - other.y()));
}

inline constexpr double PointF::azimuth(const PointF &other) const
{
    const double dx = other.x() - xp;
    const double dy = other.y() - yp;
    return (std::atan2(dx, dy) * 180.0 / M_PI);
}

inline bool PointF::isNull() const noexcept
{
    return qIsNull(xp) && qIsNull(yp);
}

inline bool PointF::isValid() const noexcept
{
    return std::isfinite(xp) || std::isfinite(yp);
}

constexpr inline double PointF::x() const noexcept { return xp; }

constexpr inline double PointF::y() const noexcept { return yp; }

constexpr inline void PointF::setX(double xpos) noexcept { xp = xpos; }

constexpr inline void PointF::setY(double ypos) noexcept { yp = ypos; }

constexpr inline double &PointF::rx() noexcept { return xp; }

constexpr inline double &PointF::ry() noexcept { return yp; }

constexpr inline PointF &PointF::operator+=(const PointF &p)
{
    xp += p.xp;
    yp += p.yp;
    return *this;
}

constexpr inline PointF &PointF::operator-=(const PointF &p)
{
    xp -= p.xp;
    yp -= p.yp;
    return *this;
}

constexpr inline PointF &PointF::operator*=(double c)
{
    xp *= c;
    yp *= c;
    return *this;
}

constexpr inline PointF &PointF::operator/=(double divisor)
{
    assert(divisor > 0 || divisor < 0);
    xp /= divisor;
    yp /= divisor;
    return *this;
}

constexpr PointF Point::toPointF() const noexcept { return *this; }

constexpr inline Point PointF::toPoint() const
{
    return Point(qRound(xp), qRound(yp));
}

}// namespace m2

#endif//M2_POINT_H_