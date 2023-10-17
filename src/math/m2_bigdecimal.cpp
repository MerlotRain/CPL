#include <iostream>
#include <m2_bigdecimal.h>
#include <stdio.h>
#include <stdlib.h>

namespace m2 {


/*******************************************************************************
 * static functions
 *******************************************************************************/
static int _scale = 100;
static const String ONE("1");
static const String ZERO("0");
static const String TEN("10");

/**
 * @brief 
 * @param  a                
 * @return String 
 */
static String fact(String a)
{
    String i("1");
    String fact("1");
    while (BigDecimal::compareTo(i, a) <= 0)
    {
        fact = BigDecimal::multiply(fact, String::toString(i));
        i = BigDecimal::add(i, ONE);
    }
    return fact;
}

/**
 * @brief 
 * @param  value            
 * @return String 
 */
static String LeftOfDot(String &value)
{
    std::size_t dot = value.find('.');
    if (dot != String::npos)
    {
        if (dot == 0) return String("0");
        if (dot == 1 && value[0] == '-') return String("-0");
        else
            return value;
    }
}

/**
 * @brief 
 * @param  input            
 * @return String 
 */
String trimTrailingZeros(String input)
{
    if (input.find(".") != String::npos)
    {
        String result = "";
        std::size_t i;
        String inp(input.rbegin(), input.rend());
        result = inp.erase(
                0, std::min(inp.find_first_not_of('0'), inp.size() - 1));
        if (result.at(0) == '.') { result = result.erase(0, 1); }
        return String(result.rbegin(), result.rend());
    }
    else { return input; }
}

/**
 * @brief 
 * @param  s                
 * @param  lsign            
 * @param  lint             
 * @param  ldot             
 * @param  lfrac            
 * @param  lscale           
 * @return int 
 */
static int parse_number(const String &s, int &lsign, int &lint, int &ldot,
                        int &lfrac, int &lscale)
{
    int i = 0;
    lsign = 1;
    if (s[i] == '-' || s[i] == '+')
    {
        if (s[i] == '-') { lsign = -1; }
        i++;
    }
    int len = s.length();
    if (i >= len) { return -1; }
    lint = i;

    while (i < len && '0' <= s[i] && s[i] <= '9') { i++; }
    ldot = i;

    lscale = 0;
    if (i < len && s[i] == '.')
    {
        lscale = (int) s.length() - i - 1;
        i++;
    }
    lfrac = i;

    while (i < len && '0' <= s[i] && s[i] <= '9') { i++; }

    if (i < len) { return -1; }

    while (s[lint] == '0' && lint + 1 < ldot) { lint++; }
    if (lscale == 0 && lfrac > ldot)
    {
        lfrac--;
        assert(lfrac == ldot);
    }

    if (lsign < 0 && (lscale == 0 && s[lint] == '0')) { lsign = 1; }
    return lscale;
}

/**
 * @brief 
 * @param  scale            
 * @return String 
 */
static String _zero(int scale)
{
    if (scale == 0) { return ZERO; }
    String result(scale + 2, '0');
    result[1] = '.';
    return result;
}

/**
 * @brief 
 * @param  lhs              
 * @param  lint             
 * @param  ldot             
 * @param  lfrac            
 * @param  lscale           
 * @param  rhs              
 * @param  rint             
 * @param  rdot             
 * @param  rfrac            
 * @param  rscale           
 * @param  scale            
 * @return int 
 */
static int _compareTo(const char *lhs, int lint, int ldot, int lfrac,
                      int lscale, const char *rhs, int rint, int rdot,
                      int rfrac, int rscale, int scale)
{
    int llen = ldot - lint;
    int rlen = rdot - rint;

    if (llen != rlen) { return (llen < rlen ? -1 : 1); }

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
        if (lchar != rchar) { return (lchar < rchar ? -1 : 1); }
    }

    return 0;
}

/**
 * @brief 
 * @param  lhs              
 * @param  lint             
 * @param  ldot             
 * @param  lfrac            
 * @param  lscale           
 * @param  scale            
 * @param  sign             
 * @param  add_trailing_zeroes
 * @param  round_last       
 * @return String 
 */
