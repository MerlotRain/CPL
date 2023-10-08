#include <shape.h>

namespace m2 {

void GsSize::Transpose() noexcept
{
    std::swap(Width, Height);
}

int GsSize::Area() const
{
    return Width * Height;
}

GsSize GsSize::Scaled(const GsSize &s, GsAspectRatioMode mode) const noexcept
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
            return GsSize(rw, s.Height);
        else
            return GsSize(s.Width, int32_t(int64_t(s.Width) * int64_t(Height) / int64_t(Width)));
    }
}


void GsSizeF::Transpose() noexcept
{
    std::swap(Width, Height);
}

float GsSizeF::Area() const
{
    return Width * Height;
}

GsSizeF GsSizeF::Scaled(const GsSizeF &s, GsAspectRatioMode mode) const noexcept
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
            return GsSizeF(rw, s.Height);
        else
            return GsSizeF(s.Width, int32_t(int64_t(s.Width) * int64_t(Height) / int64_t(Width)));
    }
}

}// namespace m2
