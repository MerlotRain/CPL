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

#ifndef M2_SIZE_H_
#define M2_SIZE_H_

#include <m2_margins.h>

namespace m2 {

enum AspectRatioMode
{
    eIgnoreAspectRatio,
    eKeepAspectRatio,
    eKeepAspectRatioByExpanding
};

class SizeF;
class M2_API Size
{
public:
    constexpr Size() noexcept;
    constexpr Size(int w, int h) noexcept;

    constexpr inline bool isNull() const noexcept;
    constexpr inline bool isEmpty() const noexcept;
    constexpr inline bool isValid() const noexcept;

    constexpr inline int width() const noexcept;
    constexpr inline int height() const noexcept;
    constexpr inline void setWidth(int w) noexcept;
    constexpr inline void setHeight(int h) noexcept;
    void transpose() noexcept;
    [[nodiscard]] constexpr inline Size transposed() const noexcept;

    inline void scale(int w, int h, AspectRatioMode mode) noexcept;
    inline void scale(const Size &s, AspectRatioMode mode) noexcept;
    [[nodiscard]] Size scaled(int w, int h,
                              AspectRatioMode mode) const noexcept;
    [[nodiscard]] Size scaled(const Size &s,
                              AspectRatioMode mode) const noexcept;

    [[nodiscard]] constexpr inline Size expandedTo(const Size &) const noexcept;
    [[nodiscard]] constexpr inline Size boundedTo(const Size &) const noexcept;

    [[nodiscard]] constexpr Size grownBy(Margins m) const noexcept
    {
        return {width() + m.left() + m.right(),
                height() + m.top() + m.bottom()};
    }
    [[nodiscard]] constexpr Size shrunkBy(Margins m) const noexcept
    {
        return {width() - m.left() - m.right(),
                height() - m.top() - m.bottom()};
    }

    constexpr inline int &rwidth() noexcept;
    constexpr inline int &rheight() noexcept;

    constexpr inline Size &operator+=(const Size &) noexcept;
    constexpr inline Size &operator-=(const Size &) noexcept;
    constexpr inline Size &operator*=(double c) noexcept;
    inline Size &operator/=(double c);

    friend inline constexpr bool operator==(const Size &s1,
                                            const Size &s2) noexcept
    {
        return s1.wd == s2.wd && s1.ht == s2.ht;
    }
    friend inline constexpr bool operator!=(const Size &s1,
                                            const Size &s2) noexcept
    {
        return s1.wd != s2.wd || s1.ht != s2.ht;
    }
    friend inline constexpr Size operator+(const Size &s1,
                                           const Size &s2) noexcept
    {
        return Size(s1.wd + s2.wd, s1.ht + s2.ht);
    }
    friend inline constexpr Size operator-(const Size &s1,
                                           const Size &s2) noexcept
    {
        return Size(s1.wd - s2.wd, s1.ht - s2.ht);
    }
    friend inline constexpr Size operator*(const Size &s, double c) noexcept
    {
        return Size(qRound(s.wd * c), qRound(s.ht * c));
    }
    friend inline constexpr Size operator*(double c, const Size &s) noexcept
    {
        return s * c;
    }
    friend inline Size operator/(const Size &s, double c)
    {
        assert(!qFuzzyIsNull(c));
        return Size(qRound(s.wd / c), qRound(s.ht / c));
    }
    [[nodiscard]] inline constexpr SizeF toSizeF() const noexcept;

private:
    int wd;
    int ht;
};

class M2_API SizeF
{
public:
    constexpr SizeF() noexcept;
    constexpr SizeF(const Size &sz) noexcept;
    constexpr SizeF(double w, double h) noexcept;

    inline bool isNull() const noexcept;
    constexpr inline bool isEmpty() const noexcept;
    constexpr inline bool isValid() const noexcept;

    constexpr inline double width() const noexcept;
    constexpr inline double height() const noexcept;
    constexpr inline void setWidth(double w) noexcept;
    constexpr inline void setHeight(double h) noexcept;
    void transpose() noexcept;
    [[nodiscard]] constexpr inline SizeF transposed() const noexcept;

