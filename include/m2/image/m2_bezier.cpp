#include <m2_bezier.h>
#include <m2_point.h>
#include <m2_polygon.h>

namespace m2 {

Bezier Bezier::fromPoints(const PointF &p1, const PointF &p2, const PointF &p3,
                          const PointF &p4)
{
    return Bezier();
}

void Bezier::coefficients(double t, double &a, double &b, double &c, double &d)
{
}

inline PointF Bezier::pointAt(double t) const { return PointF(); }

inline PointF Bezier::normalVector(double t) const { return PointF(); }

inline PointF Bezier::derivedAt(double t) const { return PointF(); }

/**
 * @brief 
 * @param  t                
 * @return PointF 
 */
inline PointF Bezier::secondDerivedAt(double t) const { return PointF(); }

PolygonF Bezier::toPolygon(double bezier_flattening_threshold) const
{
    return PolygonF();
}

void Bezier::addToPolygon(PolygonF *p, double bezier_flattening_threshold) const
{
}

RectF Bezier::bounds() const { return RectF(); }

double Bezier::length(double error) const { return 0.0; }

void Bezier::addIfClose(double *length, double error) const {}

double Bezier::tAtLength(double len) const { return 0.0; }

int Bezier::stationaryYPoints(double &t0, double &t1) const { return 0; }

double Bezier::tForY(double t0, double t1, double y) const { return 0.0; }

inline PointF Bezier::midPoint() const { return PointF(); }

inline LineF Bezier::midTangent() const { return LineF(); }

inline LineF Bezier::startTangent() const { return LineF(); }

inline LineF Bezier::endTangent() const { return LineF(); }

}// namespace m2
