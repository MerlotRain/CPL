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

#ifndef M2_TRANSFORM_H_
#define M2_TRANSFORM_H_

namespace m2 {

class Transform
{
public:
    Transform();
    Transform(double h11, double h12, double h13,
              double h21, double h22, double h23,
              double h31, double h32, double h33);
    Transform(double h11, double h12,
              double h21, double h22,
              double dx, double dy);

    Transform(const Transform &) noexcept = default;
    Transform(Transform &&) noexcept = default;
    Transform &operator=(const Transform &) noexcept = default;
    Transform &operator=(Transform &&) noexcept = default;

    bool isAffine() const;
    bool isIdentity() const;
    bool isInvertible() const;
    bool isScaling() const;
    bool isRotating() const;
    bool isTranslating() const;

    double m11() const;
    double m12() const;
    double m13() const;
    double m21() const;
    double m22() const;
    double m23() const;
    double m31() const;
    double m32() const;
    double m33() const;

private:
    double m[3][3];
    mutable unsigned int m_type;
    mutable unsigned int m_dirty;
};

}// namespace m2

#endif//M2_TRANSFORM_H_