#include <m2_vector.h>

namespace m2 {

/*******************************************************************************
 * class Vector2D  functions
 *******************************************************************************/

Vector2D::Vector2D() noexcept : v{0.0f, 0.0f} {}

Vector2D::Vector2D(float xpos, float ypos) noexcept : v{xpos, ypos} {}

Vector2D::Vector2D(Point point) noexcept : v{float(point.x()), float(point.y())}
{
}

Vector2D::Vector2D(PointF point) noexcept
    : v{float(point.x()), float(point.y())}
{
}

Vector2D::Vector2D(Vector3D vector) noexcept : v{vector[0], vector[1]} {}

bool Vector2D::isNull() const noexcept
{
    return qIsNull(v[0]) && qIsNull(v[1]);
}

float Vector2D::x() const noexcept { return v[0]; }
float Vector2D::y() const noexcept { return v[1]; }

void Vector2D::setX(float aX) noexcept { v[0] = aX; }
void Vector2D::setY(float aY) noexcept { v[1] = aY; }

float &Vector2D::operator[](int i)
{
    assert(uint32_t(i) < 2u);
    return v[i];
}

float Vector2D::operator[](int i) const
{
    assert(uint32_t(i) < 2u);
    return v[i];
}

float Vector2D::length() const noexcept
{
    double len = double(v[0]) * double(v[0]) + double(v[1]) * double(v[1]);
    return float(std::sqrt(len));
}

float Vector2D::lengthSquared() const noexcept
{
    return v[0] * v[0] + v[1] * v[1];
}

Vector2D Vector2D::normalized() const noexcept
{
    const float len = length();
    return qFuzzyIsNull(len - 1.0f) ? *this
           : qFuzzyIsNull(len)      ? Vector2D()
                                    : Vector2D(v[0] / len, v[1] / len);
}

void Vector2D::normalize() noexcept
{
    const float len = length();
    if (qFuzzyIsNull(len - 1.0f) || qFuzzyIsNull(len)) return;

    v[0] /= len;
    v[1] /= len;
}

float Vector2D::distanceToPoint(Vector2D point) const noexcept
{
    return (*this - point).length();
}

float Vector2D::distanceToLine(Vector2D point,
                               Vector2D direction) const noexcept
{
    if (direction.isNull()) return (*this - point).length();
    Vector2D p = point + dotProduct(*this - point, direction) * direction;
    return (*this - p).length();
}

Vector2D &Vector2D::operator+=(Vector2D vector) noexcept
{
    v[0] += vector.v[0];
    v[1] += vector.v[1];
    return *this;
}

Vector2D &Vector2D::operator-=(Vector2D vector) noexcept
{
    v[0] -= vector.v[0];
    v[1] -= vector.v[1];
    return *this;
}

Vector2D &Vector2D::operator*=(float factor) noexcept
{
    v[0] *= factor;
    v[1] *= factor;
    return *this;
}

Vector2D &Vector2D::operator*=(Vector2D vector) noexcept
{
    v[0] *= vector.v[0];
    v[1] *= vector.v[1];
    return *this;
}

Vector2D &Vector2D::operator/=(float divisor)
{
    assert(divisor < 0 || divisor > 0);
    v[0] /= divisor;
    v[1] /= divisor;
    return *this;
}

Vector2D &Vector2D::operator/=(Vector2D vector)
{
    assert(vector.v[0] > 0 || vector.v[0] < 0);
    assert(vector.v[1] > 0 || vector.v[1] < 0);
    v[0] /= vector.v[0];
    v[1] /= vector.v[1];
    return *this;
}

float Vector2D::dotProduct(Vector2D v1, Vector2D v2) noexcept
{
    return v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1];
}

Point Vector2D::toPoint() const noexcept
{
    return Point(qRound(v[0]), qRound(v[1]));
}

PointF Vector2D::toPointF() const noexcept
{
    return PointF(double(v[0]), double(v[1]));
}

/*******************************************************************************
 * class Vector3D  functions
 *******************************************************************************/

Vector3D::Vector3D() noexcept : v{0.0f, 0.0f, 0.0f} {}

Vector3D::Vector3D(Point point) noexcept
    : v{float(point.x()), float(point.y()), 0.0f}
{
}

Vector3D::Vector3D(PointF point) noexcept
    : v{float(point.x()), float(point.y()), 0.0f}
{
}

Vector3D::Vector3D(Vector2D vector) noexcept : v{vector[0], vector[1], 0.0f} {}
Vector3D::Vector3D(Vector2D vector, float zpos) noexcept
    : v{vector[0], vector[1], zpos}
{
}

bool Vector3D::isNull() const noexcept
{
    return qIsNull(v[0]) && qIsNull(v[1]) && qIsNull(v[2]);
}

