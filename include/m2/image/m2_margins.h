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
class M2_API Margins
{
public:
    constexpr Margins() noexcept;
    constexpr Margins(int left, int top, int right, int bottom) noexcept;

    constexpr bool isNull() const noexcept;

    constexpr int left() const noexcept;
    constexpr int top() const noexcept;
    constexpr int right() const noexcept;
    constexpr int bottom() const noexcept;

    constexpr void setLeft(int left) noexcept;
    constexpr void setTop(int top) noexcept;
    constexpr void setRight(int right) noexcept;
    constexpr void setBottom(int bottom) noexcept;

    constexpr Margins &operator+=(const Margins &margins) noexcept;
    constexpr Margins &operator-=(const Margins &margins) noexcept;
    constexpr Margins &operator+=(int) noexcept;
    constexpr Margins &operator-=(int) noexcept;
    constexpr Margins &operator*=(int) noexcept;
    constexpr Margins &operator/=(int);
    constexpr Margins &operator*=(double) noexcept;
    constexpr Margins &operator/=(double);

    [[nodiscard]] constexpr inline MarginsF toMarginsF() const noexcept;

private:
    int m_left;
    int m_top;
    int m_right;
    int m_bottom;

    friend constexpr inline bool operator==(const Margins &m1,
                                            const Margins &m2) noexcept
    {
        return m1.m_left == m2.m_left && m1.m_top == m2.m_top &&
               m1.m_right == m2.m_right && m1.m_bottom == m2.m_bottom;
    }

    friend constexpr inline bool operator!=(const Margins &m1,
                                            const Margins &m2) noexcept
    {
        return !(m1 == m2);
    }
};

class M2_API MarginsF
{
public:
    constexpr MarginsF() noexcept;
    constexpr MarginsF(double left, double top, double right,
                       double bottom) noexcept;
    constexpr MarginsF(const Margins &margins) noexcept;

    constexpr bool isNull() const noexcept;

    constexpr double left() const noexcept;
    constexpr double top() const noexcept;
    constexpr double right() const noexcept;
    constexpr double bottom() const noexcept;

    constexpr void setLeft(double aleft) noexcept;
    constexpr void setTop(double atop) noexcept;
    constexpr void setRight(double aright) noexcept;
    constexpr void setBottom(double abottom) noexcept;

    constexpr MarginsF &operator+=(const MarginsF &margins) noexcept;
    constexpr MarginsF &operator-=(const MarginsF &margins) noexcept;
    constexpr MarginsF &operator+=(double addend) noexcept;
    constexpr MarginsF &operator-=(double subtrahend) noexcept;
    constexpr MarginsF &operator*=(double factor) noexcept;
    constexpr MarginsF &operator/=(double divisor);

    constexpr inline Margins toMargins() const noexcept;

private:
    double m_left;
    double m_top;
    double m_right;
    double m_bottom;

    friend constexpr inline bool operator==(const MarginsF &lhs,
                                            const MarginsF &rhs) noexcept
    {
        return qFuzzyCompare(lhs.left(), rhs.left()) &&
               qFuzzyCompare(lhs.top(), rhs.top()) &&
               qFuzzyCompare(lhs.right(), rhs.right()) &&
               qFuzzyCompare(lhs.bottom(), rhs.bottom());
    }

    friend constexpr inline bool operator!=(const MarginsF &lhs,
                                            const MarginsF &rhs) noexcept
    {
        return !(lhs == rhs);
    }
};


/*****************************************************************************
  Margins inline functions
 *****************************************************************************/

constexpr inline Margins::Margins() noexcept
    : m_left(0), m_top(0), m_right(0), m_bottom(0)
{
}

constexpr inline Margins::Margins(int aleft, int atop, int aright,
                                  int abottom) noexcept
    : m_left(aleft), m_top(atop), m_right(aright), m_bottom(abottom)
{
}

constexpr inline bool Margins::isNull() const noexcept
{
    return m_left == 0 && m_top == 0 && m_right == 0 && m_bottom == 0;
}

constexpr inline int Margins::left() const noexcept { return m_left; }

constexpr inline int Margins::top() const noexcept { return m_top; }

constexpr inline int Margins::right() const noexcept { return m_right; }

constexpr inline int Margins::bottom() const noexcept { return m_bottom; }


constexpr inline void Margins::setLeft(int aleft) noexcept { m_left = aleft; }

constexpr inline void Margins::setTop(int atop) noexcept { m_top = atop; }

constexpr inline void Margins::setRight(int aright) noexcept
{
    m_right = aright;
}

constexpr inline void Margins::setBottom(int abottom) noexcept
{
    m_bottom = abottom;
}

constexpr inline Margins operator+(const Margins &m1,
                                   const Margins &m2) noexcept
{
    return Margins(m1.left() + m2.left(), m1.top() + m2.top(),
                   m1.right() + m2.right(), m1.bottom() + m2.bottom());
}

