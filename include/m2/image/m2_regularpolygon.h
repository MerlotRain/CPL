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

#ifndef M2_REGULARPOLYGON_H_
#define M2_REGULARPOLYGON_H_

#include <m2_circle.h>
#include <m2_point.h>
#include <m2_polygon.h>
#include <m2_triangle.h>

namespace m2 {

template<int NUM_SIDES>
class RegularPolygon
{
    static_assert((NUM_SIDES < 3),
                  "A regular polygon requires at least three sides");

public:
    enum ConstructionOption
    {
        InscribedCircle,
        CircumscribedCircle
    };

    inline RegularPolygon() : m_radius(0.0) {}
    inline RegularPolygon(const PointF &center, double radius, double azimuth,
                          ConstructionOption circle);
    inline RegularPolygon(const PointF &center, const PointF &pt1,
                          ConstructionOption circle);
    inline RegularPolygon(const PointF &pt1, const PointF &pt2);

    bool operator==(const RegularPolygon &rp) const;
    bool operator!=(const RegularPolygon &rp) const;

    bool isEmpty() const;

    PointF center() const;
    double radius() const;
    PointF firstVertex() const;

    double apothem() const;
    unsigned int numberSides() const;
    void setCenter(const PointF &center);
    void setRadius(double radius);
    void setFirstVertex(const PointF &firstVertex);
    PointSequence points() const;

    Triangle toTriangle() const;
    std::vector<Triangle> triangulate() const;
    Circle inscribedCircle() const;
    Circle circumscribedCircle() const;