    inline void scale(double w, double h, AspectRatioMode mode) noexcept;
    inline void scale(const SizeF &s, AspectRatioMode mode) noexcept;
    [[nodiscard]] SizeF scaled(double w, double h,
                               AspectRatioMode mode) const noexcept;
    [[nodiscard]] SizeF scaled(const SizeF &s,
                               AspectRatioMode mode) const noexcept;

    [[nodiscard]] constexpr inline SizeF
    expandedTo(const SizeF &) const noexcept;
    [[nodiscard]] constexpr inline SizeF
    boundedTo(const SizeF &) const noexcept;

    [[nodiscard]] constexpr SizeF grownBy(MarginsF m) const noexcept
    {
        return {width() + m.left() + m.right(),
                height() + m.top() + m.bottom()};
    }
    [[nodiscard]] constexpr SizeF shrunkBy(MarginsF m) const noexcept
    {
        return {width() - m.left() - m.right(),
                height() - m.top() - m.bottom()};
    }

    constexpr inline double &rwidth() noexcept;
    constexpr inline double &rheight() noexcept;

    constexpr inline SizeF &operator+=(const SizeF &) noexcept;
    constexpr inline SizeF &operator-=(const SizeF &) noexcept;
    constexpr inline SizeF &operator*=(double c) noexcept;
    inline SizeF &operator/=(double c);

    friend constexpr inline bool operator==(const SizeF &s1, const SizeF &s2)
    {
        return ((!s1.wd || !s2.wd) ? qFuzzyIsNull(s1.wd - s2.wd)
                                   : qFuzzyCompare(s1.wd, s2.wd)) &&
               ((!s1.ht || !s2.ht) ? qFuzzyIsNull(s1.ht - s2.ht)
                                   : qFuzzyCompare(s1.ht, s2.ht));
    }
    friend constexpr inline bool operator!=(const SizeF &s1, const SizeF &s2)
    {
        return !(s1 == s2);
    }
    friend constexpr inline SizeF operator+(const SizeF &s1,
                                            const SizeF &s2) noexcept
    {
        return SizeF(s1.wd + s2.wd, s1.ht + s2.ht);
    }
    friend constexpr inline SizeF operator-(const SizeF &s1,
                                            const SizeF &s2) noexcept
    {
        return SizeF(s1.wd - s2.wd, s1.ht - s2.ht);
    }
    friend constexpr inline SizeF operator*(const SizeF &s, double c) noexcept
    {
        return SizeF(s.wd * c, s.ht * c);
    }
    friend constexpr inline SizeF operator*(double c, const SizeF &s) noexcept
    {
        return s * c;
    }
    friend inline SizeF operator/(const SizeF &s, double c)
    {
        assert(!qFuzzyIsNull(c));
        return SizeF(s.wd / c, s.ht / c);
    }

