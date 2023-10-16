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

#ifndef M2_BEZIER_H_
#define M2_BEZIER_H_

#include <m2_point.h>

namespace m2 {

class RectF;
class PolygonF;
class PointF;
class LineF;

class M2_API Bezier
{
public:
    static Bezier fromPoints(const PointF &p1, const PointF &p2,
                             const PointF &p3, const PointF &p4);
    static void coefficients(double t, double &a, double &b, double &c,
                             double &d);

    PointF pointAt(double t) const;
    PointF normalVector(double t) const;

    PointF derivedAt(double t) const;
    PointF secondDerivedAt(double t) const;

    PolygonF toPolygon(double bezier_flattening_threshold = 0.5) const;
    void addToPolygon(PolygonF *p,
                      double bezier_flattening_threshold = 0.5) const;

    RectF bounds() const;
    double length(double error = 0.01) const;
    void addIfClose(double *length, double error) const;

    double tAtLength(double len) const;

    int stationaryYPoints(double &t0, double &t1) const;
    double tForY(double t0, double t1, double y) const;

    inline PointF pt1() const { return PointF(x1, y1); }
    inline PointF pt2() const { return PointF(x2, y2); }
    inline PointF pt3() const { return PointF(x3, y3); }
    inline PointF pt4() const { return PointF(x4, y4); }

    PointF midPoint() const;
    LineF midTangent() const;

    LineF startTangent() const;
    LineF endTangent() const;

    void parameterSplitLeft(double t, Bezier *left);
    std::pair<Bezier, Bezier> split() const;

    int shifted(Bezier *curveSegments, int maxSegmets, double offset,
                float threshold) const;

    Bezier bezierOnInterval(double t0, double t1) const;
    Bezier getSubRange(double t0, double t1) const;


    double x1, y1, x2, y2, x3, y3, x4, y4;
};

}// namespace m2

#endif//M2_BEZIER_H_