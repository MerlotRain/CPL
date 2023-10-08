#include <mathhelp.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace m2 {

GsBigDecimal::GsBigDecimal() noexcept
{
}

GsBigDecimal::GsBigDecimal(const GsBigDecimal &v) noexcept : m_Value(v.m_Value)
{
}

GsBigDecimal::GsBigDecimal(const char *v) : m_Value(v)
{
}

GsBigDecimal::GsBigDecimal(GsString v) : m_Value(v)
{
}

GsBigDecimal::GsBigDecimal(int v) noexcept : m_Value()
{
    GsStringStream ss;
    ss << v;
    m_Value = ss.Str();
}

GsBigDecimal::GsBigDecimal(long long v) noexcept : m_Value()
{
    GsStringStream ss;
    ss << v;
    m_Value = ss.Str();
}

GsBigDecimal::GsBigDecimal(long long int v) noexcept : m_Value()
{
    GsStringStream ss;
    ss << v;
    m_Value = ss.Str();
}

GsBigDecimal::GsBigDecimal(unsigned int v) noexcept : m_Value()
{
    GsStringStream ss;
    ss << v;
    m_Value = ss.Str();
}

GsBigDecimal::GsBigDecimal(unsigned long long v) noexcept
{
    GsStringStream ss;
    ss << v;
    m_Value = ss.Str();
}

GsBigDecimal::GsBigDecimal(unsigned long long int v) noexcept : m_Value()
{
    GsStringStream ss;
    ss << v;
    m_Value = ss.Str();
}

GsBigDecimal::GsBigDecimal(float v) noexcept : m_Value()
{
    GsStringStream ss;
    ss << v;
    m_Value = ss.Str();
}

GsBigDecimal::GsBigDecimal(double v) noexcept : m_Value()
{
    GsStringStream ss;
    ss << v;
    m_Value = ss.Str();
}

GsBigDecimal::GsBigDecimal(long double v) noexcept
{
    GsStringStream ss;
    ss << v;
    m_Value = ss.Str();
}

GsBigDecimal GsBigDecimal::operator+(const GsBigDecimal &rhs)
{
    return GsBigDecimal::Add(m_Value, rhs.m_Value);
}

GsBigDecimal GsBigDecimal::operator-(const GsBigDecimal &rhs)
{
    return GsBigDecimal::Subtract(m_Value, rhs.m_Value);
}

GsBigDecimal GsBigDecimal::operator*(const GsBigDecimal &rhs)
{
    return GsBigDecimal::Multiply(m_Value, rhs.m_Value);
}

GsBigDecimal GsBigDecimal::operator/(const GsBigDecimal &rhs)
{
    return GsBigDecimal::Divide(m_Value, rhs.m_Value);
}

GsBigDecimal GsBigDecimal::operator%(const GsBigDecimal &rhs)
{
    return GsBigDecimal::Modulus(m_Value, rhs.m_Value);
}

GsBigDecimal GsBigDecimal::operator^(const GsBigDecimal &rhs)
{
    return GsBigDecimal::Pow(m_Value, rhs.m_Value);
}

void GsBigDecimal::operator+=(const GsBigDecimal &rhs)
{
    m_Value = GsBigDecimal::Add(m_Value, rhs.m_Value);
}

void GsBigDecimal::operator-=(const GsBigDecimal &rhs)
{
    m_Value = GsBigDecimal::Subtract(m_Value, rhs.m_Value);
}

void GsBigDecimal::operator*=(const GsBigDecimal &rhs)
{
    m_Value = GsBigDecimal::Multiply(m_Value, rhs.m_Value);
}

void GsBigDecimal::operator/=(const GsBigDecimal &rhs)
{
    m_Value = GsBigDecimal::Divide(m_Value, rhs.m_Value);
}

void GsBigDecimal::operator^=(const GsBigDecimal &rhs)
{
    m_Value = GsBigDecimal::Pow(m_Value, rhs.m_Value);
}

bool GsBigDecimal::operator>(const GsBigDecimal &rhs)
{
    return GsBigDecimal::CompareTo(m_Value, rhs.m_Value) > 0;
}

bool GsBigDecimal::operator>=(const GsBigDecimal &rhs)
{
    return GsBigDecimal::CompareTo(m_Value, rhs.m_Value) >= 0;
}

bool GsBigDecimal::operator==(const GsBigDecimal &rhs)
{
    return GsBigDecimal::CompareTo(m_Value, rhs.m_Value) == 0;
}

