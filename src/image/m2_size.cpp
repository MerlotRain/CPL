#include <m2_size.h>

namespace m2 {

/*******************************************************************************
 * class Size functions
 *******************************************************************************/

void Size::transpose() noexcept { std::swap(wd, ht); }

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

/*******************************************************************************
 * class SizeF functions
 *******************************************************************************/

void SizeF::transpose() noexcept { std::swap(wd, ht); }

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

}// namespace m2
