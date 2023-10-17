#include <m2_line.h>
#include <m2_math.h>

namespace m2 {

LineF LineF::fromPolar(double length, double angle)
{
    const double angleR = degreesToRadians(angle);
    return LineF(0, 0, qCos(angleR) * length, -qSin(angleR) * length);
}

double LineF::length() const
{
    double len = dx() * dx() + dy() * dy();
    return std::sqrt(len);
}

void LineF::setLength(double len)
{
    assert(std::isfinite(len));
    const double oldLength = length();
    assert(std::isfinite(oldLength));
    if (oldLength > 0)
        pt2 = PointF(pt1.x() + len * (dx() / oldLength),
                     pt1.y() + len * (dy() / oldLength));
}

double LineF::angle() const
{
    const double dx = pt2.x() - pt1.x();
    const double dy = pt2.y() - pt1.y();

    const double theta = radiansToDegrees(qAtan2(-dy, dx));

    const double theta_normalized = theta < 0 ? theta + 360 : theta;

    if (qFuzzyCompare(theta_normalized, double(360))) return double(0);
    else
        return theta_normalized;
}

void LineF::setAngle(double angle)
{
    const double angleR = degreesToRadians(angle);
    const double l = length();

    const double dx = qCos(angleR) * l;
    const double dy = -qSin(angleR) * l;

    pt2.rx() = pt1.x() + dx;
    pt2.ry() = pt1.y() + dy;
}

double LineF::angleTo(const LineF &l) const
{
    if (isNull() || l.isNull()) return 0;

    const double a1 = angle();
    const double a2 = l.angle();

    const double delta = a2 - a1;
    const double delta_normalized = delta < 0 ? delta + 360 : delta;

    if (qFuzzyCompare(delta, double(360))) return 0;
    else
        return delta_normalized;
}

LineF LineF::unitVector() const
{
    const double x = dx();
    const double y = dy();

    const double len = std::sqrt(double(dx()) * double(dx()) +
                                 double(dy()) * double(dy()));
    LineF f(p1(), PointF(pt1.x() + x / len, pt1.y() + y / len));

    return f;
}

LineF LineF::normalVector() const
{
    return LineF(p1(), p1() + PointF(dy(), -dx()));
}

LineF::IntersectionType LineF::intersects(const LineF &l,
                                          PointF *intersectionPoint) const
{
    const PointF a = pt2 - pt1;
    const PointF b = l.pt1 - l.pt2;
    const PointF c = pt1 - l.pt1;

    const double denominator = a.y() * b.x() - a.x() * b.y();
    if (denominator == 0 || !std::isfinite(denominator)) return NoIntersection;

    const double reciprocal = 1 / denominator;
    const double na = (b.y() * c.x() - b.x() * c.y()) * reciprocal;
    if (intersectionPoint) *intersectionPoint = pt1 + a * na;

    if (na < 0 || na > 1) return UnboundedIntersection;

    const double nb = (a.x() * c.y() - a.y() * c.x()) * reciprocal;
    if (nb < 0 || nb > 1) return UnboundedIntersection;

    return BoundedIntersection;
}

}// namespace m2
