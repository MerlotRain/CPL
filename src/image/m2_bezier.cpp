#include <m2_bezier.h>
#include <m2_line.h>
#include <m2_point.h>
#include <m2_polygon.h>
#include <m2_rect.h>

namespace m2 {

enum ShiftResult
{
    Ok,
    Discard,
    Split,
    Circle
};

/**
 * @brief 
 * 
 * @param b1 
 * @param b2 
 * @param offset 
 * @param threshold 
 * @return ShiftResult 
 */
static ShiftResult good_offset(const Bezier *b1, const Bezier *b2,
                               double offset, double threshold)
{
    const double o2 = offset * offset;
    const double max_dist_line = threshold * offset * offset;
    const double max_dist_normal = threshold * offset;
    const int divisions = 4;
    const double spacing = double(1.0) / divisions;
    double t = spacing;
    for (int i = 1; i < divisions; ++i, t += spacing)
    {
        PointF p1 = b1->pointAt(t);
        PointF p2 = b2->pointAt(t);
        double d = (p1.x() - p2.x()) * (p1.x() - p2.x()) +
                   (p1.y() - p2.y()) * (p1.y() - p2.y());
        if (qAbs(d - o2) > max_dist_line) return Split;

        PointF normalPoint = b1->normalVector(t);
        double l = qAbs(normalPoint.x()) + qAbs(normalPoint.y());
        if (l != double(0.0))
        {
            d = qAbs(normalPoint.x() * (p1.y() - p2.y()) -
                     normalPoint.y() * (p1.x() - p2.x())) /
                l;
            if (d > max_dist_normal) return Split;
        }
    }
    return Ok;
}

/**
 * @brief 
 * 
 * @param orig 
 * @param shifted 
 * @param offset 
 * @param threshold 
 * @return ShiftResult 
 */
static ShiftResult shift(const Bezier *orig, Bezier *shifted, double offset,
                         double threshold)
{
    int map[4];
    bool p1_p2_equal = qFuzzyCompare(orig->x1, orig->x2) &&
                       qFuzzyCompare(orig->y1, orig->y2);
    bool p2_p3_equal = qFuzzyCompare(orig->x2, orig->x3) &&
                       qFuzzyCompare(orig->y2, orig->y3);
    bool p3_p4_equal = qFuzzyCompare(orig->x3, orig->x4) &&
                       qFuzzyCompare(orig->y3, orig->y4);

    PointF points[4];
    int np = 0;
    points[np] = PointF(orig->x1, orig->y1);
    map[0] = 0;
    ++np;
    if (!p1_p2_equal)
    {
        points[np] = PointF(orig->x2, orig->y2);
        ++np;
    }
    map[1] = np - 1;
    if (!p2_p3_equal)
    {
        points[np] = PointF(orig->x3, orig->y3);
        ++np;
    }
    map[2] = np - 1;
    if (!p3_p4_equal)
    {
        points[np] = PointF(orig->x4, orig->y4);
        ++np;
    }
    map[3] = np - 1;
    if (np == 1) return Discard;

    RectF b = orig->bounds();
    if (np == 4 && b.width() < .1 * offset && b.height() < .1 * offset)
    {
        double l = (orig->x1 - orig->x2) * (orig->x1 - orig->x2) +
                   (orig->y1 - orig->y2) * (orig->y1 - orig->y2) *
                           (orig->x3 - orig->x4) * (orig->x3 - orig->x4) +
                   (orig->y3 - orig->y4) * (orig->y3 - orig->y4);
        double dot = (orig->x1 - orig->x2) * (orig->x3 - orig->x4) +
                     (orig->y1 - orig->y2) * (orig->y3 - orig->y4);
        if (dot < 0 && dot * dot < 0.8 * l)
            // the points are close and reverse dirction. Approximate the whole
            // thing by a semi circle
            return Circle;
    }

    PointF points_shifted[4];

    LineF prev = LineF(PointF(), points[1] - points[0]);
    if (!prev.length()) return Discard;
    PointF prev_normal = prev.normalVector().unitVector().p2();

    points_shifted[0] = points[0] + offset * prev_normal;

    for (int i = 1; i < np - 1; ++i)
    {
        LineF next = LineF(PointF(), points[i + 1] - points[i]);
        PointF next_normal = next.normalVector().unitVector().p2();

        PointF normal_sum = prev_normal + next_normal;

        double r = double(1.0) + prev_normal.x() * next_normal.x() +
                   prev_normal.y() * next_normal.y();

        if (qFuzzyIsNull(r))
        {
            points_shifted[i] = points[i] + offset * prev_normal;
        }
        else
        {
            double k = offset / r;
            points_shifted[i] = points[i] + k * normal_sum;
        }

        prev_normal = next_normal;
    }

    points_shifted[np - 1] = points[np - 1] + offset * prev_normal;

    *shifted =
            Bezier::fromPoints(points_shifted[map[0]], points_shifted[map[1]],
                               points_shifted[map[2]], points_shifted[map[3]]);

    if (np > 2) return good_offset(orig, shifted, offset, threshold);
    return Ok;
}


#define KAPPA double(0.5522847498)

/**
 * @brief 
 * 
 * @param b 
 * @param offset 
 * @param o 
 * @return true 
 * @return false 
 */
static bool addCircle(const Bezier *b, double offset, Bezier *o)
{
    PointF normals[3];

    normals[0] = PointF(b->y2 - b->y1, b->x1 - b->x2);
    double dist = qSqrt(normals[0].x() * normals[0].x() +
                        normals[0].y() * normals[0].y());
    if (qFuzzyIsNull(dist)) return false;
    normals[0] /= dist;
    normals[2] = PointF(b->y4 - b->y3, b->x3 - b->x4);
    dist = qSqrt(normals[2].x() * normals[2].x() +
                 normals[2].y() * normals[2].y());
    if (qFuzzyIsNull(dist)) return false;
    normals[2] /= dist;

    normals[1] = PointF(b->x1 - b->x2 - b->x3 + b->x4,
                        b->y1 - b->y2 - b->y3 + b->y4);
    normals[1] /= -1 * qSqrt(normals[1].x() * normals[1].x() +
                             normals[1].y() * normals[1].y());

    double angles[2];
    double sign = 1.;
    for (int i = 0; i < 2; ++i)
    {
        double cos_a = normals[i].x() * normals[i + 1].x() +
                       normals[i].y() * normals[i + 1].y();
        if (cos_a > 1.) cos_a = 1.;
        if (cos_a < -1.) cos_a = -1;
        angles[i] = qAcos(cos_a) * double(M_1_PI);
    }

    if (angles[0] + angles[1] > 1.)
    {
        // more than 180 degrees
        normals[1] = -normals[1];
        angles[0] = 1. - angles[0];
        angles[1] = 1. - angles[1];
        sign = -1.;
    }

    PointF circle[3];
    circle[0] = PointF(b->x1, b->y1) + normals[0] * offset;
    circle[1] = PointF(double(0.5) * (b->x1 + b->x4),
                       double(0.5) * (b->y1 + b->y4)) +
                normals[1] * offset;
    circle[2] = PointF(b->x4, b->y4) + normals[2] * offset;

    for (int i = 0; i < 2; ++i)
    {
        double kappa = double(2.0) * KAPPA * sign * offset * angles[i];

        o->x1 = circle[i].x();
        o->y1 = circle[i].y();
        o->x2 = circle[i].x() - normals[i].y() * kappa;
        o->y2 = circle[i].y() + normals[i].x() * kappa;
        o->x3 = circle[i + 1].x() + normals[i + 1].y() * kappa;
        o->y3 = circle[i + 1].y() - normals[i + 1].x() * kappa;
        o->x4 = circle[i + 1].x();
        o->y4 = circle[i + 1].y();

        ++o;
    }
    return true;
}


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
    return {p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y(), p4.x(), p4.y()};
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
    double m_t = 1. - t;
    b = m_t * m_t;
    c = t * t;
    d = c * t;
    a = b * m_t;
    b *= 3. * t;
    c *= 3. * m_t;
}