bool GsBigDecimal::operator<(const GsBigDecimal &rhs)
{
    return GsBigDecimal::CompareTo(m_Value, rhs.m_Value) < 0;
}

bool GsBigDecimal::operator<=(const GsBigDecimal &rhs)
{
    return GsBigDecimal::CompareTo(m_Value, rhs.m_Value) <= 0;
}

int GsBigDecimal::ToInt()
{
    GsIStringStream buffer(m_Value);
    int ret;
    buffer >> ret;
    return ret;
}

unsigned int GsBigDecimal::ToUInt()
{
    GsIStringStream buffer(m_Value);
    unsigned int ret;
    buffer >> ret;
    return ret;
}

long long GsBigDecimal::ToLongLong()
{
    GsIStringStream buffer(m_Value);
    long long ret;
    buffer >> ret;
    return ret;
}

unsigned long long GsBigDecimal::ToULongLong()
{
    GsIStringStream buffer(m_Value);
    unsigned long long ret;
    buffer >> ret;
    return ret;
}

long double GsBigDecimal::ToLongDouble()
{
    GsIStringStream buffer(m_Value);
    long double ret;
    buffer >> ret;
    return ret;
}

double GsBigDecimal::ToDouble()
{
    GsIStringStream buffer(m_Value);
    double ret;
    buffer >> ret;
    return ret;
}

float GsBigDecimal::ToFloat()
{
    GsIStringStream buffer(m_Value);
    float ret;
    buffer >> ret;
    return ret;
}

GsString GsBigDecimal::ToString()
{
    return m_Value;
}

void GsBigDecimal::Round(int scale)
{
    if (scale >= 1)
        m_Value = GsBigDecimal::Round(m_Value, scale);
}

GsString GsBigDecimal::IntPart()
{
    size_t dot = m_Value.find('.');
    if (dot != GsString::npos)
    {
        if (dot == 0)
            return GsString("0");
        if (dot == 1 && m_Value[0] == '-')
            return GsString("-0");
        return m_Value.substr(0, dot);
    }
    else
    {
        return m_Value;
    }
}

GsString GsBigDecimal::DecPart()
{
    size_t dot = m_Value.find('.');
    if (dot != GsString::npos)
        return m_Value.length() > dot + 1 ? m_Value.substr(dot + 1) : GsString("0");
    else
        return GsString("0");
}


static int _scale = 100;
static const GsString ONE("1");
static const GsString ZERO("0");
static const GsString TEN("10");
static GsString LeftOfDot(GsString &value)
{
    std::size_t dot = value.find('.');
    if (dot != GsString::npos)
    {
        if (dot == 0)
            return GsString("0");
        if (dot == 1 && value[0] == '-')
            return GsString("-0");
        else
            return value;
    }
}

GsString trimTrailingZeros(GsString input)
{
    if (input.find(".") != GsString::npos)
    {
        GsString result = "";
        std::size_t i;
        GsString inp(input.rbegin(), input.rend());
        result = inp.erase(0, std::min(inp.find_first_not_of('0'), inp.size() - 1));
        if (result.at(0) == '.')
        {
            result = result.erase(0, 1);
        }
        return GsString(result.rbegin(), result.rend());
    }
    else
    {
        return input;
    }
}

static int parse_number(const GsString &s, int &lsign, int &lint, int &ldot, int &lfrac, int &lscale)
{
    int i = 0;
    lsign = 1;
    if (s[i] == '-' || s[i] == '+')
    {
        if (s[i] == '-')
        {
            lsign = -1;
        }
        i++;
    }
    int len = s.length();
    if (i >= len)
    {
        return -1;
    }
    lint = i;

    while (i < len && '0' <= s[i] && s[i] <= '9')
    {
        i++;
    }
    ldot = i;

    lscale = 0;
    if (i < len && s[i] == '.')
    {
        lscale = (int) s.length() - i - 1;
        i++;
    }
    lfrac = i;

    while (i < len && '0' <= s[i] && s[i] <= '9')
    {
        i++;
    }

    if (i < len)
    {
        return -1;
    }

    while (s[lint] == '0' && lint + 1 < ldot)
    {
        lint++;
    }
    if (lscale == 0 && lfrac > ldot)
    {
        lfrac--;
        assert(lfrac == ldot);
    }

    if (lsign < 0 && (lscale == 0 && s[lint] == '0'))
    {
        lsign = 1;
    }
    return lscale;
}

static GsString _zero(int scale)
{
    if (scale == 0)
    {
        return ZERO;
    }
    GsString result(scale + 2, '0');
    result[1] = '.';
    return result;
}

