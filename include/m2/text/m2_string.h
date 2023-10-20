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

#ifndef M2_STRING_H_
#define M2_STRING_H_

#include <m2_allocator.h>

namespace m2 {

class StringList;
class LIBM2_EXPORT String : public StlString
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
    String(String::reverse_iterator first,
           String::reverse_iterator last) noexcept;
    String(String::const_reverse_iterator first,
           String::const_reverse_iterator last) noexcept;
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

    bool compare(const String &) const;
    bool compare(String &&) const;
    String &toUpper();
    String &toLower();
    String &reverse();
    String &trimRight();
    String &trimLeft();
    String &trimmed();
    StringList split(const char *strSep);
    void split(const char *strSep, StringList &vecStr);
    String &replaceTo(char from, char to, size_type start = 0);
    String &replaceTo(const char *from, const char *to, size_type start = 0);
    String &replaceTo(const String &from, const String &to,
                      size_type start = 0);

    inline bool isNullOrEmpty() const;
    inline bool startsWith(const char *strHead,
                           bool bIgnoringCase = false) const;
    inline bool endsWith(const char *strEnd, bool bIgnoringCase = false) const;
    inline bool contains(char c, bool bIgnoringCase = false) const;
    inline bool contains(const char *c, bool bIgnoringCase = false) const;

    [[nodiscard]] String left(int64_t n) const;
    [[nodiscard]] String right(int64_t n) const;
    [[nodiscard]] String mid(int64_t position, int64_t n = -1) const;

    String &remove(char ch);
    String &remove(const char *src);

    static bool isNullOrEmpty(const char *str);
    static bool startsWith(const char *str, const char *strHead,
                           bool bIgnoringCase = false);
    static bool endsWith(const char *str, const char *strTail,
                         bool bIgnoringCase = false);
    static bool contains(const char *str, char c, bool bIgnoringCase = false);
    static bool contains(const char *str, const char *c,
                         bool bIgnoringCase = false);
    static String remove(const char *str, const char *c);
    static int compare(const char *strA, const char *strB);
    static String escape(const char *str, bool strictJSON = false);
    static String unescape(const char *str);

    template<typename T, typename... Args>
    inline String format(T &&t, Args &&...args)
    {
        return String::format(this->data(), t, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static String format(const char *f, Args &&...args)
    {
        auto size_buf =
                std::snprintf(nullptr, 0, f, std::forward<Args>(args)...) + 1;
        std::unique_ptr<char[]> buf(new (std::nothrow) char[size_buf]);

        if (!buf) { return {}; }

        std::snprintf(buf.get(), size_buf, f, std::forward<Args>(args)...);
        return String(buf.get(), buf.get() + size_buf - 1);
    }


public:
    enum BoolFormat
    {
        eFalseAndTrue,
        eYesAndNo,
        eOnAndOff,
    };
    static String toString(bool value, BoolFormat format = eFalseAndTrue);
    static String toString(short value, int base = 10, int width = -1,
                           char fill = '0', bool prefix = false);
    static String toString(unsigned short value, int base = 10, int width = -1,
                           char fill = '0', bool prefix = false);
    static String toString(int value, int base = 10, int width = -1,
                           char fill = '0', bool prefix = false);
    static String toString(unsigned int value, int base = 10, int width = -1,
                           char fill = '0', bool prefix = false);
    static String toString(long value, int base = 10, int width = -1,
                           char fill = '0', bool prefix = false);
    static String toString(unsigned long value, int base = 10, int width = -1,
                           char fill = '0', bool prefix = false);
    static String toString(long long value, int base = 10, int width = -1,
                           char fill = '0', bool prefix = false);
    static String toString(unsigned long long value, int base = 10,
                           int width = -1, char fill = '0',
                           bool prefix = false);
    static String toString(float value, char format = 'g', int precision = 6);
    static String toString(double value, char format = 'g', int precision = 6);

    String &appendTo(const String &str, int width = -1, char fill = ' ');
    String &appendTo(String &&str, int width = -1, char fill = ' ');
    String &appendTo(short value, int base = 10, int width = -1,
                     char fill = '0', bool prefix = false);
    String &appendTo(unsigned short value, int base = 10, int width = -1,
                     char fill = '0', bool prefix = false);
    String &appendTo(int value, int base = 10, int width = -1, char fill = '0',
                     bool prefix = false);
    String &appendTo(unsigned int value, int base = 10, int width = -1,
                     char fill = '0', bool prefix = false);
    String &appendTo(long value, int base = 10, int width = -1, char fill = '0',
                     bool prefix = false);
    String &appendTo(unsigned long value, int base = 10, int width = -1,
                     char fill = '0', bool prefix = false);
    String &appendTo(long long value, int base = 10, int width = -1,
                     char fill = '0', bool prefix = false);
    String &appendTo(unsigned long long value, int base = 10, int width = -1,
                     char fill = '0', bool prefix = false);
    String &appendTo(float value, char format = 'g', int precision = 6);
    String &appendTo(double value, char format = 'g', int precision = 6);

public:
    short toShort(bool *ok = nullptr, int base = 10) const noexcept;
    unsigned short toUShort(bool *ok = nullptr, int base = 10) const noexcept;
    int toInt(bool *ok = nullptr, int base = 10) const noexcept;
    unsigned int toUInt(bool *ok = nullptr, int base = 10) const noexcept;
    bool toBoolean(bool *ok = nullptr) const noexcept;
    long long toLongLong(bool *ok = nullptr, int base = 10) const noexcept;
    unsigned long long toULongLong(bool *ok = nullptr,
                                   int base = 10) const noexcept;
    float toFloat(bool *ok = nullptr) const noexcept;
    double toDouble(bool *ok = nullptr) const noexcept;

public:
    String toUtf8();
    String toGB2312();
    String toGB18030();
    size_t utf8Length();
};

inline bool String::isNullOrEmpty() const
{
    return String::isNullOrEmpty(this->data());
    std::string s;
}
inline bool String::startsWith(const char *strHead,
                               bool bIgnoringCase = false) const
{
    return String::startsWith(this->data(), strHead, bIgnoringCase);
}
inline bool String::endsWith(const char *strEnd,
                             bool bIgnoringCase = false) const
{
    return String::endsWith(this->data(), strEnd, bIgnoringCase);
}
inline bool String::contains(char c, bool bIgnoringCase = false) const
{
    return String::contains(this->data(), c, bIgnoringCase);
}
inline bool String::contains(const char *c, bool bIgnoringCase = false) const
{
    return String::contains(this->data(), c, bIgnoringCase);
}

inline String operator+(const String &a, const std::string &b)
{
    return a.operator+(b.c_str());
}
inline bool operator==(const String &a, const String &b)
{
    return String::compare(a.c_str(), b.c_str());
}
inline bool operator==(const String &a, const std::string &b)
{
    return String::compare(a.c_str(), b.c_str());
}
inline bool operator==(const String &a, const char *b)
{
    return String::compare(a.c_str(), b);
}
inline bool operator==(const std::string &a, const String &b)
{
    return String::compare(a.c_str(), b.c_str());
}
inline bool operator==(const char *a, const String &b)
{
    return String::compare(a, b.c_str());
}

}// namespace m2

#endif//M2_STRING_H_