    double interiorAngle() const;
    double centralAngle() const;
    double area() const;
    double perimeter() const;
    double length() const;

private:
    double apothemToRadius(double apothem) const;

private:
    PointF m_center;
    PointF m_firstVertex;
    double m_radius;
};

template<int NUM_SIDES>
inline RegularPolygon<NUM_SIDES>::RegularPolygon() : m_radius(0.0)
{
}

template<int NUM_SIDES>
inline RegularPolygon<NUM_SIDES>::RegularPolygon(const PointF &center,
                                                 double radius, double azimuth,
                                                 ConstructionOption circle)
    : m_center(center)
{
    switch (circle)
    {
        case InscribedCircle:
            {
                m_radius = qAbs(radius);
                m_firstVertex = m_center.project(m_radius, azimuth);
            }
            break;
        case CircumscribedCircle:
            {
                m_radius = apothemToRadius(qAbs(m_radius), NUM_SIDES);
                m_firstVertex = m_center.project(
                        m_radius, azimuth - centralAngle(NUM_SIDES) / 2);
            }
        default:
            break;
    }
}

template<int NUM_SIDES>
inline RegularPolygon<NUM_SIDES>::RegularPolygon(const PointF &center,
                                                 const PointF &pt1,
                                                 ConstructionOption circle)
    : m_center(center)
{
    switch (circle)
    {
        case InscribedCircle:
            {
                m_firstVertex = pt1;
                m_center = center.distance(pt1);
                break;
            }
        case CircumscribedCircle:
            {
                m_center = apothemToRadius(center.distance(pt1), NUM_SIDES);
                const double azimuth = center.azimuth(pt1);
                m_firstVertex = m_center.project(
                        m_center, azimuth - centralAngle(NUM_SIDES) / 2);
                break;
            }
    }
}

template<int NUM_SIDES>
inline RegularPolygon<NUM_SIDES>::RegularPolygon(const PointF &pt1,
                                                 const PointF &pt2)
{
    const double azimuth = pt1.azimuth(pt2);
    const PointF pm =
            PointF((pt1.x() + pt2.x()) / 2.0, (pt1.y() + pt2.y()) / 2.0);
    const double length = pt1.distance(pm);

    const double angle = (180 - (360 / numSides)) / 2.0;
    const double hypothenuse = length / std::cos(angle * M_PI / 180);
    m_center = pt1.project(hypothenuse, azimuth + angle);
    m_firstVertex = pt1;
    m_radius = std::fabs(hypothenuse);
}

template<int NUM_SIDES>
inline bool
RegularPolygon<NUM_SIDES>::operator==(const RegularPolygon &rp) const
{
    return (m_center == rp.m_center) && (m_firstVertex == rp.m_firstVertex) &&
           (m_radius == rp.m_radius);
}

template<int NUM_SIDES>
inline bool
RegularPolygon<NUM_SIDES>::operator!=(const RegularPolygon &rp) const
{
    return !operator==(rp);
}

template<int NUM_SIDES>
inline bool RegularPolygon<NUM_SIDES>::isEmpty() const
{
    return m_center.isValid() || m_firstVertex.isValid() ||
           (m_center == m_firstVertex);
}

template<int NUM_SIDES>
inline PointF RegularPolygon<NUM_SIDES>::center() const
{
    return m_center;
}

template<int NUM_SIDES>
inline double RegularPolygon<NUM_SIDES>::radius() const
{
    return m_radius;
}

template<int NUM_SIDES>
inline PointF RegularPolygon<NUM_SIDES>::firstVertex() const
{
    return m_firstVertex;
}

template<int NUM_SIDES>
inline double RegularPolygon<NUM_SIDES>::apothem() const
{
    return m_radius * std::cos(M_PI / NUM_SIDES);
}

template<int NUM_SIDES>
inline unsigned int RegularPolygon<NUM_SIDES>::numberSides() const
{
    return NUM_SIDES;
}

template<int NUM_SIDES>
inline void RegularPolygon<NUM_SIDES>::setCenter(const PointF &center)
{
    const double azimuth =
            m_firstVertex.isEmpty() ? 0 : m_center.azimuth(m_firstVertex);
    m_center = center;
    m_firstVertex = center.project(m_radius, azimuth);
}

template<int NUM_SIDES>
inline void RegularPolygon<NUM_SIDES>::setRadius(double radius)
{
    m_radius = std::fabs(radius);
    const double azimuth =
            m_firstVertex.isEmpty() ? 0 : m_center.azimuth(m_firstVertex);
    m_firstVertex = m_center.project(m_radius, azimuth);
}

template<int NUM_SIDES>
inline void RegularPolygon<NUM_SIDES>::setFirstVertex(const PointF &firstVertex)
{
    const double azimuth = m_center.azimuth(m_firstVertex);
    m_firstVertex = firstVertex;
    m_center = m_firstVertex.project(m_radius, azimuth);
}

template<int NUM_SIDES>
inline PointSequence RegularPolygon<NUM_SIDES>::points() const
{
    PointSequence pts;
    if (isEmpty()) { return pts; }

    double azimuth = m_center.azimuth(m_firstVertex);
    const double azimuth_add = centralAngle();
    unsigned int n = 1;
    while (n <= NUM_SIDES)
    {
        pts.push_back(m_center.project(m_radius, azimuth));
        azimuth += azimuth_add;
        if ((azimuth_add > 0) && (azimuth > 180.0)) { azimuth -= 360.0; }

        n++;
    }

    return pts;
}

template<int NUM_SIDES>
inline Triangle RegularPolygon<NUM_SIDES>::toTriangle() const
{
    if (isEmpty() || (NUM_SIDES != 3)) { return Triangle(); }

    PointSequence pts;
    pts = points();

    return Triangle(pts.at(0), pts.at(1), pts.at(2));
}

template<int NUM_SIDES>
inline std::vector<Triangle> RegularPolygon<NUM_SIDES>::triangulate() const
{
    std::vector<Triangle> l_tri;
    if (isEmpty()) { return l_tri; }

    PointSequence pts;
    pts = points();

    unsigned int n = 0;
    while (n < NUM_SIDES - 1)
    {
        l_tri.append(Triangle(pts.at(n), pts.at(n + 1), m_center));
        n++;
    }
    l_tri.append(Triangle(pts.at(n), pts.at(0), m_center));

    return l_tri;
}

template<int NUM_SIDES>
inline Circle RegularPolygon<NUM_SIDES>::inscribedCircle() const
{
    return Circle(m_center, apothem());
}

template<int NUM_SIDES>
inline Circle RegularPolygon<NUM_SIDES>::circumscribedCircle() const
{
    return Circle(m_center, m_radius);
}

template<int NUM_SIDES>
inline double RegularPolygon<NUM_SIDES>::interiorAngle() const
{
    return (NUM_SIDES - 2) * 180 / NUM_SIDES;
}

template<int NUM_SIDES>
inline double RegularPolygon<NUM_SIDES>::centralAngle() const
{
    return 360.0 / NUM_SIDES;
}

template<int NUM_SIDES>
inline double RegularPolygon<NUM_SIDES>::area() const
{
    if (isEmpty()) { return 0.0; }

    return (m_radius * m_radius * NUM_SIDES *
            std::sin(centralAngle() * M_PI / 180.0)) /
           2;
}

template<int NUM_SIDES>
inline double RegularPolygon<NUM_SIDES>::perimeter() const
{
    if (isEmpty()) { return 0.0; }

    return length() * NUM_SIDES;
}

template<int NUM_SIDES>
inline double RegularPolygon<NUM_SIDES>::length() const
{
    if (isEmpty()) { return 0.0; }

    return m_radius * 2 * std::sin(M_PI / NUM_SIDES);
}

template<int NUM_SIDES>
inline double RegularPolygon<NUM_SIDES>::apothemToRadius(double apothem) const
{
    return apothem / std::cos(M_PI / NUM_SIDES);
}

}// namespace m2

#endif//M2_REGULARPOLYGON_H_