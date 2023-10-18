#include <m2_ellipse.h>
#include <m2_geometrymath.h>
#include <m2_math.h>
#include <m2_polygon.h>
#include <m2_rect.h>

namespace m2 {

/**
 * @brief Construct a new Ellipse:: Ellipse object
 * 
 */
Ellipse::Ellipse() : m_azimuth(90.0), m_semiMajorAxis(0.0), m_semiMinorAxis(0.0)
{
}

/**
 * @brief Construct a new Ellipse:: Ellipse object
 * 
 */
Ellipse::Ellipse(const Ellipse &other)
    : m_azimuth(other.m_azimuth), m_semiMajorAxis(other.m_semiMajorAxis),
      m_semiMinorAxis(other.m_semiMinorAxis)
{
}

/**
 * @brief 
 * 
 * @return Ellipse& 
 */
Ellipse &Ellipse::operator=(const Ellipse &other)
{
    m_azimuth = other.m_azimuth;
    m_semiMajorAxis = other.m_semiMajorAxis;
    m_semiMinorAxis = other.m_semiMinorAxis;
}

/**
 * @brief Construct a new Ellipse:: Ellipse object
 * 
 */
Ellipse::Ellipse(Ellipse &&other) noexcept
{
    m_azimuth = other.m_azimuth;
    m_semiMajorAxis = other.m_semiMajorAxis;
    m_semiMinorAxis = other.m_semiMinorAxis;
}

/**
 * @brief 
 * 
 * @return Ellipse& 
 */
Ellipse &Ellipse::operator=(Ellipse &&other) noexcept
{
    m_azimuth = other.m_azimuth;
    m_semiMajorAxis = other.m_semiMajorAxis;
    m_semiMinorAxis = other.m_semiMinorAxis;
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
    : m_center(center), m_azimuth(azimuth), m_semiMajorAxis(semiMajorAxis),
      m_semiMinorAxis(semiMinorAxis)
{
    normalizeAxis();
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
    const double dist_p1p2 = pt1.distance(pt2);
    const double dist_p1p3 = pt1.distance(pt3);
    const double dist_p2p3 = pt2.distance(pt3);

    const double dist = dist_p1p3 + dist_p2p3;
    const double azimuth =
            180.0 / M_PI *
            GeometryMath::lineAngle(pt1.x(), pt1.y(), pt2.x(), pt2.y());
    PointF center = GeometryMath::midpoint(pt1, pt2);

    const double axis_a = dist / 2.0;
    const double axis_b =
            std::sqrt(std::pow(axis_a, 2.0) - std::pow(dist_p1p2 / 2.0, 2.0));

    return Ellipse(center, axis_a, axis_b, azimuth);
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
    PointF center = GeometryMath::midpoint(pt1, pt2);
    const double axis_a = std::fabs(pt2.x() - pt1.x()) / 2.0;
    const double axis_b = std::fabs(pt2.y() - pt1.y()) / 2.0;
    const double azimuth = 90.0;

    return Ellipse(center, axis_a, axis_b, azimuth);
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
    const double axis_a = std::fabs(pt1.x() - ptc.x());
    const double axis_b = std::fabs(pt1.y() - ptc.y());
    const double azimuth = 90.0;

    PointF centerPt(ptc);

    return Ellipse(centerPt, axis_a, axis_b, azimuth);
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
    const double azimuth =
            180.0 / M_PI *
            GeometryMath::lineAngle(ptc.x(), ptc.y(), pt1.x(), pt1.y());
    const double axis_a = ptc.distance(pt1);

    const double length =
            pt2.distance(GeometryMath::projectPointOnSegment(pt2, ptc, pt1));
    const PointF pp = ptc.project(length, 90 + azimuth);
    const double axis_b = ptc.distance(pp);

    PointF centerPt(ptc);

    return Ellipse(centerPt, axis_a, axis_b, azimuth);
}

/**
 * @brief 
 * 
 * @param elp 
 * @return true 
 * @return false 
 */
bool Ellipse::operator==(const Ellipse &elp) const
{
    return ((m_center == elp.m_center) &&
            qIsEqual(m_semiMajorAxis, elp.m_semiMajorAxis,
                     std::numeric_limits<double>::epsilon()) &&
            qIsEqual(m_semiMinorAxis, elp.m_semiMinorAxis,
                     std::numeric_limits<double>::epsilon()) &&
            qIsEqual(m_azimuth, elp.m_azimuth,
                     std::numeric_limits<double>::epsilon()));
}

/**
 * @brief 
 * 
 * @param elp 
 * @return true 
 * @return false 
 */
bool Ellipse::operator!=(const Ellipse &elp) const { return !operator==(elp); }

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool Ellipse::isEmpty() const
{
    return (qIsEqual(m_semiMajorAxis, 0.0,
                     std::numeric_limits<double>::epsilon()) ||
            qIsEqual(m_semiMinorAxis, 0.0,
                     std::numeric_limits<double>::epsilon()));
}

/**
 * @brief 
 * 
 * @return PointF 
 */
PointF Ellipse::center() const { return m_center; }

/**
 * @brief 
 * 
 * @return double 
 */
double Ellipse::semiMajorAxis() const { return m_semiMajorAxis; }

/**
 * @brief 
 * 
 * @return double 
 */
double Ellipse::semiMinorAxis() const { return m_semiMinorAxis; }

/**
 * @brief 
 * 
 * @return double 
 */
double Ellipse::azimuth() const { return m_azimuth; }

/**
 * @brief 
 * 
 * @param center 
 */
void Ellipse::setCenter(const PointF &center) { m_center = center; }

/**
 * @brief 
 * 
 * @param semiMajorAxis 
 */
void Ellipse::setSemiMajorAxis(double semiMajorAxis)
{
    m_semiMajorAxis = semiMajorAxis;
    normalizeAxis();
}

/**
 * @brief 
 * 
 * @param semiMinorAxis 
 */
void Ellipse::setSemiMinorAxis(double semiMinorAxis)
{
    m_semiMinorAxis = semiMinorAxis;
    normalizeAxis();
}

/**
 * @brief 
 * 
 * @param azimuth 
 */
void Ellipse::setAzimuth(double azimuth)
{
    m_azimuth = 180.0 / M_PI *
                GeometryMath::normalizedAngle(M_PI / 180.0 * azimuth);
}

/**
 * @brief 
 * 
 * @return double 
 */
double Ellipse::focusDistance() const
{
    return std::sqrt(m_semiMajorAxis * m_semiMajorAxis -
                     m_semiMinorAxis * m_semiMinorAxis);
}

/**
 * @brief 
 * 
 * @param f1 
 * @param f2 
 * @return true 
 * @return false 
 */
bool Ellipse::foci(PointF &f1, PointF &f2) const
{
    const double dist_focus = focusDistance();
    f1 = m_center.project(dist_focus, m_azimuth);
    f2 = m_center.project(-dist_focus, m_azimuth);
    return true;
}

/**
 * @brief 
 * 
 * @return double 
 */
double Ellipse::eccentricity() const
{
    if (isEmpty()) { return std::numeric_limits<double>::quiet_NaN(); }
    return focusDistance() / m_semiMajorAxis;
}

/**
 * @brief 
 * 
 * @return double 
 */
double Ellipse::area() const
{
    return M_PI * m_semiMajorAxis * m_semiMinorAxis;
}

/**
 * @brief 
 * 
 * @return double 
 */
double Ellipse::perimeter() const
{
    const double a = m_semiMajorAxis;
    const double b = m_semiMinorAxis;
    return M_PI * (3 * (a + b) - std::sqrt(10 * a * b + 3 * (a * a + b * b)));
}

/**
 * @brief 
 * 
 * @return PointSequence 
 */
PointSequence Ellipse::quadrant() const
{
    PointSequence quad;
    quad.push_back(m_center.project(m_semiMajorAxis, m_azimuth));
    quad.push_back(m_center.project(m_semiMinorAxis, m_azimuth + 90));
    quad.push_back(m_center.project(-m_semiMajorAxis, m_azimuth));
    quad.push_back(m_center.project(-m_semiMinorAxis, m_azimuth + 90));

    return quad;
}

/**
 * @brief 
 * 
 * @param segments 
 * @return PointSequence 
 */
PointSequence Ellipse::points(unsigned int segments) const
{
    PointSequence pts;

    if (segments < 3) { return pts; }

    std::vector<double> t;
    t.reserve(segments);
    const double azimuth = std::atan2(quadrant().at(0).y() - m_center.y(),
                                      quadrant().at(0).x() - m_center.x());
    for (unsigned int i = 0; i < segments; ++i)
    {
        t.push_back(2 * M_PI - ((2 * M_PI) / segments * i));
    }

    for (std::vector<double>::const_iterator it = t.cbegin(); it != t.cend();
         ++it)
    {
        const double x = m_center.x() +
                         m_semiMajorAxis * std::cos(*it) * std::cos(azimuth) -
                         m_semiMinorAxis * std::sin(*it) * std::sin(azimuth);
        const double y = m_center.y() +
                         m_semiMajorAxis * std::cos(*it) * std::sin(azimuth) +
                         m_semiMinorAxis * std::sin(*it) * std::cos(azimuth);
        pts.push_back(PointF(x, y));
    }

    return pts;
}

/**
 * @brief 
 * 
 * @param segments 
 * @return PolygonF 
 */
PolygonF Ellipse::toPolygon(unsigned int segments) const
{
    if (segments < 3) { return PolygonF(); }

    PointSequence pts;
    pts = points(segments);
    pts.push_back(pts.at(0));

    return static_cast<PolygonF>(pts);
}

/**
 * @brief 
 * 
 * @return PolygonF 
 */
PolygonF Ellipse::orientedBoundingBox() const
{
    if (isEmpty()) { return PolygonF(); }

    PolygonF polygon;

    const std::vector<PointF> q = quadrant();

    const PointF p1 = q.at(0).project(m_semiMinorAxis, m_azimuth - 90);
    const PointF p2 = q.at(0).project(m_semiMinorAxis, m_azimuth + 90);
    const PointF p3 = q.at(2).project(m_semiMinorAxis, m_azimuth + 90);
    const PointF p4 = q.at(2).project(m_semiMinorAxis, m_azimuth - 90);

    polygon.push_back(p1);
    polygon.push_back(p2);
    polygon.push_back(p3);
    polygon.push_back(p4);
    polygon.push_back(p1);
    return polygon;
}

/**
 * @brief 
 * 
 * @return RectF 
 */
RectF Ellipse::boundingBox() const
{
    if (isEmpty()) { return RectF(); }

    const double angle = m_azimuth * M_PI / 180.0;

    const double ux = m_semiMajorAxis * std::cos(angle);
    const double uy = m_semiMinorAxis * std::sin(angle);
    const double vx = m_semiMajorAxis * std::sin(angle);
    const double vy = m_semiMinorAxis * std::cos(angle);

    const double halfHeight = std::sqrt(ux * ux + uy * uy);
    const double halfWidth = std::sqrt(vx * vx + vy * vy);

    const PointF p1(m_center.x() - halfWidth, m_center.y() - halfHeight);
    const PointF p2(m_center.x() + halfWidth, m_center.y() + halfHeight);

    return RectF(p1, p2);
}

/**
 * @brief 
 */
void Ellipse::normalizeAxis()
{
    m_semiMajorAxis = std::fabs(m_semiMajorAxis);
    m_semiMinorAxis = std::fabs(m_semiMinorAxis);
    if (m_semiMajorAxis < m_semiMinorAxis)
    {
        std::swap(m_semiMajorAxis, m_semiMinorAxis);
        m_azimuth =
                180.0 / M_PI *
                GeometryMath::normalizedAngle(M_PI / 180.0 * (m_azimuth + 90));
    }
}

}// namespace m2
