#include "mathhelp.h"

namespace m2 {

Vector2D::Vector2D(double x, double y) : m_X(x), m_Y(y)
{
}

Vector2D Vector2D::operator-() const
{
    return Vector2D(-m_X, -m_Y);
}

Vector2D Vector2D::operator*(double scalar) const
{
    return Vector2D(m_X * scalar, m_Y * scalar);
}

Vector2D Vector2D::operator/(double scalar) const
{
    return *this * (1.0 / scalar);
}

double Vector2D::operator*(Vector2D v) const
{
    return m_X * v.m_X + m_Y * v.m_Y;
}

Vector2D Vector2D::operator+(Vector2D other) const
{
    return Vector2D(m_X + other.m_X, m_Y + other.m_Y);
}

Vector2D &Vector2D::operator+=(Vector2D other)
{
    m_X += other.m_X;
    m_Y += other.m_Y;
    return *this;
}

Vector2D Vector2D::operator-(Vector2D other) const
{
    return Vector2D(m_X - other.m_X, m_Y - other.m_Y);
}

Vector2D &Vector2D::operator-=(Vector2D other)
{
    m_X -= other.m_X;
    m_Y -= other.m_Y;
    return *this;
}

double Vector2D::Length() const
{
    return std::sqrt(m_X * m_X + m_Y * m_Y);
}

double Vector2D::LengthSquared() const
{
    return m_X * m_X + m_Y * m_Y;
}

double Vector2D::X() const
{
    return m_X;
}

double Vector2D::Y() const
{
    return m_Y;
}

Vector2D Vector2D::PerpVector() const
{
    return Vector2D(-m_Y, m_X);
}

double Vector2D::Angle() const
{
    const double angle = std::atan2(m_Y, m_X);
    return angle < 0.0 ? angle + 2.0 * Math::PI : angle;
}

double Vector2D::Angle(Vector2D v) const
{
    return v.Angle() - Angle();
}

double Vector2D::CrossProduct(Vector2D v) const
{
    return m_X * v.Y() - m_Y * v.X();
}

Vector2D Vector2D::RotateBy(double rot) const
{
    const double angle = std::atan2(m_Y, m_X) + rot;
    const double len = Length();
    return Vector2D(len * std::cos(angle), len * std::sin(angle));
}

Vector2D Vector2D::Normalized() const
{
    const double len = Length();

    if (len == 0.0)
    {
        throw Vector2D();
    }

    return *this / len;
}

bool Vector2D::operator==(Vector2D other) const
{
    return Math::IsEqual(m_X, other.m_X) && Math::IsEqual(m_Y, other.m_Y);
}

bool Vector2D::operator!=(Vector2D other) const
{
    return !Math::IsEqual(m_X, other.m_X) || !Math::IsEqual(m_Y, other.m_Y);
}

/***************************************Vector3D***************************************/

Vector3D::Vector3D(double x, double y, double z) : m_X(x), m_Y(y), m_Z(z)
{
}

bool Vector3D::IsNull() const
{
    return m_X == 0 && m_Y == 0 && m_Z == 0;
}

double Vector3D::X() const
{
    return m_X;
}

double Vector3D::Y() const
{
    return m_Y;
}

double Vector3D::Z() const
{
    return m_Z;
}

void Vector3D::X(double x)
{
    m_X = x;
}

void Vector3D::Y(double y)
{
    m_Y = y;
}

void Vector3D::Z(double z)
{
    m_Z = z;
}

void Vector3D::Set(double x, double y, double z)
{
    m_X = x;
    m_Y = y;
    m_Z = z;
}

bool Vector3D::operator==(const Vector3D &other) const
{
    return m_X == other.m_X && m_Y == other.m_Y && m_Z == other.m_Z;
}

bool Vector3D::operator!=(const Vector3D &other) const
{
    return !operator==(other);
}

Vector3D Vector3D::operator+(const Vector3D &other) const
{
    return Vector3D(m_X + other.m_X, m_Y + other.m_Y, m_Z + other.m_Z);
}

Vector3D Vector3D::operator-(const Vector3D &other) const
{
    return Vector3D(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z);
}

Vector3D Vector3D::operator*(const double factor) const
{
    return Vector3D(m_X * factor, m_Y * factor, m_Z * factor);
}

Vector3D Vector3D::operator/(const double factor) const
{
    return Vector3D(m_X / factor, m_Y / factor, m_Z / factor);
}

double Vector3D::DotProduct(const Vector3D &v1, const Vector3D &v2)
{
    return v1.X() * v2.X() + v1.Y() * v2.Y() + v1.Z() * v2.Z();
}

Vector3D Vector3D::CrossProduct(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.Y() * v2.Z() - v1.Z() * v2.Y(), v1.Z() * v2.X() - v1.X() * v2.Z(),
                      v1.X() * v2.Y() - v1.Y() * v2.X());
}

double Vector3D::Length() const
{
    return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
}

void Vector3D::Normalize()
{
    const double len = Length();
    if (!Math::IsEqual(len, 0.0))
    {
        m_X /= len;
        m_Y /= len;
        m_Z /= len;
    }
}

double Vector3D::Distance(const Vector3D &other) const
{
    return std::sqrt((m_X - other.X()) * (m_X - other.X()) + (m_Y - other.Y()) * (m_Y - other.Y()) +
                     (m_Z - other.Z()) * (m_Z - other.Z()));
}

Vector3D Vector3D::PerpendicularPoint(const Vector3D &v1, const Vector3D &v2,
                                          const Vector3D &vp)
{
    const Vector3D d = (v2 - v1) / v2.Distance(v1);
    const Vector3D v = vp - v2;
    const double t = DotProduct(v, d);
    Vector3D P = v2 + (d * t);
    return P;
}

}// namespace m2