/**
 * @brief 
 * 
 * @param t 
 * @return PointF 
 */
PointF Bezier::pointAt(double t) const
{
    double x, y;

    double m_t = 1. - t;
    {
        double a = x1 * m_t + x2 * t;
        double b = x2 * m_t + x3 * t;
        double c = x3 * m_t + x4 * t;
        a = a * m_t + b * t;
        b = b * m_t + c * t;
        x = a * m_t + b * t;
    }
    {
        double a = y1 * m_t + y2 * t;
        double b = y2 * m_t + y3 * t;
        double c = y3 * m_t + y4 * t;
        a = a * m_t + b * t;
        b = b * m_t + c * t;
        y = a * m_t + b * t;
    }
    return PointF(x, y);
}

/**
 * @brief 
 * 
 * @param t 
 * @return PointF 
 */
PointF Bezier::normalVector(double t) const
{
    double m_t = 1. - t;
    double a = m_t * m_t;
    double b = t * m_t;
    double c = t * t;

    return PointF((y2 - y1) * a + (y3 - y2) * b + (y4 - y3) * c,
                  -(x2 - x1) * a - (x3 - x2) * b - (x4 - x3) * c);
}

/**
 * @brief 
 * 
 * @param t 
 * @return PointF 
 */
PointF Bezier::derivedAt(double t) const
{
    double m_t = 1. - t;

    double d = t * t;
    double a = -m_t * m_t;
    double b = 1 - 4 * t + 3 * d;
    double c = 2 * t - 3 * d;

    return 3 * PointF(a * x1 + b * x2 + c * x3 + d * x4,
                      a * y1 + b * y2 + c * y3 + d * y4);
}

