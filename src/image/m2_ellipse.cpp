#include <m2_ellipse.h>
#include <m2_polygon.h>
#include <m2_rect.h>

namespace m2 {

Ellipse::Ellipse() {}

Ellipse::Ellipse(const Ellipse &) {}

Ellipse &Ellipse::operator=(const Ellipse &)
{
    // TODO: insert return statement here
}

Ellipse::Ellipse(Ellipse &&) noexcept {}

Ellipse &Ellipse::operator=(Ellipse &&) noexcept
{
    // TODO: insert return statement here
}

Ellipse::Ellipse(const PointF &center, double semiMajorAxis,
                 double semiMinorAxis, double azimuth)
{
}

Ellipse::~Ellipse() {}

Ellipse Ellipse::fromFoci(const PointF &pt1, const PointF &pt2,
                          const PointF &pt3)
{
    return Ellipse();
}

Ellipse Ellipse::fromExtent(const PointF &pt1, const PointF &pt2)
{
    return Ellipse();
}

Ellipse Ellipse::fromCenterPoint(const PointF &ptc, const PointF &pt1)
{
    return Ellipse();
}

Ellipse Ellipse::fromCenter2Points(const PointF &ptc, const PointF &pt1,
                                   const PointF &pt2)
{
    return Ellipse();
}

bool Ellipse::operator==(const Ellipse &elp) const { return false; }

bool Ellipse::operator!=(const Ellipse &elp) const { return false; }

bool Ellipse::isEmpty() const { return false; }

PointF Ellipse::center() const { return PointF(); }

double Ellipse::semiMajorAxis() const { return 0.0; }

double Ellipse::semiMinorAxis() const { return 0.0; }

double Ellipse::azimuth() const { return 0.0; }

void Ellipse::setCenter(const PointF &center) {}

void Ellipse::setSemiMajorAxis(double semiMajorAxis) {}

void Ellipse::setSemiMinorAxis(double semiMinorAxis) {}

void Ellipse::setAzimuth(double azimuth) {}

double Ellipse::focusDistance() const { return 0.0; }

bool Ellipse::foci(PointF &f1, PointF &f2) const { return false; }

double Ellipse::eccentricity() const { return 0.0; }

double Ellipse::area() const { return 0.0; }

double Ellipse::perimeter() const { return 0.0; }

PointSequence Ellipse::quadrant() const { return PointSequence(); }

PointSequence Ellipse::points(unsigned int segments) const
{
    return PointSequence();
}

PolygonF Ellipse::toPolygon(unsigned int segments) const { return PolygonF(); }

PolygonF Ellipse::orientedBoundingBox() const { return PolygonF(); }

RectF Ellipse::boundingBox() const { return RectF(); }

}// namespace m2
