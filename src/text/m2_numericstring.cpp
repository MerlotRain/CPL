#include "m2_numericstring.h"
#include "../3rd_party/double-conversion/bignum-dtoa.cc"
#include "../3rd_party/double-conversion/bignum.cc"
#include "../3rd_party/double-conversion/cached-powers.cc"
#include "../3rd_party/double-conversion/double-conversion.h"
#include "../3rd_party/double-conversion/double-to-string.cc"
#include "../3rd_party/double-conversion/fast-dtoa.cc"
#include "../3rd_party/double-conversion/fixed-dtoa.cc"
#include "../3rd_party/double-conversion/string-to-double.cc"
#include "../3rd_party/double-conversion/strtod.cc"

namespace m2 {

namespace {

void pad(String &str, int precision, int width, char prefix = ' ',
         char decSep = '.')
{
    assert(precision > 0);
    assert(str.length());

    String::size_type decSepPos = str.find(decSep);
    if (decSepPos == String::npos)
    {
        str.append(1, decSep);
        decSepPos = str.size() - 1;
    }

    String::size_type frac = str.length() - decSepPos - 1;

    String::size_type ePos = str.find_first_of("eE");
    std::unique_ptr<String> eStr;
    if (ePos != String::npos)
    {
        eStr.reset(new String(str.substr(ePos, String::npos)));
        frac -= eStr->length();
        str = str.substr(0, str.length() - eStr->length());
    }

    if (frac != precision)
    {
        if (frac < precision) { str.append(precision - frac, '0'); }
        else if ((frac > precision) && (decSepPos != String::npos))
        {
            int pos = static_cast<int>(decSepPos) + 1 + precision;
            if (str[pos] >= '5')// we must round up
            {
                char carry = 0;
                if (str[--pos] == '9')
                {
                    str[pos] = '0';
                    carry = 1;
                }
                else
                {
                    ++str[pos];
                    carry = 0;
                }
                while (--pos >= 0)
                {
                    if (str[pos] == decSep) { continue; }
                    if (carry)
                    {
                        if ((str[pos] + carry) <= '9')
                        {
                            ++str[pos];
                            carry = 0;
                        }
                        else
                        {
                            str[pos] = '0';
                            carry = 1;
                        }
                    }
                }
                if (carry) { str.insert(str.begin(), 1, '1'); }
            }
            str = str.substr(0, decSepPos + 1 + precision);
        }
    }

    if (eStr.get()) { str += *eStr; }

    if (width && (str.length() < width))
    {
        str.insert(str.begin(), width - str.length(), prefix);
    }
}

void insertThousandSep(String &str, char thSep, char decSep = '.')
{
    assert(decSep != thSep);
    if (str.size() == 0) { return; }

    String::size_type exPos = str.find('e');
    if (exPos == String::npos) { exPos = str.find('E'); }
    String::size_type decPos = str.find(decSep);
    // there's no rinsert, using forward iterator to go backwards
    String::iterator it = str.end();
    if (exPos != String::npos) { it -= str.size() - exPos; }

    if (decPos != String::npos)
    {
        while (it != str.begin())
        {
            --it;
            if (*it == decSep) { break; }
        }
    }
    int thCount = 0;
    if (it == str.end()) { --it; }
    for (; it != str.begin();)
    {
        String::iterator pos = it;
        String::value_type chr = *it;
        String::value_type prevChr = *--it;

        if (!std::isdigit(chr)) { continue; }

        if (++thCount == 3 && std::isdigit(prevChr))
        {
            it = str.insert(pos, thSep);
        }

        if (thCount == 3) { thCount = 0; }
    }
}

}// namespace


void floatToString(char *buff, int buffSize, float value, int low, int high)
{
    using namespace double_conversion;

    StringBuilder builder(buff, buffSize);
    int flags = DoubleToStringConverter::UNIQUE_ZERO |
                DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;
    DoubleToStringConverter dc(flags, FLOAT_INF, FLOAT_NAN, FLOAT_EXP, low,
                               high, 0, 0);
    dc.ToShortestSingle(value, &builder);
    builder.Finalize();
}

String floatToString(String &str, float value, int precision, int width,
                     char thSep, char decSep)
{
    if (!decSep) { decSep = '.'; }
    if (precision == 0) { value = std::floor(value); }

    char buffer[MAX_FLOAT_STRING_LENGTH];
    floatToString(buffer, MAX_FLOAT_STRING_LENGTH, value);
    str = buffer;

    if (decSep && (decSep != '.') && (str.find('.') != String::npos))
    {
        str.replaceTo('.', decSep);
    }

    if (thSep) { insertThousandSep(str, thSep, decSep); }
    if (precision > 0 || width)
    {
        pad(str, precision, width, ' ', decSep ? decSep : '.');
    }
    return str;
}

void floatToFixedString(char *buff, int buffSize, float value, int precision)
{
    using namespace double_conversion;

    StringBuilder builder(buff, buffSize);
    int flags = DoubleToStringConverter::UNIQUE_ZERO |
                DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;
    DoubleToStringConverter dc(flags, FLOAT_INF, FLOAT_NAN, FLOAT_EXP,
                               -std::numeric_limits<float>::digits10,
                               std::numeric_limits<float>::digits10, 0, 0);
    dc.ToFixed(value, precision, &builder);
    builder.Finalize();
}

String floatToFixedString(String &str, float value, int precision, int width,
                          char thSep, char decSep)
{
    if (!decSep) { decSep = '.'; }
    if (precision == 0) { value = std::floor(value); }

    char buffer[MAX_FLOAT_STRING_LENGTH];
    floatToFixedString(buffer, MAX_FLOAT_STRING_LENGTH, value, precision);
    str = buffer;

    if (decSep && (decSep != '.') && (str.find('.') != String::npos))
    {
        str.replaceTo('.', decSep);
    }

    if (thSep) { insertThousandSep(str, thSep, decSep); }
    if (precision > 0 || width)
    {
        pad(str, precision, width, ' ', decSep ? decSep : '.');
    }
    return str;
}

float stringToFloat(const char *str, const char *inf, const char *nan)
{
    using namespace double_conversion;

    int processed;
    int flags = StringToDoubleConverter::ALLOW_LEADING_SPACES |
                StringToDoubleConverter::ALLOW_TRAILING_SPACES;
    StringToDoubleConverter converter(flags, 0.0, Single::NaN(), inf, nan);
    float result = converter.StringToFloat(str, static_cast<int>(strlen(str)),
                                           &processed);
    return result;
}

bool stringToFloat(const String &str, float &result, char decSep, char thSep,
                   const char *inf, const char *nan)
{
    using namespace double_conversion;

    String tmp(str);
    tmp.trimmed();
    tmp.remove(thSep);
    tmp.remove('f');
    tmp.replaceTo(decSep, '.');
    result = stringToFloat(tmp.c_str(), inf, nan);
    return !std::isinf(result) && !std::isnan(result);
}

void doubleToString(char *buff, int buffSize, double value, int low, int high)
{
    using namespace double_conversion;

    StringBuilder builder(buff, buffSize);
    int flags = DoubleToStringConverter::UNIQUE_ZERO |
                DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;
    DoubleToStringConverter dc(flags, FLOAT_INF, FLOAT_NAN, FLOAT_EXP, low,
                               high, 0, 0);
    dc.ToShortest(value, &builder);
    builder.Finalize();
}

String doubleToString(String &str, double value, int precision, int width,
                      char thSep, char decSep)
{
    if (!decSep) { decSep = '.'; }
    if (precision == 0) { value = std::floor(value); }

    char buffer[MAX_FLOAT_STRING_LENGTH];
    doubleToString(buffer, MAX_FLOAT_STRING_LENGTH, value);

    str = buffer;

    if (decSep && (decSep != '.') && (str.find('.') != String::npos))
    {
        str.replaceTo('.', decSep);
    }

    if (thSep) { insertThousandSep(str, thSep, decSep); }
    if (precision > 0 || width)
    {
        pad(str, precision, width, ' ', decSep ? decSep : '.');
    }
    return str;
}

void doubleToFixedString(char *buff, int buffSize, double value, int precision)
{
    using namespace double_conversion;

    StringBuilder builder(buff, buffSize);
    int flags = DoubleToStringConverter::UNIQUE_ZERO |
                DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;
    DoubleToStringConverter dc(flags, FLOAT_INF, FLOAT_NAN, FLOAT_EXP,
                               -std::numeric_limits<double>::digits10,
                               std::numeric_limits<double>::digits10, 0, 0);
    dc.ToFixed(value, precision, &builder);
    builder.Finalize();
}

String doubleToFixedString(String &str, double value, int precision, int width,
                           char thSep, char decSep)
{
    if (!decSep) { decSep = '.'; }
    if (precision == 0) { value = std::floor(value); }

    char buffer[MAX_FLOAT_STRING_LENGTH];
    doubleToFixedString(buffer, MAX_FLOAT_STRING_LENGTH, value, precision);

    str = buffer;

    if (decSep && (decSep != '.') && (str.find('.') != String::npos))
    {
        str.replaceTo('.', decSep);
    }

    if (thSep) { insertThousandSep(str, thSep, decSep); }
    if (precision > 0 || width)
    {
        pad(str, precision, width, ' ', decSep ? decSep : '.');
    }
    return str;
}

double stringToDouble(const char *str, const char *inf, const char *nan)
{
    using namespace double_conversion;
    int processed;
    int flags = StringToDoubleConverter::ALLOW_LEADING_SPACES |
                StringToDoubleConverter::ALLOW_TRAILING_SPACES;
    StringToDoubleConverter converter(flags, 0.0, Double::NaN(), inf, nan);
    double result = converter.StringToDouble(str, static_cast<int>(strlen(str)),
                                             &processed);
    return result;
}

bool stringToDouble(const String &str, double &result, char decSep, char thSep,
                    const char *inf, const char *nan)
{
    if (str.empty()) { return false; }

    using namespace double_conversion;

    String tmp(str);
    tmp.trimmed();
    tmp.remove(thSep);
    tmp.replaceTo(decSep, '.');
    tmp.remove('f');
    result = stringToDouble(tmp.c_str(), inf, nan);
    return !std::isinf(result) && !std::isnan(result);
}


}// namespace m2
