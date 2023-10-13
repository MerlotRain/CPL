#include <m2_circle.h>

namespace m2 {

Circle::Circle() {}

Circle::Circle(const PointF &center, double radius, double azimuth) {}

Circle Circle::from2Points(const PointF &pt1, const PointF &pt2)
{
    return Circle();
}

Circle Circle::from3Points(const PointF &pt1, const PointF &pt2,
                           const PointF &pt3, double epsilon)
{
    return Circle();
}

Circle Circle::fromCenterDiameter(const PointF &center, double diameter,
                                  double azimuth)
{
    return Circle();
}

Circle Circle::fromCenterPoint(const PointF &center, const PointF &pt1)
{
    return Circle();
}

Circle Circle::from3Tangents(const PointF &pt1_tg1, const PointF &pt2_tg1,
                             const PointF &pt1_tg2, const PointF &pt2_tg2,
                             const PointF &pt1_tg3, const PointF &pt2_tg3,
                             double epsilon, const PointF &pos)
{
    return Circle();
}

std::vector<Circle>
Circle::from3TangentsMulti(const PointF &pt1_tg1, const PointF &pt2_tg1,
                           const PointF &pt1_tg2, const PointF &pt2_tg2,
                           const PointF &pt1_tg3, const PointF &pt2_tg3,
                           double epsilon, const PointF &pos)
{
    return std::vector<Circle>();
}

Circle Circle::fromExtent(const PointF &pt1, const PointF &pt2)
{
    return Circle();
}

Circle Circle::minimalCircleFrom3Points(const PointF &pt1, const PointF &pt2,
                                        const PointF &pt3, double epsilon)
{
    return Circle();
}

int Circle::intersections(const Circle &other, PointF &intersection1,
                          PointF &intersection2, bool useZ) const
{
    return 0;
}

bool Circle::tangentToPoint(const PointF &p, PointF &pt1, PointF &pt2) const
{
    return false;
}

int Circle::outerTangents(const Circle &other, PointF &line1P1, PointF &line1P2,
                          PointF &line2P1, PointF &line2P2) const
{
    return 0;
}

int Circle::innerTangents(const Circle &other, PointF &line1P1, PointF &line1P2,
                          PointF &line2P1, PointF &line2P2) const
{
    return 0;
}

double Circle::area() const { return 0.0; }

double Circle::perimeter() const { return 0.0; }

void Circle::setSemiMajorAxis(double semiMajorAxis) {}

void Circle::setSemiMinorAxis(double semiMinorAxis) {}

double Circle::radius() const { return 0.0; }

void Circle::setRadius(double radius) {}

PointSequence Circle::northQuadrant() const { return PointSequence(); }

bool Circle::contains(const PointF &point, double epsilon) const
{
    return false;
}

}// namespace m2
