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

#ifndef M2_ELLIPSE_H_
#define M2_ELLIPSE_H_

#include <m2_point.h>
#include <m2_rect.h>

namespace m2 {

class Ellipse
{
public:
    Ellipse();
    Ellipse(const Ellipse &);
    Ellipse &operator=(const Ellipse &);
    Ellipse(Ellipse &&);
    Ellipse &operator=(Ellipse &&);
    Ellipse(const PointF &center, double semiMajorAxis, double semiMinorAxis, double azimuth = 90);

    ~Ellipse();

    static Ellipse fromFoci(const PointF &pt1, const PointF &pt2, const PointF &pt3);
    static Ellipse fromExtent(const PointF &pt1, const PointF &pt2);
    static Ellipse fromCenterPoint(const PointF &ptc, const PointF &pt1);
    static Ellipse fromCenter2Points(const PointF &ptc, const PointF &pt1, const PointF &pt2);

    virtual bool operator==(const Ellipse &elp) const;
    virtual bool operator!=(const Ellipse &elp) const;

    virtual bool isEmpty() const;
    PointF center() const;
    double semiMajorAxis() const;
    double semiMinorAxis() const;
    double azimuth() const;

    void setCenter(const PointF &center);
    virtual void setSemiMajorAxis(double semiMajorAxis);
    virtual void setSemiMinorAxis(double semiMinorAxis);
    void setAzimuth(double azimuth);
    virtual double focusDistance() const;

    virtual bool foci(PointF &f1, PointF &f2) const;

    virtual double eccentricity() const;
    virtual double area() const;
    virtual double perimeter() const;

    virtual PointSequence quadrant() const;
    virtual PointSequence points(unsigned int segments = 36) const;
    virtual PolygonF toPolygon(unsigned int segments = 36) const;

    virtual PolygonF orientedBoundingBox() const;
    virtual RectF boundingBox() const;

protected:
    PointF m_Center;
    double m_SemiMajorAxis;
    double m_SemiMinorAxis;
    double m_Azimuth;

private:
    void normalizeAxis();
};

}// namespace m2

#endif//M2_ELLIPSE_H_