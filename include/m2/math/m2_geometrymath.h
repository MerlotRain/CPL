/****************************************************************************
**
** Copyright (C) 2023 MerlotRain
** Github:https://github.com/MerlotRain
**
** M2 is a cross platform C++basic library that encapsulates commonly 
** used C++ classes and functional modules, shields system functions from 
** the outside, and provides a unified interface.
**
** $M2_BEGIN_LICENSE:MIT$
** Permission is hereby granted, free of charge, to any person obtaining a 
** copy of this software and associated documentation files (the “Software”), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
** DEALINGS IN THE SOFTWARE.
** 
** $M2_END_LICENSE$
**
****************************************************************************/

#ifndef M2_GEOMETRYMATH_H_
#define M2_GEOMETRYMATH_H_

#include <m2_circle.h>
#include <m2_line.h>
#include <m2_math.h>
#include <m2_point.h>
#include <m2_vector.h>

namespace m2 {

class GeometryMath
{
public:
    enum SegmentationToleranceType
    {
        MaximumAngle = 0,
        MaximumDifference
    };

    static double sqrDistance2D(const PointF &pt1, const PointF &pt2);

    static double
    sqrDistToLine(const PointF &pt, const PointF &pt1, const PointF &pt2,
                  PointF &minpt,
                  double epsilon = std::numeric_limits<double>::epsilon());

    static double
    distToInfiniteLine(const PointF &point, const PointF &linePoint1,
                       const PointF &linePoint2,
                       double epsilon = std::numeric_limits<double>::epsilon());

    static bool lineIntersection(const PointF &p1, Vector2D v1,
                                 const PointF &p2, Vector2D v2,
                                 PointF &intersection);

    static bool segmentIntersection(
            const PointF &p1, const PointF &p2, const PointF &q1,
            const PointF &q2, PointF &intersectionPoint, bool &isIntersection,
            double tolerance = std::numeric_limits<double>::epsilon(),
            bool acceptImproperIntersection = false);

    static bool lineCircleIntersection(const PointF &center, double radius,
                                       const PointF &linePoint1,
                                       const PointF &linePoint2,
                                       PointF &intersection);

    static int circleCircleIntersections(const PointF &center1, double radius1,
                                         const PointF &center2, double radius2,
                                         PointF &intersection1,
                                         PointF &intersection2);

    static bool tangentPointAndCircle(const PointF &center, double radius,
                                      const PointF &p, PointF &pt1,
                                      PointF &pt2);

    static int circleCircleOuterTangents(const PointF &center1, double radius1,
                                         const PointF &center2, double radius2,
                                         PointF &line1P1, PointF &line1P2,
                                         PointF &line2P1, PointF &line2P2);

    static int circleCircleInnerTangents(const PointF &center1, double radius1,
                                         const PointF &center2, double radius2,
                                         PointF &line1P1, PointF &line1P2,
                                         PointF &line2P1, PointF &line2P2);

    static PointF projectPointOnSegment(const PointF &p, const PointF &s1,
                                        const PointF &s2);

    static int leftOfLine(const double x, const double y, const double x1,
                          const double y1, const double x2, const double y2);

    static int leftOfLine(const PointF &point, const PointF &p1,
                          const PointF &p2);

    static PointF pointOnLineWithDistance(const PointF &startPoint,
                                          const PointF &directionPoint,
                                          double distance);

    static void
    pointOnLineWithDistance(double x1, double y1, double x2, double y2,
                            double distance, double &x, double &y,
                            double *z1 = nullptr, double *z2 = nullptr,
                            double *z = nullptr, double *m1 = nullptr,
                            double *m2 = nullptr, double *m = nullptr);

    static void perpendicularOffsetPointAlongSegment(double x1, double y1,
                                                     double x2, double y2,
                                                     double proportion,
                                                     double offset, double *x,
                                                     double *y);

    static PointF interpolatePointOnArc(const PointF &pt1, const PointF &pt2,
                                        const PointF &pt3, double distance);

    static double ccwAngle(double dy, double dx);

    static void circleCenterRadius(const PointF &pt1, const PointF &pt2,
                                   const PointF &pt3, double &radius,
                                   double &centerX, double &centerY);

    static bool circleClockwise(double angle1, double angle2, double angle3);

    static bool circleAngleBetween(double angle, double angle1, double angle2,
                                   bool clockwise);

    static bool angleOnCircle(double angle, double angle1, double angle2,
                              double angle3);

