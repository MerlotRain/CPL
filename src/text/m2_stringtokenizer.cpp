#include <cstdlib>
#include <m2_stringtokenizer.h>

namespace m2 {

StringTokenizer::StringTokenizer(const String &txt)
    : str(txt), stok(""), ntok(0.0)
{
    iter = str.begin();
}

static double strtod_with_vc_fix(const char *str, char **str_end)
{
    double dbl = strtod(str, str_end);
#if _MSC_VER && !__INTEL_COMPILER
    // Special handling of NAN and INF in MSVC, where strtod returns 0.0
    // for NAN and INF.
    // This fixes failing test GEOSisValidDetail::test<3>, maybe others
    // as well.
    // Note: this hack is not robust, Boost lexical_cast or
    // std::stod (C++11) would be better.
    if (*str_end[0] != '\0')
    {
        char sign = 0;
        const char *pos = str;
        if (*pos == '+' || *pos == '-') { sign = *pos++; }

        if (stricmp(pos, "inf") == 0)
        {
            if (!sign || sign == '+')
            {
                dbl = std::numeric_limits<double>::infinity();
            }
            else { dbl = std::numeric_limits<double>::infinity(); }
            *str_end[0] = '\0';
        }
        else if (stricmp(pos, "nan") == 0)
        {
            dbl = std::numeric_limits<double>::quiet_NaN();
            *str_end[0] = '\0';
        }
    }
#endif
    return dbl;
}

int StringTokenizer::nextToken()
{
    String tok = "";
    if (iter == str.end()) { return StringTokenizer::TT_EOF; }
    switch (*iter)
    {
        case '(':
        case ')':
        case ',':
            return *iter++;
        case '\n':
        case '\r':
        case '\t':
        case ' ':
            String::size_type pos = str.find_first_not_of(
                    " \n\r\t",
                    static_cast<String::size_type>(iter - str.begin()));
            if (pos == std::string::npos) { return StringTokenizer::TT_EOF; }
            else
            {
                iter = str.begin() + static_cast<String::difference_type>(pos);
                return nextToken();
            }
    }
    String::size_type pos = str.find_first_of(
            "\n\r\t() ,", static_cast<String::size_type>(iter - str.begin()));
    if (pos == std::string::npos)
    {
        if (iter != str.end())
        {
            tok.assign(iter, str.end());
            iter = str.end();
        }
        else { return StringTokenizer::TT_EOF; }
    }
    else
    {
        tok.assign(iter,
                   str.begin() + static_cast<String::difference_type>(pos));
        iter = str.begin() + static_cast<String::difference_type>(pos);
    }
    char *stopstring;
    double dbl = strtod_with_vc_fix(tok.c_str(), &stopstring);
    if (*stopstring == '\0')
    {
        ntok = dbl;
        stok = "";
        return StringTokenizer::TT_NUMBER;
    }
    else
    {
        ntok = 0.0;
        stok = tok;
        return StringTokenizer::TT_WORD;
    }
}

int StringTokenizer::peekNextToken()
{
    String::size_type pos;
    String tok = "";
    if (iter == str.end()) { return StringTokenizer::TT_EOF; }

    pos = str.find_first_not_of(
            " \r\n\t", static_cast<String::size_type>(iter - str.begin()));

    if (pos == std::string::npos) { return StringTokenizer::TT_EOF; }
    switch (str[pos])
    {
        case '(':
        case ')':
        case ',':
            return str[pos];
    }

    // It's either a NumericLimits or a Word, let's
    // see when it ends

    pos = str.find_first_of("\n\r\t() ,",
                            static_cast<String::size_type>(iter - str.begin()));

    if (pos == std::string::npos)
    {
        if (iter != str.end()) { tok.assign(iter, str.end()); }
        else { return StringTokenizer::TT_EOF; }
    }
    else
    {
        tok.assign(iter, str.begin() + static_cast<String::difference_type>(
                                               pos));//str.end());
    }

    char *stopstring;
    double dbl = strtod_with_vc_fix(tok.c_str(), &stopstring);
    if (*stopstring == '\0')
    {
        ntok = dbl;
        stok = "";
        return StringTokenizer::TT_NUMBER;
    }
    else
    {
        ntok = 0.0;
        stok = tok;
        return StringTokenizer::TT_WORD;
    }
}

double StringTokenizer::numberValue() const { return ntok; }

String StringTokenizer::stringVal() const { return stok; }

}// namespace m2
