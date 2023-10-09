#include <shape.h>

namespace m2 {

void Size::Transpose() noexcept
{
    std::swap(Width, Height);
}

int Size::Area() const
{
    return Width * Height;
}

Size Size::Scaled(const Size &s, AspectRatioMode mode) const noexcept
{
    if (mode == eIgnoreAspectRatio || Width == 0 || Height == 0)
    {
        return s;
    }
    else
    {
        bool useHeight;
        int64_t rw = int64_t(s.Height) * int64_t(Width) / int64_t(Height);

        if (mode == eKeepAspectRatio)
            useHeight = (rw <= s.Width);
        else
            useHeight = (rw >= s.Width);

        if (useHeight)
            return Size(rw, s.Height);
        else
            return Size(s.Width, int32_t(int64_t(s.Width) * int64_t(Height) / int64_t(Width)));
    }
}


void SizeF::Transpose() noexcept
{
    std::swap(Width, Height);
}

float SizeF::Area() const
{
    return Width * Height;
}

SizeF SizeF::Scaled(const SizeF &s, AspectRatioMode mode) const noexcept
{
    if (mode == eIgnoreAspectRatio || Width == 0 || Height == 0)
    {
        return s;
    }
    else
    {
        bool useHeight;
        int64_t rw = int64_t(s.Height) * int64_t(Width) / int64_t(Height);

        if (mode == eKeepAspectRatio)
            useHeight = (rw <= s.Width);
        else
            useHeight = (rw >= s.Width);

        if (useHeight)
            return SizeF(rw, s.Height);
        else
            return SizeF(s.Width, int32_t(int64_t(s.Width) * int64_t(Height) / int64_t(Width)));
    }
}

}// namespace m2
