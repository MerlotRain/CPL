#include <stringhelp.h>

namespace m2 {


WString::WString() noexcept
{
}

WString::WString(const WString &str) noexcept : StlWString(str)
{
}

WString::WString(const StlWString &str) noexcept : StlWString(str)
{
}

WString::WString(const wchar_t *str) noexcept : StlWString(str)
{
}

WString::WString(wchar_t *str) noexcept : StlWString(str)
{
}

WString::WString(const wchar_t *str, int off, int count) noexcept : StlWString(str, off, count)
{
}

WString::WString(const wchar_t *str, int count) noexcept : StlWString(str, count)
{
}

WString::WString(const wchar_t *start, const wchar_t *end) noexcept : StlWString(start, end)
{
}

WString::WString(int count, wchar_t e) noexcept : StlWString(count, e)
{
}

WString::WString(WString::iterator first, WString::iterator last) noexcept
    : StlWString(first, last)
{
}

WString::WString(WString::const_iterator first, WString::const_iterator last) noexcept
    : StlWString(first, last)
{
}

WString::WString(WString::reverse_iterator first, WString::reverse_iterator last) noexcept
    : StlWString(first, last)
{
}

WString::WString(WString::const_reverse_iterator first,
                     WString::const_reverse_iterator last) noexcept
    : StlWString(first, last)
{
}

WString::~WString()
{
}

WString &WString::operator=(const wchar_t *str)
{
    this->append(str);
    return *this;
}

WString &WString::operator=(const StlWString &str)
{
    this->append(str);
    return *this;
}

WString &WString::operator=(const WString &str)
{
    this->append(str.c_str());
    return *this;
}

WString &WString::operator+=(const WString &str)
{
    this->append(str.c_str());
    return *this;
}

WString &WString::operator+=(const wchar_t *str)
{
    this->append(str);
    return *this;
}

WString WString::operator+(const wchar_t *str) const
{
    WString result;
    result.assign(this->data());
    result.append(str);
    return result;
}

WString WString::operator+(const StlWString &str) const
{
    WString result;
    result.assign(this->data());
    result.append(str);
    return result;
}

WString WString::operator+(const WString &str) const
{
    WString result;
    result.assign(this->data());
    result.append(str);
    return result;
}

bool WString::IsNullOrEmpty(const wchar_t *str)
{
    if (!str || 0 == wcslen(str))
    {
        return true;
    }
    return false;
}

}// namespace m2