    static double circleLength(double x1, double y1, double x2, double y2,
                               double x3, double y3);

    static double sweepAngle(double centerX, double centerY, double x1,
                             double y1, double x2, double y2, double x3,
                             double y3);

    static bool segmentMidPoint(const PointF &p1, const PointF &p2,
                                PointF &result, double radius,
                                const PointF &mousePos);

    static PointF segmentMidPointFromCenter(const PointF &p1, const PointF &p2,
                                            const PointF &center,
                                            bool useShortestArc = true);

    static double circleTangentDirection(const PointF &tangentPoint,
                                         const PointF &cp1, const PointF &cp2,
                                         const PointF &cp3);

    static void
    segmentizeArc(const PointF &p1, const PointF &p2, const PointF &p3,
                  PointSequence &points, double tolerance = M_PI_2 / 90,
                  SegmentationToleranceType toleranceType = MaximumAngle,
                  bool hasZ = false, bool hasM = false);

    static bool pointContinuesArc(const PointF &a1, const PointF &a2,
                                  const PointF &a3, const PointF &b,
                                  double distanceTolerance,
                                  double pointSpacingAngleTolerance);

    static int segmentSide(const PointF &pt1, const PointF &pt3,
                           const PointF &pt2);

    static double interpolateArcValue(double angle, double a1, double a2,
                                      double a3, double zm1, double zm2,
                                      double zm3);

    static double normalizedAngle(double angle);

    static double lineAngle(double x1, double y1, double x2, double y2);

    static double angleBetweenThreePoints(double x1, double y1, double x2,
                                          double y2, double x3, double y3);

    static double linePerpendicularAngle(double x1, double y1, double x2,
                                         double y2);

    static double averageAngle(double x1, double y1, double x2, double y2,
                               double x3, double y3);

    static double averageAngle(double a1, double a2);

    static PointF midpoint(const PointF &pt1, const PointF &pt2);

    static PointF interpolatePointOnLine(double x1, double y1, double x2,
                                         double y2, double fraction);

    static PointF interpolatePointOnLine(const PointF &p1, const PointF &p2,
                                         double fraction);

    static PointF interpolatePointOnLineByValue(double x1, double y1, double v1,
                                                double x2, double y2, double v2,
                                                double value);

    static double gradient(const PointF &pt1, const PointF &pt2);

    static void coefficients(const PointF &pt1, const PointF &pt2, double &a,
                             double &b, double &c);

    static LineF perpendicularSegment(const PointF &p, const PointF &s1,
                                      const PointF &s2);

    static void perpendicularCenterSegment(
            double centerPointX, double centerPointY, double segmentPoint1x,
            double segmentPoint1y, double segmentPoint2x, double segmentPoint2y,
            double &perpendicularSegmentPoint1x,
            double &perpendicularSegmentPoint1y,
            double &perpendicularSegmentPoint2x,
            double &perpendicularSegmentPoint2y, double segmentLength = 0);

    static double skewLinesDistance(const Vector3D &P1, const Vector3D &P12,
                                    const Vector3D &P2, const Vector3D &P22);

    static bool skewLinesProjection(
            const Vector3D &P1, const Vector3D &P12, const Vector3D &P2,
            const Vector3D &P22, Vector3D &X1,
            double epsilon = std::numeric_limits<double>::epsilon());

    static bool linesIntersection3D(const Vector3D &La1, const Vector3D &La2,
                                    const Vector3D &Lb1, const Vector3D &Lb2,
                                    Vector3D &intersection);

    static double triangleArea(double aX, double aY, double bX, double bY,
                               double cX, double cY);

    static double pointFractionAlongLine(double x1, double y1, double x2,
                                         double y2, double px, double py);

    static void weightedPointInTriangle(double aX, double aY, double bX,
                                        double bY, double cX, double cY,
                                        double weightB, double weightC,
                                        double &pointX, double &pointY);

    static bool
    pointsAreCollinear(double x1, double y1, double x2, double y2, double x3,
                       double y3,
                       double epsilon = std::numeric_limits<double>::epsilon());

    static bool angleBisector(double aX, double aY, double bX, double bY,
                              double cX, double cY, double dX, double dY,
                              double &pointX, double &pointY, double &angle);

    static bool bisector(double aX, double aY, double bX, double bY, double cX,
                         double cY, double &pointX, double &pointY);
};

}// namespace m2

#endif//M2_GEOMETRYMATH_H_