/**
 * @brief 
 * 
 * @param t 
 * @return PointF 
 */
PointF Bezier::secondDerivedAt(double t) const
{
    double a = 2. - 2. * t;
    double b = -4 + 6 * t;
    double c = 2 - 6 * t;
    double d = 2 * t;

    return 3 * PointF(a * x1 + b * x2 + c * x3 + d * x4,
                      a * y1 + b * y2 + c * y3 + d * y4);
}

/**
 * @brief 
 * 
 * @param bezier_flattening_threshold 
 * @return PolygonF 
 */
PolygonF Bezier::toPolygon(double bezier_flattening_threshold) const
{
    PolygonF polygon;
    polygon.push_back(PointF(x1, y1));
    addToPolygon(&polygon, bezier_flattening_threshold);
    return polygon;
}

/**
 * @brief 
 * 
 * @param p 
 * @param bezier_flattening_threshold 
 */
void Bezier::addToPolygon(PolygonF *polygon,
                          double bezier_flattening_threshold) const
{
    Bezier beziers[10];
    int levels[10];
    beziers[0] = *this;
    levels[0] = 9;
    int top = 0;

    while (top >= 0)
    {
        Bezier *b = &beziers[top];
        // check if we can pop the top bezier curve from the stack
        double y4y1 = b->y4 - b->y1;
        double x4x1 = b->x4 - b->x1;
        double l = qAbs(x4x1) + qAbs(y4y1);
        double d;
        if (l > 1.)
        {
            d = qAbs((x4x1) * (b->y1 - b->y2) - (y4y1) * (b->x1 - b->x2)) +
                qAbs((x4x1) * (b->y1 - b->y3) - (y4y1) * (b->x1 - b->x3));
        }
        else
        {
            d = qAbs(b->x1 - b->x2) + qAbs(b->y1 - b->y2) +
                qAbs(b->x1 - b->x3) + qAbs(b->y1 - b->y3);
            l = 1.;
        }
        if (d < bezier_flattening_threshold * l || levels[top] == 0)
        {
            // good enough, we pop it off and add the endpoint
            polygon->push_back(PointF(b->x4, b->y4));
            --top;
        }
        else
        {
            // split, second half of the polygon goes lower into the stack
            std::tie(b[1], b[0]) = b->split();
            levels[top + 1] = --levels[top];
            ++top;
        }
    }
}

