#include <m2_bezier.h>
#include <m2_line.h>
#include <m2_point.h>
#include <m2_polygon.h>
#include <m2_rect.h>

namespace m2 {

/**
 * @brief 
 * 
 * @param p1 
 * @param p2 
 * @param p3 
 * @param p4 
 * @return Bezier 
 */
Bezier Bezier::fromPoints(const PointF &p1, const PointF &p2, const PointF &p3,
                          const PointF &p4)
{
    return Bezier();
}

/**
 * @brief 
 * 
 * @param t 
 * @param a 
 * @param b 
 * @param c 
 * @param d 
 */
void Bezier::coefficients(double t, double &a, double &b, double &c, double &d)
{
}

/**
 * @brief 
 * 
 * @param t 
 * @return PointF 
 */
PointF Bezier::pointAt(double t) const { return PointF(); }

/**
 * @brief 
 * 
 * @param t 
 * @return PointF 
 */
PointF Bezier::normalVector(double t) const { return PointF(); }

/**
 * @brief 
 * 
 * @param t 
 * @return PointF 
 */
PointF Bezier::derivedAt(double t) const { return PointF(); }

/**
 * @brief 
 * 
 * @param t 
 * @return PointF 
 */
PointF Bezier::secondDerivedAt(double t) const { return PointF(); }

/**
 * @brief 
 * 
 * @param bezier_flattening_threshold 
 * @return PolygonF 
 */
PolygonF Bezier::toPolygon(double bezier_flattening_threshold) const
{
    return PolygonF();
}

/**
 * @brief 
 * 
 * @param p 
 * @param bezier_flattening_threshold 
 */
void Bezier::addToPolygon(PolygonF *p, double bezier_flattening_threshold) const
{
}

/**
 * @brief 
 * 
 * @return RectF 
 */
RectF Bezier::bounds() const { return RectF(); }

/**
 * @brief 
 * 
 * @param error 
 * @return double 
 */
double Bezier::length(double error) const { return 0.0; }

/**
 * @brief 
 * 
 * @param length 
 * @param error 
 */
void Bezier::addIfClose(double *length, double error) const {}

/**
 * @brief 
 * 
 * @param len 
 * @return double 
 */
double Bezier::tAtLength(double len) const { return 0.0; }

/**
 * @brief 
 * 
 * @param t0 
 * @param t1 
 * @return int 
 */
int Bezier::stationaryYPoints(double &t0, double &t1) const { return 0; }

/**
 * @brief 
 * 
 * @param t0 
 * @param t1 
 * @param y 
 * @return double 
 */
double Bezier::tForY(double t0, double t1, double y) const { return 0.0; }

/**
 * @brief 
 * 
 * @return PointF 
 */
PointF Bezier::pt1() const { return PointF(); }

/**
 * @brief 
 * 
 * @return PointF 
 */
PointF Bezier::pt2() const { return PointF(); }

/**
 * @brief 
 * 
 * @return PointF 
 */
PointF Bezier::pt3() const { return PointF(); }

/**
 * @brief 
 * 
 * @return PointF 
 */
PointF Bezier::pt4() const { return PointF(); }

/**
 * @brief 
 * 
 * @return PointF 
 */
PointF Bezier::midPoint() const { return PointF(); }

/**
 * @brief 
 * 
 * @return LineF 
 */
LineF Bezier::midTangent() const { return LineF(); }

/**
 * @brief 
 * 
 * @return LineF 
 */
LineF Bezier::startTangent() const { return LineF(); }

/**
 * @brief 
 * 
 * @return LineF 
 */
LineF Bezier::endTangent() const { return LineF(); }

/**
 * @brief 
 * 
 * @param t 
 * @param left 
 */
void Bezier::parameterSplitLeft(double t, Bezier *left) {}

/**
 * @brief 
 * 
 * @return std::pair<Bezier, Bezier> 
 */
std::pair<Bezier, Bezier> Bezier::split() const
{
    return std::pair<Bezier, Bezier>();
}

/**
 * @brief 
 * 
 * @param curveSegments 
 * @param maxSegmets 
 * @param offset 
 * @param threshold 
 * @return int 
 */
int Bezier::shifted(Bezier *curveSegments, int maxSegmets, double offset,
                    float threshold) const
{
    return 0;
}

/**
 * @brief 
 * 
 * @param t0 
 * @param t1 
 * @return Bezier 
 */
Bezier Bezier::bezierOnInterval(double t0, double t1) const { return Bezier(); }

/**
 * @brief 
 * 
 * @param t0 
 * @param t1 
 * @return Bezier 
 */
Bezier Bezier::getSubRange(double t0, double t1) const { return Bezier(); }

}// namespace m2