constexpr inline Margins operator-(const Margins &m1,
                                   const Margins &m2) noexcept
{
    return Margins(m1.left() - m2.left(), m1.top() - m2.top(),
                   m1.right() - m2.right(), m1.bottom() - m2.bottom());
}

constexpr inline Margins operator+(const Margins &lhs, int rhs) noexcept
{
    return Margins(lhs.left() + rhs, lhs.top() + rhs, lhs.right() + rhs,
                   lhs.bottom() + rhs);
}

constexpr inline Margins operator+(int lhs, const Margins &rhs) noexcept
{
    return Margins(rhs.left() + lhs, rhs.top() + lhs, rhs.right() + lhs,
                   rhs.bottom() + lhs);
}

constexpr inline Margins operator-(const Margins &lhs, int rhs) noexcept
{
    return Margins(lhs.left() - rhs, lhs.top() - rhs, lhs.right() - rhs,
                   lhs.bottom() - rhs);
}

constexpr inline Margins operator*(const Margins &margins, int factor) noexcept
{
    return Margins(margins.left() * factor, margins.top() * factor,
                   margins.right() * factor, margins.bottom() * factor);
}

constexpr inline Margins operator*(int factor, const Margins &margins) noexcept
{
    return Margins(margins.left() * factor, margins.top() * factor,
                   margins.right() * factor, margins.bottom() * factor);
}

constexpr inline Margins operator*(const Margins &margins,
                                   double factor) noexcept
{
    return Margins(qRound(margins.left() * factor),
                   qRound(margins.top() * factor),
                   qRound(margins.right() * factor),
                   qRound(margins.bottom() * factor));
}

constexpr inline Margins operator*(double factor,
                                   const Margins &margins) noexcept
{
    return Margins(qRound(margins.left() * factor),
                   qRound(margins.top() * factor),
                   qRound(margins.right() * factor),
                   qRound(margins.bottom() * factor));
}

constexpr inline Margins operator/(const Margins &margins, int divisor)
{
    return Margins(margins.left() / divisor, margins.top() / divisor,
                   margins.right() / divisor, margins.bottom() / divisor);
}

constexpr inline Margins operator/(const Margins &margins, double divisor)
{
    return Margins(qRound(margins.left() / divisor),
                   qRound(margins.top() / divisor),
                   qRound(margins.right() / divisor),
                   qRound(margins.bottom() / divisor));
}

constexpr inline Margins operator|(const Margins &m1,
                                   const Margins &m2) noexcept
{
    return Margins(qMax(m1.left(), m2.left()), qMax(m1.top(), m2.top()),
                   qMax(m1.right(), m2.right()),
                   qMax(m1.bottom(), m2.bottom()));
}

constexpr inline Margins &Margins::operator+=(const Margins &margins) noexcept
{
    return *this = *this + margins;
}

constexpr inline Margins &Margins::operator-=(const Margins &margins) noexcept
{
    return *this = *this - margins;
}

constexpr inline Margins &Margins::operator+=(int margin) noexcept
{
    m_left += margin;
    m_top += margin;
    m_right += margin;
    m_bottom += margin;
    return *this;
}

constexpr inline Margins &Margins::operator-=(int margin) noexcept
{
    m_left -= margin;
    m_top -= margin;
    m_right -= margin;
    m_bottom -= margin;
    return *this;
}

constexpr inline Margins &Margins::operator*=(int factor) noexcept
{
    return *this = *this * factor;
}

constexpr inline Margins &Margins::operator/=(int divisor)
{
    return *this = *this / divisor;
}

constexpr inline Margins &Margins::operator*=(double factor) noexcept
{
    return *this = *this * factor;
}

constexpr inline Margins &Margins::operator/=(double divisor)
{
    return *this = *this / divisor;
}

constexpr inline Margins operator+(const Margins &margins) noexcept
{
    return margins;
}

constexpr inline Margins operator-(const Margins &margins) noexcept
{
    return Margins(-margins.left(), -margins.top(), -margins.right(),
                   -margins.bottom());
}


/*****************************************************************************
  MarginsF inline functions
 *****************************************************************************/

constexpr inline MarginsF::MarginsF() noexcept
    : m_left(0), m_top(0), m_right(0), m_bottom(0)
{
}

constexpr inline MarginsF::MarginsF(double aleft, double atop, double aright,
                                    double abottom) noexcept
    : m_left(aleft), m_top(atop), m_right(aright), m_bottom(abottom)
{
}

constexpr inline MarginsF::MarginsF(const Margins &margins) noexcept
    : m_left(margins.left()), m_top(margins.top()), m_right(margins.right()),
      m_bottom(margins.bottom())
{
}

constexpr inline bool MarginsF::isNull() const noexcept
{
    return qFuzzyIsNull(m_left) && qFuzzyIsNull(m_top) &&
           qFuzzyIsNull(m_right) && qFuzzyIsNull(m_bottom);
}

