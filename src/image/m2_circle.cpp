#include <m2_circle.h>

namespace m2 {

/**
 * @brief Construct a new Circle:: Circle object
 * 
 */
Circle::Circle() {}

/**
 * @brief Construct a new Circle:: Circle object
 * 
 * @param center 
 * @param radius 
 * @param azimuth 
 */
Circle::Circle(const PointF &center, double radius, double azimuth) {}

/**
 * @brief 
 * 
 * @param pt1 
 * @param pt2 
 * @return Circle 
 */
Circle Circle::from2Points(const PointF &pt1, const PointF &pt2)
{
    return Circle();
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
    return Circle();
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
    return Circle();
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
    return Circle();
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
    return Circle();
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
    return std::vector<Circle>();
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
    return Circle();
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
    return Circle();
}

/**
 * @brief 
 * 
 * @param other 
 * @param intersection1 
 * @param intersection2 
 * @param useZ 
 * @return int 
 */
int Circle::intersections(const Circle &other, PointF &intersection1,
                          PointF &intersection2, bool useZ) const
{
    return 0;
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
    return false;
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
    return 0;
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
    return 0;
}

/**
 * @brief 
 * 
 * @return double 
 */
double Circle::area() const { return 0.0; }

/**
 * @brief 
 * 
 * @return double 
 */
double Circle::perimeter() const { return 0.0; }

/**
 * @brief 
 * 
 * @param semiMajorAxis 
 */
void Circle::setSemiMajorAxis(double semiMajorAxis) {}

/**
 * @brief 
 * 
 * @param semiMinorAxis 
 */
void Circle::setSemiMinorAxis(double semiMinorAxis) {}

/**
 * @brief 
 * 
 * @return double 
 */
double Circle::radius() const { return 0.0; }

/**
 * @brief 
 * 
 * @param radius 
 */
void Circle::setRadius(double radius) {}

/**
 * @brief 
 * 
 * @return PointSequence 
 */
PointSequence Circle::northQuadrant() const { return PointSequence(); }

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
    return false;
}

}// namespace m2
