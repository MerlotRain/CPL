#ifndef NUMERICSTRING_H
#define NUMERICSTRING_H

#include <string.h>
#include <preconfig.h>

namespace m2 {

template<bool _signed, typename T>
struct is_negative;
template<typename T>
struct is_negative<true, T>
{
    bool operator()(T t) { return t < 0; }
};
template<typename T>
struct is_negative<false, T>
{
    bool operator()(T) { return false; }
};
template<typename T>
inline bool isNegative(T value)
{
    return is_negative<std::numeric_limits<T>::is_signed(), T>();
}


// clang-format off
class CharPointer
{
public:
    constexpr CharPointer( char *ptr, std::size_t offset ) : _beg( ptr ), _cur( ptr ), _end( ptr + offset ) {}
    inline char *&operator++() { checkBounds( _cur + 1 ); return ++_cur; }
    inline char *operator++( int ) { checkBounds( _cur + 1 ); char *tmp = _cur++; return tmp; }
    inline char *&operator--() { checkBounds( _cur - 1 ); return --_cur; }
    inline char *operator--( int ) { checkBounds( _cur - 1 ); char *tmp = _cur--; return tmp; }
    inline char *&operator+=( int incr ) { checkBounds( _cur + incr ); return _cur += incr; }
    inline char *&operator-=( int decr ) { checkBounds( _cur - decr ); return _cur -= decr; }
    inline operator char *() const { return _cur; }
    inline std::size_t span() const { return _end - _beg; }
private:
    void checkBounds( char *ptr ) { if (ptr > _end) throw std::range_error( "current pointer overflow than the end pointer." ); }
    const char *_beg;
    char *_cur;
    const char *_end;
};

// clang-format on

static constexpr auto MAX_INT_STRING_LENGHT = 65;
static constexpr auto MAX_FLOAT_STRING_LENGTH = 780;
static constexpr auto FLOAT_INF = "inf";
static constexpr auto FLOAT_NAN = "nan";
static constexpr auto FLOAT_EXP = 'e';


/// @brief 有符号整型转String
/// @tparam T
/// @param value
/// @param base
/// @param result
/// @param size
/// @param prefix
/// @param width
/// @param fill
/// @param sep
/// @return
template<typename T>
bool intToString(T value, unsigned short base, char *result, size_t &size,
                 bool prefix = false, int width = -1, char fill = ' ',
                 char sep = 0)
{
    if (base < 2 || base > 0x10)
    {
        *result = '\0';
        return false;
    }

    CharPointer ptr(result, size);
    int count = 0;
    T tmpVal;
    do {
        tmpVal = value;
        value /= base;
        *ptr++ =
                "FEDCBA9876543210123456789ABCDEF"[15 + (tmpVal - value * base)];
        if (sep && (base == 10) && (++count == 3))
        {
            *ptr++ = sep;
            count = 0;
        }
    } while (value);

    if ('0' == fill)
    {
        if (tmpVal < 0) { --width; }
        if (prefix && base == 010) { --width; }
        if (prefix && base == 0x10) { width -= 2; }
        while ((ptr - result) < width) { *ptr++ = fill; }
    }

    if (prefix && base == 010) { *ptr++ = '0'; }
    else if (prefix && base == 0x10)
    {
        *ptr++ = 'x';
        *ptr++ = '0';
    }

    if (tmpVal < 0) { *ptr++ = '-'; }

    if ('0' != fill)
    {
        while ((ptr - result) < width) { *ptr++ = fill; }
    }

    size = ptr - result;
    assert(size <= ptr.span());
    assert((-1 == width) || (size >= size_t(width)));
    *ptr-- = '\0';

    char *ptrr = result;
    char tmp;
    while (ptrr < ptr)
    {
        tmp = *ptr;
        *ptr-- = *ptrr;
        *ptrr++ = tmp;
    }
    return true;
}

template<typename T>
bool intToString(T value, unsigned short base, String &result,
                 bool prefix = false, int width = -1, char fill = ' ',
                 char sep = 0)
{
    char res[MAX_INT_STRING_LENGHT] = {0};
    std::size_t size = MAX_INT_STRING_LENGHT;
    bool ret = intToString(value, base, res, size, prefix, width, fill, sep);
    result.assign(res, size);
    return ret;
}

/// @brief 无符号整型转String
/// @tparam T
/// @param value
/// @param base
/// @param result
/// @param size
/// @param prefix
/// @param width
/// @param fill
/// @param sep
/// @return
template<typename T>
bool unsignedIntToString(T value, unsigned short base, char *result,
                         size_t &size, bool prefix = false, int width = -1,
                         char fill = ' ', char sep = 0)
{
    if (base < 2 || base > 0x10)
    {
        *result = '\0';
        return false;
    }

    CharPointer ptr(result, size);
    int thCount = 0;
    T tmpVal;
    do {
        tmpVal = value;
        value /= base;
        *ptr++ =
                "FEDCBA9876543210123456789ABCDEF"[15 + (tmpVal - value * base)];
        if (sep && (base == 10) && (++thCount == 3))
        {
            *ptr++ = sep;
            thCount = 0;
        }
    } while (value);

    if ('0' == fill)
    {
        if (prefix && base == 010) { --width; }
        if (prefix && base == 0x10) { width -= 2; }
        while ((ptr - result) < width) { *ptr++ = fill; }
    }

    if (prefix && base == 010) { *ptr++ = '0'; }
    else if (prefix && base == 0x10)
    {
        *ptr++ = 'x';
        *ptr++ = '0';
    }

    if ('0' != fill)
    {
        while ((ptr - result) < width) { *ptr++ = fill; }
    }

    size = ptr - result;
    poco_assert_dbg(size <= ptr.span());
    poco_assert_dbg((-1 == width) || (size >= size_t(width)));
    *ptr-- = '\0';

    char *ptrr = result;
    char tmp;
    while (ptrr < ptr)
    {
        tmp = *ptr;
        *ptr-- = *ptrr;
        *ptrr++ = tmp;
    }

    return true;
}

template<typename T>
bool unsignedIntToString(T value, unsigned short base, String &result,
                         bool prefix = false, int width = -1, char fill = ' ',
                         char sep = 0)
{
    char res[MAX_INT_STRING_LENGHT] = {0};
    std::size_t size = MAX_INT_STRING_LENGHT;
    bool ret = unsignedIntToString(value, base, res, size, prefix, width, fill,
                                   thSep);
    result.assign(res, size);
    return ret;
}

/// @brief float模块
/// @param buff
/// @param buffSize
/// @param value
/// @param low
/// @param high
void floatToString(char *buff, int buffSize, float value,
                   int low = -std::numeric_limits<float>::digits10,
                   int high = std::numeric_limits<float>::digits10);
String floatToString(String &str, float value, int precision = -1,
                     int width = 0, char thSep = 0, char decSep = 0);
void floatToFixedString(char *buff, int buffSize, float value, int precision);
String floatToFixedString(String &str, float value, int precision,
                          int width = 0, char thSep = 0, char decSep = 0);

/// @brief double模块
/// @param buff
/// @param buffSize
/// @param value
/// @param low
/// @param high
void doubleToString(char *buff, int buffSize, double value,
                    int low = -std::numeric_limits<double>::digits10,
                    int high = std::numeric_limits<double>::digits10);
String doubleToString(String &str, double value, int precision = -1,
                      int width = 0, char thSep = 0, char decSep = 0);
void doubleToFixedString(char *buff, int buffSize, double value, int precision);
String doubleToFixedString(String &str, double value, int precision,
                           int width = 0, char thSep = 0, char decSep = 0);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/// @brief 字符串转int
/// @tparam T
/// @param str
/// @param result
/// @param base
/// @param sep
/// @return
template<typename T>
bool stringToInt(const char *str, T &out, unsigned short base, char sep = ',')
{
    assert(base == 2 || base == 8 || base == 10 || base == 16);

    if (!str) { return false; }
    while (std::isspace(*str)) { ++str; }
    if (*str == '\0') { return false; }
    bool negative = false;
    if ((base == 10) && (*str == '-'))
    {
        if (!std::numeric_limits<T>::is_signed) { return false; }
        negative = true;
        ++str;
    }
    else if (*str == '+') { ++str; }

    uintmax_t limitCheck = std::numeric_limits<T>::max();
    if (negative) { ++limitCheck; }
    uintmax_t result = 0;
    unsigned char add = 0;
    for (; *str != '\0'; ++str)
    {
        if (*str == thSep)
        {
            if (base == 10) { continue; }
            throw std::runtime_error(
                    "thousand separators only allowed for base 10");
        }
        if (result > (limitCheck / base)) { return false; }
        if (!safeMultiply(result, result, base)) { return false; }
        switch (*str)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                add = (*str - '0');
                break;

            case '8':
            case '9':
                if ((base == 10) || (base == 0x10)) { add = (*pStr - '0'); }
                else { return false; }
                break;

            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
                if (base != 0x10) { return false; }
                add = (*str - 'a') + 10;
                break;

            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
                if (base != 0x10) { return false; }
                add = (*str - 'A') + 10;
                break;

            default:
                return false;
        }
        if ((limitCheck - static_cast<uintmax_t>(result)) < add)
        {
            return false;
        }
        result += add;
    }

    if (negative && (base == 10)) { out = static_cast<T>(-result); }
    else { out = static_cast<T>(result); }

    return true;
}
template<typename T>
bool stringToInt(String &str, T &result, unsigned short base, char sep = ',')
{
    return stringToInt(str.c_str(), result, base, sep);
}


/// @brief 字符串转float
/// @param str
/// @param inf
/// @param nan
/// @return
float stringToFloat(const char *str, const char *inf = FLOAT_INF,
                    const char *nan = FLOAT_NAN);
bool stringToFloat(const String &str, float &result, char decSep = '.',
                   char thSep = ',', const char *inf = FLOAT_INF,
                   const char *nan = FLOAT_NAN);


/// @brief
/// @param str
/// @param inf
/// @param nan
/// @return
double stringToDouble(const char *str, const char *inf = FLOAT_INF,
                      const char *nan = FLOAT_NAN);
bool stringToDouble(const String &str, double &result, char decSep = '.',
                    char thSep = ',', const char *inf = FLOAT_INF,
                    const char *nan = FLOAT_NAN);


}// namespace m2


#endif//NUMERICSTRING_H
