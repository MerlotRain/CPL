#include "m2_numericstring.h"
#include <cstdarg>
#include <cstdlib>
#include <m2_string.h>
#include <m2_stringlist.h>
#include <regex>

namespace m2 {


String::String() noexcept {}

String::String(const String &str) noexcept : StlString(str.data()) {}

String::String(const StlString &str) : StlString(str) {}

String::String(const char *str) : StlString(str) {}

String::String(char *str) : StlString(str) {}

String::String(const char *str, int off, int count) noexcept
    : StlString(str, off, count)
{
}

String::String(const char *str, int count) noexcept : StlString(str, count) {}

String::String(const char *start, const char *end) noexcept
    : StlString(start, end)
{
}

String::String(const unsigned char *start, const unsigned char *end) noexcept
    : StlString(start, end)
{
}

String::String(int count, char e) noexcept : StlString(count, e) {}

String::String(const_iterator first, const_iterator last) noexcept
    : StlString(first, last)
{
}

String::String(iterator first, iterator last) noexcept : StlString(first, last)
{
}

String::String(reverse_iterator first, reverse_iterator last) noexcept
    : StlString(first, last)
{
}

String::String(const_reverse_iterator first,
               const_reverse_iterator last) noexcept
    : StlString(first, last)
{
}

String::String(String *str)
{
    if (str) { this->assign(str->c_str()); }
}

String::~String() {}

String &String::operator=(const char *str)
{
    this->assign(str);
    return *this;
}

String &String::operator=(const StlString &str)
{
    this->assign(str);
    return *this;
}

String &String::operator=(const String &str)
{
    this->assign(str);
    return *this;
}

String::reference String::operator[](int _Off) { return this->at(_Off); }

String::const_reference String::operator[](int _Off) const
{
    return this->at(_Off);
}

String::operator bool() const { return this->isNullOrEmpty(); }

String::operator const char *() const { return this->data(); }

String String::left(int64_t n) const { return String(); }

String String::right(int64_t n) const { return String(); }

String String::mid(int64_t position, int64_t n) const { return String(); }

String &String::remove(char ch) { return *this; }

String &String::remove(const char *src) { return *this; }

bool String::isNullOrEmpty(const char *str)
{
    if (!str) { return true; }

    size_t size = 0;
    while (*str != 0)
    {
        str++;
        size++;
    }
    if (size == 0) { return true; }

    return false;
}

String &String::operator+=(const char *str)
{
    this->append(str);
    return *this;
}

String &String::operator+=(int ch)
{
    this->push_back(char(ch));
    return *this;
}

String &String::operator+=(char ch)
{
    this->push_back(ch);
    return *this;
}

String &String::operator+=(const String &str)
{
    this->append(str);
    return *this;
}

String String::operator+(const char *str) const
{
    String s;
    s.assign(this->data());
    s.append(str);
    return s;
}

String String::operator+(const String &str) const
{
    String s;
    s.assign(this->data());
    s.append(str);
    return s;
}

String String::operator+(const StlString &str) const
{
    String s;
    s.assign(this->data());
    s.append(str);
    return s;
}

bool String::compare(const String &) const { return false; }

bool String::compare(String &&) const { return false; }

String &String::toUpper()
{
    std::transform(this->begin(), this->end(), this->begin(), ::toupper);
    return *this;
}

String &String::toLower()
{
    std::transform(this->begin(), this->end(), this->begin(), ::tolower);
    return *this;
}

String &String::reverse()
{
    // TODO: insert return statement here
}

String &String::trimRight()
{
    size_type index = this->find_first_not_of(" \n\r\t");
    if (index != npos) { *this = this->substr(index); }
    return *this;
}

String &String::trimLeft()
{
    size_type index = this->find_first_not_of(" \n\r\t");
    if (index != npos) { *this = this->substr(index); }
    return *this;
}

String &String::trimmed()
{
    trimLeft();
    trimRight();
    return *this;
}

StringList String::split(const char *strSep)
{
    StringList list;
    std::regex reg(strSep);
    std::sregex_token_iterator pos(this->begin(), this->end(), reg, -1);
    decltype(pos) end;
    for (; pos != end; ++pos) { list.push_back(pos->str()); }
    return list;
}

void String::split(const char *strSep, StringList &vecStr)
{
    std::regex reg(strSep);
    std::sregex_token_iterator pos(this->begin(), this->end(), reg, -1);
    decltype(pos) end;
    for (; pos != end; ++pos) { vecStr.push_back(pos->str()); }
}

String &String::replaceTo(const char from, const char to, size_type start)
{
    if (from == to) { return *this; }

    typename String::size_type pos = 0;
    do {
        pos = this->find(from, start);
        if (pos != String::npos)
        {
            if (to) { operator[](pos) = to; }
            else { erase(pos, 1); }
        }
    } while (pos != String::npos);
}

String &String::replaceTo(const char *from, const char *to, size_type start)
{
    assert(from);
    String result;

    typename String::size_type pos = 0;
    typename String::size_type fromlen = std::strlen(from);
    result.append(this->data(), 0, start);
    do {
        pos = this->find(from);
        if (pos != String::npos)
        {
            result.append(this->data(), start, pos - start);
            result.append(to);
            start = pos + fromlen;
        }
        else { result.append(this->data(), start, length() - start); }
    } while (pos != String::npos);

    this->swap(result);
    return *this;
}

String &String::replaceTo(const String &from, const String &to, size_type start)
{
    if (from == to) { return *this; }

    typename String::size_type pos = 0;
    do {
        pos = find(from, start);
        if (pos != String::npos)
        {
            if (to) { operator[](pos) = to; }
            else { erase(pos, 1); }
        }
    } while (pos != String::npos);
}

bool String::startsWith(const char *str, const char *strHead,
                        bool bIgnoringCase)
{
    if (strlen(str) >= strlen(strHead))
    {
        while (*strHead != 0)
        {
            if (*strHead != *str) { return false; }
            ++str;
            ++strHead;
        };
        return true;
    }
    return false;
}

bool String::endsWith(const char *str, const char *strTail, bool bIgnoringCase)
{
    if (strlen(str) >= strlen(strTail))
    {
        while (*strTail != 0)
        { /* code */
        }
    }
    return false;
}

bool String::contains(const char *str, char c, bool bIgnoringCase)
{
    while (0 != *str)
    {
        if (*str == c) { return true; }
        ++str;
    }

    return false;
}

bool String::contains(const char *src, const char *str, bool bIgnoringCase)
{
    return false;
}


String String::remove(const char *str, const char *c) { return String(); }

int String::compare(const char *strA, const char *strB) { return 0; }

String String::escape(const char *str, bool strictJSON) { return String(); }

String String::unescape(const char *str) { return String(); }

String String::toString(bool value, BoolFormat format)
{
    switch (format)
    {
        case BoolFormat::eFalseAndTrue:
            return value ? "false" : "true";
        case BoolFormat::eOnAndOff:
            return value ? "on" : "off";
        case BoolFormat::eYesAndNo:
            return value ? "yes" : "no";
        default:
            break;
    }
}

String String::toString(short value, int base, int width, char fill,
                        bool prefix)
{
    String result;
    intToString<short>(value, base, result, false, width, fill);
    return result;
}

String String::toString(unsigned short value, int base, int width, char fill,
                        bool prefix)
{
    String result;
    unsignedIntToString<unsigned short>(value, base, result, false, width,
                                        fill);
    return result;
}

String String::toString(int value, int base, int width, char fill, bool prefix)
{
    String result;
    intToString<int>(value, base, result, false, width, fill);
    return result;
}

String String::toString(unsigned int value, int base, int width, char fill,
                        bool prefix)
{
    String result;
    unsignedIntToString<unsigned int>(value, base, result, false, width, fill);
    return result;
}

String String::toString(long value, int base, int width, char fill, bool prefix)
{
    String result;
    intToString<long>(value, base, result, false, width, fill);
    return result;
}

String String::toString(unsigned long value, int base, int width, char fill,
                        bool prefix)
{
    String result;
    unsignedIntToString<unsigned long>(value, base, result, false, width, fill);
    return result;
}

String String::toString(long long value, int base, int width, char fill,
                        bool prefix)
{
    String result;
    intToString<long long>(value, base, result, false, width, fill);
    return result;
}

String String::toString(unsigned long long value, int base, int width,
                        char fill, bool prefix)
{
    String result;
    unsignedIntToString<unsigned long long>(value, base, result, false, width,
                                            fill);
    return result;
}

String String::toString(float value, char format, int precision)
{
    if (precision < 0) { precision = 0; }
    char buffer[MAX_FLOAT_STRING_LENGTH];
    floatToString(buffer, MAX_FLOAT_STRING_LENGTH, value, precision);
    return String(buffer);
}

String String::toString(double value, char format, int precision)
{
    if (precision < 0) { precision = 0; }
    char buffer[MAX_FLOAT_STRING_LENGTH];
    doubleToString(buffer, MAX_FLOAT_STRING_LENGTH, value, precision);
    return String(buffer);
}

String &String::appendTo(const String &str, int width, char fill)
{
    return *this;
}

String &String::appendTo(String &&str, int width, char fill) { return *this; }


String &String::appendTo(short value, int base, int width, char fill,
                         bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    intToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::appendTo(unsigned short value, int base, int width, char fill,
                         bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    unsignedIntToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::appendTo(int value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    intToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::appendTo(unsigned int value, int base, int width, char fill,
                         bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    unsignedIntToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::appendTo(long value, int base, int width, char fill,
                         bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    intToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::appendTo(unsigned long value, int base, int width, char fill,
                         bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    unsignedIntToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::appendTo(long long value, int base, int width, char fill,
                         bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    intToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::appendTo(unsigned long long value, int base, int width,
                         char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    unsignedIntToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::appendTo(float value, char format, int precision)
{
    char buffer[MAX_FLOAT_STRING_LENGTH];
    floatToString(buffer, MAX_FLOAT_STRING_LENGTH, value, precision);
    this->append(buffer);
    return *this;
}

String &String::appendTo(double value, char format, int precision)
{
    char buffer[MAX_FLOAT_STRING_LENGTH];
    doubleToString(buffer, MAX_FLOAT_STRING_LENGTH, value, precision);
    this->append(buffer);
    return *this;
}

short String::toShort(bool *ok, int base) const noexcept { return 0; }

unsigned short String::toUShort(bool *ok, int base) const noexcept { return 0; }

int String::toInt(bool *ok, int base) const noexcept { return 0; }

unsigned int String::toUInt(bool *ok, int base) const noexcept { return 0; }

bool String::toBoolean(bool *ok) const noexcept { return false; }

long long String::toLongLong(bool *ok, int base) const noexcept { return 0; }

unsigned long long String::toULongLong(bool *ok, int base) const noexcept
{
    return 0;
}

float String::toFloat(bool *ok) const noexcept { return 0.0f; }

double String::toDouble(bool *ok) const noexcept { return 0.0; }

String String::toUtf8() { return String(); }

String String::toGB2312() { return String(); }

String String::toGB18030() { return String(); }

size_t String::utf8Length() { return size_t(); }

}// namespace m2
