#include <m2_size.h>

namespace m2 {


/*****************************************************************************
  Size  functions
 *****************************************************************************/

Size::Size() noexcept : wd(-1), ht(-1) {}

Size::Size(int w, int h) noexcept : wd(w), ht(h) {}

bool Size::isNull() const noexcept { return wd == 0 && ht == 0; }

bool Size::isEmpty() const noexcept { return wd < 1 || ht < 1; }

bool Size::isValid() const noexcept { return wd >= 0 && ht >= 0; }

int Size::width() const noexcept { return wd; }

int Size::height() const noexcept { return ht; }

void Size::setWidth(int w) noexcept { wd = w; }

void Size::setHeight(int h) noexcept { ht = h; }

void Size::transpose() noexcept { std::swap(wd, ht); }

Size Size::transposed() const noexcept { return Size(ht, wd); }

void Size::scale(int w, int h, AspectRatioMode mode) noexcept
{
    scale(Size(w, h), mode);
}

void Size::scale(const Size &s, AspectRatioMode mode) noexcept
{
    *this = scaled(s, mode);
}

Size Size::scaled(int w, int h, AspectRatioMode mode) const noexcept
{
    return scaled(Size(w, h), mode);
}

Size Size::grownBy(Margins m) const noexcept
{
    return {width() + m.left() + m.right(), height() + m.top() + m.bottom()};
}

Size Size::shrunkBy(Margins m) const noexcept
{
    return {width() - m.left() - m.right(), height() - m.top() - m.bottom()};
}

int &Size::rwidth() noexcept { return wd; }

int &Size::rheight() noexcept { return ht; }

Size &Size::operator+=(const Size &s) noexcept
{
    wd += s.wd;
    ht += s.ht;
    return *this;
}

Size &Size::operator-=(const Size &s) noexcept
{
    wd -= s.wd;
    ht -= s.ht;
    return *this;
}

Size &Size::operator*=(double c) noexcept
{
    wd = qRound(wd * c);
    ht = qRound(ht * c);
    return *this;
}

Size &Size::operator/=(double c)
{
    assert(!qFuzzyIsNull(c));
    wd = qRound(wd / c);
    ht = qRound(ht / c);
    return *this;
}

Size Size::expandedTo(const Size &otherSize) const noexcept
{
    return Size(qMax(wd, otherSize.wd), qMax(ht, otherSize.ht));
}

Size Size::boundedTo(const Size &otherSize) const noexcept
{
    return Size(qMin(wd, otherSize.wd), qMin(ht, otherSize.ht));
}


/*****************************************************************************
  SizeF  functions
 *****************************************************************************/

SizeF::SizeF() noexcept : wd(-1.), ht(-1.) {}

SizeF::SizeF(const Size &sz) noexcept : wd(sz.width()), ht(sz.height()) {}

SizeF::SizeF(double w, double h) noexcept : wd(w), ht(h) {}

bool SizeF::isNull() const noexcept { return qIsNull(wd) && qIsNull(ht); }

bool SizeF::isEmpty() const noexcept { return wd <= 0. || ht <= 0.; }

bool SizeF::isValid() const noexcept { return wd >= 0. && ht >= 0.; }

double SizeF::width() const noexcept { return wd; }

double SizeF::height() const noexcept { return ht; }

void SizeF::setWidth(double w) noexcept { wd = w; }

void SizeF::setHeight(double h) noexcept { ht = h; }

void SizeF::transpose() noexcept { std::swap(wd, ht); }

SizeF SizeF::transposed() const noexcept { return SizeF(ht, wd); }

void SizeF::scale(double w, double h, AspectRatioMode mode) noexcept
{
    scale(SizeF(w, h), mode);
}

void SizeF::scale(const SizeF &s, AspectRatioMode mode) noexcept
{
    *this = scaled(s, mode);
}

SizeF SizeF::scaled(double w, double h, AspectRatioMode mode) const noexcept
{
    return scaled(SizeF(w, h), mode);
}

Size Size::scaled(const Size &s, AspectRatioMode mode) const noexcept
{
    if (mode == eIgnoreAspectRatio || wd == 0 || ht == 0) { return s; }
    else
    {
        bool useHeight;
        int64_t rw = int64_t(s.ht) * int64_t(wd) / int64_t(ht);

        if (mode == eKeepAspectRatio) { useHeight = (rw <= s.wd); }
        else { useHeight = (rw >= s.wd); }

        if (useHeight) { return Size(rw, s.ht); }
        else
        {
            return Size(s.wd,
                        int32_t(int64_t(s.wd) * int64_t(ht) / int64_t(wd)));
        }
    }
}

SizeF SizeF::scaled(const SizeF &s, AspectRatioMode mode) const noexcept
{
    if (mode == eIgnoreAspectRatio || qIsNull(wd) || qIsNull(ht)) { return s; }
    else
    {
        bool useHeight;
        double rw = s.ht * wd / ht;

        if (mode == eKeepAspectRatio) { useHeight = (rw <= s.wd); }
        else { useHeight = (rw >= s.wd); }

        if (useHeight) { return SizeF(rw, s.ht); }
        else { return SizeF(s.wd, s.wd * ht / wd); }
    }
}

SizeF SizeF::grownBy(MarginsF m) const noexcept
{
    return {width() + m.left() + m.right(), height() + m.top() + m.bottom()};
}

SizeF SizeF::shrunkBy(MarginsF m) const noexcept
{
    return {width() - m.left() - m.right(), height() - m.top() - m.bottom()};
}

double &SizeF::rwidth() noexcept { return wd; }

double &SizeF::rheight() noexcept { return ht; }

SizeF &SizeF::operator+=(const SizeF &s) noexcept
{
    wd += s.wd;
    ht += s.ht;
    return *this;
}

SizeF &SizeF::operator-=(const SizeF &s) noexcept
{
    wd -= s.wd;
    ht -= s.ht;
    return *this;
}

SizeF &SizeF::operator*=(double c) noexcept
{
    wd *= c;
    ht *= c;
    return *this;
}

SizeF &SizeF::operator/=(double c)
{
    assert(!qFuzzyIsNull(c) && std::isfinite(c));
    wd = wd / c;
    ht = ht / c;
    return *this;
}

SizeF SizeF::expandedTo(const SizeF &otherSize) const noexcept
{
    return SizeF(qMax(wd, otherSize.wd), qMax(ht, otherSize.ht));
}

SizeF SizeF::boundedTo(const SizeF &otherSize) const noexcept
{
    return SizeF(qMin(wd, otherSize.wd), qMin(ht, otherSize.ht));
}

Size SizeF::toSize() const noexcept { return Size(qRound(wd), qRound(ht)); }

SizeF Size::toSizeF() const noexcept { return *this; }

}// namespace m2
