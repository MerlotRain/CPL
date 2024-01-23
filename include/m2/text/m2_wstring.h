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
** copy of this software and associated documentation files (the "Software"), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
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

#ifndef M2_WSTRING_H_
#define M2_WSTRING_H_

#include <m2_allocator.h>

namespace m2 {

class LIBM2_EXPORT WString : public StlWString
{
public:
    WString() noexcept;
    WString(const WString &str);
    WString(const StlWString &str);
    template<class STD>
    WString(const STD &str)
    {
        operator=(str.c_str());
    }
    WString(const wchar_t *str);
    WString(wchar_t *str);
    WString(const wchar_t *str, int off, int count) noexcept;
    WString(const wchar_t *str, int count) noexcept;
    WString(const wchar_t *start, const wchar_t *end) noexcept;
    WString(int count, wchar_t e) noexcept;
    WString(WString::iterator first, WString::iterator last) noexcept;
    WString(WString::const_iterator first,
            WString::const_iterator last) noexcept;
    WString(WString::reverse_iterator first,
            WString::reverse_iterator last) noexcept;
    WString(WString::const_reverse_iterator first,
            WString::const_reverse_iterator last) noexcept;
    ~WString();

    WString &operator=(const wchar_t *str);
    WString &operator=(const StlWString &str);
    WString &operator=(const WString &str);

    template<class STD>
    operator STD() const
    {
        return STD(c_str());
    }

    operator bool() const;

    using StlWString::operator+=;
    template<class STD>
    WString &operator+=(const STD &str)
    {
        StlWString::operator+=(str.c_str());
        return *this;
    }

    inline bool isNullOrEmpty() const
    {
        return WString::isNullOrEmpty(this->data());
    }

    WString &operator+=(const WString &str);
    WString &operator+=(const wchar_t *str);
    WString operator+(const wchar_t *str) const;
    WString operator+(const StlWString &str) const;
    WString operator+(const WString &str) const;

    static bool isNullOrEmpty(const wchar_t *str);
    template<typename... Args>
    static WString format(const wchar_t *f, Args &&...args)
    {
        auto size_buf =
                std::snprintf(nullptr, 0, f, std::forward<Args>(args)...) + 1;
        std::unique_ptr<char[]> buf(new (std::nothrow) char[size_buf]);

        if (!buf) { return {}; }

        std::snprintf(buf.get(), size_buf, f, std::forward<Args>(args)...);
        return WString(buf.get(), buf.get() + size_buf - 1);
    }
};

inline WString operator+(const WString &a, const std::wstring &b)
{
    return a.operator+(b.c_str());
}

}// namespace m2

#endif//M2_WSTRING_H_