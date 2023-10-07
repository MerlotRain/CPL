#include "mathvector.h"

namespace Lite {
namespace Utility {

GsVector2D::GsVector2D(double x, double y) : m_X(x), m_Y(y)
{
}

GsVector2D GsVector2D::operator-() const
{
    return GsVector2D(-m_X, -m_Y);
}

GsVector2D GsVector2D::operator*(double scalar) const
{
    return GsVector2D(m_X * scalar, m_Y * scalar);
}

GsVector2D GsVector2D::operator/(double scalar) const
{
    return *this * (1.0 / scalar);
}

double GsVector2D::operator*(GsVector2D v) const
{
    return m_X * v.m_X + m_Y * v.m_Y;
}

GsVector2D GsVector2D::operator+(GsVector2D other) const
{
    return GsVector2D(m_X + other.m_X, m_Y + other.m_Y);
}

GsVector2D &GsVector2D::operator+=(GsVector2D other)
{
    m_X += other.m_X;
    m_Y += other.m_Y;
    return *this;
}

GsVector2D GsVector2D::operator-(GsVector2D other) const
{
    return GsVector2D(m_X - other.m_X, m_Y - other.m_Y);
}

GsVector2D &GsVector2D::operator-=(GsVector2D other)
{
    m_X -= other.m_X;
    m_Y -= other.m_Y;
    return *this;
}

double GsVector2D::Length() const
{
    return std::sqrt(m_X * m_X + m_Y * m_Y);
}

double GsVector2D::LengthSquared() const
{
    return m_X * m_X + m_Y * m_Y;
}

double GsVector2D::X() const
{
    return m_X;
}

double GsVector2D::Y() const
{
    return m_Y;
}

GsVector2D GsVector2D::PerpVector() const
{
    return GsVector2D(-m_Y, m_X);
}

double GsVector2D::Angle() const
{
    const double angle = std::atan2(m_Y, m_X);
    return angle < 0.0 ? angle + 2.0 * Math::PI : angle;
}

double GsVector2D::Angle(GsVector2D v) const
{
    return v.Angle() - Angle();
}

double GsVector2D::CrossProduct(GsVector2D v) const
{
    return m_X * v.Y() - m_Y * v.X();
}

GsVector2D GsVector2D::RotateBy(double rot) const
{
    const double angle = std::atan2(m_Y, m_X) + rot;
    const double len = Length();
    return GsVector2D(len * std::cos(angle), len * std::sin(angle));
}

GsVector2D GsVector2D::Normalized() const
{
    const double len = Length();

    if (len == 0.0)
    {
        throw GsVector2D();
    }

    return *this / len;
}

bool GsVector2D::operator==(GsVector2D other) const
{
    return Math::IsEqual(m_X, other.m_X) && Math::IsEqual(m_Y, other.m_Y);
}

bool GsVector2D::operator!=(GsVector2D other) const
{
    return !Math::IsEqual(m_X, other.m_X) || !Math::IsEqual(m_Y, other.m_Y);
}

/***************************************GsVector3D***************************************/

GsVector3D::GsVector3D(double x, double y, double z) : m_X(x), m_Y(y), m_Z(z)
{
}

bool GsVector3D::IsNull() const
{
    return m_X == 0 && m_Y == 0 && m_Z == 0;
}

double GsVector3D::X() const
{
    return m_X;
}

double GsVector3D::Y() const
{
    return m_Y;
}

double GsVector3D::Z() const
{
    return m_Z;
}

void GsVector3D::X(double x)
{
    m_X = x;
}

void GsVector3D::Y(double y)
{
    m_Y = y;
}

void GsVector3D::Z(double z)
{
    m_Z = z;
}

void GsVector3D::Set(double x, double y, double z)
{
    m_X = x;
    m_Y = y;
    m_Z = z;
}

bool GsVector3D::operator==(const GsVector3D &other) const
{
    return m_X == other.m_X && m_Y == other.m_Y && m_Z == other.m_Z;
}

bool GsVector3D::operator!=(const GsVector3D &other) const
{
    return !operator==(other);
}

GsVector3D GsVector3D::operator+(const GsVector3D &other) const
{
    return GsVector3D(m_X + other.m_X, m_Y + other.m_Y, m_Z + other.m_Z);
}

GsVector3D GsVector3D::operator-(const GsVector3D &other) const
{
    return GsVector3D(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z);
}

GsVector3D GsVector3D::operator*(const double factor) const
{
    return GsVector3D(m_X * factor, m_Y * factor, m_Z * factor);
}

GsVector3D GsVector3D::operator/(const double factor) const
{
    return GsVector3D(m_X / factor, m_Y / factor, m_Z / factor);
}

double GsVector3D::DotProduct(const GsVector3D &v1, const GsVector3D &v2)
{
    return v1.X() * v2.X() + v1.Y() * v2.Y() + v1.Z() * v2.Z();
}

GsVector3D GsVector3D::CrossProduct(const GsVector3D &v1, const GsVector3D &v2)
{
    return GsVector3D(v1.Y() * v2.Z() - v1.Z() * v2.Y(), v1.Z() * v2.X() - v1.X() * v2.Z(),
                      v1.X() * v2.Y() - v1.Y() * v2.X());
}

double GsVector3D::Length() const
{
    return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
}

void GsVector3D::Normalize()
{
    const double len = Length();
    if (!Math::IsEqual(len, 0.0))
    {
        m_X /= len;
        m_Y /= len;
        m_Z /= len;
    }
}

double GsVector3D::Distance(const GsVector3D &other) const
{
    return std::sqrt((m_X - other.X()) * (m_X - other.X()) + (m_Y - other.Y()) * (m_Y - other.Y()) +
                     (m_Z - other.Z()) * (m_Z - other.Z()));
}

GsVector3D GsVector3D::PerpendicularPoint(const GsVector3D &v1, const GsVector3D &v2,
                                          const GsVector3D &vp)
{
    const GsVector3D d = (v2 - v1) / v2.Distance(v1);
    const GsVector3D v = vp - v2;
    const double t = DotProduct(v, d);
    GsVector3D P = v2 + (d * t);
    return P;
}

}// namespace Utility
}// namespace Lite
