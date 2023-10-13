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

#ifndef M2_TRIANGLE_H_
#define M2_TRIANGLE_H_

#include <m2_line.h>
#include <m2_point.h>

namespace m2 {

class Circle;
class Triangle
{
public:
    Triangle();
    Triangle(const PointF &p1, const PointF &p2, const PointF &p3);
    bool operator==(const Triangle &other) const;
    bool operator!=(const Triangle &other) const;

    std::vector<double> lengths() const;
    std::vector<double> angles() const;

    bool isDegenerate() const;
    bool isIsocele(double lengthTolerance = 0.0001) const;
    bool isEquilateral(double lengthTolerance = 0.0001) const;
    bool isRight(double angleTolerance = 0.0001) const;
    bool isScalene(double lengthTolerance = 0.0001) const;

    std::vector<LineF> altitudes() const;
    std::vector<LineF> medians() const;
    std::vector<LineF> bisectors(double lengthTolerance = 0.0001) const;

    Triangle medial() const;
    PointF orthocenter(double lengthTolerance = 0.0001) const;
    PointF circumscribedCenter() const;
    double circumscribedRadius() const;
    Circle circumscribedCircle() const;

    PointF inscribedCenter() const;
    double inscribedRadius() const;
    Circle inscribedCircle() const;

private:
    PointF m_points[3];
};

}// namespace m2

#endif//M2_TRIANGLE_H_