static int _compareTo(const char *lhs, int lint, int ldot, int lfrac, int lscale, const char *rhs,
                      int rint, int rdot, int rfrac, int rscale, int scale)
{
    int llen = ldot - lint;
    int rlen = rdot - rint;

    if (llen != rlen)
    {
        return (llen < rlen ? -1 : 1);
    }

    for (int i = 0; i < llen; i++)
    {
        if (lhs[lint + i] != rhs[rint + i])
        {
            return (lhs[lint + i] < rhs[rint + i] ? -1 : 1);
        }
    }

    int i;
    for (i = 0; (i < lscale || i < rscale) && i < scale; i++)
    {
        int lchar = (i < lscale ? lhs[lfrac + i] : '0');
        int rchar = (i < rscale ? rhs[rfrac + i] : '0');
        if (lchar != rchar)
        {
            return (lchar < rchar ? -1 : 1);
        }
    }

    return 0;
}

static GsString _round(char *lhs, int lint, int ldot, int lfrac, int lscale, int scale, int sign,
                       bool add_trailing_zeroes, bool round_last = false)
{
    while (lhs[lint] == '0' && lint + 1 < ldot)
    {
        lint++;
    }

    assert(lint > 0 && lscale >= 0 && scale >= 0);

    if (sign < 0 && lhs[lint] == '0')
    {
        sign = 1;
        for (int i = 0; i < lscale; i++)
        {
            if (lhs[lfrac + i] != '0')
            {
                sign = -1;
                break;
            }
        }
    }

    if (round_last)
    {
        if (lscale > scale)
        {
            while (scale > 0 && lhs[lfrac + scale - 1] == '9' && lhs[lfrac + scale] >= '5')
            {
                scale--;
            }
            lscale = scale;
            if (lhs[lfrac + scale] >= '5')
            {
                if (scale > 0)
                {
                    lhs[lfrac + scale - 1]++;
                }
                else
                {
                    lfrac--;
                    assert(lfrac == ldot);

                    int i;
                    lhs[lint - 1] = '0';
                    for (i = 0; lhs[ldot - i - 1] == '9'; i++)
                    {
                        lhs[ldot - i - 1] = '0';
                    }
                    lhs[ldot - i - 1]++;
                    if (ldot - i - 1 < lint)
                    {
                        lint = ldot - i - 1;
                    }
                }
            }
        }

        while (lscale > 0 && lhs[lfrac + lscale - 1] == '0')
        {
            lscale--;
        }
    }
    else
    {
        if (lscale > scale)
        {
            lscale = scale;
        }
    }

    if (lscale == 0 && lfrac > ldot)
    {
        lfrac--;
        assert(lfrac == ldot);
    }

    if (sign < 0)
    {
        lhs[--lint] = '-';
    }

    if (lscale == scale || !add_trailing_zeroes)
    {
        return GsString(GsString(lhs + lint).substr(0, lfrac + lscale - lint));
    }
    else
    {
        GsString result(GsString(lhs + lint).substr(0, lfrac + lscale - lint));
        if (lscale == 0)
        {
            result += '.';
        }
        for (int kI = 0; kI < scale - lscale; ++kI) result += '0';
        return result;
    }
}

static GsString add_positive(const char *lhs, int lint, int ldot, int lfrac, int lscale, const char *rhs,
                             int rint, int rdot, int rfrac, int rscale, int scale, int sign)
{
    int llen = ldot - lint;
    int rlen = rdot - rint;

    int resint, resdot, resfrac, resscale;

    int result_len = std::max(llen, rlen) + 1;
    int result_scale = std::max(lscale, rscale);
    int result_size = result_len + result_scale + 3;
    GsString result(result_size, '0');

    int i, um = 0;
    int cur_pos = result_size;
    int was_frac = 0;
    for (i = result_scale - 1; i >= 0; i--)
    {
        if (i < lscale)
        {
            um += lhs[lfrac + i] - '0';
        }
        if (i < rscale)
        {
            um += rhs[rfrac + i] - '0';
        }

        if (um != 0 || was_frac)
        {
            result[--cur_pos] = (char) (um % 10 + '0');
            um /= 10;
            was_frac = 1;
        }
    }
    resscale = result_size - cur_pos;
    resfrac = cur_pos;
    if (was_frac)
    {
        result[--cur_pos] = '.';
    }
    resdot = cur_pos;

    for (int i = 0; i < result_len; i++)
    {
        if (i < llen)
        {
            um += lhs[ldot - i - 1] - '0';
        }
        if (i < rlen)
        {
            um += rhs[rdot - i - 1] - '0';
        }

        result[--cur_pos] = (char) (um % 10 + '0');
        um /= 10;
    }
    resint = cur_pos;
    assert(cur_pos > 0);

    return _round((char *) result.data(), resint, resdot, resfrac, resscale, scale, sign, 1);
}

