#include <m2_circle.h>
#include <m2_geometrymath.h>
#include <m2_math.h>
#include <m2_triangle.h>

namespace m2 {

static bool isPerpendicular(const PointF &pt1, const PointF &pt2,
                            const PointF &pt3, double epsilon)
{
    // check the given point are perpendicular to x or y axis

    const double yDelta_a = pt2.y() - pt1.y();
    const double xDelta_a = pt2.x() - pt1.x();
    const double yDelta_b = pt3.y() - pt2.y();
    const double xDelta_b = pt3.x() - pt2.x();

    if ((std::fabs(xDelta_a) <= epsilon) && (std::fabs(yDelta_b) <= epsilon))
    {
        return false;
    }

    if (std::fabs(yDelta_a) <= epsilon) { return true; }
    else if (std::fabs(yDelta_b) <= epsilon) { return true; }
    else if (std::fabs(xDelta_a) <= epsilon) { return true; }
    else if (std::fabs(xDelta_b) <= epsilon) { return true; }

    return false;
}

static std::vector<Circle>
from2ParallelsLine(const PointF &pt1_par1, const PointF &pt2_par1,
                   const PointF &pt1_par2, const PointF &pt2_par2,
                   const PointF &pt1_line1, const PointF &pt2_line1,
                   const PointF &pos, double epsilon)
{
    const double radius =
            GeometryMath::perpendicularSegment(pt1_par2, pt1_par1, pt2_par1)
                    .length() /
            2.0;

    bool isInter;
    const PointF ptInter;
    std::vector<Circle> circles;

    PointF ptInter_par1line1, ptInter_par2line1;
    double angle1, angle2;
    double x, y;
    GeometryMath::angleBisector(pt1_par1.x(), pt1_par1.y(), pt2_par1.x(),
                                pt2_par1.y(), pt1_line1.x(), pt1_line1.y(),
                                pt2_line1.x(), pt2_line1.y(), x, y, angle1);
    ptInter_par1line1.setX(x);
    ptInter_par1line1.setY(y);

    GeometryMath::angleBisector(pt1_par2.x(), pt1_par2.y(), pt2_par2.x(),
                                pt2_par2.y(), pt1_line1.x(), pt1_line1.y(),
                                pt2_line1.x(), pt2_line1.y(), x, y, angle2);
    ptInter_par2line1.setX(x);
    ptInter_par2line1.setY(y);

    PointF center;
    GeometryMath::segmentIntersection(
            ptInter_par1line1, ptInter_par1line1.project(1.0, angle1),
            ptInter_par2line1, ptInter_par2line1.project(1.0, angle2), center,
            isInter, epsilon, true);
    if (isInter)
    {
        if (pos.isValid())
        {
            if (GeometryMath::leftOfLine(center, pt1_line1, pt2_line1) ==
                GeometryMath::leftOfLine(pos, pt1_line1, pt2_line1))
            {
                circles.push_back(Circle(center, radius));
            }
        }
        else { circles.push_back(Circle(center, radius)); }
    }

    GeometryMath::segmentIntersection(
            ptInter_par1line1, ptInter_par1line1.project(1.0, angle1),
            ptInter_par2line1, ptInter_par2line1.project(1.0, angle2 + 90.0),
            center, isInter, epsilon, true);
    if (isInter)
    {
        if (pos.isValid())
        {
            if (GeometryMath::leftOfLine(center, pt1_line1, pt2_line1) ==
                GeometryMath::leftOfLine(pos, pt1_line1, pt2_line1))
            {
                circles.push_back(Circle(center, radius));
            }
        }
        else { circles.push_back(Circle(center, radius)); }
    }

    GeometryMath::segmentIntersection(
            ptInter_par1line1, ptInter_par1line1.project(1.0, angle1 + 90.0),
            ptInter_par2line1, ptInter_par2line1.project(1.0, angle2), center,
            isInter, epsilon, true);
    if (isInter && std::find(circles.begin(), circles.end(),
                             Circle(center, radius)) != circles.end())
    {
        if (pos.isValid())
        {
            if (GeometryMath::leftOfLine(center, pt1_line1, pt2_line1) ==
                GeometryMath::leftOfLine(pos, pt1_line1, pt2_line1))
            {
                circles.push_back(Circle(center, radius));
            }
        }
        else { circles.push_back(Circle(center, radius)); }
    }
    GeometryMath::segmentIntersection(
            ptInter_par1line1, ptInter_par1line1.project(1.0, angle1 + 90.0),
            ptInter_par2line1, ptInter_par2line1.project(1.0, angle2 + 90.0),
            center, isInter, epsilon, true);
    if (isInter && std::find(circles.begin(), circles.end(),
                             Circle(center, radius)) != circles.end())
    {
        if (pos.isValid())
        {
            if (GeometryMath::leftOfLine(center, pt1_line1, pt2_line1) ==
                GeometryMath::leftOfLine(pos, pt1_line1, pt2_line1))
            {
                circles.push_back(Circle(center, radius));
            }
        }
        else { circles.push_back(Circle(center, radius)); }
    }

    return circles;
}


/**
 * @brief Construct a new Circle:: Circle object
 * 
 */
Circle::Circle() : Ellipse(PointF(), 0.0, 0.0, 0.0) {}

/**
 * @brief Construct a new Circle:: Circle object
 * 
 * @param center 
 * @param radius 
 * @param azimuth 
 */
Circle::Circle(const PointF &center, double radius, double azimuth)
    : Ellipse(center, radius, radius, azimuth)
{
}

/**
 * @brief 
 * 
 * @param pt1 
 * @param pt2 
 * @return Circle 
 */
Circle Circle::from2Points(const PointF &pt1, const PointF &pt2)
{
    PointF center = GeometryMath::midpoint(pt1, pt2);
    const double azimuth =
            GeometryMath::lineAngle(pt1.x(), pt1.y(), pt2.x(), pt2.y()) *
            180.0 / M_PI;
    const double radius = pt1.distance(pt2) / 2.0;

    return Circle(center, radius, azimuth);
}

/**
 * @brief 
 * 
 * @param pt1 
 * @param pt2 
 * @param pt3 
 * @param epsilon 
 * @return Circle 
 */
Circle Circle::from3Points(const PointF &pt1, const PointF &pt2,
                           const PointF &pt3, double epsilon)
{
    PointF p1, p2, p3;

    if (!isPerpendicular(pt1, pt2, pt3, epsilon))
    {
        p1 = pt1;
        p2 = pt2;
        p3 = pt3;
    }
    else if (!isPerpendicular(pt1, pt3, pt2, epsilon))
    {
        p1 = pt1;
        p2 = pt3;
        p3 = pt2;
    }
    else if (!isPerpendicular(pt2, pt1, pt3, epsilon))
    {
        p1 = pt2;
        p2 = pt1;
        p3 = pt3;
    }
    else if (!isPerpendicular(pt2, pt3, pt1, epsilon))
    {
        p1 = pt2;
        p2 = pt3;
        p3 = pt1;
    }
    else if (!isPerpendicular(pt3, pt2, pt1, epsilon))
    {
        p1 = pt3;
        p2 = pt2;
        p3 = pt1;
    }
    else if (!isPerpendicular(pt3, pt1, pt2, epsilon))
    {
        p1 = pt3;
        p2 = pt1;
        p3 = pt2;
    }
    else { return Circle(); }
    PointF center = PointF();
    double radius = -0.0;
    const double yDelta_a = p2.y() - p1.y();
    const double xDelta_a = p2.x() - p1.x();
    const double yDelta_b = p3.y() - p2.y();
    const double xDelta_b = p3.x() - p2.x();

    if (qIsEqual(xDelta_a, 0.0, epsilon) || qIsEqual(xDelta_b, 0.0, epsilon))
    {
        return Circle();
    }

    const double aSlope = yDelta_a / xDelta_a;
    const double bSlope = yDelta_b / xDelta_b;

    if ((std::fabs(xDelta_a) <= epsilon) && (std::fabs(yDelta_b) <= epsilon))
    {
        center.setX(0.5 * (p2.x() + p3.x()));
        center.setY(0.5 * (p1.y() + p2.y()));
        radius = center.distance(pt1);

        return Circle(center, radius);
    }

    if (std::fabs(aSlope - bSlope) <= epsilon) { return Circle(); }

    center.setX((aSlope * bSlope * (p1.y() - p3.y()) +
                 bSlope * (p1.x() + p2.x()) - aSlope * (p2.x() + p3.x())) /
                (2.0 * (bSlope - aSlope)));
    center.setY(-1.0 * (center.x() - (p1.x() + p2.x()) / 2.0) / aSlope +
                (p1.y() + p2.y()) / 2.0);

    radius = center.distance(p1);

    return Circle(center, radius);
}

/**
 * @brief 
 * 
 * @param center 
 * @param diameter 
 * @param azimuth 
 * @return Circle 
 */
Circle Circle::fromCenterDiameter(const PointF &center, double diameter,
                                  double azimuth)
{
    return Circle(center, diameter / 2.0, azimuth);
}

/**
 * @brief 
 * 
 * @param center 
 * @param pt1 
 * @return Circle 
 */
Circle Circle::fromCenterPoint(const PointF &center, const PointF &pt1)
{
    const double azimuth =
            GeometryMath::lineAngle(center.x(), center.y(), pt1.x(), pt1.y()) *
            180.0 / M_PI;

    PointF centerPt(center);

    return Circle(centerPt, centerPt.distance(pt1), azimuth);
}

/**
 * @brief 
 * 
 * @param pt1_tg1 
 * @param pt2_tg1 
 * @param pt1_tg2 
 * @param pt2_tg2 
 * @param pt1_tg3 
 * @param pt2_tg3 
 * @param epsilon 
 * @param pos 
 * @return Circle 
 */
Circle Circle::from3Tangents(const PointF &pt1_tg1, const PointF &pt2_tg1,
                             const PointF &pt1_tg2, const PointF &pt2_tg2,
                             const PointF &pt1_tg3, const PointF &pt2_tg3,
                             double epsilon, const PointF &pos)
{
    const std::vector<Circle> circles = from3TangentsMulti(
            pt1_tg1, pt2_tg1, pt1_tg2, pt2_tg2, pt1_tg3, pt2_tg3, epsilon, pos);
    if (circles.size() != 1) return Circle();
    return circles.at(0);
}

/**
 * @brief 
 * 
 * @param pt1_tg1 
 * @param pt2_tg1 
 * @param pt1_tg2 
 * @param pt2_tg2 
 * @param pt1_tg3 
 * @param pt2_tg3 
 * @param epsilon 
 * @param pos 
 * @return std::vector<Circle> 
 */
std::vector<Circle>
Circle::from3TangentsMulti(const PointF &pt1_tg1, const PointF &pt2_tg1,
                           const PointF &pt1_tg2, const PointF &pt2_tg2,
                           const PointF &pt1_tg3, const PointF &pt2_tg3,
                           double epsilon, const PointF &pos)
{
    PointF p1, p2, p3;
    bool isIntersect_tg1tg2 = false;
    bool isIntersect_tg1tg3 = false;
    bool isIntersect_tg2tg3 = false;
    GeometryMath::segmentIntersection(pt1_tg1, pt2_tg1, pt1_tg2, pt2_tg2, p1,
                                      isIntersect_tg1tg2, epsilon);
    GeometryMath::segmentIntersection(pt1_tg1, pt2_tg1, pt1_tg3, pt2_tg3, p2,
                                      isIntersect_tg1tg3, epsilon);
    GeometryMath::segmentIntersection(pt1_tg2, pt2_tg2, pt1_tg3, pt2_tg3, p3,
                                      isIntersect_tg2tg3, epsilon);

    std::vector<Circle> circles;
    if (!isIntersect_tg1tg2 && !isIntersect_tg2tg3)// three lines are parallels
        return circles;

    if (!isIntersect_tg1tg2)
        return from2ParallelsLine(pt1_tg1, pt2_tg1, pt1_tg2, pt2_tg2, pt1_tg3,
                                  pt2_tg3, pos, epsilon);
    else if (!isIntersect_tg1tg3)
        return from2ParallelsLine(pt1_tg1, pt2_tg1, pt1_tg3, pt2_tg3, pt1_tg2,
                                  pt2_tg2, pos, epsilon);
    else if (!isIntersect_tg2tg3)
        return from2ParallelsLine(pt1_tg2, pt2_tg2, pt1_tg3, pt2_tg3, pt1_tg1,
                                  pt1_tg1, pos, epsilon);

    circles.push_back(Triangle(p1, p2, p3).inscribedCircle());
    return circles;
}

/**
 * @brief 
 * 
 * @param pt1 
 * @param pt2 
 * @return Circle 
 */
Circle Circle::fromExtent(const PointF &pt1, const PointF &pt2)
{
    const double delta_x = std::fabs(pt1.x() - pt2.x());
    const double delta_y = std::fabs(pt1.x() - pt2.y());
    if (!qIsEqual(delta_x, delta_y)) { return Circle(); }

    PointF center = GeometryMath::midpoint(pt1, pt2);
    return Circle(center, delta_x / 2.0, 0);
}

/**
 * @brief 
 * 
 * @param pt1 
 * @param pt2 
 * @param pt3 
 * @param epsilon 
 * @return Circle 
 */
Circle Circle::minimalCircleFrom3Points(const PointF &pt1, const PointF &pt2,
                                        const PointF &pt3, double epsilon)
{
    const double l1 = pt2.distance(pt3);
    const double l2 = pt3.distance(pt1);
    const double l3 = pt1.distance(pt2);

    if ((l1 * l1) - (l2 * l2 + l3 * l3) >= epsilon)
        return Circle().from2Points(pt2, pt3);
    else if ((l2 * l2) - (l1 * l1 + l3 * l3) >= epsilon)
        return Circle().from2Points(pt3, pt1);
    else if ((l3 * l3) - (l1 * l1 + l2 * l2) >= epsilon)
        return Circle().from2Points(pt1, pt2);
    else
        return Circle().from3Points(pt1, pt2, pt3, epsilon);
}

/**
 * @brief 
 * 
 * @param other 
 * @param intersection1 
 * @param intersection2 
 * @return int 
 */
int Circle::intersections(const Circle &other, PointF &intersection1,
                          PointF &intersection2) const
{
    PointF int1, int2;

    const int res = GeometryMath::circleCircleIntersections(
            PointF(m_center), radius(), PointF(other.center()), other.radius(),
            int1, int2);
    if (res == 0) return 0;

    intersection1 = PointF(int1);
    intersection2 = PointF(int2);
    return res;
}

/**
 * @brief 
 * 
 * @param p 
 * @param pt1 
 * @param pt2 
 * @return true 
 * @return false 
 */
bool Circle::tangentToPoint(const PointF &p, PointF &pt1, PointF &pt2) const
{
    return GeometryMath::tangentPointAndCircle(PointF(m_center), radius(), p,
                                               pt1, pt2);
}

/**
 * @brief 
 * 
 * @param other 
 * @param line1P1 
 * @param line1P2 
 * @param line2P1 
 * @param line2P2 
 * @return int 
 */
int Circle::outerTangents(const Circle &other, PointF &line1P1, PointF &line1P2,
                          PointF &line2P1, PointF &line2P2) const
{
    return GeometryMath::circleCircleOuterTangents(
            PointF(m_center), radius(), PointF(other.center()), other.radius(),
            line1P1, line1P2, line2P1, line2P2);
}

/**
 * @brief 
 * 
 * @param other 
 * @param line1P1 
 * @param line1P2 
 * @param line2P1 
 * @param line2P2 
 * @return int 
 */
int Circle::innerTangents(const Circle &other, PointF &line1P1, PointF &line1P2,
                          PointF &line2P1, PointF &line2P2) const
{
    return GeometryMath::circleCircleInnerTangents(
            PointF(m_center), radius(), PointF(other.center()), other.radius(),
            line1P1, line1P2, line2P1, line2P2);
}

/**
 * @brief 
 * 
 * @return double 
 */
double Circle::area() const { return M_PI * m_semiMajorAxis * m_semiMajorAxis; }

/**
 * @brief 
 * 
 * @return double 
 */
double Circle::perimeter() const { return 2.0 * M_PI * m_semiMajorAxis; }

/**
 * @brief 
 * 
 * @param semiMajorAxis 
 */
void Circle::setSemiMajorAxis(double semiMajorAxis)
{
    m_semiMajorAxis = std::fabs(semiMajorAxis);
    m_semiMinorAxis = m_semiMajorAxis;
}

/**
 * @brief 
 * 
 * @param semiMinorAxis 
 */
void Circle::setSemiMinorAxis(double semiMinorAxis)
{
    m_semiMajorAxis = std::fabs(semiMinorAxis);
    m_semiMinorAxis = m_semiMajorAxis;
}

/**
 * @brief 
 * 
 * @return double 
 */
double Circle::radius() const { return m_semiMajorAxis; }

/**
 * @brief 
 * 
 * @param radius 
 */
void Circle::setRadius(double radius)
{
    m_semiMajorAxis = std::fabs(radius);
    m_semiMinorAxis = m_semiMajorAxis;
}

/**
 * @brief 
 * 
 * @return PointSequence 
 */
PointSequence Circle::northQuadrant() const
{
    PointSequence quad;
    quad.push_back(PointF(m_center.x(), m_center.y() + m_semiMajorAxis));
    quad.push_back(PointF(m_center.x() + m_semiMajorAxis, m_center.y()));
    quad.push_back(PointF(m_center.x(), m_center.y() - m_semiMajorAxis));
    quad.push_back(PointF(m_center.x() - m_semiMajorAxis, m_center.y()));

    return quad;
}

/**
 * @brief 
 * 
 * @param point 
 * @param epsilon 
 * @return true 
 * @return false 
 */
bool Circle::contains(const PointF &point, double epsilon) const
{
    return (m_center.distance(point) <= m_semiMajorAxis + epsilon);
}

}// namespace m2