static String _round(char *lhs, int lint, int ldot, int lfrac, int lscale,
                     int scale, int sign, bool add_trailing_zeroes,
                     bool round_last = false)
{
    while (lhs[lint] == '0' && lint + 1 < ldot) { lint++; }

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
            while (scale > 0 && lhs[lfrac + scale - 1] == '9' &&
                   lhs[lfrac + scale] >= '5')
            {
                scale--;
            }
            lscale = scale;
            if (lhs[lfrac + scale] >= '5')
            {
                if (scale > 0) { lhs[lfrac + scale - 1]++; }
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
                    if (ldot - i - 1 < lint) { lint = ldot - i - 1; }
                }
            }
        }

        while (lscale > 0 && lhs[lfrac + lscale - 1] == '0') { lscale--; }
    }
    else
    {
        if (lscale > scale) { lscale = scale; }
    }

    if (lscale == 0 && lfrac > ldot)
    {
        lfrac--;
        assert(lfrac == ldot);
    }

    if (sign < 0) { lhs[--lint] = '-'; }

    if (lscale == scale || !add_trailing_zeroes)
    {
        return String(String(lhs + lint).substr(0, lfrac + lscale - lint));
    }
    else
    {
        String result(String(lhs + lint).substr(0, lfrac + lscale - lint));
        if (lscale == 0) { result += '.'; }
        for (int kI = 0; kI < scale - lscale; ++kI) result += '0';
        return result;
    }
}

/**
 * @brief 
 * @param  lhs              
 * @param  lint             
 * @param  ldot             
 * @param  lfrac            
 * @param  lscale           
 * @param  rhs              
 * @param  rint             
 * @param  rdot             
 * @param  rfrac            
 * @param  rscale           
 * @param  scale            
 * @param  sign             
 * @return String 
 */
static String add_positive(const char *lhs, int lint, int ldot, int lfrac,
                           int lscale, const char *rhs, int rint, int rdot,
                           int rfrac, int rscale, int scale, int sign)
{
    int llen = ldot - lint;
    int rlen = rdot - rint;

    int resint, resdot, resfrac, resscale;

    int result_len = std::max(llen, rlen) + 1;
    int result_scale = std::max(lscale, rscale);
    int result_size = result_len + result_scale + 3;
    String result(result_size, '0');

    int i, um = 0;
    int cur_pos = result_size;
    int was_frac = 0;
    for (i = result_scale - 1; i >= 0; i--)
    {
        if (i < lscale) { um += lhs[lfrac + i] - '0'; }
        if (i < rscale) { um += rhs[rfrac + i] - '0'; }

        if (um != 0 || was_frac)
        {
            result[--cur_pos] = (char) (um % 10 + '0');
            um /= 10;
            was_frac = 1;
        }
    }
    resscale = result_size - cur_pos;
    resfrac = cur_pos;
    if (was_frac) { result[--cur_pos] = '.'; }
    resdot = cur_pos;

    for (int i = 0; i < result_len; i++)
    {
        if (i < llen) { um += lhs[ldot - i - 1] - '0'; }
        if (i < rlen) { um += rhs[rdot - i - 1] - '0'; }

        result[--cur_pos] = (char) (um % 10 + '0');
        um /= 10;
    }
    resint = cur_pos;
    assert(cur_pos > 0);

    return _round((char *) result.data(), resint, resdot, resfrac, resscale,
                  scale, sign, 1);
}

/**
 * @brief 
 * @param  lhs              
 * @param  lint             
 * @param  ldot             
 * @param  lfrac            
 * @param  lscale           
 * @param  rhs              
 * @param  rint             
 * @param  rdot             
 * @param  rfrac            
 * @param  rscale           
 * @param  scale            
 * @param  sign             
 * @return String 
 */