static GsString subtract_positive(const char *lhs, int lint, int ldot, int lfrac, int lscale,
                                  const char *rhs, int rint, int rdot, int rfrac, int rscale, int scale,
                                  int sign)
{
    int llen = ldot - lint;
    int rlen = rdot - rint;

    int resint, resdot, resfrac, resscale;

    int result_len = llen;
    int result_scale = std::max(lscale, rscale);
    int result_size = result_len + result_scale + 3;
    GsString result(result_size, '0');

    int i, um = 0, next_um = 0;
    int cur_pos = result_size;
    int was_frac = 0;
    for (i = result_scale - 1; i >= 0; i--)
    {
        um = next_um;
        if (i < lscale)
        {
            um += lhs[lfrac + i] - '0';
        }
        if (i < rscale)
        {
            um -= rhs[rfrac + i] - '0';
        }
        if (um < 0)
        {
            next_um = -1;
            um += 10;
        }
        else
        {
            next_um = 0;
        }

        if (um != 0 || was_frac)
        {
            result[--cur_pos] = (char) (um + '0');
            was_frac = 1;
        }
    }
    resscale = result_size - cur_pos;
    resfrac = cur_pos;
    if (was_frac)
    {
        result[--cur_pos] = '.';
    }
    resdot = cur_pos;

    for (int i = 0; i < result_len; i++)
    {
        um = next_um;
        um += lhs[ldot - i - 1] - '0';
        if (i < rlen)
        {
            um -= rhs[rdot - i - 1] - '0';
        }
        if (um < 0)
        {
            next_um = -1;
            um += 10;
        }
        else
        {
            next_um = 0;
        }

        result[--cur_pos] = (char) (um + '0');
    }
    resint = cur_pos;
    assert(cur_pos > 0);

    return _round((char *) result.data(), resint, resdot, resfrac, resscale, scale, sign, 1);
}

static GsString multiply_positive(const char *lhs, int lint, int ldot, int lfrac, int lscale,
                                  const char *rhs, int rint, int rdot, int rfrac, int rscale, int scale,
                                  int sign)
{
    int llen = ldot - lint;
    int rlen = rdot - rint;

    int resint, resdot, resfrac, resscale;

    int result_len = llen + rlen;
    int result_scale = lscale + rscale;
    int result_size = result_len + result_scale + 3;
    GsString result(result_size, '0');

    int *res = (int *) malloc(sizeof(int) * result_size);
    memset(res, 0, sizeof(int) * result_size);
    for (int i = -lscale; i < llen; i++)
    {
        int x = (i < 0 ? lhs[lfrac - i - 1] : lhs[ldot - i - 1]) - '0';
        for (int j = -rscale; j < rlen; j++)
        {
            int y = (j < 0 ? rhs[rfrac - j - 1] : rhs[rdot - j - 1]) - '0';
            res[i + j + result_scale] += x * y;
        }
    }
    for (int i = 0; i + 1 < result_size; i++)
    {
        res[i + 1] += res[i] / 10;
        res[i] %= 10;
    }

    int cur_pos = result_size;
    for (int i = 0; i < result_scale; i++)
    {
        result[--cur_pos] = (char) (res[i] + '0');
    }
    resscale = result_size - cur_pos;
    resfrac = cur_pos;
    if (result_scale > 0)
    {
        result[--cur_pos] = '.';
    }
    resdot = cur_pos;

    for (int i = result_scale; i < result_len + result_scale; i++)
    {
        result[--cur_pos] = (char) (res[i] + '0');
    }
    resint = cur_pos;
    assert(cur_pos > 0);

    free(res);

    char *data = (char *) malloc((result.length() + 1) * sizeof(char));
    sprintf(data, result.c_str());
    GsString ret = _round(data, resint, resdot, resfrac, resscale, scale, sign, 0);
    free(data);

    return ret;
}