/**
 * @brief 
 * 
 * @return RectF 
 */
RectF Bezier::bounds() const
{
    double xmin = x1;
    double xmax = x1;
    if (x2 < xmin) xmin = x2;
    else if (x2 > xmax)
        xmax = x2;
    if (x3 < xmin) xmin = x3;
    else if (x3 > xmax)
        xmax = x3;
    if (x4 < xmin) xmin = x4;
    else if (x4 > xmax)
        xmax = x4;

    double ymin = y1;
    double ymax = y1;
    if (y2 < ymin) ymin = y2;
    else if (y2 > ymax)
        ymax = y2;
    if (y3 < ymin) ymin = y3;
    else if (y3 > ymax)
        ymax = y3;
    if (y4 < ymin) ymin = y4;
    else if (y4 > ymax)
        ymax = y4;
    return RectF(xmin, ymin, xmax - xmin, ymax - ymin);
}

/**
 * @brief 
 * 
 * @param error 
 * @return double 
 */
double Bezier::length(double error) const
{
    double length = double(0.0);

    addIfClose(&length, error);

    return length;
}

/**
 * @brief 
 * 
 * @param length 
 * @param error 
 */
void Bezier::addIfClose(double *length, double error) const
{
    double len = double(0.0); /* arc length */
    double chord;             /* chord length */

    len = len + LineF(PointF(x1, y1), PointF(x2, y2)).length();
    len = len + LineF(PointF(x2, y2), PointF(x3, y3)).length();
    len = len + LineF(PointF(x3, y3), PointF(x4, y4)).length();

    chord = LineF(PointF(x1, y1), PointF(x4, y4)).length();

    if ((len - chord) > error)
    {
        const auto halves = split();             /* split in two */
        halves.first.addIfClose(length, error);  /* try left side */
        halves.second.addIfClose(length, error); /* try right side */
        return;
    }

    *length = *length + len;

    return;
}

/**
 * @brief 
 * 
 * @param len 
 * @return double 
 */
double Bezier::tAtLength(double l) const
{
    double len = length();
    double t = double(1.0);
    const double error = double(0.01);
    if (l > len || qFuzzyCompare(l, len)) return t;

    t *= double(0.5);
    //int iters = 0;
    //qDebug()<<"LEN is "<<l<<len;
    double lastBigger = double(1.0);
    while (1)
    {
        //qDebug()<<"\tt is "<<t;
        Bezier right = *this;
        Bezier left;
        right.parameterSplitLeft(t, &left);
        double lLen = left.length();
        if (qAbs(lLen - l) < error) break;

        if (lLen < l) { t += (lastBigger - t) * double(0.5); }
        else
        {
            lastBigger = t;
            t -= t * double(0.5);
        }
        //++iters;
    }
    //qDebug()<<"number of iters is "<<iters;
    return t;
}

/**
 * @brief 
 * 
 * @param t0 
 * @param t1 
 * @return int 
 */