static String subtract_positive(const char *lhs, int lint, int ldot, int lfrac,
                                int lscale, const char *rhs, int rint, int rdot,
                                int rfrac, int rscale, int scale, int sign)
{
    int llen = ldot - lint;
    int rlen = rdot - rint;

    int resint, resdot, resfrac, resscale;

    int result_len = llen;
    int result_scale = std::max(lscale, rscale);
    int result_size = result_len + result_scale + 3;
    String result(result_size, '0');

    int i, um = 0, next_um = 0;
    int cur_pos = result_size;
    int was_frac = 0;
    for (i = result_scale - 1; i >= 0; i--)
    {
        um = next_um;
        if (i < lscale) { um += lhs[lfrac + i] - '0'; }
        if (i < rscale) { um -= rhs[rfrac + i] - '0'; }
        if (um < 0)
        {
            next_um = -1;
            um += 10;
        }
        else { next_um = 0; }

        if (um != 0 || was_frac)
        {
            result[--cur_pos] = (char) (um + '0');
            was_frac = 1;
        }
    }
    resscale = result_size - cur_pos;
    resfrac = cur_pos;
    if (was_frac) { result[--cur_pos] = '.'; }
    resdot = cur_pos;

    for (int i = 0; i < result_len; i++)
    {
        um = next_um;
        um += lhs[ldot - i - 1] - '0';
        if (i < rlen) { um -= rhs[rdot - i - 1] - '0'; }
        if (um < 0)
        {
            next_um = -1;
            um += 10;
        }
        else { next_um = 0; }

        result[--cur_pos] = (char) (um + '0');
    }
    resint = cur_pos;
    assert(cur_pos > 0);

    return _round((char *) result.data(), resint, resdot, resfrac, resscale,
                  scale, sign, 1);
}

/**
 * @brief 
 * @param  lhs              
 * @param  lint             
 * @param  ldot             
 * @param  lfrac            
 * @param  lscale           
 * @param  rhs              
 * @param  rint             
 * @param  rdot             
 * @param  rfrac            
 * @param  rscale           
 * @param  scale            
 * @param  sign             
 * @return String 
 */
static String multiply_positive(const char *lhs, int lint, int ldot, int lfrac,
                                int lscale, const char *rhs, int rint, int rdot,
                                int rfrac, int rscale, int scale, int sign)
{
    int llen = ldot - lint;
    int rlen = rdot - rint;

    int resint, resdot, resfrac, resscale;

    int result_len = llen + rlen;
    int result_scale = lscale + rscale;
    int result_size = result_len + result_scale + 3;
    String result(result_size, '0');

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
    if (result_scale > 0) { result[--cur_pos] = '.'; }
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
    String ret =
            _round(data, resint, resdot, resfrac, resscale, scale, sign, 0);
    free(data);

    return ret;
}

/**
 * @brief 
 * @param  lhs              
 * @param  lint             
 * @param  ldot             
 * @param  lfrac            
 * @param  lscale           
 * @param  rhs              
 * @param  rint             
 * @param  rdot             
 * @param  rfrac            
 * @param  rscale           
 * @param  scale            
 * @param  sign             
 * @return String 
 */