static GsString divide_positive(const char *lhs, int lint, int ldot, int lfrac, int lscale,
                                const char *rhs, int rint, int rdot, int rfrac, int rscale, int scale,
                                int sign)
{
    int llen = ldot - lint;
    int rlen = rdot - rint;

    int resint, resdot = -1, resfrac = -1, resscale;

    int result_len = std::max(llen + rscale - rlen + 1, 1);
    int result_scale = scale;
    int result_size = result_len + result_scale + 3;

    if (rscale == 0 && rhs[rint] == '0')
    {
        std::cerr << ("Division By ZERO") << std::endl
                  << std::endl;
        return ZERO;
    }

    int dividend_len = llen + lscale;
    int divider_len = rlen + rscale;
    int *dividend = (int *) malloc(sizeof(int) * (result_size + dividend_len + divider_len));
    int *divider = (int *) malloc(sizeof(int) * divider_len);
    memset(dividend, 0, sizeof(int) * (result_size + dividend_len + divider_len));
    memset(divider, 0, sizeof(int) * divider_len);

    for (int i = -lscale; i < llen; i++)
    {
        int x = (i < 0 ? lhs[lfrac - i - 1] : lhs[ldot - i - 1]) - '0';
        dividend[llen - i - 1] = x;
    }

    for (int i = -rscale; i < rlen; i++)
    {
        int x = (i < 0 ? rhs[rfrac - i - 1] : rhs[rdot - i - 1]) - '0';
        divider[rlen - i - 1] = x;
    }

    int divider_skip = 0;
    while (divider_len > 0 && divider[0] == 0)
    {
        divider++;
        divider_skip++;
        divider_len--;
    }
    assert(divider_len > 0);

    int cur_pow = llen - rlen + divider_skip;
    int cur_pos = 2;

    if (cur_pow < -scale)
    {
        divider -= divider_skip;
        divider_len += divider_skip;
        free(dividend);
        free(divider);
        return _zero(scale);
    }

    GsString result(result_size, '0');
    resint = cur_pos;
    if (cur_pow < 0)
    {
        result[cur_pos++] = '0';
        resdot = cur_pos;
        result[cur_pos++] = '.';
        resfrac = cur_pos;
        for (int i = -1; i > cur_pow; i--)
        {
            result[cur_pos++] = '0';
        }
    }

    int beg = 0, real_beg = 0;
    while (cur_pow >= -scale)
    {
        char dig = '0';
        while (true)
        {
            if (real_beg < beg && dividend[real_beg] == 0)
            {
                real_beg++;
            }

            bool less = false;
            if (real_beg == beg)
            {
                for (int i = 0; i < divider_len; i++)
                {
                    if (dividend[beg + i] != divider[i])
                    {
                        less = (dividend[beg + i] < divider[i]);
                        break;
                    }
                }
            }
            if (less)
            {
                break;
            }

            for (int i = divider_len - 1; i >= 0; i--)
            {
                dividend[beg + i] -= divider[i];
                if (dividend[beg + i] < 0)
                {
                    dividend[beg + i] += 10;
                    dividend[beg + i - 1]--;
                }
            }
            dig++;
        }

        result[cur_pos++] = dig;

        if (cur_pow == 0)
        {
            resdot = cur_pos;
            if (scale > 0)
            {
                result[cur_pos++] = '.';
            }
            resfrac = cur_pos;
        }
        cur_pow--;
        beg++;
    }
    resscale = cur_pos - resfrac;

    divider -= divider_skip;
    divider_len += divider_skip;
    free(dividend);
    free(divider);

    char *data = (char *) malloc((result.length() + 1) * sizeof(char));
    sprintf(data, result.c_str());
    GsString ret = _round(data, resint, resdot, resfrac, resscale, scale, sign, 0);
    free(data);

    return ret;
}


static GsString _add(const char *lhs, int lsign, int lint, int ldot, int lfrac, int lscale,
                     const char *rhs, int rsign, int rint, int rdot, int rfrac, int rscale, int scale)
{
    if (lsign > 0 && rsign > 0)
    {
        return add_positive(lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot, rfrac, rscale, scale, 1);
    }

    if (lsign > 0 && rsign < 0)
    {
        if (_compareTo(lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot, rfrac, rscale, 1000000000) >= 0)
        {
            return subtract_positive(lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot, rfrac, rscale,
                                     scale, 1);
        }
        else
        {
            return subtract_positive(rhs, rint, rdot, rfrac, rscale, lhs, lint, ldot, lfrac, lscale,
                                     scale, -1);
        }
    }

    if (lsign < 0 && rsign > 0)
    {
        if (_compareTo(lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot, rfrac, rscale, 1000000000) <= 0)
        {
            return subtract_positive(rhs, rint, rdot, rfrac, rscale, lhs, lint, ldot, lfrac, lscale,
                                     scale, 1);
        }
        else
        {
            return subtract_positive(lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot, rfrac, rscale,
                                     scale, -1);
        }
    }

    if (lsign < 0 && rsign < 0)
    {
        return add_positive(lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot, rfrac, rscale, scale, -1);
    }

    assert(0);
    return ZERO;
}

