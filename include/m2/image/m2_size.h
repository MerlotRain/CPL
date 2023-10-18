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
    Size() noexcept;
    Size(int w, int h) noexcept;

    bool isNull() const noexcept;
    bool isEmpty() const noexcept;
    bool isValid() const noexcept;

    int width() const noexcept;
    int height() const noexcept;
    void setWidth(int w) noexcept;
    void setHeight(int h) noexcept;
    void transpose() noexcept;
    [[nodiscard]] Size transposed() const noexcept;

    void scale(int w, int h, AspectRatioMode mode) noexcept;
    void scale(const Size &s, AspectRatioMode mode) noexcept;
    [[nodiscard]] Size scaled(int w, int h,
                              AspectRatioMode mode) const noexcept;
    [[nodiscard]] Size scaled(const Size &s,
                              AspectRatioMode mode) const noexcept;

    [[nodiscard]] Size expandedTo(const Size &) const noexcept;
    [[nodiscard]] Size boundedTo(const Size &) const noexcept;

    [[nodiscard]] Size grownBy(Margins m) const noexcept;
    [[nodiscard]] Size shrunkBy(Margins m) const noexcept;

    int &rwidth() noexcept;
    int &rheight() noexcept;

    Size &operator+=(const Size &) noexcept;
    Size &operator-=(const Size &) noexcept;
    Size &operator*=(double c) noexcept;
    Size &operator/=(double c);

    friend inline bool operator==(const Size &s1, const Size &s2) noexcept
    {
        return s1.wd == s2.wd && s1.ht == s2.ht;
    }
    friend inline bool operator!=(const Size &s1, const Size &s2) noexcept
    {
        return s1.wd != s2.wd || s1.ht != s2.ht;
    }
    friend inline Size operator+(const Size &s1, const Size &s2) noexcept
    {
        return Size(s1.wd + s2.wd, s1.ht + s2.ht);
    }
    friend inline Size operator-(const Size &s1, const Size &s2) noexcept
    {
        return Size(s1.wd - s2.wd, s1.ht - s2.ht);
    }
    friend inline Size operator*(const Size &s, double c) noexcept
    {
        return Size(qRound(s.wd * c), qRound(s.ht * c));
    }
    friend inline Size operator*(double c, const Size &s) noexcept
    {
        return s * c;
    }
    friend inline Size operator/(const Size &s, double c)
    {
        assert(!qFuzzyIsNull(c));
        return Size(qRound(s.wd / c), qRound(s.ht / c));
    }
    [[nodiscard]] SizeF toSizeF() const noexcept;

private:
    int wd;
    int ht;
};

class M2_API SizeF
{
public:
    SizeF() noexcept;
    SizeF(const Size &sz) noexcept;
    SizeF(double w, double h) noexcept;

    bool isNull() const noexcept;
    bool isEmpty() const noexcept;
    bool isValid() const noexcept;

    double width() const noexcept;
    double height() const noexcept;
    void setWidth(double w) noexcept;
    void setHeight(double h) noexcept;
    void transpose() noexcept;
    [[nodiscard]] SizeF transposed() const noexcept;

    void scale(double w, double h, AspectRatioMode mode) noexcept;
    void scale(const SizeF &s, AspectRatioMode mode) noexcept;
    [[nodiscard]] SizeF scaled(double w, double h,
                               AspectRatioMode mode) const noexcept;
    [[nodiscard]] SizeF scaled(const SizeF &s,
                               AspectRatioMode mode) const noexcept;

    [[nodiscard]] SizeF expandedTo(const SizeF &) const noexcept;
    [[nodiscard]] SizeF boundedTo(const SizeF &) const noexcept;

    [[nodiscard]] SizeF grownBy(MarginsF m) const noexcept;
    [[nodiscard]] SizeF shrunkBy(MarginsF m) const noexcept;

    double &rwidth() noexcept;
    double &rheight() noexcept;

    SizeF &operator+=(const SizeF &) noexcept;
    SizeF &operator-=(const SizeF &) noexcept;
    SizeF &operator*=(double c) noexcept;
    SizeF &operator/=(double c);

    friend inline bool operator==(const SizeF &s1, const SizeF &s2)
    {
        return ((!s1.wd || !s2.wd) ? qFuzzyIsNull(s1.wd - s2.wd)
                                   : qFuzzyCompare(s1.wd, s2.wd)) &&
               ((!s1.ht || !s2.ht) ? qFuzzyIsNull(s1.ht - s2.ht)
                                   : qFuzzyCompare(s1.ht, s2.ht));
    }
    friend inline bool operator!=(const SizeF &s1, const SizeF &s2)
    {
        return !(s1 == s2);
    }
    friend inline SizeF operator+(const SizeF &s1, const SizeF &s2) noexcept
    {
        return SizeF(s1.wd + s2.wd, s1.ht + s2.ht);
    }
    friend inline SizeF operator-(const SizeF &s1, const SizeF &s2) noexcept
    {
        return SizeF(s1.wd - s2.wd, s1.ht - s2.ht);
    }
    friend inline SizeF operator*(const SizeF &s, double c) noexcept
    {
        return SizeF(s.wd * c, s.ht * c);
    }
    friend inline SizeF operator*(double c, const SizeF &s) noexcept
    {
        return s * c;
    }
    friend inline SizeF operator/(const SizeF &s, double c)
    {
        assert(!qFuzzyIsNull(c));
        return SizeF(s.wd / c, s.ht / c);
    }

    Size toSize() const noexcept;

private:
    double wd;
    double ht;
};

}// namespace m2

#endif//M2_SIZE_H_