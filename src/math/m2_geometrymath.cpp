#include <m2_geometrymath.h>
#include <m2_math.h>
#include <m2_vector.h>

namespace m2 {

/**
 * @brief 
 * @param  pt1              
 * @param  pt2              
 * @return double 
 */
double GeometryMath::sqrDistance2D(const PointF &pt1, const PointF &pt2)
{
    return (pt1.x() - pt2.x()) * (pt1.x() - pt2.x()) +
           (pt1.y() - pt2.y()) * (pt1.y() - pt2.y());
}

/**
 * @brief 
 * @param  ptX              
 * @param  ptY              
 * @param  x1               
 * @param  y1               
 * @param  x2               
 * @param  y2               
 * @param  minDistX         
 * @param  minDistY         
 * @param  epsilon          
 * @return double 
 */
double GeometryMath::sqrDistToLine(double ptX, double ptY, double x1, double y1,
                                   double x2, double y2, double &minDistX,
                                   double &minDistY, double epsilon)
{
    minDistX = x1;
    minDistY = y1;

    double dx = x2 - x1;
    double dy = y2 - y1;

    if (!qIsEqual(dx, 0.0) || !qIsEqual(dy, 0.0))
    {
        const double t =
                ((ptX - x1) * dx + (ptY - y1) * dy) / (dx * dx + dy * dy);
        if (t > 1)
        {
            minDistX = x2;
            minDistY = y2;
        }
        else if (t > 0)
        {
            minDistX += dx * t;
            minDistY += dy * t;
        }
    }

    dx = ptX - minDistX;
    dy = ptY - minDistY;

    const double dist = dx * dx + dy * dy;

    //prevent rounding errors if the point is directly on the segment
    if (qIsEqual(dist, 0.0, epsilon))
    {
        minDistX = ptX;
        minDistY = ptY;
        return 0.0;
    }

    return dist;
}

/**
 * @brief 
 * @param  point            
 * @param  linePoint1       
 * @param  linePoint2       
 * @param  epsilon          
 * @return double 
 */
double GeometryMath::distToInfiniteLine(const PointF &point,
                                        const PointF &linePoint1,
                                        const PointF &linePoint2,
                                        double epsilon)
{
    const double area = std::abs(
            (linePoint1.x() - linePoint2.x()) * (point.y() - linePoint2.y()) -
            (linePoint1.y() - linePoint2.y()) * (point.x() - linePoint2.x()));

    const double length =
            std::sqrt(std::pow(linePoint1.x() - linePoint2.x(), 2) +
                      std::pow(linePoint1.y() - linePoint2.y(), 2));

    const double distance = area / length;
    return qIsEqual(distance, 0.0, epsilon) ? 0.0 : distance;
}

/**
 * @brief 
 * @param  p1               
 * @param  v1               
 * @param  p2               
 * @param  v2               
 * @param  intersection     
 * @return true 
 * @return false 
 */
bool GeometryMath::lineIntersection(const PointF &p1, Vector2D v1,
                                    const PointF &p2, Vector2D v2,
                                    PointF &intersection)
{
    const double d = v1.y() * v2.x() - v1.x() * v2.y();

    if (qIsEqual(d, 0)) return false;

    const double dx = p2.x() - p1.x();
    const double dy = p2.y() - p1.y();
    const double k = (dy * v2.x() - dx * v2.y()) / d;

    intersection = PointF(p1.x() + v1.x() * k, p1.y() + v1.y() * k);

    return true;
}

/**
 * @brief 
 * @param  p1               
 * @param  p2               
 * @param  q1               
 * @param  q2               
 * @param  intersectionPoint
 * @param  isIntersection   
 * @param  tolerance        
 * @param  acceptImproperIntersection
 * @return true 
 * @return false 
 */
bool GeometryMath::segmentIntersection(const PointF &p1, const PointF &p2,
                                       const PointF &q1, const PointF &q2,
                                       PointF &intersectionPoint,
                                       bool &isIntersection, double tolerance,
                                       bool acceptImproperIntersection)
{
    isIntersection = false;

    Vector2D v(p2.x() - p1.x(), p2.y() - p1.y());
    Vector2D w(q2.x() - q1.x(), q2.y() - q1.y());
    const double vl = v.length();
    const double wl = w.length();

    if (qIsEqual(vl, 0.0, tolerance) || qIsEqual(wl, 0.0, tolerance))
    {
        return false;
    }
    v = v / vl;
    w = w / wl;

    if (!GeometryMath::lineIntersection(p1, v, q1, w, intersectionPoint))
    {
        return false;
    }

    isIntersection = true;
    if (acceptImproperIntersection)
    {
        if ((p1 == q1) || (p1 == q2))
        {
            intersectionPoint = p1;
            return true;
        }
        else if ((p2 == q1) || (p2 == q2))
        {
            intersectionPoint = p2;
            return true;
        }

        double x, y;
        if (
                // intersectionPoint = p1
                qIsEqual(GeometryMath::sqrDistToLine(p1.x(), p1.y(), q1.x(),
                                                     q1.y(), q2.x(), q2.y(), x,
                                                     y, tolerance),
                         0.0, tolerance) ||
                // intersectionPoint = p2
                qIsEqual(GeometryMath::sqrDistToLine(p2.x(), p2.y(), q1.x(),
                                                     q1.y(), q2.x(), q2.y(), x,
                                                     y, tolerance),
                         0.0, tolerance) ||
                // intersectionPoint = q1
                qIsEqual(GeometryMath::sqrDistToLine(q1.x(), q1.y(), p1.x(),
                                                     p1.y(), p2.x(), p2.y(), x,
                                                     y, tolerance),
                         0.0, tolerance) ||
                // intersectionPoint = q2
                qIsEqual(GeometryMath::sqrDistToLine(q2.x(), q2.y(), p1.x(),
                                                     p1.y(), p2.x(), p2.y(), x,
                                                     y, tolerance),
                         0.0, tolerance))
        {
            return true;
        }
    }

    const double lambdav = Vector2D(intersectionPoint.x() - p1.x(),
                                    intersectionPoint.y() - p1.y()) *
                           v;
    if (lambdav < 0. + tolerance || lambdav > vl - tolerance) return false;

    const double lambdaw = Vector2D(intersectionPoint.x() - q1.x(),
                                    intersectionPoint.y() - q1.y()) *
                           w;
    return !(lambdaw < 0. + tolerance || lambdaw >= wl - tolerance);
}

/**
 * @brief 
 * @param  center           
 * @param  radius           
 * @param  linePoint1       
 * @param  linePoint2       
 * @param  intersection     
 * @return true 
 * @return false 
 */
bool GeometryMath::lineCircleIntersection(const PointF &center, double radius,
                                          const PointF &linePoint1,
                                          const PointF &linePoint2,
                                          PointF &intersection)
{
    const double x1 = linePoint1.x() - center.x();
    const double y1 = linePoint1.y() - center.y();
    const double x2 = linePoint2.x() - center.x();
    const double y2 = linePoint2.y() - center.y();
    const double dx = x2 - x1;
    const double dy = y2 - y1;

    const double dr2 = std::pow(dx, 2) + std::pow(dy, 2);
    const double d = x1 * y2 - x2 * y1;

    const double disc = std::pow(radius, 2) * dr2 - std::pow(d, 2);

    if (disc < 0)
    {
        //no intersection or tangent
        return false;
    }
    else
    {
        // two solutions
        const int sgnDy = dy < 0 ? -1 : 1;

        const double sqrDisc = std::sqrt(disc);

        const double ax = center.x() + (d * dy + sgnDy * dx * sqrDisc) / dr2;
        const double ay =
                center.y() + (-d * dx + std::fabs(dy) * sqrDisc) / dr2;
        const PointF p1(ax, ay);

        const double bx = center.x() + (d * dy - sgnDy * dx * sqrDisc) / dr2;
        const double by =
                center.y() + (-d * dx - std::fabs(dy) * sqrDisc) / dr2;
        const PointF p2(bx, by);

        // snap to nearest intersection

        if (intersection.distance(p1) < intersection.distance(p2))
        {
            intersection = {p1.x(), p1.y()};
        }
        else { intersection = {p2.x(), p2.y()}; }
        return true;
    }
}

/**
 * @brief 
 * @param  center1          
 * @param  radius1          
 * @param  center2          
 * @param  radius2          
 * @param  intersection1    
 * @param  intersection2    
 * @return int 
 */
int GeometryMath::circleCircleIntersections(const PointF &center1, double r1,
                                            const PointF &center2, double r2,
                                            PointF &intersection1,
                                            PointF &intersection2)
{
    const double d = center1.distance(center2);

    // check if the circles intersect at only 1 point, either "externally" or "internally"
    const bool singleSolutionExt = qIsEqual(d, r1 + r2);
    const bool singleSolutionInt = qIsEqual(d, std::fabs(r1 - r2));

    // check for solvability
    if (!singleSolutionExt && d > (r1 + r2))
    {
        // no solution. circles do not intersect.
        return 0;
    }
    else if (!singleSolutionInt && d < std::fabs(r1 - r2))
    {
        // no solution. one circle is contained in the other
        return 0;
    }
    else if (qIsEqual(d, 0) && (qIsEqual(r1, r2)))
    {
        // no solutions, the circles coincide
        return 0;
    }

    /* 'point 2' is the point where the line through the circle
   * intersection points crosses the line between the circle
   * centers.
  */

    /* Determine the distance 'a' from point 0 to point 2.
   * In the general case, a = ( ( r1 * r1 ) - ( r2 * r2 ) + ( d * d ) ) / ( 2.0 * d ).
   * If d = r1 + r2 or d = r1 - r2 (i.e. r1 > r2), then a = r1; if d = r2 - r1 (i.e. r2 > r1), then a = -r1.
  */
    const double a =
            singleSolutionExt
                    ? r1
                    : (singleSolutionInt
                               ? (r1 > r2 ? r1 : -r1)
                               : ((r1 * r1) - (r2 * r2) + (d * d)) / (2.0 * d));

    /* dx and dy are the vertical and horizontal distances between
   * the circle centers.
   */
    const double dx = center2.x() - center1.x();
    const double dy = center2.y() - center1.y();

    // Determine the coordinates of point 2.
    const double x2 = center1.x() + (dx * a / d);
    const double y2 = center1.y() + (dy * a / d);

    // only 1 solution
    if (singleSolutionExt || singleSolutionInt)
    {
        intersection1 = PointF(x2, y2);
        intersection2 = PointF(x2, y2);

        return 1;
    }

    // 2 solutions

    /* Determine the distance from point 2 to either of the
   * intersection points.
   */
    const double h = std::sqrt((r1 * r1) - (a * a));

    /* Now determine the offsets of the intersection points from
   * point 2.
   */
    const double rx = dy * (h / d);
    const double ry = dx * (h / d);

    // determine the absolute intersection points
    intersection1 = PointF(x2 + rx, y2 - ry);
    intersection2 = PointF(x2 - rx, y2 + ry);

    return 2;
}

/**
 * @brief 
 * @param  center           
 * @param  radius           
 * @param  p                
 * @param  pt1              
 * @param  pt2              
 * @return true 
 * @return false 
 */
bool GeometryMath::tangentPointAndCircle(const PointF &center, double radius,
                                         const PointF &p, PointF &pt1,
                                         PointF &pt2)
{
    const double dx = center.x() - p.x();
    const double dy = center.y() - p.y();
    const double distanceSquared = dx * dx + dy * dy;
    const double radiusSquared = radius * radius;
    if (distanceSquared < radiusSquared) { return false; }

    const double distanceToTangent = std::sqrt(distanceSquared - radiusSquared);
    circleCircleIntersections(center, radius, p, distanceToTangent, pt1, pt2);

    return true;
}

/**
 * @brief 
 * @param  center1          
 * @param  radius1          
 * @param  center2          
 * @param  radius2          
 * @param  line1P1          
 * @param  line1P2          
 * @param  line2P1          
 * @param  line2P2          
 * @return int 
 */
int GeometryMath::circleCircleOuterTangents(const PointF &center1,
                                            double radius1,
                                            const PointF &center2,
                                            double radius2, PointF &line1P1,
                                            PointF &line1P2, PointF &line2P1,
                                            PointF &line2P2)
{
    if (radius1 > radius2)
        return circleCircleOuterTangents(center2, radius2, center1, radius1,
                                         line1P1, line1P2, line2P1, line2P2);

    const double radius2a = radius2 - radius1;
    if (!tangentPointAndCircle(center2, radius2a, center1, line1P2, line2P2))
    {
        // there are no tangents
        return 0;
    }

    // get the vector perpendicular to the
    // first tangent with length radius1
    Vector2D v1(-(line1P2.y() - center1.y()), line1P2.x() - center1.x());
    const double v1Length = v1.length();
    v1 = v1 * (radius1 / v1Length);

    // offset the tangent vector's points
    line1P1 = center1.offset(v1.x(), v1.y());
    line1P2 = line1P2.offset(v1.x(), v1.y());

    // get the vector perpendicular to the
    // second tangent with length radius1
    Vector2D v2(line2P2.y() - center1.y(), -(line2P2.x() - center1.x()));
    const double v2Length = v2.length();
    v2 = v2 * (radius1 / v2Length);

    // offset the tangent vector's points
    line2P1 = center1.offset(v2.x(), v2.y());
    line2P2 = line2P2.offset(v2.x(), v2.y());

    return 2;
}

/**
 * @brief 
 * @param  center1          
 * @param  radius1          
 * @param  center2          
 * @param  radius2          
 * @param  line1P1          
 * @param  line1P2          
 * @param  line2P1          
 * @param  line2P2          
 * @return int 
 */
int GeometryMath::circleCircleInnerTangents(const PointF &center1,
                                            double radius1,
                                            const PointF &center2,
                                            double radius2, PointF &line1P1,
                                            PointF &line1P2, PointF &line2P1,
                                            PointF &line2P2)
{
    if (radius1 > radius2)
        return circleCircleInnerTangents(center2, radius2, center1, radius1,
                                         line1P1, line1P2, line2P1, line2P2);

    // determine the straight-line distance between the centers
    const double d = center1.distance(center2);
    const double radius1a = radius1 + radius2;

    // check for solvability
    if (d <= radius1a || qIsEqual(d, radius1a))
    {
        // no solution. circles intersect or touch.
        return 0;
    }

    if (!tangentPointAndCircle(center1, radius1a, center2, line1P2, line2P2))
    {
        // there are no tangents
        return 0;
    }

    // get the vector perpendicular to the
    // first tangent with length radius2
    Vector2D v1((line1P2.y() - center2.y()), -(line1P2.x() - center2.x()));
    const double v1Length = v1.length();
    v1 = v1 * (radius2 / v1Length);

    // offset the tangent vector's points
    line1P1 = center2.offset(v1.x(), v1.y());
    line1P2 = line1P2.offset(v1.x(), v1.y());

    // get the vector perpendicular to the
    // second tangent with length radius2
    Vector2D v2(-(line2P2.y() - center2.y()), line2P2.x() - center2.x());
    const double v2Length = v2.length();
    v2 = v2 * (radius2 / v2Length);

    // offset the tangent vector's points in opposite direction
    line2P1 = center2.offset(v2.x(), v2.y());
    line2P2 = line2P2.offset(v2.x(), v2.y());

    return 2;
}

/**
 * @brief 
 * @param  p                
 * @param  s1               
 * @param  s2               
 * @return PointF 
 */
PointF GeometryMath::projectPointOnSegment(const PointF &p, const PointF &s1,
                                           const PointF &s2)
{
    const double nx = s2.y() - s1.y();
    const double ny = -(s2.x() - s1.x());
    const double t = (p.x() * ny - p.y() * nx - s1.x() * ny + s1.y() * nx) /
                     ((s2.x() - s1.x()) * ny - (s2.y() - s1.y()) * nx);
    return t < 0.   ? s1
           : t > 1. ? s2
                    : PointF(s1.x() + (s2.x() - s1.x()) * t,
                             s1.y() + (s2.y() - s1.y()) * t);
}

/**
 * @brief 
 * @param  x                
 * @param  y                
 * @param  x1               
 * @param  y1               
 * @param  x2               
 * @param  y2               
 * @return int 
 */
int GeometryMath::leftOfLine(const double x, const double y, const double x1,
                             const double y1, const double x2, const double y2)
{
    const double f1 = x - x1;
    const double f2 = y2 - y1;
    const double f3 = y - y1;
    const double f4 = x2 - x1;
    const double test = (f1 * f2 - f3 * f4);
    // return -1, 0, or 1
    return qIsEqual(test, 0.0) ? 0 : (test < 0 ? -1 : 1);
}

/**
 * @brief 
 * @param  point            
 * @param  p1               
 * @param  p2               
 * @return int 
 */
int GeometryMath::leftOfLine(const PointF &point, const PointF &p1,
                             const PointF &p2)
{
    return leftOfLine(point.x(), point.y(), p1.x(), p1.y(), p2.x(), p2.y());
}

/**
 * @brief 
 * @param  startPoint       
 * @param  directionPoint   
 * @param  distance         
 * @return PointF 
 */
PointF GeometryMath::pointOnLineWithDistance(const PointF &startPoint,
                                             const PointF &directionPoint,
                                             double distance)
{
    double x, y;
    pointOnLineWithDistance(startPoint.x(), startPoint.y(), directionPoint.x(),
                            directionPoint.y(), distance, x, y);
    return PointF(x, y);
}

/**
 * @brief 
 * @param  x1               
 * @param  y1               
 * @param  x2               
 * @param  y2               
 * @param  distance         
 * @param  x                
 * @param  y                
 * @param  z1               
 * @param  z2               
 * @param  z                
 * @param  m1               
 * @param  m2               
 * @param  m                
 */
void GeometryMath::pointOnLineWithDistance(double x1, double y1, double x2,
                                           double y2, double distance,
                                           double &x, double &y, double *z1,
                                           double *z2, double *z, double *m1,
                                           double *m2, double *m)
{
    const double dx = x2 - x1;
    const double dy = y2 - y1;
    const double length = std::sqrt(dx * dx + dy * dy);

    if (qIsEqual(length, 0.0))
    {
        x = x1;
        y = y1;
        if (z && z1) *z = *z1;
        if (m && m1) *m = *m1;
    }
    else
    {
        const double scaleFactor = distance / length;
        x = x1 + dx * scaleFactor;
        y = y1 + dy * scaleFactor;
        if (z && z1 && z2) *z = *z1 + (*z2 - *z1) * scaleFactor;
        if (m && m1 && m2) *m = *m1 + (*m2 - *m1) * scaleFactor;
    }
}

/**
 * @brief 
 * @param  x1               
 * @param  y1               
 * @param  x2               
 * @param  y2               
 * @param  proportion       
 * @param  offset           
 * @param  x                
 * @param  y                
 */
void GeometryMath::perpendicularOffsetPointAlongSegment(double x1, double y1,
                                                        double x2, double y2,
                                                        double proportion,
                                                        double offset,
                                                        double *x, double *y)
{
    // calculate point along segment
    const double mX = x1 + (x2 - x1) * proportion;
    const double mY = y1 + (y2 - y1) * proportion;
    const double pX = x1 - x2;
    const double pY = y1 - y2;
    double normalX = -pY;
    double normalY = pX;//#spellok
    const double normalLength =
            sqrt((normalX * normalX) + (normalY * normalY));//#spellok
    normalX /= normalLength;
    normalY /= normalLength;//#spellok

    *x = mX + offset * normalX;
    *y = mY + offset * normalY;
}

/**
 * @brief 
 * @param  pt1              
 * @param  pt2              
 * @param  pt3              
 * @param  distance         
 * @return PointF 
 */
PointF GeometryMath::interpolatePointOnArc(const PointF &pt1, const PointF &pt2,
                                           const PointF &pt3, double distance)
{
    double centerX, centerY, radius;
    circleCenterRadius(pt1, pt2, pt3, radius, centerX, centerY);

    const double theta = distance / radius;// angle subtended
    const double anglePt1 = std::atan2(pt1.y() - centerY, pt1.x() - centerX);
    const double anglePt2 = std::atan2(pt2.y() - centerY, pt2.x() - centerX);
    const double anglePt3 = std::atan2(pt3.y() - centerY, pt3.x() - centerX);
    const bool isClockwise = circleClockwise(anglePt1, anglePt2, anglePt3);
    const double angleDest = anglePt1 + (isClockwise ? -theta : theta);

    const double x = centerX + radius * (std::cos(angleDest));
    const double y = centerY + radius * (std::sin(angleDest));
    return PointF(x, y);
}

/**
 * @brief 
 * @param  dy               
 * @param  dx               
 * @return double 
 */
double GeometryMath::ccwAngle(double dy, double dx)
{
    const double angle = std::atan2(dy, dx) * 180 / M_PI;
    if (angle < 0) { return 360 + angle; }
    else if (angle > 360) { return 360 - angle; }
    return angle;
}

/**
 * @brief 
 * @param  pt1              
 * @param  pt2              
 * @param  pt3              
 * @param  radius           
 * @param  centerX          
 * @param  centerY          
 */
void GeometryMath::circleCenterRadius(const PointF &pt1, const PointF &pt2,
                                      const PointF &pt3, double &radius,
                                      double &centerX, double &centerY)
{
    double dx21, dy21, dx31, dy31, h21, h31, d;

    //closed circle
    if (qIsEqual(pt1.x(), pt3.x()) && qIsEqual(pt1.y(), pt3.y()))
    {
        centerX = (pt1.x() + pt2.x()) / 2.0;
        centerY = (pt1.y() + pt2.y()) / 2.0;
        radius = std::sqrt(std::pow(centerX - pt1.x(), 2.0) +
                           std::pow(centerY - pt1.y(), 2.0));
        return;
    }

    // Using Cartesian circumcenter eguations from page https://en.wikipedia.org/wiki/Circumscribed_circle
    dx21 = pt2.x() - pt1.x();
    dy21 = pt2.y() - pt1.y();
    dx31 = pt3.x() - pt1.x();
    dy31 = pt3.y() - pt1.y();

    h21 = std::pow(dx21, 2.0) + std::pow(dy21, 2.0);
    h31 = std::pow(dx31, 2.0) + std::pow(dy31, 2.0);

    // 2*Cross product, d<0 means clockwise and d>0 counterclockwise sweeping angle
    d = 2 * (dx21 * dy31 - dx31 * dy21);

    // Check colinearity, Cross product = 0
    if (qIsEqual(std::fabs(d), 0.0, 0.00000000001))
    {
        radius = -1.0;
        return;
    }

    // Calculate centroid coordinates and radius
    centerX = pt1.x() + (h21 * dy31 - h31 * dy21) / d;
    centerY = pt1.y() - (h21 * dx31 - h31 * dx21) / d;
    radius = std::sqrt(std::pow(centerX - pt1.x(), 2.0) +
                       std::pow(centerY - pt1.y(), 2.0));
}

/**
 * @brief 
 * @param  angle1           
 * @param  angle2           
 * @param  angle3           
 * @return true 
 * @return false 
 */
bool GeometryMath::circleClockwise(double angle1, double angle2, double angle3)
{
    if (angle3 >= angle1) { return !(angle2 > angle1 && angle2 < angle3); }
    else { return !(angle2 > angle1 || angle2 < angle3); }
}

/**
 * @brief 
 * @param  angle            
 * @param  angle1           
 * @param  angle2           
 * @param  clockwise        
 * @return true 
 * @return false 
 */
bool GeometryMath::circleAngleBetween(double angle, double angle1,
                                      double angle2, bool clockwise)
{
    if (clockwise)
    {
        if (angle2 < angle1) { return (angle <= angle1 && angle >= angle2); }
        else { return (angle <= angle1 || angle >= angle2); }
    }
    else
    {
        if (angle2 > angle1) { return (angle >= angle1 && angle <= angle2); }
        else { return (angle >= angle1 || angle <= angle2); }
    }
}

/**
 * @brief 
 * @param  angle            
 * @param  angle1           
 * @param  angle2           
 * @param  angle3           
 * @return true 
 * @return false 
 */
bool GeometryMath::angleOnCircle(double angle, double angle1, double angle2,
                                 double angle3)
{
    const bool clockwise = circleClockwise(angle1, angle2, angle3);
    return circleAngleBetween(angle, angle1, angle3, clockwise);
}

/**
 * @brief 
 * @param  x1               
 * @param  y1               
 * @param  x2               
 * @param  y2               
 * @param  x3               
 * @param  y3               
 * @return double 
 */
double GeometryMath::circleLength(double x1, double y1, double x2, double y2,
                                  double x3, double y3)
{
    double centerX, centerY, radius;
    circleCenterRadius(PointF(x1, y1), PointF(x2, y2), PointF(x3, y3), radius,
                       centerX, centerY);
    double length = M_PI / 180.0 * radius *
                    sweepAngle(centerX, centerY, x1, y1, x2, y2, x3, y3);
    if (length < 0) { length = -length; }
    return length;
}

/**
 * @brief 
 * @param  centerX          
 * @param  centerY          
 * @param  x1               
 * @param  y1               
 * @param  x2               
 * @param  y2               
 * @param  x3               
 * @param  y3               
 * @return double 
 */
double GeometryMath::sweepAngle(double centerX, double centerY, double x1,
                                double y1, double x2, double y2, double x3,
                                double y3)
{
    const double p1Angle = GeometryMath::ccwAngle(y1 - centerY, x1 - centerX);
    const double p2Angle = GeometryMath::ccwAngle(y2 - centerY, x2 - centerX);
    const double p3Angle = GeometryMath::ccwAngle(y3 - centerY, x3 - centerX);

    if (p3Angle >= p1Angle)
    {
        if (p2Angle > p1Angle && p2Angle < p3Angle)
        {
            return (p3Angle - p1Angle);
        }
        else { return (-(p1Angle + (360 - p3Angle))); }
    }
    else
    {
        if (p2Angle < p1Angle && p2Angle > p3Angle)
        {
            return (-(p1Angle - p3Angle));
        }
        else { return (p3Angle + (360 - p1Angle)); }
    }
}

/**
 * @brief 
 * @param  p1               
 * @param  p2               
 * @param  result           
 * @param  radius           
 * @param  mousePos         
 * @return true 
 * @return false 
 */
bool GeometryMath::segmentMidPoint(const PointF &p1, const PointF &p2,
                                   PointF &result, double radius,
                                   const PointF &mousePos)
{
    const PointF midPoint((p1.x() + p2.x()) / 2.0, (p1.y() + p2.y()) / 2.0);
    const double midDist = std::sqrt(sqrDistance2D(p1, midPoint));
    if (radius < midDist) { return false; }
    const double centerMidDist = std::sqrt(radius * radius - midDist * midDist);
    const double dist = radius - centerMidDist;

    const double midDx = midPoint.x() - p1.x();
    const double midDy = midPoint.y() - p1.y();

    //get the four possible midpoints
    std::vector<PointF> possibleMidPoints;
    possibleMidPoints.push_back(pointOnLineWithDistance(
            midPoint, PointF(midPoint.x() - midDy, midPoint.y() + midDx),
            dist));
    possibleMidPoints.push_back(pointOnLineWithDistance(
            midPoint, PointF(midPoint.x() - midDy, midPoint.y() + midDx),
            2 * radius - dist));
    possibleMidPoints.push_back(pointOnLineWithDistance(
            midPoint, PointF(midPoint.x() + midDy, midPoint.y() - midDx),
            dist));
    possibleMidPoints.push_back(pointOnLineWithDistance(
            midPoint, PointF(midPoint.x() + midDy, midPoint.y() - midDx),
            2 * radius - dist));

    //take the closest one
    double minDist = std::numeric_limits<double>::max();
    int minDistIndex = -1;
    for (int i = 0; i < possibleMidPoints.size(); ++i)
    {
        const double currentDist =
                sqrDistance2D(mousePos, possibleMidPoints.at(i));
        if (currentDist < minDist)
        {
            minDistIndex = i;
            minDist = currentDist;
        }
    }

    if (minDistIndex == -1) { return false; }

    result = possibleMidPoints.at(minDistIndex);

    return true;
}

/**
 * @brief 
 * @param  p1               
 * @param  p2               
 * @param  center           
 * @param  useShortestArc   
 * @return PointF 
 */
PointF GeometryMath::segmentMidPointFromCenter(const PointF &p1,
                                               const PointF &p2,
                                               const PointF &center,
                                               bool useShortestArc)
{
    double midPointAngle =
            averageAngle(lineAngle(center.x(), center.y(), p1.x(), p1.y()),
                         lineAngle(center.x(), center.y(), p2.x(), p2.y()));
    if (!useShortestArc) midPointAngle += M_PI;
    return center.project(center.distance(p1), midPointAngle * 180 / M_PI);
}

/**
 * @brief 
 * @param  tangentPoint     
 * @param  cp1              
 * @param  cp2              
 * @param  cp3              
 * @return double 
 */
double GeometryMath::circleTangentDirection(const PointF &tangentPoint,
                                            const PointF &cp1,
                                            const PointF &cp2,
                                            const PointF &cp3)
{
    //calculate circle midpoint
    double mX, mY, radius;
    circleCenterRadius(cp1, cp2, cp3, radius, mX, mY);

    const double p1Angle = GeometryMath::ccwAngle(cp1.y() - mY, cp1.x() - mX);
    const double p2Angle = GeometryMath::ccwAngle(cp2.y() - mY, cp2.x() - mX);
    const double p3Angle = GeometryMath::ccwAngle(cp3.y() - mY, cp3.x() - mX);
    double angle = 0;
    if (circleClockwise(p1Angle, p2Angle, p3Angle))
    {
        angle = lineAngle(tangentPoint.x(), tangentPoint.y(), mX, mY) - M_PI_2;
    }
    else
    {
        angle = lineAngle(mX, mY, tangentPoint.x(), tangentPoint.y()) - M_PI_2;
    }
    if (angle < 0) angle += 2 * M_PI;
    return angle;
}

/**
 * @brief 
 * @param  p1               
 * @param  p2               
 * @param  p3               
 * @param  points           
 * @param  tolerance        
 * @param  toleranceType    
 * @param  hasZ             
 * @param  hasM             
 */
void GeometryMath::segmentizeArc(const PointF &p1, const PointF &p2,
                                 const PointF &p3, PointSequence &points,
                                 double tolerance,
                                 SegmentationToleranceType toleranceType)
{
    bool reversed = false;
    const int segSide = segmentSide(p1, p3, p2);

    PointF circlePoint1;
    const PointF &circlePoint2 = p2;
    PointF circlePoint3;

    if (segSide == -1)
    {
        // Reverse !
        circlePoint1 = p3;
        circlePoint3 = p1;
        reversed = true;
    }
    else
    {
        circlePoint1 = p1;
        circlePoint3 = p3;
    }

    //adapted code from PostGIS
    double radius = 0;
    double centerX = 0;
    double centerY = 0;
    circleCenterRadius(circlePoint1, circlePoint2, circlePoint3, radius,
                       centerX, centerY);

    if (circlePoint1 != circlePoint3 &&
        (radius < 0 || qIsEqual(segSide, 0.0)))//points are colinear
    {
        points.push_back(p1);
        points.push_back(p2);
        points.push_back(p3);
        return;
    }

    double increment = tolerance;//one segment per degree
    if (toleranceType == MaximumDifference)
    {
        // Ensure tolerance is not higher than twice the radius
        tolerance = std::min(tolerance, radius * 2);
        const double halfAngle = std::acos(-tolerance / radius + 1);
        increment = 2 * halfAngle;
    }

    //angles of pt1, pt2, pt3
    const double a1 =
            std::atan2(circlePoint1.y() - centerY, circlePoint1.x() - centerX);
    double a2 =
            std::atan2(circlePoint2.y() - centerY, circlePoint2.x() - centerX);
    double a3 =
            std::atan2(circlePoint3.y() - centerY, circlePoint3.x() - centerX);

    // Make segmentation symmetric
    const bool symmetric = true;
    if (symmetric)
    {
        double angle = a3 - a1;
        // angle == 0 when full circle
        if (angle <= 0) angle += M_PI * 2;

        /* Number of segments in output */
        const int segs = ceil(angle / increment);
        /* Tweak increment to be regular for all the arc */
        increment = angle / segs;
    }

    /* Adjust a3 up so we can increment from a1 to a3 cleanly */
    // a3 == a1 when full circle
    if (a3 <= a1) a3 += 2.0 * M_PI;
    if (a2 < a1) a2 += 2.0 * M_PI;

    double x, y;
    double z = 0;
    double m = 0;

    std::vector<PointF> stringPoints;
    stringPoints.push_back(circlePoint1);
    if (circlePoint2 != circlePoint3 &&
        circlePoint1 !=
                circlePoint2)//draw straight line segment if two points have the same position
    {

        // As we're adding the last point in any case, we'll avoid
        // including a point which is at less than 1% increment distance
        // from it (may happen to find them due to numbers approximation).
        // NOTE that this effectively allows in output some segments which
        //      are more distant than requested. This is at most 1% off
        //      from requested MaxAngle and less for MaxError.
        const double tolError = increment / 100;
        const double stopAngle = a3 - tolError;
        for (double angle = a1 + increment; angle < stopAngle;
             angle += increment)
        {
            x = centerX + radius * std::cos(angle);
            y = centerY + radius * std::sin(angle);
            stringPoints.push_back(PointF(x, y));
        }
    }
    stringPoints.push_back(circlePoint3);

    // TODO: check if or implement QgsPointSequence directly taking an iterator to append
    if (reversed) { std::reverse(stringPoints.begin(), stringPoints.end()); }
    if (!points.empty() && stringPoints.front() == points.back())
        stringPoints.erase(stringPoints.begin());
    points.insert(points.end(), stringPoints.begin(), stringPoints.end());
}

/**
 * @brief 
 * @param  a1               
 * @param  a2               
 * @param  a3               
 * @param  b                
 * @param  distanceTolerance
 * @param  pointSpacingAngleTolerance
 * @return true 
 * @return false 
 */
bool GeometryMath::pointContinuesArc(const PointF &a1, const PointF &a2,
                                     const PointF &a3, const PointF &b,
                                     double distanceTolerance,
                                     double pointSpacingAngleTolerance)
{
    double centerX = 0;
    double centerY = 0;
    double radius = 0;
    circleCenterRadius(a1, a2, a3, radius, centerX, centerY);

    // Co-linear a1/a2/a3
    if (radius < 0.0) return false;

    // distance of candidate point to center of arc a1-a2-a3
    const double bDistance = std::sqrt((b.x() - centerX) * (b.x() - centerX) +
                                       (b.y() - centerY) * (b.y() - centerY));

    double diff = std::fabs(radius - bDistance);

    auto arcAngle = [](const PointF &a, const PointF &b,
                       const PointF &c) -> double {
        const double abX = b.x() - a.x();
        const double abY = b.y() - a.y();

        const double cbX = b.x() - c.x();
        const double cbY = b.y() - c.y();

        const double dot = (abX * cbX + abY * cbY);   /* dot product */
        const double cross = (abX * cbY - abY * cbX); /* cross product */

        const double alpha = std::atan2(cross, dot);

        return alpha;
    };

    // Is the point b on the circle?
    if (diff < distanceTolerance)
    {
        const double angle1 = arcAngle(a1, a2, a3);
        const double angle2 = arcAngle(a2, a3, b);

        // Is the sweep angle similar to the previous one?
        // We only consider a segment replaceable by an arc if the points within
        // it are regularly spaced
        diff = std::fabs(angle1 - angle2);
        if (diff > pointSpacingAngleTolerance) { return false; }

        const int a2Side =
                leftOfLine(a2.x(), a2.y(), a1.x(), a1.y(), a3.x(), a3.y());
        const int bSide =
                leftOfLine(b.x(), b.y(), a1.x(), a1.y(), a3.x(), a3.y());

        // Is the point b on the same side of a1/a3 as the mid-point a2 is?
        // If not, it's in the unbounded part of the circle, so it continues the arc, return true.
        if (bSide != a2Side) return true;
    }
    return false;
}

/**
 * @brief 
 * @param  pt1              
 * @param  pt3              
 * @param  pt2              
 * @return int 
 */
int GeometryMath::segmentSide(const PointF &pt1, const PointF &pt3,
                              const PointF &pt2)
{
    const double side = ((pt2.x() - pt1.x()) * (pt3.y() - pt1.y()) -
                         (pt3.x() - pt1.x()) * (pt2.y() - pt1.y()));
    if (side == 0.0) { return 0; }
    else
    {
        if (side < 0) { return -1; }
        if (side > 0) { return 1; }
        return 0;
    }
}

/**
 * @brief 
 * @param  angle            
 * @param  a1               
 * @param  a2               
 * @param  a3               
 * @param  zm1              
 * @param  zm2              
 * @param  zm3              
 * @return double 
 */
double GeometryMath::interpolateArcValue(double angle, double a1, double a2,
                                         double a3, double zm1, double zm2,
                                         double zm3)
{
    /* Counter-clockwise sweep */
    if (a1 < a2)
    {
        if (angle <= a2) return zm1 + (zm2 - zm1) * (angle - a1) / (a2 - a1);
        else
            return zm2 + (zm3 - zm2) * (angle - a2) / (a3 - a2);
    }
    /* Clockwise sweep */
    else
    {
        if (angle >= a2) return zm1 + (zm2 - zm1) * (a1 - angle) / (a1 - a2);
        else
            return zm2 + (zm3 - zm2) * (a2 - angle) / (a2 - a3);
    }
}

/**
 * @brief 
 * @param  angle            
 * @return double 
 */
double GeometryMath::normalizedAngle(double angle)
{
    double clippedAngle = angle;
    if (clippedAngle >= M_PI * 2 || clippedAngle <= -2 * M_PI)
    {
        clippedAngle = std::fmod(clippedAngle, 2 * M_PI);
    }
    if (clippedAngle < 0.0) { clippedAngle += 2 * M_PI; }
    return clippedAngle;
}

/**
 * @brief 
 * @param  x1               
 * @param  y1               
 * @param  x2               
 * @param  y2               
 * @return double 
 */
double GeometryMath::lineAngle(double x1, double y1, double x2, double y2)
{
    const double at = std::atan2(y2 - y1, x2 - x1);
    const double a = -at + M_PI_2;
    return normalizedAngle(a);
}

/**
 * @brief 
 * @param  x1               
 * @param  y1               
 * @param  x2               
 * @param  y2               
 * @param  x3               
 * @param  y3               
 * @return double 
 */
double GeometryMath::angleBetweenThreePoints(double x1, double y1, double x2,
                                             double y2, double x3, double y3)
{
    const double angle1 = std::atan2(y1 - y2, x1 - x2);
    const double angle2 = std::atan2(y3 - y2, x3 - x2);
    return normalizedAngle(angle1 - angle2);
}

/**
 * @brief 
 * @param  x1               
 * @param  y1               
 * @param  x2               
 * @param  y2               
 * @return double 
 */
double GeometryMath::linePerpendicularAngle(double x1, double y1, double x2,
                                            double y2)
{
    double a = lineAngle(x1, y1, x2, y2);
    a += M_PI_2;
    return normalizedAngle(a);
}

/**
 * @brief 
 * @param  x1               
 * @param  y1               
 * @param  x2               
 * @param  y2               
 * @param  x3               
 * @param  y3               
 * @return double 
 */
double GeometryMath::averageAngle(double x1, double y1, double x2, double y2,
                                  double x3, double y3)
{
    const double a1 = lineAngle(x1, y1, x2, y2);
    const double a2 = lineAngle(x2, y2, x3, y3);
    return averageAngle(a1, a2);
}

/**
 * @brief 
 * @param  a1               
 * @param  a2               
 * @return double 
 */
double GeometryMath::averageAngle(double a1, double a2)
{
    a1 = normalizedAngle(a1);
    a2 = normalizedAngle(a2);
    double clockwiseDiff = 0.0;
    if (a2 >= a1) { clockwiseDiff = a2 - a1; }
    else { clockwiseDiff = a2 + (2 * M_PI - a1); }
    const double counterClockwiseDiff = 2 * M_PI - clockwiseDiff;

    double resultAngle = 0;
    if (clockwiseDiff <= counterClockwiseDiff)
    {
        resultAngle = a1 + clockwiseDiff / 2.0;
    }
    else { resultAngle = a1 - counterClockwiseDiff / 2.0; }
    return normalizedAngle(resultAngle);
}

/**
 * @brief 
 * @param  pt1              
 * @param  pt2              
 * @return PointF 
 */
PointF GeometryMath::midpoint(const PointF &pt1, const PointF &pt2)
{
    const double x = (pt1.x() + pt2.x()) / 2.0;
    const double y = (pt1.y() + pt2.y()) / 2.0;
    return PointF(x, y);
}

/**
 * @brief 
 * @param  x1               
 * @param  y1               
 * @param  x2               
 * @param  y2               
 * @param  fraction         
 * @return PointF 
 */
PointF GeometryMath::interpolatePointOnLine(double x1, double y1, double x2,
                                            double y2, double fraction)
{
    const double deltaX = (x2 - x1) * fraction;
    const double deltaY = (y2 - y1) * fraction;
    return PointF(x1 + deltaX, y1 + deltaY);
}

/**
 * @brief 
 * @param  p1               
 * @param  p2               
 * @param  fraction         
 * @return PointF 
 */
PointF GeometryMath::interpolatePointOnLine(const PointF &p1, const PointF &p2,
                                            double fraction)
{
    const double _fraction = 1 - fraction;
    return PointF(p1.x() * _fraction + p2.x() * fraction,
                  p1.y() * _fraction + p2.y() * fraction);
}

/**
 * @brief 
 * @param  x1               
 * @param  y1               
 * @param  v1               
 * @param  x2               
 * @param  y2               
 * @param  v2               
 * @param  value            
 * @return PointF 
 */
PointF GeometryMath::interpolatePointOnLineByValue(double x1, double y1,
                                                   double v1, double x2,
                                                   double y2, double v2,
                                                   double value)
{
    if (qIsEqual(v1, v2)) return PointF(x1, y1);

    const double fraction = (value - v1) / (v2 - v1);
    return interpolatePointOnLine(x1, y1, x2, y2, fraction);
}

/**
 * @brief 
 * @param  pt1              
 * @param  pt2              
 * @return double 
 */
double GeometryMath::gradient(const PointF &pt1, const PointF &pt2)
{
    const double delta_x = pt2.x() - pt1.x();
    const double delta_y = pt2.y() - pt1.y();
    if (qIsEqual(delta_x, 0.0)) { return INFINITY; }

    return delta_y / delta_x;
}

/**
 * @brief 
 * @param  pt1              
 * @param  pt2              
 * @param  a                
 * @param  b                
 * @param  c                
 */
void GeometryMath::coefficients(const PointF &pt1, const PointF &pt2, double &a,
                                double &b, double &c)
{
    if (qIsEqual(pt1.x(), pt2.x()))
    {
        a = 1;
        b = 0;
        c = -pt1.x();
    }
    else if (qIsEqual(pt1.y(), pt2.y()))
    {
        a = 0;
        b = 1;
        c = -pt1.y();
    }
    else
    {
        a = pt1.y() - pt2.y();
        b = pt2.x() - pt1.x();
        c = pt1.x() * pt2.y() - pt1.y() * pt2.x();
    }
}

/**
 * @brief 
 * @param  p                
 * @param  s1               
 * @param  s2               
 * @return LineF 
 */
LineF GeometryMath::perpendicularSegment(const PointF &p, const PointF &s1,
                                         const PointF &s2)
{
    LineF line;
    PointF p2;

    if ((p == s1) || (p == s2)) { return line; }

    double a, b, c;
    coefficients(s1, s2, a, b, c);

    if (qIsEqual(a, 0)) { p2 = PointF(p.x(), s1.y()); }
    else if (qIsEqual(b, 0)) { p2 = PointF(s1.x(), p.y()); }
    else
    {
        const double y = (-c - a * p.x()) / b;
        const double m = gradient(s1, s2);
        const double d2 = 1 + m * m;
        const double H = p.y() - y;
        const double dx = m * H / d2;
        const double dy = m * dx;
        p2 = PointF(p.x() + dx, y + dy);
    }

    line.setP1(p);
    line.setP2(p2);

    return line;
}

/**
 * @brief 
 * @param  centerPointX     
 * @param  centerPointY     
 * @param  segmentPoint1x   
 * @param  segmentPoint1y   
 * @param  segmentPoint2x   
 * @param  segmentPoint2y   
 * @param  perpendicularSegmentPoint1x
 * @param  perpendicularSegmentPoint1y
 * @param  perpendicularSegmentPoint2x
 * @param  perpendicularSegmentPoint2y
 * @param  segmentLength    
 */
void GeometryMath::perpendicularCenterSegment(
        double centerPointX, double centerPointY, double segmentPoint1x,
        double segmentPoint1y, double segmentPoint2x, double segmentPoint2y,
        double &perpendicularSegmentPoint1x,
        double &perpendicularSegmentPoint1y,
        double &perpendicularSegmentPoint2x,
        double &perpendicularSegmentPoint2y, double segmentLength)
{
    Vector2D segmentVector = Vector2D(segmentPoint2x - segmentPoint1x,
                                      segmentPoint2y - segmentPoint1y);
    Vector2D perpendicularVector = segmentVector.perpVector();
    if (segmentLength != 0)
    {
        perpendicularVector =
                perpendicularVector.normalized() * (segmentLength) / 2;
    }

    perpendicularSegmentPoint1x = centerPointX - perpendicularVector.x();
    perpendicularSegmentPoint1y = centerPointY - perpendicularVector.y();
    perpendicularSegmentPoint2x = centerPointX + perpendicularVector.x();
    perpendicularSegmentPoint2y = centerPointY + perpendicularVector.y();
}

/**
 * @brief 
 * @param  P1               
 * @param  P12              
 * @param  P2               
 * @param  P22              
 * @return double 
 */
double GeometryMath::skewLinesDistance(const Vector3D &P1, const Vector3D &P12,
                                       const Vector3D &P2, const Vector3D &P22)
{
    const Vector3D u1 = P12 - P1;
    const Vector3D u2 = P22 - P2;
    Vector3D u3 = Vector3D::crossProduct(u1, u2);
    if (u3.length() == 0) return 1;
    u3.normalize();
    const Vector3D dir = P1 - P2;
    return std::fabs(
            (Vector3D::dotProduct(dir, u3)));// u3 is already normalized
}

/**
 * @brief 
 * @param  P1               
 * @param  P12              
 * @param  P2               
 * @param  P22              
 * @param  X1               
 * @param  epsilon          
 * @return true 
 * @return false 
 */
bool GeometryMath::skewLinesProjection(const Vector3D &P1, const Vector3D &P12,
                                       const Vector3D &P2, const Vector3D &P22,
                                       Vector3D &X1, double epsilon)
{
    const Vector3D d = P2 - P1;
    Vector3D u1 = P12 - P1;
    u1.normalize();
    Vector3D u2 = P22 - P2;
    u2.normalize();
    const Vector3D u3 = Vector3D::crossProduct(u1, u2);

    if (std::fabs(u3.x()) <= epsilon && std::fabs(u3.y()) <= epsilon &&
        std::fabs(u3.z()) <= epsilon)
    {
        // The rays are almost parallel.
        return false;
    }

    // X1 and X2 are the closest points on lines
    // we want to find X1 (lies on u1)
    // solving the linear equation in r1 and r2: Xi = Pi + ri*ui
    // we are only interested in X1 so we only solve for r1.
    float a1 = Vector3D::dotProduct(u1, u1), b1 = Vector3D::dotProduct(u1, u2),
          c1 = Vector3D::dotProduct(u1, d);
    float a2 = Vector3D::dotProduct(u1, u2), b2 = Vector3D::dotProduct(u2, u2),
          c2 = Vector3D::dotProduct(u2, d);
    if (!(std::fabs(b1) > epsilon))
    {
        // Denominator is close to zero.
        return false;
    }
    if (!(a2 != -1 && a2 != 1))
    {
        // Lines are parallel
        return false;
    }

    const double r1 = (c2 - b2 * c1 / b1) / (a2 - b2 * a1 / b1);
    X1 = P1 + u1 * r1;

    return true;
}

/**
 * @brief 
 * @param  La1              
 * @param  La2              
 * @param  Lb1              
 * @param  Lb2              
 * @param  intersection     
 * @return true 
 * @return false 
 */
bool GeometryMath::linesIntersection3D(const Vector3D &La1, const Vector3D &La2,
                                       const Vector3D &Lb1, const Vector3D &Lb2,
                                       Vector3D &intersection)
{
    // if all Vector are on the same plane (have the same Z), use the 2D intersection
    // else return a false result
    if (qIsEqual(La1.z(), La2.z()) && qIsEqual(La1.z(), Lb1.z()) &&
        qIsEqual(La1.z(), Lb2.z()))
    {
        PointF ptInter;
        bool isIntersection;
        segmentIntersection(PointF(La1.x(), La1.y()), PointF(La2.x(), La2.y()),
                            PointF(Lb1.x(), Lb1.y()), PointF(Lb2.x(), Lb2.y()),
                            ptInter, isIntersection, 1e-8, true);
        intersection.set(ptInter.x(), ptInter.y(), La1.z());
        return true;
    }

    // first check if lines have an exact intersection point
    // do it by checking if the shortest distance is exactly 0
    const float distance = skewLinesDistance(La1, La2, Lb1, Lb2);
    if (qIsEqual(distance, 0.0f))
    {
        // 3d lines have exact intersection point.
        const Vector3D C = La2;
        const Vector3D D = Lb2;
        const Vector3D e = La1 - La2;
        const Vector3D f = Lb1 - Lb2;
        const Vector3D g = D - C;
        if (qIsEqual((Vector3D::crossProduct(f, g)).length(), 0.0) ||
            qIsEqual((Vector3D::crossProduct(f, e)).length(), 0.0))
        {
            // Lines have no intersection, are they parallel?
            return false;
        }

        Vector3D fgn = Vector3D::crossProduct(f, g);
        fgn.normalize();

        Vector3D fen = Vector3D::crossProduct(f, e);
        fen.normalize();

        int di = -1;
        if (fgn == fen)// same direction?
            di *= -1;

        intersection = C + e * di *
                                   (Vector3D::crossProduct(f, g).length() /
                                    Vector3D::crossProduct(f, e).length());
        return true;
    }

    // try to calculate the approximate intersection point
    Vector3D X1, X2;
    const bool firstIsDone = skewLinesProjection(La1, La2, Lb1, Lb2, X1);
    const bool secondIsDone = skewLinesProjection(Lb1, Lb2, La1, La2, X2);

    if (!firstIsDone || !secondIsDone)
    {
        // Could not obtain projection point.
        return false;
    }

    intersection = (X1 + X2) / 2.0;
    return true;
}

/**
 * @brief 
 * @param  aX               
 * @param  aY               
 * @param  bX               
 * @param  bY               
 * @param  cX               
 * @param  cY               
 * @return double 
 */
double GeometryMath::triangleArea(double aX, double aY, double bX, double bY,
                                  double cX, double cY)
{
    return 0.5 * std::abs((aX - cX) * (bY - aY) - (aX - bX) * (cY - aY));
}

/**
 * @brief 
 * @param  x1               
 * @param  y1               
 * @param  x2               
 * @param  y2               
 * @param  px               
 * @param  py               
 * @return double 
 */
double GeometryMath::pointFractionAlongLine(double x1, double y1, double x2,
                                            double y2, double px, double py)
{
    const double dxp = px - x1;
    const double dyp = py - y1;

    const double dxl = x2 - x1;
    const double dyl = y2 - y1;

    return std::sqrt((dxp * dxp) + (dyp * dyp)) /
           std::sqrt((dxl * dxl) + (dyl * dyl));
}

/**
 * @brief 
 * @param  aX               
 * @param  aY               
 * @param  bX               
 * @param  bY               
 * @param  cX               
 * @param  cY               
 * @param  weightB          
 * @param  weightC          
 * @param  pointX           
 * @param  pointY           
 */
void GeometryMath::weightedPointInTriangle(double aX, double aY, double bX,
                                           double bY, double cX, double cY,
                                           double weightB, double weightC,
                                           double &pointX, double &pointY)
{
    if (weightB + weightC > 1)
    {
        weightB = 1 - weightB;
        weightC = 1 - weightC;
    }

    const double rBx = weightB * (bX - aX);
    const double rBy = weightB * (bY - aY);
    const double rCx = weightC * (cX - aX);
    const double rCy = weightC * (cY - aY);

    pointX = rBx + rCx + aX;
    pointY = rBy + rCy + aY;
}

/**
 * @brief 
 * @param  x1               
 * @param  y1               
 * @param  x2               
 * @param  y2               
 * @param  x3               
 * @param  y3               
 * @param  epsilon          
 * @return true 
 * @return false 
 */
bool GeometryMath::pointsAreCollinear(double x1, double y1, double x2,
                                      double y2, double x3, double y3,
                                      double epsilon)
{
    return qIsEqual(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2), 0,
                    epsilon);
}

