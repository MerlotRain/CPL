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

#ifndef M2_MARGINS_H_
#define M2_MARGINS_H_

#include <m2_math.h>
#include <preconfig.h>

namespace m2 {

class MarginsF;
class LIBM2_EXPORT Margins
{
public:
    Margins() noexcept;
    Margins(int left, int top, int right, int bottom) noexcept;

    bool isNull() const noexcept;

    int left() const noexcept;
    int top() const noexcept;
    int right() const noexcept;
    int bottom() const noexcept;

    void setLeft(int left) noexcept;
    void setTop(int top) noexcept;
    void setRight(int right) noexcept;
    void setBottom(int bottom) noexcept;

    Margins &operator+=(const Margins &margins) noexcept;
    Margins &operator-=(const Margins &margins) noexcept;
    Margins &operator+=(int) noexcept;
    Margins &operator-=(int) noexcept;
    Margins &operator*=(int) noexcept;
    Margins &operator/=(int);
    Margins &operator*=(double) noexcept;
    Margins &operator/=(double);

    [[nodiscard]] MarginsF toMarginsF() const noexcept;

private:
    int m_left;
    int m_top;
    int m_right;
    int m_bottom;

    friend inline bool operator==(const Margins &m1, const Margins &m2) noexcept
    {
        return m1.m_left == m2.m_left && m1.m_top == m2.m_top &&
               m1.m_right == m2.m_right && m1.m_bottom == m2.m_bottom;
    }

    friend inline bool operator!=(const Margins &m1, const Margins &m2) noexcept
    {
        return !(m1 == m2);
    }
};

class LIBM2_EXPORT MarginsF
{
public:
    MarginsF() noexcept;
    MarginsF(double left, double top, double right, double bottom) noexcept;
    MarginsF(const Margins &margins) noexcept;

    bool isNull() const noexcept;

    double left() const noexcept;
    double top() const noexcept;
    double right() const noexcept;
    double bottom() const noexcept;

    void setLeft(double aleft) noexcept;
    void setTop(double atop) noexcept;
    void setRight(double aright) noexcept;
    void setBottom(double abottom) noexcept;

    MarginsF &operator+=(const MarginsF &margins) noexcept;
    MarginsF &operator-=(const MarginsF &margins) noexcept;
    MarginsF &operator+=(double addend) noexcept;
    MarginsF &operator-=(double subtrahend) noexcept;
    MarginsF &operator*=(double factor) noexcept;
    MarginsF &operator/=(double divisor);

    Margins toMargins() const noexcept;

private:
    double m_left;
    double m_top;
    double m_right;
    double m_bottom;

    friend inline bool operator==(const MarginsF &lhs,
                                  const MarginsF &rhs) noexcept
    {
        return qFuzzyCompare(lhs.left(), rhs.left()) &&
               qFuzzyCompare(lhs.top(), rhs.top()) &&
               qFuzzyCompare(lhs.right(), rhs.right()) &&
               qFuzzyCompare(lhs.bottom(), rhs.bottom());
    }

    friend inline bool operator!=(const MarginsF &lhs,
                                  const MarginsF &rhs) noexcept
    {
        return !(lhs == rhs);
    }
};

}// namespace m2

#endif//M2_MARGINS_H_