int Bezier::stationaryYPoints(double &t0, double &t1) const
{
    const double a = -y1 + 3 * y2 - 3 * y3 + y4;
    const double b = 2 * y1 - 4 * y2 + 2 * y3;
    const double c = -y1 + y2;

    if (qFuzzyIsNull(a))
    {
        if (qFuzzyIsNull(b)) return 0;

        t0 = -c / b;
        return t0 > 0 && t0 < 1;
    }

    double reciprocal = b * b - 4 * a * c;

    if (qFuzzyIsNull(reciprocal))
    {
        t0 = -b / (2 * a);
        return t0 > 0 && t0 < 1;
    }
    else if (reciprocal > 0)
    {
        double temp = qSqrt(reciprocal);

        t0 = (-b - temp) / (2 * a);
        t1 = (-b + temp) / (2 * a);

        if (t1 < t0) std::swap(t0, t1);

        int count = 0;
        double t[2] = {0, 1};

        if (t0 > 0 && t0 < 1) t[count++] = t0;
        if (t1 > 0 && t1 < 1) t[count++] = t1;

        t0 = t[0];
        t1 = t[1];

        return count;
    }

    return 0;
}

/**
 * @brief 
 * 
 * @param t0 
 * @param t1 
 * @param y 
 * @return double 
 */
double Bezier::tForY(double t0, double t1, double y) const
{
    double py0 = pointAt(t0).y();
    double py1 = pointAt(t1).y();

    if (py0 > py1)
    {
        std::swap(py0, py1);
        std::swap(t0, t1);
    }

    assert(py0 <= py1);

    if (py0 >= y) return t0;
    else if (py1 <= y)
        return t1;

    assert(py0 < y && y < py1);

    double lt = t0;
    double dt;
    do {
        double t = double(0.5) * (t0 + t1);

        double a, b, c, d;
        Bezier::coefficients(t, a, b, c, d);
        double yt = a * y1 + b * y2 + c * y3 + d * y4;

        if (yt < y)
        {
            t0 = t;
            py0 = yt;
        }
        else
        {
            t1 = t;
            py1 = yt;
        }
        dt = lt - t;
        lt = t;
    } while (qAbs(dt) > double(1e-7));

    return t0;
}

/**
 * @brief 
 * 
 * @return PointF 
 */
PointF Bezier::midPoint() const
{
    return PointF((x1 + x4 + 3 * (x2 + x3)) / 8.,
                  (y1 + y4 + 3 * (y2 + y3)) / 8.);
}

/**
 * @brief 
 * 
 * @return LineF 
 */
LineF Bezier::midTangent() const
{
    PointF mid = midPoint();
    LineF dir(LineF(x1, y1, x2, y2).pointAt(0.5),
              LineF(x3, y3, x4, y4).pointAt(0.5));
    return LineF(mid.x() - dir.dx(), mid.y() - dir.dy(), mid.x() + dir.dx(),
                 mid.y() + dir.dy());
}

/**
 * @brief 
 * 
 * @return LineF 
 */
LineF Bezier::startTangent() const
{
    LineF tangent(pt1(), pt2());
    if (tangent.isNull()) tangent = LineF(pt1(), pt3());
    if (tangent.isNull()) tangent = LineF(pt1(), pt4());
    return tangent;
}

/**
 * @brief 
 * 
 * @return LineF 
 */
LineF Bezier::endTangent() const
{
    LineF tangent(pt4(), pt3());
    if (tangent.isNull()) tangent = LineF(pt4(), pt2());
    if (tangent.isNull()) tangent = LineF(pt4(), pt1());
    return tangent;
}

/**
 * @brief 
 * 
 * @param t 
 * @param left 
 */
void Bezier::parameterSplitLeft(double t, Bezier *left)
{
    left->x1 = x1;
    left->y1 = y1;

    left->x2 = x1 + t * (x2 - x1);
    left->y2 = y1 + t * (y2 - y1);

    left->x3 = x2 + t * (x3 - x2);// temporary holding spot
    left->y3 = y2 + t * (y3 - y2);// temporary holding spot

    x3 = x3 + t * (x4 - x3);
    y3 = y3 + t * (y4 - y3);

    x2 = left->x3 + t * (x3 - left->x3);
    y2 = left->y3 + t * (y3 - left->y3);

    left->x3 = left->x2 + t * (left->x3 - left->x2);
    left->y3 = left->y2 + t * (left->y3 - left->y2);

    left->x4 = x1 = left->x3 + t * (x2 - left->x3);
    left->y4 = y1 = left->y3 + t * (y2 - left->y3);
}

