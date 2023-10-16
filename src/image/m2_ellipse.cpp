#include <m2_ellipse.h>
#include <m2_polygon.h>
#include <m2_rect.h>

namespace m2 {

/**
 * @brief Construct a new Ellipse:: Ellipse object
 * 
 */
Ellipse::Ellipse() {}

/**
 * @brief Construct a new Ellipse:: Ellipse object
 * 
 */
Ellipse::Ellipse(const Ellipse &) {}

/**
 * @brief 
 * 
 * @return Ellipse& 
 */
Ellipse &Ellipse::operator=(const Ellipse &)
{
    // TODO: insert return statement here
}

/**
 * @brief Construct a new Ellipse:: Ellipse object
 * 
 */
Ellipse::Ellipse(Ellipse &&) noexcept {}

/**
 * @brief 
 * 
 * @return Ellipse& 
 */
Ellipse &Ellipse::operator=(Ellipse &&) noexcept
{
    // TODO: insert return statement here
}

/**
 * @brief Construct a new Ellipse:: Ellipse object
 * 
 * @param center 
 * @param semiMajorAxis 
 * @param semiMinorAxis 
 * @param azimuth 
 */
Ellipse::Ellipse(const PointF &center, double semiMajorAxis,
                 double semiMinorAxis, double azimuth)
{
}

/**
 * @brief Destroy the Ellipse:: Ellipse object
 * 
 */
Ellipse::~Ellipse() {}

/**
 * @brief 
 * 
 * @param pt1 
 * @param pt2 
 * @param pt3 
 * @return Ellipse 
 */
Ellipse Ellipse::fromFoci(const PointF &pt1, const PointF &pt2,
                          const PointF &pt3)
{
    return Ellipse();
}

/**
 * @brief 
 * 
 * @param pt1 
 * @param pt2 
 * @return Ellipse 
 */
Ellipse Ellipse::fromExtent(const PointF &pt1, const PointF &pt2)
{
    return Ellipse();
}

/**
 * @brief 
 * 
 * @param ptc 
 * @param pt1 
 * @return Ellipse 
 */
Ellipse Ellipse::fromCenterPoint(const PointF &ptc, const PointF &pt1)
{
    return Ellipse();
}

/**
 * @brief 
 * 
 * @param ptc 
 * @param pt1 
 * @param pt2 
 * @return Ellipse 
 */
Ellipse Ellipse::fromCenter2Points(const PointF &ptc, const PointF &pt1,
                                   const PointF &pt2)
{
    return Ellipse();
}

/**
 * @brief 
 * 
 * @param elp 
 * @return true 
 * @return false 
 */
bool Ellipse::operator==(const Ellipse &elp) const { return false; }

/**
 * @brief 
 * 
 * @param elp 
 * @return true 
 * @return false 
 */
bool Ellipse::operator!=(const Ellipse &elp) const { return false; }

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool Ellipse::isEmpty() const { return false; }

/**
 * @brief 
 * 
 * @return PointF 
 */
PointF Ellipse::center() const { return PointF(); }

/**
 * @brief 
 * 
 * @return double 
 */
double Ellipse::semiMajorAxis() const { return 0.0; }

/**
 * @brief 
 * 
 * @return double 
 */
double Ellipse::semiMinorAxis() const { return 0.0; }

/**
 * @brief 
 * 
 * @return double 
 */
double Ellipse::azimuth() const { return 0.0; }

/**
 * @brief 
 * 
 * @param center 
 */
void Ellipse::setCenter(const PointF &center) {}

/**
 * @brief 
 * 
 * @param semiMajorAxis 
 */
void Ellipse::setSemiMajorAxis(double semiMajorAxis) {}

/**
 * @brief 
 * 
 * @param semiMinorAxis 
 */
void Ellipse::setSemiMinorAxis(double semiMinorAxis) {}

/**
 * @brief 
 * 
 * @param azimuth 
 */
void Ellipse::setAzimuth(double azimuth) {}

/**
 * @brief 
 * 
 * @return double 
 */
double Ellipse::focusDistance() const { return 0.0; }

/**
 * @brief 
 * 
 * @param f1 
 * @param f2 
 * @return true 
 * @return false 
 */
bool Ellipse::foci(PointF &f1, PointF &f2) const { return false; }

/**
 * @brief 
 * 
 * @return double 
 */
double Ellipse::eccentricity() const { return 0.0; }

/**
 * @brief 
 * 
 * @return double 
 */
double Ellipse::area() const { return 0.0; }

/**
 * @brief 
 * 
 * @return double 
 */
double Ellipse::perimeter() const { return 0.0; }

/**
 * @brief 
 * 
 * @return PointSequence 
 */
PointSequence Ellipse::quadrant() const { return PointSequence(); }

/**
 * @brief 
 * 
 * @param segments 
 * @return PointSequence 
 */
PointSequence Ellipse::points(unsigned int segments) const
{
    return PointSequence();
}

/**
 * @brief 
 * 
 * @param segments 
 * @return PolygonF 
 */
PolygonF Ellipse::toPolygon(unsigned int segments) const { return PolygonF(); }

/**
 * @brief 
 * 
 * @return PolygonF 
 */
PolygonF Ellipse::orientedBoundingBox() const { return PolygonF(); }

/**
 * @brief 
 * 
 * @return RectF 
 */
RectF Ellipse::boundingBox() const { return RectF(); }

}// namespace m2