/**
 * @brief 
 * @param  aX               
 * @param  aY               
 * @param  bX               
 * @param  bY               
 * @param  cX               
 * @param  cY               
 * @param  dX               
 * @param  dY               
 * @param  pointX           
 * @param  pointY           
 * @param  angle            
 * @return true 
 * @return false 
 */
bool GeometryMath::angleBisector(double aX, double aY, double bX, double bY,
                                 double cX, double cY, double dX, double dY,
                                 double &pointX, double &pointY, double &angle)
{
    const PointF pA = PointF(aX, aY);
    const PointF pB = PointF(bX, bY);
    const PointF pC = PointF(cX, cY);
    const PointF pD = PointF(dX, dY);
    angle = (pA.azimuth(pB) + pC.azimuth(pD)) / 2.0;

    PointF pOut;
    bool intersection = false;
    GeometryMath::segmentIntersection(pA, pB, pC, pD, pOut, intersection);

    pointX = pOut.x();
    pointY = pOut.y();

    return intersection;
}

/**
 * @brief 
 * @param  aX               
 * @param  aY               
 * @param  bX               
 * @param  bY               
 * @param  cX               
 * @param  cY               
 * @param  pointX           
 * @param  pointY           
 * @return true 
 * @return false 
 */
bool GeometryMath::bisector(double aX, double aY, double bX, double bY,
                            double cX, double cY, double &pointX,
                            double &pointY)
{
    const PointF pA = PointF(aX, aY);
    const PointF pB = PointF(bX, bY);
    const PointF pC = PointF(cX, cY);
    const double angle = (pA.azimuth(pB) + pA.azimuth(pC)) / 2.0;

    PointF pOut;
    bool intersection = false;
    GeometryMath::segmentIntersection(pB, pC, pA, pA.project(1.0, angle), pOut,
                                      intersection);

    pointX = pOut.x();
    pointY = pOut.y();

    return intersection;
}

}// namespace m2