/**
 * @brief 
 * 
 * @return std::pair<Bezier, Bezier> 
 */
std::pair<Bezier, Bezier> Bezier::split() const
{
    const auto mid = [](PointF lhs, PointF rhs) { return (lhs + rhs) * .5; };

    const PointF mid_12 = mid(pt1(), pt2());
    const PointF mid_23 = mid(pt2(), pt3());
    const PointF mid_34 = mid(pt3(), pt4());
    const PointF mid_12_23 = mid(mid_12, mid_23);
    const PointF mid_23_34 = mid(mid_23, mid_34);
    const PointF mid_12_23__23_34 = mid(mid_12_23, mid_23_34);

    return {
            fromPoints(pt1(), mid_12, mid_12_23, mid_12_23__23_34),
            fromPoints(mid_12_23__23_34, mid_23_34, mid_34, pt4()),
    };
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
int Bezier::shifted(Bezier *curveSegments, int maxSegments, double offset,
                    float threshold) const
{
    assert(curveSegments);
    assert(maxSegments > 0);

    if (qFuzzyCompare(x1, x2) && qFuzzyCompare(x1, x3) &&
        qFuzzyCompare(x1, x4) && qFuzzyCompare(y1, y2) &&
        qFuzzyCompare(y1, y3) && qFuzzyCompare(y1, y4))
        return 0;

    --maxSegments;
    Bezier beziers[10];
redo:
    beziers[0] = *this;
    Bezier *b = beziers;
    Bezier *o = curveSegments;

    while (b >= beziers)
    {
        int stack_segments = b - beziers + 1;
        if ((stack_segments == 10) ||
            (o - curveSegments == maxSegments - stack_segments))
        {
            threshold *= double(1.5);
            if (threshold > double(2.0)) goto give_up;
            goto redo;
        }
        ShiftResult res = shift(b, o, offset, threshold);
        if (res == Discard) { --b; }
        else if (res == Ok)
        {
            ++o;
            --b;
        }
        else if (res == Circle && maxSegments - (o - curveSegments) >= 2)
        {
            // add semi circle
            if (addCircle(b, offset, o)) o += 2;
            --b;
        }
        else
        {
            std::tie(b[1], b[0]) = b->split();
            ++b;
        }
    }

give_up:
    while (b >= beziers)
    {
        ShiftResult res = shift(b, o, offset, threshold);

        // if res isn't Ok or Split then *o is undefined
        if (res == Ok || res == Split) ++o;

        --b;
    }

    assert(o - curveSegments <= maxSegments);
    return o - curveSegments;
}

/**
 * @brief 
 * 
 * @param t0 
 * @param t1 
 * @return Bezier 
 */
Bezier Bezier::bezierOnInterval(double t0, double t1) const
{
    if (t0 == 0 && t1 == 1) return *this;

    Bezier bezier = *this;

    Bezier result;
    bezier.parameterSplitLeft(t0, &result);
    double trueT = (t1 - t0) / (1 - t0);
    bezier.parameterSplitLeft(trueT, &result);

    return result;
}

/**
 * @brief 
 * 
 * @param t0 
 * @param t1 
 * @return Bezier 
 */
Bezier Bezier::getSubRange(double t0, double t1) const
{
    Bezier result;
    Bezier temp;

    // cut at t1
    if (qFuzzyIsNull(t1 - double(1.))) { result = *this; }
    else
    {
        temp = *this;
        temp.parameterSplitLeft(t1, &result);
    }

    // cut at t0
    if (!qFuzzyIsNull(t0)) result.parameterSplitLeft(t0 / t1, &temp);

    return result;
}

}// namespace m2