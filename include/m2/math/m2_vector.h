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

#ifndef M2_VECTOR_H
#define M2_VECTOR_H

#include <m2_math.h>
#include <m2_point.h>

namespace m2 {

class Vector2D
{
public:
    constexpr Vector2D() noexcept;
    constexpr Vector2D(float xpos, float ypos) noexcept;
    constexpr explicit Vector2D(Point point) noexcept;
    constexpr explicit Vector2D(PointF point) noexcept;
    constexpr explicit Vector2D(Vector3D vector) noexcept;
    constexpr bool isNull() const noexcept;

    constexpr float x() const noexcept;
    constexpr float y() const noexcept;

    constexpr void setX(float x) noexcept;
    constexpr void setY(float y) noexcept;

    constexpr float &operator[](int i);
    constexpr float operator[](int i) const;

    [[nodiscard]] float length() const noexcept;
    [[nodiscard]] constexpr float lengthSquared() const noexcept;

    [[nodiscard]] Vector2D normalized() const noexcept;
    void normalize() noexcept;

    [[nodiscard]] float distanceToPoint(Vector2D point) const noexcept;
    [[nodiscard]] float distanceToLine(Vector2D point, Vector2D direction) const noexcept;

    constexpr Vector2D &operator+=(Vector2D vector) noexcept;
    constexpr Vector2D &operator-=(Vector2D vector) noexcept;
    constexpr Vector2D &operator*=(float factor) noexcept;
    constexpr Vector2D &operator*=(Vector2D vector) noexcept;
    constexpr Vector2D &operator/=(float divisor);
    constexpr Vector2D &operator/=(Vector2D vector);

    [[nodiscard]] static constexpr float dotProduct(Vector2D v1, Vector2D v2) noexcept;

    constexpr friend inline bool operator==(Vector2D v1, Vector2D v2) noexcept
    {
        return v1.v[0] == v2.v[0] && v1.v[1] == v2.v[1];
    }

    constexpr friend inline bool operator!=(Vector2D v1, Vector2D v2) noexcept
    {
        return v1.v[0] != v2.v[0] || v1.v[1] != v2.v[1];
    }

    constexpr friend inline Vector2D operator+(Vector2D v1, Vector2D v2) noexcept
    {
        return Vector2D(v1.v[0] + v2.v[0], v1.v[1] + v2.v[1]);
    }

    constexpr friend inline Vector2D operator-(Vector2D v1, Vector2D v2) noexcept
    {
        return Vector2D(v1.v[0] - v2.v[0], v1.v[1] - v2.v[1]);
    }

    constexpr friend inline Vector2D operator*(float factor, Vector2D vector) noexcept
    {
        return Vector2D(vector.v[0] * factor, vector.v[1] * factor);
    }

    constexpr friend inline Vector2D operator*(Vector2D vector, float factor) noexcept
    {
        return Vector2D(vector.v[0] * factor, vector.v[1] * factor);
    }

    constexpr friend inline Vector2D operator*(Vector2D v1, Vector2D v2) noexcept
    {
        return Vector2D(v1.v[0] * v2.v[0], v1.v[1] * v2.v[1]);
    }

    constexpr friend inline Vector2D operator-(Vector2D vector) noexcept
    {
        return Vector2D(-vector.v[0], -vector.v[1]);
    }

    constexpr friend inline Vector2D operator/(Vector2D vector, float divisor)
    {
        assert(divisor < 0 || divisor > 0);
        return Vector2D(vector.v[0] / divisor, vector.v[1] / divisor);
    }

    constexpr friend inline Vector2D operator/(Vector2D vector, Vector2D divisor)
    {
        assert(divisor.v[0] < 0 || divisor.v[0] > 0);
        assert(divisor.v[1] < 0 || divisor.v[1] > 0);
        return Vector2D(vector.v[0] / divisor.v[0], vector.v[1] / divisor.v[1]);
    }

    friend bool qFuzzyCompare(Vector2D v1, Vector2D v2) noexcept;

    constexpr Vector3D toVector3D() const noexcept;
    constexpr Point toPoint() const noexcept;
    constexpr PointF toPointF() const noexcept;

private:
    float v[2];
    friend class Vector3D;
};

class Vector3D
{
public:
    constexpr Vector3D() noexcept;
    constexpr Vector3D(float xpos, float ypos, float zpos) noexcept : v{xpos, ypos, zpos} {}

    constexpr explicit Vector3D(Point point) noexcept;
    constexpr explicit Vector3D(PointF point) noexcept;
#ifndef QT_NO_VECTOR2D
    constexpr explicit Vector3D(Vector2D vector) noexcept;
    constexpr Vector3D(Vector2D vector, float zpos) noexcept;
#endif

