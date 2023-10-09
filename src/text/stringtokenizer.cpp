#include <cstdlib>
#include <stringhelp.h>
#include <stringtokenizer.h>

namespace m2 {

StringTokenizer::StringTokenizer(const String &txt) : m_str(txt), m_stok(""), m_ntok(0.0)
{
    m_iter = m_str.begin();
}

static double strtod_with_vc_fix(const char *m_str, char **str_end)
{
    double dbl = strtod(m_str, str_end);
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
        const char *pos = m_str;
        if (*pos == '+' || *pos == '-')
        {
            sign = *pos++;
        }

        if (stricmp(pos, "inf") == 0)
        {
            if (!sign || sign == '+')
            {
                dbl = std::numeric_limits<double>::infinity();
            }
            else
            {
                dbl = std::numeric_limits<double>::infinity();
            }
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

int StringTokenizer::NextToken()
{
    String tok = "";
    if (m_iter == m_str.end())
    {
        return StringTokenizer::TT_EOF;
    }
    switch (*m_iter)
    {
        case '(':
        case ')':
        case ',':
            return *m_iter++;
        case '\n':
        case '\r':
        case '\t':
        case ' ':
            String::size_type pos = m_str.find_first_not_of(
                    " \n\r\t", static_cast<String::size_type>(m_iter - m_str.begin()));
            if (pos == std::string::npos)
            {
                return StringTokenizer::TT_EOF;
            }
            else
            {
                m_iter = m_str.begin() + static_cast<String::difference_type>(pos);
                return NextToken();
            }
    }
    String::size_type pos =
            m_str.find_first_of("\n\r\t() ,", static_cast<String::size_type>(m_iter - m_str.begin()));
    if (pos == std::string::npos)
    {
        if (m_iter != m_str.end())
        {
            tok.assign(m_iter, m_str.end());
            m_iter = m_str.end();
        }
        else
        {
            return StringTokenizer::TT_EOF;
        }
    }
    else
    {
        tok.assign(m_iter, m_str.begin() + static_cast<String::difference_type>(pos));
        m_iter = m_str.begin() + static_cast<String::difference_type>(pos);
    }
    char *stopstring;
    double dbl = strtod_with_vc_fix(tok.c_str(), &stopstring);
    if (*stopstring == '\0')
    {
        m_ntok = dbl;
        m_stok = "";
        return StringTokenizer::TT_NUMBER;
    }
    else
    {
        m_ntok = 0.0;
        m_stok = tok;
        return StringTokenizer::TT_WORD;
    }
}

int StringTokenizer::PeekNextToken()
{
    String::size_type pos;
    String tok = "";
    if (m_iter == m_str.end())
    {
        return StringTokenizer::TT_EOF;
    }

    pos = m_str.find_first_not_of(" \r\n\t", static_cast<String::size_type>(m_iter - m_str.begin()));

    if (pos == std::string::npos)
    {
        return StringTokenizer::TT_EOF;
    }
    switch (m_str[pos])
    {
        case '(':
        case ')':
        case ',':
            return m_str[pos];
    }

    // It's either a NumericLimits or a Word, let's
    // see when it ends

    pos = m_str.find_first_of("\n\r\t() ,", static_cast<String::size_type>(m_iter - m_str.begin()));

    if (pos == std::string::npos)
    {
        if (m_iter != m_str.end())
        {
            tok.assign(m_iter, m_str.end());
        }
        else
        {
            return StringTokenizer::TT_EOF;
        }
    }
    else
    {
        tok.assign(m_iter, m_str.begin() + static_cast<String::difference_type>(pos));//m_str.end());
    }

    char *stopstring;
    double dbl = strtod_with_vc_fix(tok.c_str(), &stopstring);
    if (*stopstring == '\0')
    {
        m_ntok = dbl;
        m_stok = "";
        return StringTokenizer::TT_NUMBER;
    }
    else
    {
        m_ntok = 0.0;
        m_stok = tok;
        return StringTokenizer::TT_WORD;
    }
}

double StringTokenizer::GetNVal() const
{
    return m_ntok;
}

String StringTokenizer::GetSVal() const
{
    return m_stok;
}

}// namespace m2
