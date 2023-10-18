#include <m2_vector.h>

namespace m2 {

/*******************************************************************************
 * class Vector2D  functions
 *******************************************************************************/

Vector2D::Vector2D() noexcept = default;

Vector2D::Vector2D(double x, double y) noexcept : xp(x), yp(y) {}

Vector2D Vector2D::operator-() const { return Vector2D(-xp, -yp); }

Vector2D Vector2D::operator*(double scalar) const
{
    return Vector2D(xp * scalar, yp * scalar);
}

Vector2D Vector2D::operator/(double scalar) const
{
    return *this * (1.0 / scalar);
}

double Vector2D::operator*(Vector2D v) const { return xp * v.xp + yp * v.yp; }

Vector2D Vector2D::operator+(Vector2D other) const
{
    return Vector2D(xp + other.xp, yp + other.yp);
}

Vector2D &Vector2D::operator+=(Vector2D other)
{
    xp += other.xp;
    yp += other.yp;
    return *this;
}

Vector2D Vector2D::operator-(Vector2D other) const
{
    return Vector2D(xp - other.xp, yp - other.yp);
}

Vector2D &Vector2D::operator-=(Vector2D other)
{
    xp -= other.xp;
    yp -= other.yp;
    return *this;
}

double Vector2D::length() const { return std::sqrt(xp * xp + yp * yp); }

double Vector2D::lengthSquared() const { return xp * xp + yp * yp; }

double Vector2D::x() const noexcept { return xp; }

double Vector2D::y() const noexcept { return yp; }

void Vector2D::setX(double x) noexcept { xp = x; }

void Vector2D::setY(double y) noexcept { yp = y; }

Vector2D Vector2D::perpVector() const { return Vector2D(-yp, xp); }

double Vector2D::angle() const
{
    const double angle = std::atan2(yp, xp);
    return angle < 0.0 ? angle + 2.0 * M_PI : angle;
}

double Vector2D::angle(Vector2D v) const { return v.angle() - angle(); }

double Vector2D::crossProduct(Vector2D v) const
{
    return xp * v.y() - yp * v.x();
}

Vector2D Vector2D::rotateBy(double rot) const
{
    const double angle = std::atan2(yp, xp) + rot;
    const double len = length();
    return Vector2D(len * std::cos(angle), len * std::sin(angle));
}

Vector2D Vector2D::normalized() const
{
    const double len = length();

    if (len == 0.0) { return Vector2D(); }

    return *this / len;
}

bool Vector2D::operator==(Vector2D other) const
{
    return qIsEqual(xp, other.xp) && qIsEqual(yp, other.yp);
}

bool Vector2D::operator!=(Vector2D other) const
{
    return !qIsEqual(xp, other.xp) || !qIsEqual(yp, other.yp);
}

/*******************************************************************************
 * class Vector3D  functions
 *******************************************************************************/

Vector3D::Vector3D() noexcept = default;

Vector3D::Vector3D(double x, double y, double z) noexcept : xp(x), yp(y), zp(z)
{
}

bool Vector3D::isNull() const { return xp == 0 && yp == 0 && zp == 0; }

double Vector3D::x() const noexcept { return xp; }

double Vector3D::y() const noexcept { return yp; }

double Vector3D::z() const noexcept { return zp; }

void Vector3D::setX(double x) noexcept { xp = x; }

void Vector3D::setY(double y) noexcept { yp = y; }

void Vector3D::setZ(double z) noexcept { zp = z; }

void Vector3D::set(double x, double y, double z) noexcept
{
    xp = x;
    yp = y;
    zp = z;
}

bool Vector3D::operator==(const Vector3D &other) const
{
    return xp == other.xp && yp == other.yp && zp == other.zp;
}

bool Vector3D::operator!=(const Vector3D &other) const
{
    return !operator==(other);
}

Vector3D Vector3D::operator+(const Vector3D &other) const
{
    return Vector3D(xp + other.xp, yp + other.yp, zp + other.zp);
}

Vector3D Vector3D::operator-(const Vector3D &other) const
{
    return Vector3D(xp - other.xp, yp - other.yp, zp - other.zp);
}

Vector3D Vector3D::operator*(const double factor) const
{
    return Vector3D(xp * factor, yp * factor, zp * factor);
}

Vector3D Vector3D::operator/(const double factor) const
{
    return Vector3D(xp / factor, yp / factor, zp / factor);
}

double Vector3D::dotProduct(const Vector3D &v1, const Vector3D &v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

Vector3D Vector3D::crossProduct(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.y() * v2.z() - v1.z() * v2.y(),
                    v1.z() * v2.x() - v1.x() * v2.z(),
                    v1.x() * v2.y() - v1.y() * v2.x());
}

double Vector3D::length() const { return sqrt(xp * xp + yp * yp + zp * zp); }

void Vector3D::normalize()
{
    const double len = length();
    if (!qIsEqual(len, 0.0))
    {
        xp /= len;
        yp /= len;
        zp /= len;
    }
}

double Vector3D::distance(const Vector3D &other) const
{
    return std::sqrt((xp - other.x()) * (xp - other.x()) +
                     (yp - other.y()) * (yp - other.y()) +
                     (zp - other.z()) * (zp - other.z()));
}

Vector3D Vector3D::perpendicularPoint(const Vector3D &v1, const Vector3D &v2,
                                      const Vector3D &vp)
{
    const Vector3D d = (v2 - v1) / v2.distance(v1);
    const Vector3D v = vp - v2;
    const double t = dotProduct(v, d);
    Vector3D P = v2 + (d * t);
    return P;
}

}// namespace m2
