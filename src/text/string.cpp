#include "numericstring.h"
#include <cstdarg>
#include <cstdlib>
#include <regex>
#include <stringhelp.h>

namespace m2 {


GsString::GsString() noexcept
{
}

GsString::GsString(const GsString &str) noexcept : GsStlString(str.data())
{
}

GsString::GsString(const GsStlString &str) noexcept : GsStlString(str)
{
}

GsString::GsString(const char *str) noexcept : GsStlString(str)
{
}

GsString::GsString(char *str) noexcept : GsStlString(str)
{
}

GsString::GsString(const char *str, int off, int count) noexcept : GsStlString(str, off, count)
{
}

GsString::GsString(const char *str, int count) noexcept : GsStlString(str, count)
{
}

GsString::GsString(const char *start, const char *end) noexcept : GsStlString(start, end)
{
}

GsString::GsString(const unsigned char *start, const unsigned char *end) noexcept
    : GsStlString(start, end)
{
}

GsString::GsString(int count, char e) noexcept : GsStlString(count, e)
{
}

GsString::GsString(const_iterator first, const_iterator last) noexcept : GsStlString(first, last)
{
}

GsString::GsString(iterator first, iterator last) noexcept : GsStlString(first, last)
{
}

GsString::GsString(reverse_iterator first, reverse_iterator last) noexcept : GsStlString(first, last)
{
}

GsString::GsString(const_reverse_iterator first, const_reverse_iterator last) noexcept
    : GsStlString(first, last)
{
}

GsString::GsString(GsString *str) noexcept
{
    if (str)
    {
        this->assign(str->c_str());
    }
}

GsString::~GsString()
{
}

GsString &GsString::operator=(const char *str)
{
    this->assign(str);
    return *this;
}

GsString &GsString::operator=(const GsStlString &str)
{
    this->assign(str);
    return *this;
}

GsString &GsString::operator=(const GsString &str)
{
    this->assign(str);
    return *this;
}

GsString::reference GsString::operator[](int _Off)
{
    return this->at(_Off);
}

GsString::const_reference GsString::operator[](int _Off) const
{
    return this->at(_Off);
}

GsString::operator bool() const
{
    return this->IsNullOrEmpty();
}

GsString::operator const char *() const
{
    return this->data();
}

GsString &GsString::Remove(char ch)
{
    return *this;
}

GsString &GsString::Remove(const char *src)
{
    return *this;
}

bool GsString::IsNullOrEmpty(const char *str)
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

GsString &GsString::operator+=(const char *str)
{
    this->append(str);
    return *this;
}

GsString &GsString::operator+=(int ch)
{
    this->push_back(char(ch));
    return *this;
}

GsString &GsString::operator+=(char ch)
{
    this->push_back(ch);
    return *this;
}

GsString &GsString::operator+=(const GsString &str)
{
    this->append(str);
    return *this;
}

GsString GsString::operator+(const char *str) const
{
    GsString s;
    s.assign(this->data());
    s.append(str);
    return s;
}

GsString GsString::operator+(const GsString &str) const
{
    GsString s;
    s.assign(this->data());
    s.append(str);
    return s;
}

GsString GsString::operator+(const GsStlString &str) const
{
    GsString s;
    s.assign(this->data());
    s.append(str);
    return s;
}

int GsString::Length() const
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

GsString &GsString::ToUpper()
{
    std::transform(this->begin(), this->end(), this->begin(), ::toupper);
    return *this;
}

GsString &GsString::ToLower()
{
    std::transform(this->begin(), this->end(), this->begin(), ::tolower);
    return *this;
}

GsString &GsString::Reverse()
{
    std::reverse(this->begin(), this->end());
    return *this;
}

GsString &GsString::TrimRight()
{
    size_type index = this->find_first_not_of(" \n\r\t");
    if (index != npos)
    {
        *this = this->substr(index);
    }
    return *this;
}

GsString &GsString::TrimLeft()
{
    size_type index = this->find_first_not_of(" \n\r\t");
    if (index != npos)
    {
        *this = this->substr(index);
    }
    return *this;
}

GsString &GsString::Trimmed()
{
    TrimLeft();
    TrimRight();
    return *this;
}

GsStringList GsString::Split(const char *strSep)
{
    GsStringList list;
    std::regex reg(strSep);
    std::sregex_token_iterator pos(this->begin(), this->end(), reg, -1);
    decltype(pos) end;
    for (; pos != end; ++pos)
    {
        list.push_back(pos->str());
    }
    return list;
}

void GsString::Split(const char *strSep, GsStringList &vecStr)
{
    std::regex reg(strSep);
    std::sregex_token_iterator pos(this->begin(), this->end(), reg, -1);
    decltype(pos) end;
    for (; pos != end; ++pos)
    {
        vecStr.push_back(pos->str());
    }
}

GsString &GsString::Replace(const char from, const char to, size_type start)
{
    if (from == to)
    {
        return *this;
    }

    typename GsString::size_type pos = 0;
    do
    {
        pos = this->find(from, start);
        if (pos != GsString::npos)
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
    } while (pos != GsString::npos);
}

GsString &GsString::Replace(const char *from, const char *to, size_type start)
{
    assert(from);
    GsString result;

    typename GsString::size_type pos = 0;
    typename GsString::size_type fromlen = std::strlen(from);
    result.append(this->data(), 0, start);
    do
    {
        pos = this->find(from);
        if (pos != GsString::npos)
        {
            result.append(this->data(), start, pos - start);
            result.append(to);
            start = pos + fromlen;
        }
        else
        {
            result.append(this->data(), start, length() - start);
        }
    } while (pos != GsString::npos);

    this->swap(result);
    return *this;
}

GsString &GsString::Replace(const GsString &from, const GsString &to, size_type start)
{
    if (from == to)
    {
        return *this;
    }

    typename GsString::size_type pos = 0;
    do
    {
        pos = find(from, start);
        if (pos != GsString::npos)
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
    } while (pos != GsString::npos);
}

bool GsString::StartWith(const char *str, const char *strHead, bool bIgnoringCase)
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

bool GsString::EndWith(const char *str, const char *strTail, bool bIgnoringCase)
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

bool GsString::Contains(const char *str, char c, bool bIgnoringCase)
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

bool GsString::Contains(const char *src, const char *str, bool bIgnoringCase)
{
    return false;
}


GsString GsString::Remove(const char *str, const char *c)
{
    return GsString();
}

int GsString::Compare(const char *strA, const char *strB)
{
    return 0;
}

GsString GsString::Escape(const char *str, bool strictJSON)
{
    return GsString();
}

GsString GsString::Unescape(const char *str)
{
    return GsString();
}

GsString GsString::ToString(bool value, GsBoolFormat format)
{
    switch (format)
    {
        case GsBoolFormat::eFalseAndTrue:
            return value ? "false" : "true";
        case GsBoolFormat::eOnAndOff:
            return value ? "on" : "off";
        case GsBoolFormat::eYesAndNo:
            return value ? "yes" : "no";
        default:
            break;
    }
}

GsString GsString::ToString(short value, int base, int width, char fill, bool prefix)
{
    GsString result;
    intToString<short>(value, base, result, false, width, fill);
    return result;
}

GsString GsString::ToString(unsigned short value, int base, int width, char fill, bool prefix)
{
    GsString result;
    unsignedIntToString<unsigned short>(value, base, result, false, width, fill);
    return result;
}

GsString GsString::ToString(int value, int base, int width, char fill, bool prefix)
{
    GsString result;
    intToString<int>(value, base, result, false, width, fill);
    return result;
}

GsString GsString::ToString(unsigned int value, int base, int width, char fill, bool prefix)
{
    GsString result;
    unsignedIntToString<unsigned int>(value, base, result, false, width, fill);
    return result;
}

GsString GsString::ToString(long value, int base, int width, char fill, bool prefix)
{
    GsString result;
    intToString<long>(value, base, result, false, width, fill);
    return result;
}

GsString GsString::ToString(unsigned long value, int base, int width, char fill, bool prefix)
{
    GsString result;
    unsignedIntToString<unsigned long>(value, base, result, false, width, fill);
    return result;
}

GsString GsString::ToString(long long value, int base, int width, char fill, bool prefix)
{
    GsString result;
    intToString<long long>(value, base, result, false, width, fill);
    return result;
}

GsString GsString::ToString(unsigned long long value, int base, int width, char fill, bool prefix)
{
    GsString result;
    unsignedIntToString<unsigned long long>(value, base, result, false, width, fill);
    return result;
}

GsString GsString::ToString(float value, char format, int precision)
{
    if (precision < 0)
    {
        precision = 0;
    }
    char buffer[MAX_FLOAT_STRING_LENGTH];
    floatToString(buffer, MAX_FLOAT_STRING_LENGTH, value, precision);
    return GsString(buffer);
}

GsString GsString::ToString(double value, char format, int precision)
{
    if (precision < 0)
    {
        precision = 0;
    }
    char buffer[MAX_FLOAT_STRING_LENGTH];
    doubleToString(buffer, MAX_FLOAT_STRING_LENGTH, value, precision);
    return GsString(buffer);
}

GsString &GsString::Arg(const GsString &str, int width, char fill)
{
    return *this;
}

GsString &GsString::Arg(GsString &&str, int width, char fill)
{
    return *this;
}


GsString &GsString::Arg(short value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    intToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

GsString &GsString::Arg(unsigned short value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    unsignedIntToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

GsString &GsString::Arg(int value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    intToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

GsString &GsString::Arg(unsigned int value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    unsignedIntToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

GsString &GsString::Arg(long value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    intToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

GsString &GsString::Arg(unsigned long value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    unsignedIntToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

GsString &GsString::Arg(long long value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    intToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

GsString &GsString::Arg(unsigned long long value, int base, int width, char fill, bool prefix)
{
    char result[MAX_INT_STRING_LENGHT];
    std::size_t sz = MAX_INT_STRING_LENGHT;
    unsignedIntToString(value, base, result, sz, prefix, width, fill);
    this->append(result, sz);
    return *this;
}

GsString &GsString::Arg(float value, char format, int precision)
{
    char buffer[MAX_FLOAT_STRING_LENGTH];
    floatToString(buffer, MAX_FLOAT_STRING_LENGTH, value, precision);
    this->append(buffer);
    return *this;
}

GsString &GsString::Arg(double value, char format, int precision)
{
    char buffer[MAX_FLOAT_STRING_LENGTH];
    doubleToString(buffer, MAX_FLOAT_STRING_LENGTH, value, precision);
    this->append(buffer);
    return *this;
}

short GsString::ToShort(bool *ok, int base) const noexcept
{
    return 0;
}

unsigned short GsString::ToUShort(bool *ok, int base) const noexcept
{
    return 0;
}

int GsString::ToInt(bool *ok, int base) const noexcept
{
    return 0;
}

unsigned int GsString::ToUInt(bool *ok, int base) const noexcept
{
    return 0;
}

bool GsString::ToBoolean(bool *ok) const noexcept
{
    return false;
}

long long GsString::ToLongLong(bool *ok, int base) const noexcept
{
    return 0;
}

unsigned long long GsString::ToULongLong(bool *ok, int base) const noexcept
{
    return 0;
}

float GsString::ToFloat(bool *ok) const noexcept
{
    return 0.0f;
}

double GsString::ToDouble(bool *ok) const noexcept
{
    return 0.0;
}

}// namespace m2