static String divide_positive(const char *lhs, int lint, int ldot, int lfrac,
                              int lscale, const char *rhs, int rint, int rdot,
                              int rfrac, int rscale, int scale, int sign)
{
    int llen = ldot - lint;
    int rlen = rdot - rint;

    int resint, resdot = -1, resfrac = -1, resscale;

    int result_len = std::max(llen + rscale - rlen + 1, 1);
    int result_scale = scale;
    int result_size = result_len + result_scale + 3;

    if (rscale == 0 && rhs[rint] == '0')
    {
        std::cerr << ("Division By ZERO") << std::endl << std::endl;
        return ZERO;
    }

    int dividend_len = llen + lscale;
    int divider_len = rlen + rscale;
    int *dividend = (int *) malloc(sizeof(int) *
                                   (result_size + dividend_len + divider_len));
    int *divider = (int *) malloc(sizeof(int) * divider_len);
    memset(dividend, 0,
           sizeof(int) * (result_size + dividend_len + divider_len));
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

    String result(result_size, '0');
    resint = cur_pos;
    if (cur_pow < 0)
    {
        result[cur_pos++] = '0';
        resdot = cur_pos;
        result[cur_pos++] = '.';
        resfrac = cur_pos;
        for (int i = -1; i > cur_pow; i--) { result[cur_pos++] = '0'; }
    }

    int beg = 0, real_beg = 0;
    while (cur_pow >= -scale)
    {
        char dig = '0';
        while (true)
        {
            if (real_beg < beg && dividend[real_beg] == 0) { real_beg++; }

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
            if (less) { break; }

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
            if (scale > 0) { result[cur_pos++] = '.'; }
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
    String ret =
            _round(data, resint, resdot, resfrac, resscale, scale, sign, 0);
    free(data);

    return ret;
}

/**
 * @brief 
 * @param  lhs              
 * @param  lsign            
 * @param  lint             
 * @param  ldot             
 * @param  lfrac            
 * @param  lscale           
 * @param  rhs              
 * @param  rsign            
 * @param  rint             
 * @param  rdot             
 * @param  rfrac            
 * @param  rscale           
 * @param  scale            
 * @return String 
 */
static String _add(const char *lhs, int lsign, int lint, int ldot, int lfrac,
                   int lscale, const char *rhs, int rsign, int rint, int rdot,
                   int rfrac, int rscale, int scale)
{
    if (lsign > 0 && rsign > 0)
    {
        return add_positive(lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot,
                            rfrac, rscale, scale, 1);
    }

    if (lsign > 0 && rsign < 0)
    {
        if (_compareTo(lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot, rfrac,
                       rscale, 1000000000) >= 0)
        {
            return subtract_positive(lhs, lint, ldot, lfrac, lscale, rhs, rint,
                                     rdot, rfrac, rscale, scale, 1);
        }
        else
        {
            return subtract_positive(rhs, rint, rdot, rfrac, rscale, lhs, lint,
                                     ldot, lfrac, lscale, scale, -1);
        }
    }

    if (lsign < 0 && rsign > 0)
    {
        if (_compareTo(lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot, rfrac,
                       rscale, 1000000000) <= 0)
        {
            return subtract_positive(rhs, rint, rdot, rfrac, rscale, lhs, lint,
                                     ldot, lfrac, lscale, scale, 1);
        }
        else
        {
            return subtract_positive(lhs, lint, ldot, lfrac, lscale, rhs, rint,
                                     rdot, rfrac, rscale, scale, -1);
        }
    }

    if (lsign < 0 && rsign < 0)
    {
        return add_positive(lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot,
                            rfrac, rscale, scale, -1);
    }

    assert(0);
    return ZERO;
}


/*******************************************************************************
 * Class BigDecimal functions
 *******************************************************************************/

/**
 * @brief Construct a new Big Decimal:: Big Decimal object
 */
BigDecimal::BigDecimal() noexcept {}

/**
 * @brief Construct a new Big Decimal:: Big Decimal object
 * @param  v                
 */
BigDecimal::BigDecimal(const BigDecimal &v) noexcept : value(v.value) {}

/**
 * @brief Construct a new Big Decimal:: Big Decimal object
 * @param  v                
 */
BigDecimal::BigDecimal(const char *v) : value(v) {}

/**
 * @brief Construct a new Big Decimal:: Big Decimal object
 * @param  v                
 */
BigDecimal::BigDecimal(String v) : value(v) {}

/**
 * @brief Construct a new Big Decimal:: Big Decimal object
 * @param  v                
 */
BigDecimal::BigDecimal(int v) noexcept : value()
{
    std::stringstream ss;
    ss << v;
    value = ss.str();
}

/**
 * @brief Construct a new Big Decimal:: Big Decimal object
 * @param  v                
 */
BigDecimal::BigDecimal(long long v) noexcept : value()
{
    std::stringstream ss;
    ss << v;
    value = ss.str();
}

/**
 * @brief Construct a new Big Decimal:: Big Decimal object
 * @param  v                
 */
BigDecimal::BigDecimal(long long int v) noexcept : value()
{
    std::stringstream ss;
    ss << v;
    value = ss.str();
}

/**
 * @brief Construct a new Big Decimal:: Big Decimal object
 * @param  v                
 */
BigDecimal::BigDecimal(unsigned int v) noexcept : value()
{
    std::stringstream ss;
    ss << v;
    value = ss.str();
}

/**
 * @brief Construct a new Big Decimal:: Big Decimal object
 * @param  v                
 */
BigDecimal::BigDecimal(unsigned long long v) noexcept
{
    std::stringstream ss;
    ss << v;
    value = ss.str();
}

/**
 * @brief Construct a new Big Decimal:: Big Decimal object
 * @param  v                
 */
BigDecimal::BigDecimal(unsigned long long int v) noexcept : value()
{
    std::stringstream ss;
    ss << v;
    value = ss.str();
}

/**
 * @brief Construct a new Big Decimal:: Big Decimal object
 * @param  v                
 */
BigDecimal::BigDecimal(float v) noexcept : value()
{
    std::stringstream ss;
    ss << v;
    value = ss.str();
}

/**
 * @brief Construct a new Big Decimal:: Big Decimal object
 * @param  v                
 */
BigDecimal::BigDecimal(double v) noexcept : value()
{
    std::stringstream ss;
    ss << v;
    value = ss.str();
}

/**
 * @brief Construct a new Big Decimal:: Big Decimal object
 * @param  v                
 */
BigDecimal::BigDecimal(long double v) noexcept
{
    std::stringstream ss;
    ss << v;
    value = ss.str();
}

/**
 * @brief 
 * @param  rhs              
 * @return BigDecimal 
 */
BigDecimal BigDecimal::operator+(const BigDecimal &rhs)
{
    return BigDecimal::add(value, rhs.value);
}

/**
 * @brief 
 * @param  rhs              
 * @return BigDecimal 
 */
BigDecimal BigDecimal::operator-(const BigDecimal &rhs)
{
    return BigDecimal::subtract(value, rhs.value);
}

/**
 * @brief 
 * @param  rhs              
 * @return BigDecimal 
 */
BigDecimal BigDecimal::operator*(const BigDecimal &rhs)
{
    return BigDecimal::multiply(value, rhs.value);
}

/**
 * @brief 
 * @param  rhs              
 * @return BigDecimal 
 */
BigDecimal BigDecimal::operator/(const BigDecimal &rhs)
{
    return BigDecimal::divide(value, rhs.value);
}

/**
 * @brief 
 * @param  rhs              
 * @return BigDecimal 
 */
BigDecimal BigDecimal::operator%(const BigDecimal &rhs)
{
    return BigDecimal::modulus(value, rhs.value);
}

/**
 * @brief 
 * @param  rhs              
 * @return BigDecimal 
 */
BigDecimal BigDecimal::operator^(const BigDecimal &rhs)
{
    return BigDecimal::pow(value, rhs.value);
}

/**
 * @brief 
 * @param  rhs              
 */
void BigDecimal::operator+=(const BigDecimal &rhs)
{
    value = BigDecimal::add(value, rhs.value);
}

/**
 * @brief 
 * @param  rhs              
 */
void BigDecimal::operator-=(const BigDecimal &rhs)
{
    value = BigDecimal::subtract(value, rhs.value);
}

/**
 * @brief 
 * @param  rhs              
 */
void BigDecimal::operator*=(const BigDecimal &rhs)
{
    value = BigDecimal::multiply(value, rhs.value);
}

/**
 * @brief 
 * @param  rhs              
 */
void BigDecimal::operator/=(const BigDecimal &rhs)
{
    value = BigDecimal::divide(value, rhs.value);
}

/**
 * @brief 
 * @param  rhs              
 */
void BigDecimal::operator^=(const BigDecimal &rhs)
{
    value = BigDecimal::pow(value, rhs.value);
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool BigDecimal::operator>(const BigDecimal &rhs)
{
    return BigDecimal::compareTo(value, rhs.value) > 0;
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool BigDecimal::operator>=(const BigDecimal &rhs)
{
    return BigDecimal::compareTo(value, rhs.value) >= 0;
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool BigDecimal::operator==(const BigDecimal &rhs)
{
    return BigDecimal::compareTo(value, rhs.value) == 0;
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool BigDecimal::operator<(const BigDecimal &rhs)
{
    return BigDecimal::compareTo(value, rhs.value) < 0;
}

/**
 * @brief 
 * @param  rhs              
 * @return true 
 * @return false 
 */
bool BigDecimal::operator<=(const BigDecimal &rhs)
{
    return BigDecimal::compareTo(value, rhs.value) <= 0;
}

/**
 * @brief 
 * @return int 
 */
int BigDecimal::toInt()
{
    std::istringstream buffer(value.c_str());
    int ret;
    buffer >> ret;
    return ret;
}

/**
 * @brief 
 * @return unsigned int 
 */
unsigned int BigDecimal::toUInt()
{
    std::istringstream buffer(value.c_str());
    unsigned int ret;
    buffer >> ret;
    return ret;
}

/**
 * @brief 
 * @return long long 
 */
long long BigDecimal::toLongLong()
{
    std::istringstream buffer(value.c_str());
    long long ret;
    buffer >> ret;
    return ret;
}

/**
 * @brief 
 * @return unsigned long long 
 */
unsigned long long BigDecimal::toULongLong()
{
    std::istringstream buffer(value.c_str());
    unsigned long long ret;
    buffer >> ret;
    return ret;
}

/**
 * @brief 
 * @return long double 
 */
long double BigDecimal::toLongDouble()
{
    std::istringstream buffer(value.c_str());
    long double ret;
    buffer >> ret;
    return ret;
}

/**
 * @brief 
 * @return double 
 */
double BigDecimal::toDouble()
{
    std::istringstream buffer(value.c_str());
    double ret;
    buffer >> ret;
    return ret;
}

/**
 * @brief 
 * @return float 
 */
float BigDecimal::toFloat()
{
    std::istringstream buffer(value.c_str());
    float ret;
    buffer >> ret;
    return ret;
}

/**
 * @brief 
 * @return String 
 */
String BigDecimal::toString() { return value; }

/**
 * @brief 
 * @param  scale            
 */
void BigDecimal::round(int scale)
{
    if (scale >= 1) value = BigDecimal::round(value, scale);
}

/**
 * @brief 
 * @return String 
 */
String BigDecimal::integerPart()
{
    size_t dot = value.find('.');
    if (dot != String::npos)
    {
        if (dot == 0) return String("0");
        if (dot == 1 && value[0] == '-') return String("-0");
        return value.substr(0, dot);
    }
    else { return value; }
}

/**
 * @brief 
 * @return String 
 */
String BigDecimal::decimalPart()
{
    size_t dot = value.find('.');
    if (dot != String::npos)
        return value.length() > dot + 1 ? value.substr(dot + 1) : String("0");
    else
        return String("0");
}

/**
 * @brief 
 * @param  scale            
 */
void BigDecimal::scale(int scale)
{
    if (scale < 0) _scale = 0;
    else
        _scale = scale;
}

/**
 * @brief 
 * @param  lhs              
 * @param  rhs              
 * @param  scale            
 * @return String 
 */
String BigDecimal::divide(const String &lhs, const String &rhs, int scale)
{
    if (scale == INT_MIN) { scale = _scale; }
    if (scale < 0)
    {
        std::cerr << "Scale (" << String::toString(scale).c_str()
                  << ") Cant Be Negative!!!" << std::endl;
        scale = 0;
    }
    if (lhs.empty()) { return _zero(scale); }
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

    return trimTrailingZeros(
            divide_positive(lhs.c_str(), lint, ldot, lfrac, lscale, rhs.c_str(),
                            rint, rdot, rfrac, rscale, scale, lsign * rsign));
}

/**
 * @brief 
 * @param  lhs              
 * @param  rhs              
 * @param  scale            
 * @return String 
 */
String BigDecimal::modulus(const String &lhs, const String &rhs, int scale)
{
    if (lhs.empty()) { return ZERO; }
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
    for (int i = rint; i < rdot; i++) { mod = mod * 10 + rhs[i] - '0'; }

    if (rdot - rint > 18 || mod == 0)
    {
        std::cerr << "\"" << rhs.c_str()
                  << "\" Is Not A Non Zero Integer Less Than 1e18 By Absolute "
                     "Value"
                  << std::endl;
        return ZERO;
    }

    long long res = 0;
    for (int i = lint; i < ldot; i++)
    {
        res = res * 2;
        if (res >= mod) { res -= mod; }
        res = res * 5 + lhs[i] - '0';
        while (res >= mod) { res -= mod; }
    }

    char buffer[20];
    int cur_pos = 20;
    do {
        buffer[--cur_pos] = (char) (res % 10 + '0');
        res /= 10;
    } while (res > 0);

    if (lsign < 0) { buffer[--cur_pos] = '-'; }

    return String(trimTrailingZeros(
            String(buffer + cur_pos).substr(0, 20 - cur_pos)));
}

/**
 * @brief 
 * @param  lhs              
 * @param  rhs              
 * @param  scale            
 * @return String 
 */
String BigDecimal::pow(const String &lhs, const String &rhs, int scale)
{
    if (lhs.empty()) { return ZERO; }
    if (rhs.empty()) { return ONE; }

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
    for (int i = rint; i < rdot; i++) { deg = deg * 10 + rhs[i] - '0'; }

    if (rdot - rint > 18 || (rsign < 0 && deg != 0))
    {
        std::cerr << "\"" << rhs.c_str()
                  << "\" Is Not A Non Negative Integer Less Than 1e18"
                  << std::endl;
        return ZERO;
    }

    if (deg == 0) { return ONE; }

    String result = ONE;
    String mul = lhs;
    while (deg > 0)
    {
        if (deg & 1) { result = multiply(result, mul, 0); }
        mul = multiply(mul, mul, 0);
        deg >>= 1;
    }

    return trimTrailingZeros(result);
}

/**
 * @brief 
 * @param  lhs              
 * @param  rhs              
 * @param  scale            
 * @return String 
 */
String BigDecimal::add(const String &lhs, const String &rhs, int scale)
{
    if (lhs.empty()) { return add(ZERO, rhs, scale); }
    if (rhs.empty()) { return add(lhs, ZERO, scale); }

    if (scale < 0)
    {
        std::cerr << "Scale (" << String::toString(scale).c_str()
                  << ") Cant Be Negative!!!" << std::endl;
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

    return trimTrailingZeros(_add(lhs.c_str(), lsign, lint, ldot, lfrac, lscale,
                                  rhs.c_str(), rsign, rint, rdot, rfrac, rscale,
                                  std::max(lscale, rscale)));
}

/**
 * @brief 
 * @param  lhs              
 * @param  rhs              
 * @param  scale            
 * @return String 
 */
String BigDecimal::subtract(const String &lhs, const String &rhs, int scale)
{
    if (lhs.empty()) { return subtract(ZERO, rhs, scale); }
    if (rhs.empty()) { return subtract(lhs, ZERO, scale); }

    if (scale < 0)
    {
        std::cerr << "Scale (" << String::toString(scale).c_str()
                  << ") Cant Be Negative!!!" << std::endl;
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

    return trimTrailingZeros(_add(lhs.c_str(), lsign, lint, ldot, lfrac, lscale,
                                  rhs.c_str(), rsign, rint, rdot, rfrac, rscale,
                                  std::max(lscale, rscale)));
}

/**
 * @brief 
 * @param  lhs              
 * @param  rhs              
 * @param  scale            
 * @return String 
 */
String BigDecimal::multiply(const String &lhs, const String &rhs, int scale)
{
    if (lhs.empty()) { return multiply(ZERO, rhs, scale); }
    if (rhs.empty()) { return multiply(lhs, ZERO, scale); }

    if (scale < 0)
    {
        std::cerr << "Scale (" << String::toString(scale).c_str()
                  << ") Cant Be Negative!!!" << std::endl;
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

    return trimTrailingZeros(multiply_positive(
            lhs.c_str(), lint, ldot, lfrac, lscale, rhs.c_str(), rint, rdot,
            rfrac, rscale, lscale + rscale, lsign * rsign));
}

/**
 * @brief 
 * @param  lhs              
 * @param  scale            
 * @return String 
 */
String BigDecimal::round(const String &lhs, int scale)
{
    if (lhs.empty()) { return BigDecimal::round(ZERO, scale); }

    if (scale == INT_MIN) { scale = _scale; }

    if (scale < 0)
    {
        std::cerr << "Scale (" << String::toString(scale).c_str()
                  << ") Cant Be Negative!!!" << std::endl;
        scale = 0;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number(lhs, lsign, lint, ldot, lfrac, lscale) < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Is Not A Number" << std::endl;
        return 0;
    }

    int len = lhs.size();
    String result(len + 1, '0');
    for (int i = len - 1; i >= lint; --i) { result[i + 1] = lhs[i]; }

    char *data = (char *) malloc((result.length() + 1) * sizeof(char));
    sprintf(data, result.c_str());
    String ret = _round(data, lint + 1, ldot + 1, lfrac + 1, lscale, scale,
                        lsign, 1, 1);
    free(data);
    return ret;
}

/**
 * @brief 
 * @param  lhs              
 * @param  rhs              
 * @param  scale            
 * @return int 
 */
int BigDecimal::compareTo(const String &lhs, const String &rhs, int scale)
{
    if (lhs.empty()) { return BigDecimal::compareTo(ZERO, rhs, scale); }
    if (rhs.empty()) { return BigDecimal::compareTo(lhs, ZERO, scale); }

    if (scale == INT_MIN) { scale = _scale; }
    if (scale < 0)
    {
        std::cerr << "Scale (" << String::toString(scale).c_str()
                  << ") Cant Be Negative!!!" << std::endl;
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

    if (lsign != rsign) { return (lsign - rsign) / 2; }

    return (1 - 2 * (lsign < 0)) * _compareTo(lhs.c_str(), lint, ldot, lfrac,
                                              lscale, rhs.c_str(), rint, rdot,
                                              rfrac, rscale, scale);
}

/**
 * @brief 
 * @param  lhs              
 * @param  scale            
 * @return String 
 */
String BigDecimal::log2(const String &lhs, int scale)
{
    if (lhs.empty()) { return BigDecimal::round(ZERO, scale); }

    if (scale == INT_MIN) { scale = _scale; }
    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number(lhs, lsign, lint, ldot, lfrac, lscale) < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Is Not A Number" << std::endl;
        return "0";
    }
    if (lsign < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Cannot Be A Negative Number"
                  << std::endl;
        return "0";
    }
    return (BigDecimal::compareTo(lhs, ONE) > 0)
                   ? String(BigDecimal::add(
                             ONE,
                             BigDecimal::log(BigDecimal::divide(lhs, TEN))))
                   : ZERO;
}

/**
 * @brief 
 * @param  lhs              
 * @param  scale            
 * @return String 
 */
String BigDecimal::ln(const String &lhs, int scale) { return String(); }

/**
 * @brief 
 * @param  lhs              
 * @param  scale            
 * @return String 
 */
String BigDecimal::log(const String &lhs, int scale)
{
    if (lhs.empty()) { return BigDecimal::round(ZERO, scale); }

    if (scale == INT_MIN) { scale = _scale; }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number(lhs, lsign, lint, ldot, lfrac, lscale) < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Is Not A Number" << std::endl;
        return _zero(scale);
    }
    if (lsign < 0)
    {
        std::cerr << "\"" << lhs.c_str() << "\" Cannot Be A Negative Number"
                  << std::endl;
        return _zero(scale);
    }
    return String(BigDecimal::divide(BigDecimal::ln(lhs, 0),
                                     BigDecimal::ln(String::toString("10"), 0),
                                     0));
}

/**
 * @brief 
 * @param  lhs              
 * @param  scale            
 * @return String 
 */
String BigDecimal::sin(const String &lhs, int scale)
{
    String sum("0"), n, d, t, i("0"), j("0");
    while (BigDecimal::compareTo(i, lhs) <= 0)
    {
        if (BigDecimal::modulus(i, "2") != "0")
        {
            j = BigDecimal::add(j, ONE);
            n = BigDecimal::pow(lhs, i);
            d = fact(i);
            t = BigDecimal::divide(n, d);
            if (BigDecimal::modulus(j, "2") != "0")
            {
                sum = BigDecimal::subtract(sum, t);
            }
            else { sum = BigDecimal::add(sum, t); }
        }
        i = BigDecimal::add(i, ONE);
    }
    return sum;
}

/**
 * @brief 
 * @param  lhs              
 * @param  caps             
 * @return String 
 */
String BigDecimal::stringToHex(String &lhs, int caps)
{
    long int i = 1;
    int temp;
    lhs = LeftOfDot(lhs);
    String quotient = lhs, hexoutput("");
    temp = atoi(modulus(quotient, String::toString("16"), 0).c_str());
    std::cout << temp;
    return hexoutput;
}

}// namespace m2