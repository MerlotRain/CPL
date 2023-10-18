#include <m2_line.h>
#include <m2_math.h>

namespace m2 {


/*******************************************************************************
 * class Line  members
 *******************************************************************************/

Line::Line() noexcept {}

Line::Line(const Point &pt1_, const Point &pt2_) noexcept : pt1(pt1_), pt2(pt2_)
{
}

Line::Line(int x1pos, int y1pos, int x2pos, int y2pos) noexcept
    : pt1(Point(x1pos, y1pos)), pt2(Point(x2pos, y2pos))
{
}

bool Line::isNull() const noexcept { return pt1 == pt2; }

int Line::x1() const noexcept { return pt1.x(); }

int Line::y1() const noexcept { return pt1.y(); }

int Line::x2() const noexcept { return pt2.x(); }

int Line::y2() const noexcept { return pt2.y(); }

Point Line::p1() const noexcept { return pt1; }

Point Line::p2() const noexcept { return pt2; }

int Line::dx() const noexcept { return pt2.x() - pt1.x(); }

int Line::dy() const noexcept { return pt2.y() - pt1.y(); }

void Line::translate(const Point &point) noexcept
{
    pt1 += point;
    pt2 += point;
}

void Line::translate(int adx, int ady) noexcept
{
    this->translate(Point(adx, ady));
}

Line Line::translated(const Point &p) const noexcept
{
    return Line(pt1 + p, pt2 + p);
}

Line Line::translated(int adx, int ady) const noexcept
{
    return translated(Point(adx, ady));
}

Point Line::center() const noexcept
{
    return Point(int((int64_t(pt1.x()) + pt2.x()) / 2),
                 int((int64_t(pt1.y()) + pt2.y()) / 2));
}

void Line::setP1(const Point &aP1) noexcept { pt1 = aP1; }

void Line::setP2(const Point &aP2) noexcept { pt2 = aP2; }

void Line::setPoints(const Point &aP1, const Point &aP2) noexcept
{
    pt1 = aP1;
    pt2 = aP2;
}

void Line::setLine(int aX1, int aY1, int aX2, int aY2) noexcept
{
    pt1 = Point(aX1, aY1);
    pt2 = Point(aX2, aY2);
}

bool Line::operator==(const Line &d) const noexcept
{
    return pt1 == d.pt1 && pt2 == d.pt2;
}


/*******************************************************************************
 * class LineF  members
 *******************************************************************************/

LineF::LineF() noexcept {}

LineF::LineF(const PointF &apt1, const PointF &apt2) noexcept
    : pt1(apt1), pt2(apt2)
{
}

LineF::LineF(double x1pos, double y1pos, double x2pos, double y2pos) noexcept
    : pt1(x1pos, y1pos), pt2(x2pos, y2pos)
{
}

double LineF::x1() const noexcept { return pt1.x(); }

double LineF::y1() const noexcept { return pt1.y(); }

double LineF::x2() const noexcept { return pt2.x(); }

double LineF::y2() const noexcept { return pt2.y(); }

LineF LineF::fromPolar(double length, double angle)
{
    const double angleR = degreesToRadians(angle);
    return LineF(0, 0, qCos(angleR) * length, -qSin(angleR) * length);
}

bool LineF::isNull() const noexcept
{
    return qFuzzyCompare(pt1.x(), pt2.x()) && qFuzzyCompare(pt1.y(), pt2.y());
}

PointF LineF::p1() const noexcept { return pt1; }

PointF LineF::p2() const noexcept { return pt2; }

double LineF::dx() const noexcept { return pt2.x() - pt1.x(); }

double LineF::dy() const noexcept { return pt2.y() - pt1.y(); }

double LineF::angle() const noexcept
{
    const double dx = pt2.x() - pt1.x();
    const double dy = pt2.y() - pt1.y();

    const double theta = radiansToDegrees(qAtan2(-dy, dx));

    const double theta_normalized = theta < 0 ? theta + 360 : theta;

    if (qFuzzyCompare(theta_normalized, double(360))) return double(0);
    else
        return theta_normalized;
}

void LineF::setAngle(double angle) noexcept
{
    const double angleR = degreesToRadians(angle);
    const double l = length();

    const double dx = qCos(angleR) * l;
    const double dy = -qSin(angleR) * l;

    pt2.rx() = pt1.x() + dx;
    pt2.ry() = pt1.y() + dy;
}

double LineF::angleTo(const LineF &l) const noexcept
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

LineF LineF::unitVector() const noexcept
{
    const double x = dx();
    const double y = dy();

    const double len = std::sqrt(double(dx()) * double(dx()) +
                                 double(dy()) * double(dy()));
    LineF f(p1(), PointF(pt1.x() + x / len, pt1.y() + y / len));

    return f;
}

LineF LineF::normalVector() const noexcept
{
    return LineF(p1(), p1() + PointF(dy(), -dx()));
}

LineF::IntersectionType
LineF::intersects(const LineF &l, PointF *intersectionPoint) const noexcept
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

void LineF::translate(const PointF &point) noexcept
{
    pt1 += point;
    pt2 += point;
}

void LineF::translate(double adx, double ady) noexcept
{
    this->translate(PointF(adx, ady));
}

LineF LineF::translated(const PointF &p) const noexcept
{
    return LineF(pt1 + p, pt2 + p);
}

LineF LineF::translated(double adx, double ady) const noexcept
{
    return translated(PointF(adx, ady));
}

PointF LineF::center() const noexcept
{
    return PointF(0.5 * pt1.x() + 0.5 * pt2.x(), 0.5 * pt1.y() + 0.5 * pt2.y());
}

double LineF::length() const noexcept
{
    double len = dx() * dx() + dy() * dy();
    return std::sqrt(len);
}

void LineF::setLength(double len) noexcept
{
    assert(std::isfinite(len));
    const double oldLength = length();
    assert(std::isfinite(oldLength));
    if (oldLength > 0)
        pt2 = PointF(pt1.x() + len * (dx() / oldLength),
                     pt1.y() + len * (dy() / oldLength));
}

PointF LineF::pointAt(double t) const noexcept
{
    return PointF(pt1.x() + (pt2.x() - pt1.x()) * t,
                  pt1.y() + (pt2.y() - pt1.y()) * t);
}

LineF Line::toLineF() const noexcept { return *this; }

Line LineF::toLine() const noexcept
{
    return Line(pt1.toPoint(), pt2.toPoint());
}

void LineF::setP1(const PointF &aP1) noexcept { pt1 = aP1; }

void LineF::setP2(const PointF &aP2) noexcept { pt2 = aP2; }

void LineF::setPoints(const PointF &aP1, const PointF &aP2) noexcept
{
    pt1 = aP1;
    pt2 = aP2;
}

void LineF::setLine(double aX1, double aY1, double aX2, double aY2) noexcept
{
    pt1 = PointF(aX1, aY1);
    pt2 = PointF(aX2, aY2);
}

bool LineF::operator==(const LineF &d) const noexcept
{
    return pt1 == d.pt1 && pt2 == d.pt2;
}

}// namespace m2