    constexpr inline Size toSize() const noexcept;

private:
    double wd;
    double ht;
};


/*****************************************************************************
  Size inline functions
 *****************************************************************************/

constexpr inline Size::Size() noexcept : wd(-1), ht(-1) {}

constexpr inline Size::Size(int w, int h) noexcept : wd(w), ht(h) {}

constexpr inline bool Size::isNull() const noexcept
{
    return wd == 0 && ht == 0;
}

constexpr inline bool Size::isEmpty() const noexcept
{
    return wd < 1 || ht < 1;
}

constexpr inline bool Size::isValid() const noexcept
{
    return wd >= 0 && ht >= 0;
}

constexpr inline int Size::width() const noexcept { return wd; }

constexpr inline int Size::height() const noexcept { return ht; }

constexpr inline void Size::setWidth(int w) noexcept { wd = w; }

constexpr inline void Size::setHeight(int h) noexcept { ht = h; }

constexpr inline Size Size::transposed() const noexcept { return Size(ht, wd); }

inline void Size::scale(int w, int h, AspectRatioMode mode) noexcept
{
    scale(Size(w, h), mode);
}

inline void Size::scale(const Size &s, AspectRatioMode mode) noexcept
{
    *this = scaled(s, mode);
}

inline Size Size::scaled(int w, int h, AspectRatioMode mode) const noexcept
{
    return scaled(Size(w, h), mode);
}

constexpr inline int &Size::rwidth() noexcept { return wd; }

constexpr inline int &Size::rheight() noexcept { return ht; }

constexpr inline Size &Size::operator+=(const Size &s) noexcept
{
    wd += s.wd;
    ht += s.ht;
    return *this;
}

constexpr inline Size &Size::operator-=(const Size &s) noexcept
{
    wd -= s.wd;
    ht -= s.ht;
    return *this;
}

constexpr inline Size &Size::operator*=(double c) noexcept
{
    wd = qRound(wd * c);
    ht = qRound(ht * c);
    return *this;
}

inline Size &Size::operator/=(double c)
{
    assert(!qFuzzyIsNull(c));
    wd = qRound(wd / c);
    ht = qRound(ht / c);
    return *this;
}

constexpr inline Size Size::expandedTo(const Size &otherSize) const noexcept
{
    return Size(qMax(wd, otherSize.wd), qMax(ht, otherSize.ht));
}

constexpr inline Size Size::boundedTo(const Size &otherSize) const noexcept
{
    return Size(qMin(wd, otherSize.wd), qMin(ht, otherSize.ht));
}


/*****************************************************************************
  SizeF inline functions
 *****************************************************************************/

constexpr inline SizeF::SizeF() noexcept : wd(-1.), ht(-1.) {}

constexpr inline SizeF::SizeF(const Size &sz) noexcept
    : wd(sz.width()), ht(sz.height())
{
}

constexpr inline SizeF::SizeF(double w, double h) noexcept : wd(w), ht(h) {}

inline bool SizeF::isNull() const noexcept
{
    return qIsNull(wd) && qIsNull(ht);
}

constexpr inline bool SizeF::isEmpty() const noexcept
{
    return wd <= 0. || ht <= 0.;
}

constexpr inline bool SizeF::isValid() const noexcept
{
    return wd >= 0. && ht >= 0.;
}

constexpr inline double SizeF::width() const noexcept { return wd; }

constexpr inline double SizeF::height() const noexcept { return ht; }

constexpr inline void SizeF::setWidth(double w) noexcept { wd = w; }

constexpr inline void SizeF::setHeight(double h) noexcept { ht = h; }

constexpr inline SizeF SizeF::transposed() const noexcept
{
    return SizeF(ht, wd);
}

inline void SizeF::scale(double w, double h, AspectRatioMode mode) noexcept
{
    scale(SizeF(w, h), mode);
}

inline void SizeF::scale(const SizeF &s, AspectRatioMode mode) noexcept
{
    *this = scaled(s, mode);
}

inline SizeF SizeF::scaled(double w, double h,
                           AspectRatioMode mode) const noexcept
{
    return scaled(SizeF(w, h), mode);
}

constexpr inline double &SizeF::rwidth() noexcept { return wd; }

constexpr inline double &SizeF::rheight() noexcept { return ht; }

constexpr inline SizeF &SizeF::operator+=(const SizeF &s) noexcept
{
    wd += s.wd;
    ht += s.ht;
    return *this;
}

constexpr inline SizeF &SizeF::operator-=(const SizeF &s) noexcept
{
    wd -= s.wd;
    ht -= s.ht;
    return *this;
}

constexpr inline SizeF &SizeF::operator*=(double c) noexcept
{
    wd *= c;
    ht *= c;
    return *this;
}

inline SizeF &SizeF::operator/=(double c)
{
    assert(!qFuzzyIsNull(c) && std::isfinite(c));
    wd = wd / c;
    ht = ht / c;
    return *this;
}

constexpr inline SizeF SizeF::expandedTo(const SizeF &otherSize) const noexcept
{
    return SizeF(qMax(wd, otherSize.wd), qMax(ht, otherSize.ht));
}

constexpr inline SizeF SizeF::boundedTo(const SizeF &otherSize) const noexcept
{
    return SizeF(qMin(wd, otherSize.wd), qMin(ht, otherSize.ht));
}

constexpr inline Size SizeF::toSize() const noexcept
{
    return Size(qRound(wd), qRound(ht));
}

constexpr SizeF Size::toSizeF() const noexcept { return *this; }


}// namespace m2

#endif//M2_SIZE_H_