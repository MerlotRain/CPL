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

#ifndef M2_STRING_H
#define M2_STRING_H

#include <m2_allocator.h>

namespace m2 {

class StringList;
class String : public StlString
{
public:
    String() noexcept;
    String(const String &str) noexcept;
    String(const StlString &str);
    String(String *str);

    template<class STD>
    String(const STD &str)
    {
        operator=(str.c_str());
    }
    String(const char *str);
    String(char *str);
    String(const char *str, int off, int count) noexcept;
    String(const char *str, int count) noexcept;
    String(const char *start, const char *end) noexcept;
    String(const unsigned char *start, const unsigned char *end) noexcept;
    String(int count, char e) noexcept;
    String(String::const_iterator first, String::const_iterator last) noexcept;
    String(String::iterator first, String::iterator last) noexcept;
    String(String::reverse_iterator first, String::reverse_iterator last) noexcept;
    String(String::const_reverse_iterator first, String::const_reverse_iterator last) noexcept;
    ~String();

    String &operator=(const char *str);
    String &operator=(const StlString &str);
    String &operator=(const String &str);
    reference operator[](int index);
    const_reference operator[](int index) const;
    operator bool() const;
    operator const char *() const;

    using StlString::operator+=;
    template<class STD>
    String &operator+=(const STD &str)
    {
        StlString::operator+=(str.c_str());
        return *this;
    }
    String &operator+=(const char *str);
    String &operator+=(int ch);
    String &operator+=(char ch);
    String &operator+=(const String &str);
    String operator+(const char *str) const;
    String operator+(const String &str) const;
    String operator+(const StlString &str) const;

    String &ToUpper();
    String &ToLower();
    String &Reverse();
    String &TrimRight();
    String &TrimLeft();
    String &Trimmed();
    StringList Split(const char *strSep);
    void Split(const char *strSep, StringList &vecStr);

    String &Replace(char from, char to, size_type start = 0);
    String &Replace(const char *from, const char *to, size_type start = 0);
    String &Replace(const String &from, const String &to, size_type start = 0);

    inline bool IsNullOrEmpty() const;
    inline bool StartWith(const char *strHead, bool bIgnoringCase = false) const;
    inline bool EndWith(const char *strEnd, bool bIgnoringCase = false) const;
    inline bool Contains(char c, bool bIgnoringCase = false) const;
    inline bool Contains(const char *c, bool bIgnoringCase = false) const;

    String &Remove(char ch);
    String &Remove(const char *src);

    static bool IsNullOrEmpty(const char *str);
    static bool StartWith(const char *str, const char *strHead, bool bIgnoringCase = false);
    static bool EndWith(const char *str, const char *strTail, bool bIgnoringCase = false);
    static bool Contains(const char *str, char c, bool bIgnoringCase = false);
    static bool Contains(const char *str, const char *c, bool bIgnoringCase = false);
    static String Remove(const char *str, const char *c);
    static int Compare(const char *strA, const char *strB);
    static String Escape(const char *str, bool strictJSON = false);
    static String Unescape(const char *str);

    template<typename T, typename... Args>
    inline String Format(T &&t, Args &&...args)
    {
        return String::Format(this->data(), t, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static String Format(const char *format, Args &&...args)
    {
        auto size_buf = std::snprintf(nullptr, 0, format, std::forward<Args>(args)...) + 1;
        std::unique_ptr<char[]> buf(new (std::nothrow) char[size_buf]);

        if (!buf)
        {
            return {};
        }

        std::snprintf(buf.get(), size_buf, format, std::forward<Args>(args)...);
        return String(buf.get(), buf.get() + size_buf - 1);
    }

public:
    enum BoolFormat
    {
        eFalseAndTrue,
        eYesAndNo,
        eOnAndOff,
    };
    static String ToString(bool value, BoolFormat format = eFalseAndTrue);
    static String ToString(short value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    static String ToString(unsigned short value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    static String ToString(int value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    static String ToString(unsigned int value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    static String ToString(long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    static String ToString(unsigned long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    static String ToString(long long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    static String ToString(unsigned long long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    static String ToString(float value, char format = 'g', int precision = 6);
    static String ToString(double value, char format = 'g', int precision = 6);

    String &Append(const String &str, int width = -1, char fill = ' ');
    String &Append(String &&str, int width = -1, char fill = ' ');
    String &Append(short value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    String &Append(unsigned short value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    String &Append(int value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    String &Append(unsigned int value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    String &Append(long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    String &Append(unsigned long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    String &Append(long long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    String &Append(unsigned long long value, int base = 10, int width = -1, char fill = '0', bool prefix = false);
    String &Append(float value, char format = 'g', int precision = 6);
    String &Append(double value, char format = 'g', int precision = 6);

public:
    short ToShort(bool *ok = nullptr, int base = 10) const noexcept;
    unsigned short ToUShort(bool *ok = nullptr, int base = 10) const noexcept;
    int ToInt(bool *ok = nullptr, int base = 10) const noexcept;
    unsigned int ToUInt(bool *ok = nullptr, int base = 10) const noexcept;
    bool ToBoolean(bool *ok = nullptr) const noexcept;
    long long ToLongLong(bool *ok = nullptr, int base = 10) const noexcept;
    unsigned long long ToULongLong(bool *ok = nullptr, int base = 10) const noexcept;
    float ToFloat(bool *ok = nullptr) const noexcept;
    double ToDouble(bool *ok = nullptr) const noexcept;
};

inline bool String::IsNullOrEmpty() const
{
    return String::IsNullOrEmpty(this->data());
}
inline bool String::StartWith(const char *strHead, bool bIgnoringCase = false) const
{
    return String::StartWith(this->data(), strHead, bIgnoringCase);
}
inline bool String::EndWith(const char *strEnd, bool bIgnoringCase = false) const
{
    return String::EndWith(this->data(), strEnd, bIgnoringCase);
}
inline bool String::Contains(char c, bool bIgnoringCase = false) const
{
    return String::Contains(this->data(), c, bIgnoringCase);
}
inline bool String::Contains(const char *c, bool bIgnoringCase = false) const
{
    return String::Contains(this->data(), c, bIgnoringCase);
}

inline String operator+(const String &a, const std::string &b)
{
    return a.operator+(b.c_str());
}
inline bool operator==(const String &a, const String &b)
{
    return String::Compare(a.c_str(), b.c_str());
}
inline bool operator==(const String &a, const std::string &b)
{
    return String::Compare(a.c_str(), b.c_str());
}
inline bool operator==(const String &a, const char *b)
{
    return String::Compare(a.c_str(), b);
}
inline bool operator==(const std::string &a, const String &b)
{
    return String::Compare(a.c_str(), b.c_str());
}
inline bool operator==(const char *a, const String &b)
{
    return String::Compare(a, b.c_str());
}

}// namespace m2


#endif//M2_STRING_H