template<typename T>
GsString to_string(const T &t)
{
    GsStringStream ss;
    ss << t;
    return ss.Str();
}

GsString fact(GsString a)
{
    GsString i("1");
    GsString fact("1");
    while (GsBigDecimal::CompareTo(i, a) <= 0)
    {
        fact = GsBigDecimal::Multiply(fact, to_string(i));
        i = GsBigDecimal::Add(i, ONE);
    }
    return fact;
}


void GsBigDecimal::Scale(int scale)
{
    if (scale < 0)
        _scale = 0;
    else
        _scale = scale;
}

GsString GsBigDecimal::Divide(const GsString &lhs, const GsString &rhs, int scale)
{
    if (scale == INT_MIN)
    {
        scale = _scale;
    }
    if (scale < 0)
    {
        std::cerr << "Scale (" << to_string(scale).c_str() << ") Cant Be Negative!!!" << std::endl;
        scale = 0;
    }
    if (lhs.empty())
    {
        return _zero(scale);
    }
    if (rhs.empty())
    {
        std::cerr << "Division By Empty " << rhs.c_str() << std::endl;
        return _zero(scale);
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number(lhs, lsign, lint, ldot, lfrac, lscale) < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Is Not A Number" << std::endl;
        return ZERO;
    }

    int rsign, rint, rdot, rfrac, rscale;
    if (parse_number(rhs, rsign, rint, rdot, rfrac, rscale) < 0)
    {
        std::cerr << "\"" << rhs.c_str() << "\" Is Not A Number" << std::endl;
        return ZERO;
    }

    return trimTrailingZeros(divide_positive(lhs.c_str(), lint, ldot, lfrac, lscale, rhs.c_str(), rint,
                                             rdot, rfrac, rscale, scale, lsign * rsign));
}

GsString GsBigDecimal::Modulus(const GsString &lhs, const GsString &rhs, int scale)
{
    if (lhs.empty())
    {
        return ZERO;
    }
    if (rhs.empty())
    {
        std::cerr << "Modulo By empty " << std::endl;
        return ZERO;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number(lhs, lsign, lint, ldot, lfrac, lscale) != 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Is Not A Integer" << std::endl;
        return ZERO;
    }

    int rsign, rint, rdot, rfrac, rscale;
    if (parse_number(rhs, rsign, rint, rdot, rfrac, rscale) != 0)
    {
        std::cerr << "\"" << rhs.c_str() << "\" Is Not A Number" << std::endl;
        return ZERO;
    }

    long long mod = 0;
    for (int i = rint; i < rdot; i++)
    {
        mod = mod * 10 + rhs[i] - '0';
    }

    if (rdot - rint > 18 || mod == 0)
    {
        std::cerr << "\"" << rhs.c_str()
                  << "\" Is Not A Non Zero Integer Less Than 1e18 By Absolute Value" << std::endl;
        return ZERO;
    }

    long long res = 0;
    for (int i = lint; i < ldot; i++)
    {
        res = res * 2;
        if (res >= mod)
        {
            res -= mod;
        }
        res = res * 5 + lhs[i] - '0';
        while (res >= mod)
        {
            res -= mod;
        }
    }

    char buffer[20];
    int cur_pos = 20;
    do
    {
        buffer[--cur_pos] = (char) (res % 10 + '0');
        res /= 10;
    } while (res > 0);

    if (lsign < 0)
    {
        buffer[--cur_pos] = '-';
    }

    return GsString(trimTrailingZeros(GsString(buffer + cur_pos).substr(0, 20 - cur_pos)));
}

