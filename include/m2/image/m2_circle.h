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

#ifndef M2_CIRCLE_H_
#define M2_CIRCLE_H_

#include <m2_ellipse.h>

namespace m2 {

class Circle : public Ellipse
{
public:
    Circle();
    Circle(const PointF &center, double radius, double azimuth = 0);

    static Circle from2Points(const PointF &pt1, const PointF &pt2);
    
    static Circle
    from3Points(const PointF &pt1, const PointF &pt2, const PointF &pt3,
                double epsilon = std::numeric_limits<double>::epsilon());

    static Circle fromCenterDiameter(const PointF &center, double diameter,
                                     double azimuth = 0);
    static Circle fromCenterPoint(const PointF &center, const PointF &pt1);

    static Circle
    from3Tangents(const PointF &pt1_tg1, const PointF &pt2_tg1,
                  const PointF &pt1_tg2, const PointF &pt2_tg2,
                  const PointF &pt1_tg3, const PointF &pt2_tg3,
                  double epsilon = std::numeric_limits<double>::epsilon(),
                  const PointF &pos = PointF());

    static std::vector<Circle>
    from3TangentsMulti(const PointF &pt1_tg1, const PointF &pt2_tg1,
                       const PointF &pt1_tg2, const PointF &pt2_tg2,
                       const PointF &pt1_tg3, const PointF &pt2_tg3,
                       double epsilon = std::numeric_limits<double>::epsilon(),
                       const PointF &pos = PointF());

    static Circle fromExtent(const PointF &pt1, const PointF &pt2);

    static Circle minimalCircleFrom3Points(
            const PointF &pt1, const PointF &pt2, const PointF &pt3,
            double epsilon = std::numeric_limits<double>::epsilon());

    int intersections(const Circle &other, PointF &intersection1,
                      PointF &intersection2) const;

    bool tangentToPoint(const PointF &p, PointF &pt1, PointF &pt2) const;

    int outerTangents(const Circle &other, PointF &line1P1, PointF &line1P2,
                      PointF &line2P1, PointF &line2P2) const;

    int innerTangents(const Circle &other, PointF &line1P1, PointF &line1P2,
                      PointF &line2P1, PointF &line2P2) const;

    double area() const override;
    double perimeter() const override;

    void setSemiMajorAxis(double semiMajorAxis) override;
    void setSemiMinorAxis(double semiMinorAxis) override;
    double radius() const;
    void setRadius(double radius);

    PointSequence northQuadrant() const;
    bool
    contains(const PointF &point,
             double epsilon = std::numeric_limits<double>::epsilon()) const;

    RectF boundingBox() const override;
};

}// namespace m2

#endif//M2_CIRCLE_H_