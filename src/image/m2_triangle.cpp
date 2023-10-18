#include <m2_circle.h>
#include <m2_geometrymath.h>
#include <m2_triangle.h>

namespace m2 {

/**
 * @brief Construct a new Triangle:: Triangle object
 * 
 */
Triangle::Triangle() {}

/**
 * @brief Construct a new Triangle:: Triangle object
 * 
 * @param p1 
 * @param p2 
 * @param p3 
 */
Triangle::Triangle(const PointF &p1, const PointF &p2, const PointF &p3)
{
    m_points[0] = p1;
    m_points[1] = p2;
    m_points[2] = p3;
}

/**
 * @brief Construct a new Triangle:: Triangle object
 * 
 * @param other 
 */
Triangle::Triangle(const Triangle &other)
{
    m_points[0] = other.m_points[0];
    m_points[1] = other.m_points[1];
    m_points[2] = other.m_points[2];
}

/**
 * @brief 
 * 
 * @param other 
 * @return Triangle& 
 */
Triangle &Triangle::operator=(const Triangle &other)
{
    m_points[0] = other.m_points[0];
    m_points[1] = other.m_points[1];
    m_points[2] = other.m_points[2];
}

/**
 * @brief 
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Triangle::operator==(const Triangle &other) const
{
    return m_points[0] == other.m_points[0] &&
           m_points[1] == other.m_points[1] && m_points[2] == other.m_points[2];
}

/**
 * @brief 
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Triangle::operator!=(const Triangle &other) const
{
    return !operator==(other);
}

bool Triangle::isEmpty() const {}

/**
 * @brief 
 * 
 * @return std::vector<double> 
 */
std::vector<double> Triangle::lengths() const
{
    std::vector<double> lengths;
    if (isEmpty()) return lengths;

    lengths.push_back(m_points[0].distance(m_points[1]));// c = |AB|
    lengths.push_back(m_points[1].distance(m_points[2]));// a = |BC|
    lengths.push_back(m_points[0].distance(m_points[2]));// b = |AC|

    return lengths;
}

/**
 * @brief 
 * 
 * @return std::vector<double> 
 */
std::vector<double> Triangle::angles() const
{
    std::vector<double> angles;
    if (isEmpty()) return angles;

    std::vector<double> l = lengths();

    const double a = l[1];
    const double b = l[2];
    const double c = l[0];

    const double a2 = a * a;
    const double b2 = b * b;
    const double c2 = c * c;

    const double alpha = acos((b2 + c2 - a2) / (2 * b * c));
    const double beta = acos((a2 + c2 - b2) / (2 * a * c));
    const double gamma =
            M_PI - alpha -
            beta;// acos((a2 + b2 - c2)/(2*a*b)); but ensure that alpha+beta+gamma = 180.0

    angles.push_back(alpha);
    angles.push_back(beta);
    angles.push_back(gamma);

    return angles;
}

/**
 * @brief 
 * @return double 
 */
double Triangle::area() const
{
    return 0.5 * (m_points[0].x() * m_points[1].y() +
                  m_points[1].x() * m_points[2].y() +
                  m_points[2].x() * m_points[0].y() -
                  m_points[0].x() * m_points[2].y() -
                  m_points[1].x() * m_points[0].y() -
                  m_points[2].x() * m_points[1].y());
}

/**
 * @brief 
 * @return double 
 */
double Triangle::perimeter() const
{
    double per = 0;

    per += m_points[0].distance(m_points[1]);// c = |AB|
    per += m_points[1].distance(m_points[2]);// a = |BC|
    per += m_points[0].distance(m_points[2]);// b = |AC|

    return per;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool Triangle::isDegenerate() const
{
    if (isEmpty()) return true;

    const PointF p1(m_points[0]);
    const PointF p2(m_points[1]);
    const PointF p3(m_points[2]);
    return (((p1 == p2) || (p1 == p3) || (p2 == p3)) ||
            GeometryMath::leftOfLine(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(),
                                     p3.y()) == 0);
}

/**
 * @brief 
 * 
 * @param lengthTolerance 
 * @return true 
 * @return false 
 */
bool Triangle::isIsocele(double lengthTolerance) const
{
    if (isEmpty()) return false;
    const std::vector<double> sides = lengths();
    const bool ab_bc = qIsEqual(sides.at(0), sides.at(1), lengthTolerance);
    const bool bc_ca = qIsEqual(sides.at(1), sides.at(2), lengthTolerance);
    const bool ca_ab = qIsEqual(sides.at(2), sides.at(0), lengthTolerance);

    return (ab_bc || bc_ca || ca_ab);
}

/**
 * @brief 
 * 
 * @param lengthTolerance 
 * @return true 
 * @return false 
 */
bool Triangle::isEquilateral(double lengthTolerance) const
{
    if (isEmpty()) return false;
    const std::vector<double> sides = lengths();
    const bool ab_bc = qIsEqual(sides.at(0), sides.at(1), lengthTolerance);
    const bool bc_ca = qIsEqual(sides.at(1), sides.at(2), lengthTolerance);
    const bool ca_ab = qIsEqual(sides.at(2), sides.at(0), lengthTolerance);

    return (ab_bc && bc_ca && ca_ab);
}

/**
 * @brief 
 * 
 * @param angleTolerance 
 * @return true 
 * @return false 
 */
bool Triangle::isRight(double angleTolerance) const
{
    if (isEmpty()) return false;
    std::vector<double> a = angles();
    std::vector<double>::iterator ita = a.begin();
    while (ita != a.end())
    {
        if (qIsEqual(*ita, M_PI_2, angleTolerance)) return true;
        ++ita;
    }
    return false;
}

/**
 * @brief 
 * 
 * @param lengthTolerance 
 * @return true 
 * @return false 
 */
bool Triangle::isScalene(double lengthTolerance) const
{
    if (isEmpty()) return false;
    return !isIsocele(lengthTolerance);
}

/**
 * @brief 
 * 
 * @return std::vector<LineF> 
 */
std::vector<LineF> Triangle::altitudes() const
{
    std::vector<LineF> alt;
    if (isEmpty()) return alt;

    alt.push_back(GeometryMath::perpendicularSegment(m_points[0], m_points[2],
                                                     m_points[1]));
    alt.push_back(GeometryMath::perpendicularSegment(m_points[1], m_points[0],
                                                     m_points[2]));
    alt.push_back(GeometryMath::perpendicularSegment(m_points[2], m_points[0],
                                                     m_points[1]));

    return alt;
}

/**
 * @brief 
 * 
 * @return std::vector<LineF> 
 */
std::vector<LineF> Triangle::medians() const
{
    std::vector<LineF> med;
    if (isEmpty()) return med;

    LineF med1;
    LineF med2;
    LineF med3;
    med1.setPoints(m_points[0],
                   GeometryMath::midpoint(m_points[1], m_points[2]));
    med2.setPoints(m_points[1],
                   GeometryMath::midpoint(m_points[0], m_points[2]));
    med3.setPoints(m_points[2],
                   GeometryMath::midpoint(m_points[0], m_points[1]));
    med.push_back(med1);
    med.push_back(med2);
    med.push_back(med3);

    return med;
}

/**
 * @brief 
 * 
 * @param lengthTolerance 
 * @return std::vector<LineF> 
 */
std::vector<LineF> Triangle::bisectors(double lengthTolerance) const
{
    std::vector<LineF> bis;
    if (isEmpty()) return bis;

    LineF bis1;
    LineF bis2;
    LineF bis3;
    const PointF incenter = inscribedCenter();
    PointF out;
    bool intersection = false;

    GeometryMath::segmentIntersection(m_points[0], incenter, m_points[1],
                                      m_points[2], out, intersection,
                                      lengthTolerance);
    bis1.setPoints(m_points[0], out);

    GeometryMath::segmentIntersection(m_points[1], incenter, m_points[0],
                                      m_points[2], out, intersection,
                                      lengthTolerance);
    bis2.setPoints(m_points[1], out);

    GeometryMath::segmentIntersection(m_points[2], incenter, m_points[0],
                                      m_points[1], out, intersection,
                                      lengthTolerance);
    bis3.setPoints(m_points[2], out);

    bis.push_back(bis1);
    bis.push_back(bis2);
    bis.push_back(bis3);

    return bis;
}

/**
 * @brief 
 * 
 * @return Triangle 
 */
Triangle Triangle::medial() const
{
    if (isEmpty()) return Triangle();
    PointF p1, p2, p3;
    p1 = GeometryMath::midpoint(m_points[0], m_points[1]);
    p2 = GeometryMath::midpoint(m_points[1], m_points[2]);
    p3 = GeometryMath::midpoint(m_points[2], m_points[0]);
    return Triangle(p1, p2, p3);
}

/**
 * @brief 
 * 
 * @param lengthTolerance 
 * @return PointF 
 */
PointF Triangle::orthocenter(double lengthTolerance) const
{
    if (isEmpty()) return PointF();
    const std::vector<LineF> alt = altitudes();
    PointF ortho;
    bool intersection;
    GeometryMath::segmentIntersection(alt.at(0).p1(), alt.at(0).p2(),
                                      alt.at(1).p1(), alt.at(1).p2(), ortho,
                                      intersection, lengthTolerance);

    return ortho;
}

/**
 * @brief 
 * 
 * @return PointF 
 */
PointF Triangle::circumscribedCenter() const
{
    if (isEmpty()) return PointF();
    double r, x, y;
    GeometryMath::circleCenterRadius(m_points[0], m_points[1], m_points[2], r,
                                     x, y);
    return PointF(x, y);
}

/**
 * @brief 
 * 
 * @return double 
 */
double Triangle::circumscribedRadius() const
{
    if (isEmpty()) return 0.0;
    double r, x, y;
    GeometryMath::circleCenterRadius(m_points[0], m_points[1], m_points[2], r,
                                     x, y);
    return r;
}

/**
 * @brief 
 * 
 * @return Circle 
 */
Circle Triangle::circumscribedCircle() const
{
    if (isEmpty()) return Circle();
    return Circle(circumscribedCenter(), circumscribedRadius());
}

/**
 * @brief 
 * 
 * @return PointF 
 */
PointF Triangle::inscribedCenter() const
{
    if (isEmpty()) return PointF();

    const std::vector<double> l = lengths();
    const double x = (l.at(0) * m_points[2].x() + l.at(1) * m_points[0].x() +
                      l.at(2) * m_points[1].x()) /
                     perimeter();
    const double y = (l.at(0) * m_points[2].y() + l.at(1) * m_points[0].y() +
                      l.at(2) * m_points[1].y()) /
                     perimeter();

    PointF center(x, y);

    return center;
}

/**
 * @brief 
 * 
 * @return double 
 */
double Triangle::inscribedRadius() const
{
    if (isEmpty()) return 0.0;
    return (2.0 * area() / perimeter());
}

/**
 * @brief 
 * 
 * @return Circle 
 */
Circle Triangle::inscribedCircle() const
{
    if (isEmpty()) return Circle();
    return Circle(inscribedCenter(), inscribedRadius());
}

}// namespace m2