constexpr inline double MarginsF::left() const noexcept { return m_left; }

constexpr inline double MarginsF::top() const noexcept { return m_top; }

constexpr inline double MarginsF::right() const noexcept { return m_right; }

constexpr inline double MarginsF::bottom() const noexcept { return m_bottom; }


constexpr inline void MarginsF::setLeft(double aleft) noexcept
{
    m_left = aleft;
}

constexpr inline void MarginsF::setTop(double atop) noexcept { m_top = atop; }

constexpr inline void MarginsF::setRight(double aright) noexcept
{
    m_right = aright;
}

constexpr inline void MarginsF::setBottom(double abottom) noexcept
{
    m_bottom = abottom;
}

constexpr inline MarginsF operator+(const MarginsF &lhs,
                                    const MarginsF &rhs) noexcept
{
    return MarginsF(lhs.left() + rhs.left(), lhs.top() + rhs.top(),
                    lhs.right() + rhs.right(), lhs.bottom() + rhs.bottom());
}

constexpr inline MarginsF operator-(const MarginsF &lhs,
                                    const MarginsF &rhs) noexcept
{
    return MarginsF(lhs.left() - rhs.left(), lhs.top() - rhs.top(),
                    lhs.right() - rhs.right(), lhs.bottom() - rhs.bottom());
}

constexpr inline MarginsF operator+(const MarginsF &lhs, double rhs) noexcept
{
    return MarginsF(lhs.left() + rhs, lhs.top() + rhs, lhs.right() + rhs,
                    lhs.bottom() + rhs);
}

constexpr inline MarginsF operator+(double lhs, const MarginsF &rhs) noexcept
{
    return MarginsF(rhs.left() + lhs, rhs.top() + lhs, rhs.right() + lhs,
                    rhs.bottom() + lhs);
}

constexpr inline MarginsF operator-(const MarginsF &lhs, double rhs) noexcept
{
    return MarginsF(lhs.left() - rhs, lhs.top() - rhs, lhs.right() - rhs,
                    lhs.bottom() - rhs);
}

constexpr inline MarginsF operator*(const MarginsF &lhs, double rhs) noexcept
{
    return MarginsF(lhs.left() * rhs, lhs.top() * rhs, lhs.right() * rhs,
                    lhs.bottom() * rhs);
}

constexpr inline MarginsF operator*(double lhs, const MarginsF &rhs) noexcept
{
    return MarginsF(rhs.left() * lhs, rhs.top() * lhs, rhs.right() * lhs,
                    rhs.bottom() * lhs);
}

constexpr inline MarginsF operator/(const MarginsF &lhs, double divisor)
{
    assert(divisor < 0 || divisor > 0);
    return MarginsF(lhs.left() / divisor, lhs.top() / divisor,
                    lhs.right() / divisor, lhs.bottom() / divisor);
}

constexpr inline MarginsF operator|(const MarginsF &m1,
                                    const MarginsF &m2) noexcept
{
    return MarginsF(qMax(m1.left(), m2.left()), qMax(m1.top(), m2.top()),
                    qMax(m1.right(), m2.right()),
                    qMax(m1.bottom(), m2.bottom()));
}

constexpr inline MarginsF &
MarginsF::operator+=(const MarginsF &margins) noexcept
{
    return *this = *this + margins;
}

constexpr inline MarginsF &
MarginsF::operator-=(const MarginsF &margins) noexcept
{
    return *this = *this - margins;
}

constexpr inline MarginsF &MarginsF::operator+=(double addend) noexcept
{
    m_left += addend;
    m_top += addend;
    m_right += addend;
    m_bottom += addend;
    return *this;
}

constexpr inline MarginsF &MarginsF::operator-=(double subtrahend) noexcept
{
    m_left -= subtrahend;
    m_top -= subtrahend;
    m_right -= subtrahend;
    m_bottom -= subtrahend;
    return *this;
}

constexpr inline MarginsF &MarginsF::operator*=(double factor) noexcept
{
    return *this = *this * factor;
}

constexpr inline MarginsF &MarginsF::operator/=(double divisor)
{
    return *this = *this / divisor;
}

constexpr inline MarginsF operator+(const MarginsF &margins) noexcept
{
    return margins;
}

constexpr inline MarginsF operator-(const MarginsF &margins) noexcept
{
    return MarginsF(-margins.left(), -margins.top(), -margins.right(),
                    -margins.bottom());
}

constexpr MarginsF Margins::toMarginsF() const noexcept { return *this; }

constexpr inline Margins MarginsF::toMargins() const noexcept
{
    return Margins(qRound(m_left), qRound(m_top), qRound(m_right),
                   qRound(m_bottom));
}

}// namespace m2

#endif//M2_MARGINS_H_