    constexpr bool isNull() const noexcept;

    constexpr float x() const noexcept;
    constexpr float y() const noexcept;
    constexpr float z() const noexcept;

    constexpr void setX(float x) noexcept;
    constexpr void setY(float y) noexcept;
    constexpr void setZ(float z) noexcept;

    constexpr float &operator[](int i);
    constexpr float operator[](int i) const;

    [[nodiscard]] float length() const noexcept;
    [[nodiscard]] constexpr float lengthSquared() const noexcept;

    [[nodiscard]] Vector3D normalized() const noexcept;
    void normalize() noexcept;

    constexpr Vector3D &operator+=(Vector3D vector) noexcept;
    constexpr Vector3D &operator-=(Vector3D vector) noexcept;
    constexpr Vector3D &operator*=(float factor) noexcept;
    constexpr Vector3D &operator*=(Vector3D vector) noexcept;
    constexpr Vector3D &operator/=(float divisor);
    constexpr Vector3D &operator/=(Vector3D vector);

    [[nodiscard]] static constexpr float dotProduct(Vector3D v1, Vector3D v2) noexcept;
    [[nodiscard]] static constexpr Vector3D crossProduct(Vector3D v1, Vector3D v2) noexcept;

    [[nodiscard]] static Vector3D normal(Vector3D v1, Vector3D v2) noexcept;
    [[nodiscard]] static Vector3D normal(Vector3D v1, Vector3D v2, Vector3D v3) noexcept;

    constexpr friend inline bool operator==(Vector3D v1, Vector3D v2) noexcept
    {
        return v1.v[0] == v2.v[0] && v1.v[1] == v2.v[1] && v1.v[2] == v2.v[2];
    }

    constexpr friend inline bool operator!=(Vector3D v1, Vector3D v2) noexcept
    {
        return v1.v[0] != v2.v[0] || v1.v[1] != v2.v[1] || v1.v[2] != v2.v[2];
    }
    float distanceToPoint(Vector3D point) const noexcept;
    constexpr float distanceToPlane(Vector3D plane, Vector3D normal) const noexcept;
    float distanceToPlane(Vector3D plane1, Vector3D plane2, Vector3D plane3) const noexcept;
    float distanceToLine(Vector3D point, Vector3D direction) const noexcept;


    constexpr friend inline Vector3D operator+(Vector3D v1, Vector3D v2) noexcept
    {
        return Vector3D(v1.v[0] + v2.v[0], v1.v[1] + v2.v[1], v1.v[2] + v2.v[2]);
    }

    constexpr friend inline Vector3D operator-(Vector3D v1, Vector3D v2) noexcept
    {
        return Vector3D(v1.v[0] - v2.v[0], v1.v[1] - v2.v[1], v1.v[2] - v2.v[2]);
    }

    constexpr friend inline Vector3D operator*(float factor, Vector3D vector) noexcept
    {
        return Vector3D(vector.v[0] * factor, vector.v[1] * factor, vector.v[2] * factor);
    }

    constexpr friend inline Vector3D operator*(Vector3D vector, float factor) noexcept
    {
        return Vector3D(vector.v[0] * factor, vector.v[1] * factor, vector.v[2] * factor);
    }

    constexpr friend inline Vector3D operator*(Vector3D v1, Vector3D v2) noexcept
    {
        return Vector3D(v1.v[0] * v2.v[0], v1.v[1] * v2.v[1], v1.v[2] * v2.v[2]);
    }

    constexpr friend inline Vector3D operator-(Vector3D vector) noexcept
    {
        return Vector3D(-vector.v[0], -vector.v[1], -vector.v[2]);
    }

    constexpr friend inline Vector3D operator/(Vector3D vector, float divisor)
    {
        assert(divisor < 0 || divisor > 0);
        return Vector3D(vector.v[0] / divisor, vector.v[1] / divisor, vector.v[2] / divisor);
    }

    constexpr friend inline Vector3D operator/(Vector3D vector, Vector3D divisor)
    {
        assert(divisor.v[0] > 0 || divisor.v[0] < 0);
        assert(divisor.v[1] > 0 || divisor.v[1] < 0);
        assert(divisor.v[2] > 0 || divisor.v[2] < 0);
        return Vector3D(vector.v[0] / divisor.v[0], vector.v[1] / divisor.v[1],
                        vector.v[2] / divisor.v[2]);
    }

    friend bool qFuzzyCompare(Vector3D v1, Vector3D v2) noexcept;

    constexpr Vector2D toVector2D() const noexcept;

    constexpr Point toPoint() const noexcept;
    constexpr PointF toPointF() const noexcept;

private:
    float v[3];
    friend class Vector2D;
};


}// namespace m2

#endif//M2_VECTOR_H