#include <stringhelp.h>

namespace Lite {
namespace Utility {


GsWString::GsWString() noexcept
{
}

GsWString::GsWString(const GsWString &str) noexcept : GsStlWString(str)
{
}

GsWString::GsWString(const GsStlWString &str) noexcept : GsStlWString(str)
{
}

GsWString::GsWString(const wchar_t *str) noexcept : GsStlWString(str)
{
}

GsWString::GsWString(wchar_t *str) noexcept : GsStlWString(str)
{
}

GsWString::GsWString(const wchar_t *str, int off, int count) noexcept : GsStlWString(str, off, count)
{
}

GsWString::GsWString(const wchar_t *str, int count) noexcept : GsStlWString(str, count)
{
}

GsWString::GsWString(const wchar_t *start, const wchar_t *end) noexcept : GsStlWString(start, end)
{
}

GsWString::GsWString(int count, wchar_t e) noexcept : GsStlWString(count, e)
{
}

GsWString::GsWString(GsWString::iterator first, GsWString::iterator last) noexcept
    : GsStlWString(first, last)
{
}

GsWString::GsWString(GsWString::const_iterator first, GsWString::const_iterator last) noexcept
    : GsStlWString(first, last)
{
}

GsWString::GsWString(GsWString::reverse_iterator first, GsWString::reverse_iterator last) noexcept
    : GsStlWString(first, last)
{
}

GsWString::GsWString(GsWString::const_reverse_iterator first,
                     GsWString::const_reverse_iterator last) noexcept
    : GsStlWString(first, last)
{
}

GsWString::~GsWString()
{
}

GsWString &GsWString::operator=(const wchar_t *str)
{
    this->append(str);
    return *this;
}

GsWString &GsWString::operator=(const GsStlWString &str)
{
    this->append(str);
    return *this;
}

GsWString &GsWString::operator=(const GsWString &str)
{
    this->append(str.c_str());
    return *this;
}

GsWString &GsWString::operator+=(const GsWString &str)
{
    this->append(str.c_str());
    return *this;
}

GsWString &GsWString::operator+=(const wchar_t *str)
{
    this->append(str);
    return *this;
}

GsWString GsWString::operator+(const wchar_t *str) const
{
    GsWString result;
    result.assign(this->data());
    result.append(str);
    return result;
}

GsWString GsWString::operator+(const GsStlWString &str) const
{
    GsWString result;
    result.assign(this->data());
    result.append(str);
    return result;
}

GsWString GsWString::operator+(const GsWString &str) const
{
    GsWString result;
    result.assign(this->data());
    result.append(str);
    return result;
}

bool GsWString::IsNullOrEmpty(const wchar_t *str)
{
    if (!str || 0 == wcslen(str))
    {
        return true;
    }
    return false;
}

}// namespace Utility
}// namespace Lite
