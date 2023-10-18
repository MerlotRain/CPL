#include <m2_point.h>

namespace m2 {


/*****************************************************************************
  Point inline functions
 *****************************************************************************/

Point::Point() noexcept : xp(0), yp(0) {}

Point::Point(int xpos, int ypos) noexcept : xp(xpos), yp(ypos) {}

inline bool Point::isValid() const noexcept
{
    return std::isfinite(xp) || std::isfinite(yp);
}

bool Point::isNull() const noexcept { return xp == 0 && yp == 0; }

int Point::x() const noexcept { return xp; }

int Point::y() const noexcept { return yp; }

void Point::setX(int xpos) noexcept { xp = xpos; }

void Point::setY(int ypos) noexcept { yp = ypos; }

inline int Point::manhattanLength() const { return qAbs(x()) + qAbs(y()); }

int &Point::rx() noexcept { return xp; }

int &Point::ry() noexcept { return yp; }

Point &Point::operator+=(const Point &p)
{
    xp += p.xp;
    yp += p.yp;
    return *this;
}

Point &Point::operator-=(const Point &p)
{
    xp -= p.xp;
    yp -= p.yp;
    return *this;
}

Point &Point::operator*=(float factor)
{
    xp = qRound(xp * factor);
    yp = qRound(yp * factor);
    return *this;
}

Point &Point::operator*=(double factor)
{
    xp = qRound(xp * factor);
    yp = qRound(yp * factor);
    return *this;
}

Point &Point::operator*=(int factor)
{
    xp = xp * factor;
    yp = yp * factor;
    return *this;
}

Point &Point::operator/=(double c)
{
    xp = qRound(xp / c);
    yp = qRound(yp / c);
    return *this;
}

/*****************************************************************************
  PointF inline functions
 *****************************************************************************/

PointF::PointF() noexcept : xp(0), yp(0) {}

PointF::PointF(double xpos, double ypos) noexcept : xp(xpos), yp(ypos) {}

PointF::PointF(const Point &p) noexcept : xp(p.x()), yp(p.y()) {}

double PointF::manhattanLength() const { return qAbs(x()) + qAbs(y()); }

inline double PointF::distance(const PointF &other) const
{
    return std::sqrt((xp - other.x()) * (xp - other.x()) +
                     (yp - other.y()) * (yp - other.y()));
}

inline double PointF::azimuth(const PointF &other) const
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

double PointF::x() const noexcept { return xp; }

double PointF::y() const noexcept { return yp; }

void PointF::setX(double xpos) noexcept { xp = xpos; }

void PointF::setY(double ypos) noexcept { yp = ypos; }

PointF PointF::offset(double x, double y) const noexcept
{
    return PointF(xp + x, yp + y);
}

double &PointF::rx() noexcept { return xp; }

double &PointF::ry() noexcept { return yp; }

PointF &PointF::operator+=(const PointF &p)
{
    xp += p.xp;
    yp += p.yp;
    return *this;
}

PointF &PointF::operator-=(const PointF &p)
{
    xp -= p.xp;
    yp -= p.yp;
    return *this;
}

PointF &PointF::operator*=(double c)
{
    xp *= c;
    yp *= c;
    return *this;
}

PointF &PointF::operator/=(double divisor)
{
    assert(divisor > 0 || divisor < 0);
    xp /= divisor;
    yp /= divisor;
    return *this;
}

PointF PointF::project(double distance, double azimuth) const
{
    const double radsXy = azimuth * M_PI / 180.0;
    double dx = 0.0, dy = 0.0, dz = 0.0;

    dy = distance * std::cos(radsXy);

    return PointF(xp + dx, yp + dy);
}

PointF Point::toPointF() const noexcept { return *this; }

Point PointF::toPoint() const { return Point(qRound(xp), qRound(yp)); }

}// namespace m2
