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

#ifndef M2_TRANSFORM_H_
#define M2_TRANSFORM_H_

#include <m2_line.h>
#include <m2_point.h>
#include <m2_polygon.h>
#include <m2_rect.h>

namespace m2 {

class Transform
{
public:
    enum TransformationType
    {
        TxNone = 0x00,
        TxTranslate = 0x01,
        TxScale = 0x02,
        TxRotate = 0x04,
        TxShear = 0x08,
        TxProject = 0x10
    };

    Transform();
    Transform(double h11, double h12, double h13, double h21, double h22,
              double h23, double h31, double h32, double h33);
    Transform(double h11, double h12, double h21, double h22, double dx,
              double dy);

    Transform(const Transform &) noexcept = default;
    Transform(Transform &&) noexcept = default;
    Transform &operator=(const Transform &) noexcept = default;
    Transform &operator=(Transform &&) noexcept = default;

    bool isAffine() const;
    bool isIdentity() const;
    bool isInvertible() const;
    bool isScaling() const;
    bool isRotating() const;
    bool isTranslating() const;

    TransformationType type() const;
    double determinant() const;

    double m11() const;
    double m12() const;
    double m13() const;
    double m21() const;
    double m22() const;
    double m23() const;
    double m31() const;
    double m32() const;
    double m33() const;

    void setMatrix(double m11, double m12, double m13, double m21, double m22,
                   double m23, double m31, double m32, double m33);

    [[nodiscard]] Transform inverted(bool *invertible = nullptr) const;
    [[nodiscard]] Transform adjoint() const;
    [[nodiscard]] Transform transposed() const;

    Transform &translate(double dx, double dy);
    Transform &scale(double sx, double sy);
    Transform &shear(double sh, double sv);
    Transform &rotate(double a);
    Transform &rotateRadians(double a);

    static bool squareToQuad(const PolygonF &square, Transform &result);
    static bool quadToSquare(const PolygonF &quad, Transform &result);
    static bool quadToQuad(const PolygonF &one, const PolygonF &two,
                           Transform &result);

    bool operator==(const Transform &) const;
    bool operator!=(const Transform &) const;

    Transform &operator*=(const Transform &);
    Transform operator*(const Transform &o) const;

    void reset();
    Point map(const Point &p) const;
    PointF map(const PointF &p) const;
    Line map(const Line &l) const;
    LineF map(const LineF &l) const;
    PolygonF map(const PolygonF &a) const;
    Polygon map(const Polygon &a) const;
    void map(int x, int y, int *tx, int *ty) const;
    void map(double x, double y, double *tx, double *ty) const;
    void map(double* coordinate, int count) const;

    Transform &operator*=(double div);
    Transform &operator/=(double div);
    Transform &operator+=(double div);
    Transform &operator-=(double div);

    static Transform fromTranslate(double dx, double dy);
    static Transform fromScale(double dx, double dy);

private:
    inline TransformationType inline_type() const;

    double m_matrix[3][3];
    mutable unsigned int m_type;
    mutable unsigned int m_dirty;
};

/*******************************************************************************
 * class Transform inline members
 *******************************************************************************/

inline Transform::TransformationType Transform::inline_type() const
{
    if (m_dirty == TxNone) return static_cast<TransformationType>(m_type);
    return type();
}

inline Point operator*(const Point &p, const Transform &m) { return m.map(p); }
inline PointF operator*(const PointF &p, const Transform &m)
{
    return m.map(p);
}
inline LineF operator*(const LineF &l, const Transform &m) { return m.map(l); }
inline Line operator*(const Line &l, const Transform &m) { return m.map(l); }
inline Polygon operator*(const Polygon &a, const Transform &m)
{
    return m.map(a);
}
inline PolygonF operator*(const PolygonF &a, const Transform &m)
{
    return m.map(a);
}

inline Transform operator*(const Transform &a, double n)
{
    Transform t(a);
    t *= n;
    return t;
}
inline Transform operator/(const Transform &a, double n)
{
    Transform t(a);
    t /= n;
    return t;
}
inline Transform operator+(const Transform &a, double n)
{
    Transform t(a);
    t += n;
    return t;
}
inline Transform operator-(const Transform &a, double n)
{
    Transform t(a);
    t -= n;
    return t;
}

}// namespace m2

#endif//M2_TRANSFORM_H_