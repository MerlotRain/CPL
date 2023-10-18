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

class Vector3D;
class Vector2D
{
public:
    Vector2D() noexcept;
    Vector2D(double x, double y) noexcept;

    Vector2D operator-() const;
    Vector2D operator*(double scalar) const;
    Vector2D operator/(double scalar) const;
    double operator*(Vector2D v) const;
    Vector2D operator+(Vector2D other) const;
    Vector2D &operator+=(Vector2D other);
    Vector2D operator-(Vector2D other) const;
    Vector2D &operator-=(Vector2D other);

    double length() const;
    double lengthSquared() const;

    double x() const noexcept;
    double y() const noexcept;

    void setX(double x) noexcept;
    void setY(double y) noexcept;

    Vector2D perpVector() const;

    double angle() const;
    double angle(Vector2D v) const;
    double crossProduct(Vector2D v) const;
    Vector2D rotateBy(double rot) const;
    Vector2D normalized() const;

    bool operator==(Vector2D other) const;
    bool operator!=(Vector2D other) const;

private:
    double xp = 0.0;
    double yp = 0.0;
};

class Vector3D
{
public:
    Vector3D() noexcept;
    Vector3D(double x, double y, double z) noexcept;
    bool isNull() const;

    double x() const noexcept;
    double y() const noexcept;
    double z() const noexcept;

    void setX(double x) noexcept;
    void setY(double y) noexcept;
    void setZ(double z) noexcept;
    void set(double x, double y, double z) noexcept;

    bool operator==(const Vector3D &other) const;
    bool operator!=(const Vector3D &other) const;

    Vector3D operator+(const Vector3D &other) const;
    Vector3D operator-(const Vector3D &other) const;
    Vector3D operator*(const double factor) const;
    Vector3D operator/(const double factor) const;

    static double dotProduct(const Vector3D &v1, const Vector3D &v2);
    static Vector3D crossProduct(const Vector3D &v1, const Vector3D &v2);

    double length() const;
    void normalize();
    double distance(const Vector3D &other) const;
    static Vector3D perpendicularPoint(const Vector3D &v1, const Vector3D &v2,
                                       const Vector3D &vp);

private:
    double xp = 0, yp = 0, zp = 0;
};

}// namespace m2

#endif//M2_VECTOR_H