GsString GsBigDecimal::Pow(const GsString &lhs, const GsString &rhs, int scale)
{
    if (lhs.empty())
    {
        return ZERO;
    }
    if (rhs.empty())
    {
        return ONE;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number(lhs, lsign, lint, ldot, lfrac, lscale) != 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Is Not A Number" << std::endl;
        return ZERO;
    }

    int rsign, rint, rdot, rfrac, rscale;
    if (parse_number(rhs, rsign, rint, rdot, rfrac, rscale) != 0)
    {
        std::cerr << "\"" << rhs.c_str() << "\" Is Not A Number" << std::endl;
        return ZERO;
    }

    long long deg = 0;
    for (int i = rint; i < rdot; i++)
    {
        deg = deg * 10 + rhs[i] - '0';
    }

    if (rdot - rint > 18 || (rsign < 0 && deg != 0))
    {
        std::cerr << "\"" << rhs.c_str() << "\" Is Not A Non Negative Integer Less Than 1e18"
                  << std::endl;
        return ZERO;
    }

    if (deg == 0)
    {
        return ONE;
    }

    GsString result = ONE;
    GsString mul = lhs;
    while (deg > 0)
    {
        if (deg & 1)
        {
            result = Multiply(result, mul, 0);
        }
        mul = Multiply(mul, mul, 0);
        deg >>= 1;
    }

    return trimTrailingZeros(result);
}

GsString GsBigDecimal::Add(const GsString &lhs, const GsString &rhs, int scale)
{
    if (lhs.empty())
    {
        return Add(ZERO, rhs, scale);
    }
    if (rhs.empty())
    {
        return Add(lhs, ZERO, scale);
    }

    if (scale < 0)
    {
        std::cerr << "Scale (" << to_string(scale).c_str() << ") Cant Be Negative!!!" << std::endl;
        scale = 0;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number(lhs, lsign, lint, ldot, lfrac, lscale) < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Is Not A Number" << std::endl;
        return _zero(scale);
    }

    int rsign, rint, rdot, rfrac, rscale;
    if (parse_number(rhs, rsign, rint, rdot, rfrac, rscale) < 0)
    {
        std::cerr << "\"" << rhs.c_str() << "\" Is Not A Number" << std::endl;
        return _zero(scale);
    }

    return trimTrailingZeros(_add(lhs.c_str(), lsign, lint, ldot, lfrac, lscale, rhs.c_str(), rsign,
                                  rint, rdot, rfrac, rscale, std::max(lscale, rscale)));
}

GsString GsBigDecimal::Subtract(const GsString &lhs, const GsString &rhs, int scale)
{
    if (lhs.empty())
    {
        return Subtract(ZERO, rhs, scale);
    }
    if (rhs.empty())
    {
        return Subtract(lhs, ZERO, scale);
    }

    if (scale < 0)
    {
        std::cerr << "Scale (" << to_string(scale).c_str() << ") Cant Be Negative!!!" << std::endl;
        scale = 0;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number(lhs, lsign, lint, ldot, lfrac, lscale) < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Is Not A Number" << std::endl;
        return _zero(scale);
    }

    int rsign, rint, rdot, rfrac, rscale;
    if (parse_number(rhs, rsign, rint, rdot, rfrac, rscale) < 0)
    {
        std::cerr << "\"" << rhs.c_str() << "\" Is Not A Number" << std::endl;
        return _zero(scale);
    }

    rsign *= -1;

    return trimTrailingZeros(_add(lhs.c_str(), lsign, lint, ldot, lfrac, lscale, rhs.c_str(), rsign,
                                  rint, rdot, rfrac, rscale, std::max(lscale, rscale)));
}

GsString GsBigDecimal::Multiply(const GsString &lhs, const GsString &rhs, int scale)
{
    if (lhs.empty())
    {
        return Multiply(ZERO, rhs, scale);
    }
    if (rhs.empty())
    {
        return Multiply(lhs, ZERO, scale);
    }

    if (scale < 0)
    {
        std::cerr << "Scale (" << to_string(scale).c_str() << ") Cant Be Negative!!!" << std::endl;
        scale = 0;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number(lhs, lsign, lint, ldot, lfrac, lscale) < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Is Not A Number" << std::endl;
        return ZERO;
    }

    int rsign, rint, rdot, rfrac, rscale;
    if (parse_number(rhs, rsign, rint, rdot, rfrac, rscale) < 0)
    {
        std::cerr << "\"" << rhs.c_str() << "\" Is Not A Number" << std::endl;
        return ZERO;
    }

    return trimTrailingZeros(multiply_positive(lhs.c_str(), lint, ldot, lfrac, lscale, rhs.c_str(), rint,
                                               rdot, rfrac, rscale, lscale + rscale, lsign * rsign));
}

