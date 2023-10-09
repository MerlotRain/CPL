#include "numericstring.h"
#include <cstdarg>
#include <cstdlib>
#include <regex>
#include <stringhelp.h>

namespace m2 {


String::String() noexcept
{
}

String::String(const String &str) noexcept : StlString(str.data())
{
}

String::String(const StlString &str) : StlString(str)
{
}

String::String(const char *str) : StlString(str)
{
}

String::String(char *str) : StlString(str)
{
}

String::String(const char *str, int off, int count) noexcept : StlString(str, off, count)
{
}

String::String(const char *str, int count) noexcept : StlString(str, count)
{
}

String::String(const char *start, const char *end) noexcept : StlString(start, end)
{
}

String::String(const unsigned char *start, const unsigned char *end) noexcept
    : StlString(start, end)
{
}

String::String(int count, char e) noexcept : StlString(count, e)
{
}

String::String(const_iterator first, const_iterator last) noexcept : StlString(first, last)
{
}

String::String(iterator first, iterator last) noexcept : StlString(first, last)
{
}

String::String(reverse_iterator first, reverse_iterator last) noexcept : StlString(first, last)
{
}

String::String(const_reverse_iterator first, const_reverse_iterator last) noexcept
    : StlString(first, last)
{
}

String::String(String *str)
{
    if (str)
    {
        this->assign(str->c_str());
    }
}

String::~String()
{
}

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

String::reference String::operator[](int _Off)
{
    return this->at(_Off);
}

String::const_reference String::operator[](int _Off) const
{
    return this->at(_Off);
}

String::operator bool() const
{
    return this->IsNullOrEmpty();
}

String::operator const char *() const
{
    return this->data();
}

String &String::Remove(char ch)
{
    return *this;
}

String &String::Remove(const char *src)
{
    return *this;
}

bool String::IsNullOrEmpty(const char *str)
{
    if (!str)
    {
        return true;
    }

    size_t size = 0;
    while (*str != 0)
    {
        str++;
        size++;
    }
    if (size == 0)
    {
        return true;
    }

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

int String::Length() const
{
    int nCharacterCount = 0;
    for (int i = 0; operator[](i) != '\0'; ++i)
    {
        if ((operator[](i) & 0xc0) != 0x80)
        {
            ++nCharacterCount;
        }
    }
    return nCharacterCount;
}

String &String::ToUpper()
{
    std::transform(this->begin(), this->end(), this->begin(), ::toupper);
    return *this;
}

String &String::ToLower()
{
    std::transform(this->begin(), this->end(), this->begin(), ::tolower);
    return *this;
}

String &String::Reverse()
{
    std::reverse(this->begin(), this->end());
    return *this;
}

String &String::TrimRight()
{
    size_type index = this->find_first_not_of(" \n\r\t");
    if (index != npos)
    {
        *this = this->substr(index);
    }
    return *this;
}

String &String::TrimLeft()
{
    size_type index = this->find_first_not_of(" \n\r\t");
    if (index != npos)
    {
        *this = this->substr(index);
    }
    return *this;
}

String &String::Trimmed()
{
    TrimLeft();
    TrimRight();
    return *this;
}

StringList String::Split(const char *strSep)
{
    StringList list;
    std::regex reg(strSep);
    std::sregex_token_iterator pos(this->begin(), this->end(), reg, -1);
    decltype(pos) end;
    for (; pos != end; ++pos)
    {
        list.push_back(pos->str());
    }
    return list;
}

void String::Split(const char *strSep, StringList &vecStr)
{
    std::regex reg(strSep);
    std::sregex_token_iterator pos(this->begin(), this->end(), reg, -1);
    decltype(pos) end;
    for (; pos != end; ++pos)
    {
        vecStr.push_back(pos->str());
    }
}

String &String::Replace(const char from, const char to, size_type start)
{
    if (from == to)
    {
        return *this;
    }

    typename String::size_type pos = 0;
    do
    {
        pos = this->find(from, start);
        if (pos != String::npos)
        {
            if (to)
            {
                operator[](pos) = to;
            }
            else
            {
                erase(pos, 1);
            }
        }
    } while (pos != String::npos);
}

String &String::Replace(const char *from, const char *to, size_type start)
{
    assert(from);
    String result;

    typename String::size_type pos = 0;
    typename String::size_type fromlen = std::strlen(from);
    result.append(this->data(), 0, start);
    do
    {
        pos = this->find(from);
        if (pos != String::npos)
        {
            result.append(this->data(), start, pos - start);
            result.append(to);
            start = pos + fromlen;
        }
        else
        {
            result.append(this->data(), start, length() - start);
        }
    } while (pos != String::npos);

    this->swap(result);
    return *this;
}

String &String::Replace(const String &from, const String &to, size_type start)
{
    if (from == to)
    {
        return *this;
    }

    typename String::size_type pos = 0;
    do
    {
        pos = find(from, start);
        if (pos != String::npos)
        {
            if (to)
            {
                operator[](pos) = to;
            }
            else
            {
                erase(pos, 1);
            }
        }
    } while (pos != String::npos);
}

bool String::StartWith(const char *str, const char *strHead, bool bIgnoringCase)
{
    if (strlen(str) >= strlen(strHead))
    {
        while (*strHead != 0)
        {
            if (*strHead != *str)
            {
                return false;
            }
            ++str;
            ++strHead;
        };
        return true;
    }
    return false;
}

bool String::EndWith(const char *str, const char *strTail, bool bIgnoringCase)
{
    if (strlen(str) >= strlen(strTail))
    {
        while (*strTail != 0)
        {
            /* code */
        }
    }
    return false;
}

bool String::Contains(const char *str, char c, bool bIgnoringCase)
{
    while (0 != *str)
    {
        if (*str == c)
        {
            return true;
        }
        ++str;
    }

    return false;
}

bool String::Contains(const char *src, const char *str, bool bIgnoringCase)
{
    return false;
}


String String::Remove(const char *str, const char *c)
{
    return String();
}

int String::Compare(const char *strA, const char *strB)
{
    return 0;
}

String String::Escape(const char *str, bool strictJSON)
{
    return String();
}

String String::Unescape(const char *str)
{
    return String();
}

String String::ToString(bool value, BoolFormat format)
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

String String::ToString(short value, int base, int width, char fill, bool prefix)
{
    String result;
    intToString<short>(value, base, result, false, width, fill);
    return result;
}

String String::ToString(unsigned short value, int base, int width, char fill, bool prefix)
{
    String result;
    unsignedIntToString<unsigned short>(value, base, result, false, width, fill);
    return result;
}

String String::ToString(int value, int base, int width, char fill, bool prefix)
{
    String result;
    intToString<int>(value, base, result, false, width, fill);
    return result;
}

String String::ToString(unsigned int value, int base, int width, char fill, bool prefix)
{
    String result;
    unsignedIntToString<unsigned int>(value, base, result, false, width, fill);
    return result;
}

String String::ToString(long value, int base, int width, char fill, bool prefix)
{
    String result;
    intToString<long>(value, base, result, false, width, fill);
    return result;
}

String String::ToString(unsigned long value, int base, int width, char fill, bool prefix)
{
    String result;
    unsignedIntToString<unsigned long>(value, base, result, false, width, fill);
    return result;
}

String String::ToString(long long value, int base, int width, char fill, bool prefix)
{
    String result;
    intToString<long long>(value, base, result, false, width, fill);
    return result;
}

String String::ToString(unsigned long long value, int base, int width, char fill, bool prefix)
{
    String result;
    unsignedIntToString<unsigned long long>(value, base, result, false, width, fill);
    return result;
}

String String::ToString(float value, char format, int precision)
{
    if (precision < 0)
    {
        precision = 0;
    }
    char buffer[MAX_FLOAT_STRING_LENGTH];
    floatToString(buffer, MAX_FLOAT_STRING_LENGTH, value, precision);
    return String(buffer);
}

String String::ToString(double value, char format, int precision)
{
    if (precision < 0)
    {
        precision = 0;
    }
    char buffer[MAX_FLOAT_STRING_LENGTH];
    doubleToString(buffer, MAX_FLOAT_STRING_LENGTH, value, precision);
    return String(buffer);
}

String &String::Append(const String &str, int width, char fill)
{
    return *this;
}

String &String::Append(String &&str, int width, char fill)
{
    return *this;
}


String &String::Append(short value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    intToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::Append(unsigned short value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    unsignedIntToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::Append(int value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    intToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::Append(unsigned int value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    unsignedIntToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::Append(long value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    intToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::Append(unsigned long value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    unsignedIntToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::Append(long long value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    intToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::Append(unsigned long long value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    unsignedIntToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

String &String::Append(float value, char format, int precision)
{
    char buffer[MAX_FLOAT_STRING_LENGTH];
    floatToString(buffer, MAX_FLOAT_STRING_LENGTH, value, precision);
    this->append(buffer);
    return *this;
}

String &String::Append(double value, char format, int precision)
{
    char buffer[MAX_FLOAT_STRING_LENGTH];
    doubleToString(buffer, MAX_FLOAT_STRING_LENGTH, value, precision);
    this->append(buffer);
    return *this;
}

short String::ToShort(bool *ok, int base) const noexcept
{
    return 0;
}

unsigned short String::ToUShort(bool *ok, int base) const noexcept
{
    return 0;
}

int String::ToInt(bool *ok, int base) const noexcept
{
    return 0;
}

unsigned int String::ToUInt(bool *ok, int base) const noexcept
{
    return 0;
}

bool String::ToBoolean(bool *ok) const noexcept
{
    return false;
}

long long String::ToLongLong(bool *ok, int base) const noexcept
{
    return 0;
}

unsigned long long String::ToULongLong(bool *ok, int base) const noexcept
{
    return 0;
}

float String::ToFloat(bool *ok) const noexcept
{
    return 0.0f;
}

double String::ToDouble(bool *ok) const noexcept
{
    return 0.0;
}

}// namespace m2
