#include <m2_transform.h>

namespace m2 {

Transform::Transform() {}

Transform::Transform(double h11, double h12, double h13, double h21, double h22,
                     double h23, double h31, double h32, double h33)
{
}

Transform::Transform(double h11, double h12, double h21, double h22, double dx,
                     double dy)
{
}

bool Transform::isAffine() const { return false; }

bool Transform::isIdentity() const { return false; }

bool Transform::isInvertible() const { return false; }

bool Transform::isScaling() const { return false; }

bool Transform::isRotating() const { return false; }

bool Transform::isTranslating() const { return false; }

Transform::TransformationType Transform::type() const
{
    return TransformationType();
}

double Transform::determinant() const { return 0.0; }

double Transform::m11() const { return 0.0; }

double Transform::m12() const { return 0.0; }

double Transform::m13() const { return 0.0; }

double Transform::m21() const { return 0.0; }

double Transform::m22() const { return 0.0; }

double Transform::m23() const { return 0.0; }

double Transform::m31() const { return 0.0; }

double Transform::m32() const { return 0.0; }

double Transform::m33() const { return 0.0; }

void Transform::setMatrix(double m11, double m12, double m13, double m21,
                          double m22, double m23, double m31, double m32,
                          double m33)
{
}

Transform Transform::inverted(bool *invertible) const { return Transform(); }

Transform Transform::adjoint() const { return Transform(); }

Transform Transform::transposed() const { return Transform(); }

Transform &Transform::translate(double dx, double dy)
{
    // TODO: insert return statement here
}

Transform &Transform::scale(double sx, double sy)
{
    // TODO: insert return statement here
}

Transform &Transform::shear(double sh, double sv)
{
    // TODO: insert return statement here
}

Transform &Transform::rotate(double a)
{
    // TODO: insert return statement here
}

Transform &Transform::rotateRadians(double a)
{
    // TODO: insert return statement here
}

bool Transform::squareToQuad(const PolygonF &square, Transform &result)
{
    return false;
}

bool Transform::quadToSquare(const PolygonF &quad, Transform &result)
{
    return false;
}

bool Transform::quadToQuad(const PolygonF &one, const PolygonF &two,
                           Transform &result)
{
    return false;
}

bool Transform::operator==(const Transform &) const { return false; }

bool Transform::operator!=(const Transform &) const { return false; }

Transform &Transform::operator*=(const Transform &)
{
    // TODO: insert return statement here
}

Transform Transform::operator*(const Transform &o) const { return Transform(); }

void Transform::reset() {}

Point Transform::map(const Point &p) const { return Point(); }

PointF Transform::map(const PointF &p) const { return PointF(); }

Line Transform::map(const Line &l) const { return Line(); }

LineF Transform::map(const LineF &l) const { return LineF(); }

PolygonF Transform::map(const PolygonF &a) const { return PolygonF(); }

Polygon Transform::map(const Polygon &a) const { return Polygon(); }

Polygon Transform::mapToPolygon(const Rect &r) const { return Polygon(); }

Rect Transform::mapRect(const Rect &) const { return Rect(); }

RectF Transform::mapRect(const RectF &) const { return RectF(); }

void Transform::map(int x, int y, int *tx, int *ty) const {}

void Transform::map(double x, double y, double *tx, double *ty) const {}

Transform &Transform::operator*=(double div)
{
    // TODO: insert return statement here
}

Transform &Transform::operator/=(double div)
{
    // TODO: insert return statement here
}

Transform &Transform::operator+=(double div)
{
    // TODO: insert return statement here
}

Transform &Transform::operator-=(double div)
{
    // TODO: insert return statement here
}

Transform Transform::fromTranslate(double dx, double dy) { return Transform(); }

Transform Transform::fromScale(double dx, double dy) { return Transform(); }

}// namespace m2