GsString GsBigDecimal::Round(const GsString &lhs, int scale)
{
    if (lhs.empty())
    {
        return GsBigDecimal::Round(ZERO, scale);
    }

    if (scale == INT_MIN)
    {
        scale = _scale;
    }

    if (scale < 0)
    {
        std::cerr << "Scale (" << to_string(scale).c_str() << ") Cant Be Negative!!!" << std::endl;
        scale = 0;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number(lhs, lsign, lint, ldot, lfrac, lscale) < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Is Not A Number" << std::endl;
        return 0;
    }

    int len = lhs.size();
    GsString result(len + 1, '0');
    for (int i = len - 1; i >= lint; --i)
    {
        result[i + 1] = lhs[i];
    }

    char *data = (char *) malloc((result.length() + 1) * sizeof(char));
    sprintf(data, result.c_str());
    GsString ret = _round(data, lint + 1, ldot + 1, lfrac + 1, lscale, scale, lsign, 1, 1);
    free(data);
    return ret;
}

int GsBigDecimal::CompareTo(const GsString &lhs, const GsString &rhs, int scale)
{
    if (lhs.empty())
    {
        return GsBigDecimal::CompareTo(ZERO, rhs, scale);
    }
    if (rhs.empty())
    {
        return GsBigDecimal::CompareTo(lhs, ZERO, scale);
    }

    if (scale == INT_MIN)
    {
        scale = _scale;
    }
    if (scale < 0)
    {
        std::cerr << "Scale (" << to_string(scale).c_str() << ") Cant Be Negative!!!" << std::endl;
        scale = 0;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number(lhs, lsign, lint, ldot, lfrac, lscale) < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Is Not A Number" << std::endl;
        return 0;
    }

    int rsign, rint, rdot, rfrac, rscale;
    if (parse_number(rhs, rsign, rint, rdot, rfrac, rscale) < 0)
    {
        std::cerr << "\"" << rhs.c_str() << "\" Is Not A Number" << std::endl;
        return 0;
    }

    if (lsign != rsign)
    {
        return (lsign - rsign) / 2;
    }

    return (1 - 2 * (lsign < 0)) * _compareTo(lhs.c_str(), lint, ldot, lfrac, lscale, rhs.c_str(), rint,
                                              rdot, rfrac, rscale, scale);
}

GsString GsBigDecimal::Log2(const GsString &lhs, int scale)
{
    if (lhs.empty())
    {
        return GsBigDecimal::Round(ZERO, scale);
    }

    if (scale == INT_MIN)
    {
        scale = _scale;
    }
    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number(lhs, lsign, lint, ldot, lfrac, lscale) < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Is Not A Number" << std::endl;
        return "0";
    }
    if (lsign < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Cannot Be A Negative Number" << std::endl;
        return "0";
    }
    return (GsBigDecimal::CompareTo(lhs, ONE) > 0)
                   ? GsString(GsBigDecimal::Add(ONE, GsBigDecimal::Log(GsBigDecimal::Divide(lhs, TEN))))
                   : ZERO;
}

GsString GsBigDecimal::Ln(const GsString &lhs, int scale)
{
    return GsString();
}

GsString GsBigDecimal::Log(const GsString &lhs, int scale)
{
    if (lhs.empty())
    {
        return GsBigDecimal::Round(ZERO, scale);
    }

    if (scale == INT_MIN)
    {
        scale = _scale;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number(lhs, lsign, lint, ldot, lfrac, lscale) < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Is Not A Number" << std::endl;
        return _zero(scale);
    }
    if (lsign < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Cannot Be A Negative Number" << std::endl;
        return _zero(scale);
    }
    return GsString(
            GsBigDecimal::Divide(GsBigDecimal::Ln(lhs, 0), GsBigDecimal::Ln(to_string("10"), 0), 0));
}


GsString GsBigDecimal::Sin(const GsString &lhs, int scale)
{
    GsString sum("0"), n, d, t, i("0"), j("0");
    while (GsBigDecimal::CompareTo(i, lhs) <= 0)
    {
        if (GsBigDecimal::Modulus(i, "2") != "0")
        {
            j = GsBigDecimal::Add(j, ONE);
            n = GsBigDecimal::Pow(lhs, i);
            d = fact(i);
            t = GsBigDecimal::Divide(n, d);
            if (GsBigDecimal::Modulus(j, "2") != "0")
            {
                sum = GsBigDecimal::Subtract(sum, t);
            }
            else
            {
                sum = GsBigDecimal::Add(sum, t);
            }
        }
        i = GsBigDecimal::Add(i, ONE);
    }
    return sum;
}

GsString GsBigDecimal::StringToHex(GsString &lhs, int caps)
{
    long int i = 1;
    int temp;
    lhs = LeftOfDot(lhs);
    GsString quotient = lhs, hexoutput("");
    temp = atoi(Modulus(quotient, to_string("16"), 0).c_str());
    std::cout << temp;
    return hexoutput;
}


}// namespace m2