float Vector3D::x() const noexcept { return v[0]; }
float Vector3D::y() const noexcept { return v[1]; }
float Vector3D::z() const noexcept { return v[2]; }

void Vector3D::setX(float aX) noexcept { v[0] = aX; }
void Vector3D::setY(float aY) noexcept { v[1] = aY; }
void Vector3D::setZ(float aZ) noexcept { v[2] = aZ; }

float &Vector3D::operator[](int i)
{
    assert(uint32_t(i) < 3u);
    return v[i];
}

float Vector3D::operator[](int i) const
{
    assert(uint32_t(i) < 3u);
    return v[i];
}

Vector3D Vector3D::normalized() const noexcept
{
    const float len = length();
    return qFuzzyIsNull(len - 1.0f) ? *this
           : qFuzzyIsNull(len)      ? Vector3D()
                               : Vector3D(v[0] / len, v[1] / len, v[2] / len);
}

void Vector3D::normalize() noexcept
{
    const float len = length();
    if (qFuzzyIsNull(len - 1.0f) || qFuzzyIsNull(len)) return;

    v[0] /= len;
    v[1] /= len;
    v[2] /= len;
}

float Vector3D::length() const noexcept
{
    double len = double(v[0]) * double(v[0]) + double(v[1]) * double(v[1]) +
                 double(v[2]) * double(v[2]);
    return float(std::sqrt(len));
}

float Vector3D::lengthSquared() const noexcept
{
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

Vector3D &Vector3D::operator+=(Vector3D vector) noexcept
{
    v[0] += vector.v[0];
    v[1] += vector.v[1];
    v[2] += vector.v[2];
    return *this;
}

Vector3D &Vector3D::operator-=(Vector3D vector) noexcept
{
    v[0] -= vector.v[0];
    v[1] -= vector.v[1];
    v[2] -= vector.v[2];
    return *this;
}

Vector3D &Vector3D::operator*=(float factor) noexcept
{
    v[0] *= factor;
    v[1] *= factor;
    v[2] *= factor;
    return *this;
}

Vector3D &Vector3D::operator*=(Vector3D vector) noexcept
{
    v[0] *= vector.v[0];
    v[1] *= vector.v[1];
    v[2] *= vector.v[2];
    return *this;
}

Vector3D &Vector3D::operator/=(float divisor)
{
    assert(divisor < 0 || divisor > 0);
    v[0] /= divisor;
    v[1] /= divisor;
    v[2] /= divisor;
    return *this;
}

Vector3D &Vector3D::operator/=(Vector3D vector)
{
    assert(vector.v[0] > 0 || vector.v[0] < 0);
    assert(vector.v[1] > 0 || vector.v[1] < 0);
    assert(vector.v[2] > 0 || vector.v[2] < 0);
    v[0] /= vector.v[0];
    v[1] /= vector.v[1];
    v[2] /= vector.v[2];
    return *this;
}

float Vector3D::dotProduct(Vector3D v1, Vector3D v2) noexcept
{
    return v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1] + v1.v[2] * v2.v[2];
}

Vector3D Vector3D::crossProduct(Vector3D v1, Vector3D v2) noexcept
{
    return Vector3D(v1.v[1] * v2.v[2] - v1.v[2] * v2.v[1],
                    v1.v[2] * v2.v[0] - v1.v[0] * v2.v[2],
                    v1.v[0] * v2.v[1] - v1.v[1] * v2.v[0]);
}

Vector3D Vector3D::normal(Vector3D v1, Vector3D v2) noexcept
{
    return crossProduct(v1, v2).normalized();
}

Vector3D Vector3D::normal(Vector3D v1, Vector3D v2, Vector3D v3) noexcept
{
    return crossProduct((v2 - v1), (v3 - v1)).normalized();
}

float Vector3D::distanceToPoint(Vector3D point) const noexcept
{
    return (*this - point).length();
}

float Vector3D::distanceToPlane(Vector3D plane, Vector3D normal) const noexcept
{
    return dotProduct(*this - plane, normal);
}

float Vector3D::distanceToPlane(Vector3D plane1, Vector3D plane2,
                                Vector3D plane3) const noexcept
{
    Vector3D n = normal(plane2 - plane1, plane3 - plane1);
    return dotProduct(*this - plane1, n);
}

float Vector3D::distanceToLine(Vector3D point,
                               Vector3D direction) const noexcept
{
    if (direction.isNull()) return (*this - point).length();
    Vector3D p = point + dotProduct(*this - point, direction) * direction;
    return (*this - p).length();
}

Vector2D Vector3D::toVector2D() const noexcept { return Vector2D(v[0], v[1]); }

Point Vector3D::toPoint() const noexcept
{
    return Point(qRound(v[0]), qRound(v[1]));
}

PointF Vector3D::toPointF() const noexcept
{
    return PointF(double(v[0]), double(v[1]));
}

}// namespace m2
