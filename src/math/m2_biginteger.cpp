#include <cmath>
#include <iostream>
#include <m2_biginteger.h>
#include <sstream>

namespace m2 {

/**
 * @brief Construct a new Big Integer:: Big Integer object
 * @param  v           
 */
BigInteger::BigInteger(const String &v) : value(v) {}

/**
 * @brief Construct a new Big Integer:: Big Integer object
 * @param  v                
 */
BigInteger::BigInteger(int v) noexcept : value(String::toString(v)) {}

/**
 * @brief Construct a new Big Integer:: Big Integer object
 * @param  v           
 */
BigInteger::BigInteger(long long v) noexcept : value(String::toString(v)) {}

/**
 * @brief Construct a new Big Integer:: Big Integer object
 * @param  v                
 */
BigInteger::BigInteger(unsigned int v) noexcept : value(String::toString(v)) {}

/**
 * @brief Construct a new Big Integer:: Big Integer object
 * @param  v                
 */
BigInteger::BigInteger(unsigned long long v) noexcept
    : value(String::toString(v))
{
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger 
 */
BigInteger BigInteger::add(BigInteger other)
{
    BigInteger b1 = other > *this ? other : *this;
    BigInteger b2 = other > *this ? *this : other;
    if (b1.isNegative() || b2.isNegative())
    {
        if (b1.isNegative() && b2.isNegative())
        {
            return b1.negative().add(b2.negative()).negative();
        }
        else if (b1.isNegative() && !b2.isNegative())
        {
            return b1.negative().subtract(b2).negative();
        }
        else { return b2.negative().subtract(b1).negative(); }
    }
    String results;
    int carry = 0;
    int diff = int(b1.value.size() - b2.value.size());
    for (int i = 0; i < diff; ++i) { b2.value.insert(b2.value.begin(), '0'); }
    for (int i = int(b1.value.size() - 1); i >= 0; --i)
    {
        int sum = (b1.value[i] - '0') + (b2.value[i] - '0') + carry;
        carry = 0;
        if (sum <= 9 || i == 0)
        {
            results.insert(0, std::to_string(sum).c_str());
        }
        else
        {
            results.insert(0, std::to_string(sum % 10).c_str());
            carry = 1;
        }
    }
    return BigInteger(results);
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger 
 */
BigInteger BigInteger::addll(const long long &other)
{
    return this->add(BigInteger(other));
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger 
 */
BigInteger BigInteger::addstr(const String &other)
{
    return this->add(BigInteger(other));
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger 
 */
BigInteger BigInteger::subtract(BigInteger other)
{
    BigInteger b1 = *this, b2 = other;
    if (b1.isNegative() || b2.isNegative())
    {
        if (b1.isNegative() && b2.isNegative())
        {
            return b1.negative().add(b2.negative()).negative();
        }
        else if (b1.isNegative() && !b2.isNegative())
        {
            return b1.negative().add(b2).negative();
        }
        else { return b2.negative().add(b1); }
    }
    String results;
    int n = 0, p = 0;
    bool takeOffOne = false;
    bool shouldBeTen = false;

    if (b1 < b2)
    {
        //Negative answer
        String t = b2.subtract(*this).negative().toString();
        for (unsigned int i = 1; i < t.length(); ++i)
        {
            if (t[i] != '0') break;
            t.erase(1, 1);
        }
        return BigInteger(t);
    }

    //This next if-block fixes the case where the digit difference is greater than 1
    //100 - 5 is an example. This code adds 0's to make it, for example, 100 - 05, which
    //allows the rest of the subtraction code to work.
    if (b1.value.size() - b2.toString().size() > 1)
    {
        for (unsigned long i = 0;
             i < b1.value.size() - b2.toString().size() - 1; ++i)
        {
            b2.value.insert(b2.value.begin(), '0');
        }
    }
    int i = int(b1.value.size() - 1);
    for (int j = int(b2.value.size() - 1); j >= 0; --j)
    {
        if (((b1.value[i] - '0') < (b2.value[j] - '0')) && i > 0)
        {
            n = char((b1.value[i] - '0') + 10);
            takeOffOne = true;
            if (j > 0 || b1.value[i - 1] != '0')
            {
                p = char((b1.value[i - 1] - '0') - 1);
                if (p == -1)
                {
                    p = 9;
                    shouldBeTen = true;
                }
                takeOffOne = false;
            }
            if (shouldBeTen)
            {
                int index = i - 1;
                for (int a = i - 1; (b1.value[a] - '0') == 0; --a)
                {
                    b1.value[a] = static_cast<char>(p + '0');
                    --index;
                }
                int t = (b1.value[index] - '0') - 1;
                b1.value[index] = static_cast<char>(t + '0');
            }
            b1.value[i - 1] = static_cast<char>(p + '0');
            shouldBeTen = false;
        }
        std::stringstream ss;
        if (((b1.value[i] - '0') == (b2.value[j] - '0'))) { ss << "0"; }
        else
        {
            if (n <= 0) { ss << ((b1.value[i] - '0') - (b2.value[j] - '0')); }
            else { ss << (n - (b2.value[j] - '0')); }
        }

        results.insert(0, ss.str());
        --i;
        n = 0;
    }
    if (takeOffOne)
    {
        String number = "";
        for (int j = b1.value.length() - b2.value.length() - 1; j >= 0; --j)
        {
            if (b1.value[j] == '0')
            {
                number += "0";
                continue;
            }
            else
            {
                number.insert(number.begin(), b1.value[j]);
                int t = atoi(number.c_str());
                --t;
                b1.value.replace(0, number.size(), std::to_string(t).c_str());
                break;
            }
        }
    }
    while (i >= 0)
    {
        std::stringstream ss;
        if (i == 0)
        {
            if (b1.value[i] - '0' != 0)
            {
                ss << (b1.value[i] - '0');
                results.insert(0, ss.str());
            }
        }
        else
        {
            ss << (b1.value[i] - '0');
            results.insert(0, ss.str());
        }

        --i;
    }
    //In the case of all 0's, we only want to return one of them
    if (results.find_first_not_of('0') == String::npos) { results = "0"; }
    else if (results[0] == '0')
    {
        int index = results.find_first_not_of('0');
        results = results.substr(index, results.length() - 1);
    }
    return BigInteger(results);
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger 
 */
BigInteger BigInteger::subtractll(const long long &other)
{
    return this->subtract(BigInteger(other));
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger 
 */
BigInteger BigInteger::subtractstr(const String &other)
{
    return this->subtract(BigInteger(other));
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger 
 */
BigInteger BigInteger::multiply(BigInteger other)
{
    BigInteger b1 = other > *this ? other : *this;
    BigInteger b2 = other > *this ? *this : other;
    if (b1.isNegative() || b2.isNegative())
    {
        if (b1.isNegative() && b2.isNegative())
        {
            return b1.negative().multiply(b2.negative());
        }
        else if (b1.isNegative() && !b2.isNegative())
        {
            return b1.negative().multiply(b2).negative();
        }
        else { return b2.negative().multiply(b1).negative(); }
    }
    if (b1 == 0 || b2 == 0) return 0;
    int carry = 0;
    int zeroCounter = 0;
    BigInteger b = 0;

    for (unsigned int i = 0; i < b1.value.size() - b2.value.size(); ++i)
    {
        b2.value.insert(b2.value.begin(), '0');
    }
    for (int i = (b2.value.size() - 1); i >= 0; --i)
    {
        String rr;
        for (int j = int(b1.value.size() - 1); j >= 0; --j)
        {
            int val = ((b2.value[i] - '0') * (b1.value[j] - '0')) + carry;
            carry = 0;
            if (val > 9 && j != 0)
            {
                carry = val / 10;
                rr.insert(0, std::to_string(val % 10).c_str());
            }
            else { rr.insert(0, std::to_string(val).c_str()); }
        }
        if (zeroCounter > 0)
        {
            for (int x = 0; x < zeroCounter; ++x) { rr.append("0"); }
        }
        ++zeroCounter;
        b += BigInteger(rr);
    }
    if (b.value.find_first_not_of('0') != String::npos)
    {
        b.setString(b.value.erase(0, b.value.find_first_not_of('0')));
    }
    else
    {
        //In the case of all 0's, we only want to return one of them
        b.setString("0");
    }
    return b;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger 
 */
BigInteger BigInteger::multiplyll(const long long &other)
{
    if (other == 0) return 0;
    if (other == 1) return *this;
    auto original = *this;
    for (auto i = 0; i < other - 1; ++i) { *this += original; }
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger 
 */
BigInteger BigInteger::multiplystr(const String &other)
{
    return this->multiply(BigInteger(other));
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger 
 */
BigInteger BigInteger::divide(BigInteger other)
{
    if (other == 0) { std::cerr << "You cannot divide by 0!" << std::endl; }
    BigInteger b1 = *this, b2 = other;
    bool sign = false;
    if (b1.isNegative() && b2.isNegative())
    {
        b1.negative();
        b2.negative();
    }
    else if (b1.isNegative() && !b2.isNegative())
    {
        b1.negative();
        sign = true;
    }
    else if (!b1.isNegative() && b2.isNegative())
    {
        b2.negative();
        sign = true;
    }
    BigInteger quotient = 0;
    while (b1 >= b2)
    {
        b1 -= b2;
        ++quotient;
    }
    if (sign) quotient.negative();
    return quotient;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger 
 */
BigInteger BigInteger::dividell(const long long &other)
{
    return this->divide(BigInteger(other));
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger 
 */
BigInteger BigInteger::dividestr(const String &other)
{
    return this->divide(BigInteger(other));
}

/**
 * @brief 
 * @param  exponent         
 * @return BigInteger 
 */
BigInteger BigInteger::pow(int exponent)
{
    if (exponent < 0)
        std::cerr << "Powers less than 0 are not supported" << std::endl;
    if (exponent == 0) return BigInteger("1");
    if (exponent == 1) return *this;
    BigInteger result = 1, base = *this;
    while (exponent)
    {
        if (exponent & 1) { result *= base; }
        exponent >>= 1;
        base *= base;
    }
    return result;
}

/**
 * @brief 
 * @return String 
 */
String BigInteger::toString() const { return this->value; }

/**
 * @brief 
 * @param  newStr           
 * @return BigInteger 
 */
BigInteger BigInteger::setString(const String &newStr)
{
    this->value = newStr;
    return *this;
}

/**
 * @brief 
 * @return BigInteger 
 */
BigInteger BigInteger::negative()
{
    if (this->value[0] == '-') { this->value.erase(0, 1); }
    else { this->value.insert(this->value.begin(), '-'); }
    return *this;
}

/**
 * @brief 
 * @return BigInteger 
 */
BigInteger BigInteger::trimLeadingZeros()
{
    BigInteger b = *this;
    if (b.value.find_first_not_of('0') != String::npos)
    {
        b.setString(b.value.erase(0, b.value.find_first_not_of('0')));
    }
    return b;
}

/**
 * @brief 
 * @param  other            
 * @return true 
 * @return false 
 */
bool BigInteger::equals(const BigInteger &other) const
{
    return this->value == other.value;
}

/**
 * @brief 
 * @param  other            
 * @return true 
 * @return false 
 */
bool BigInteger::equals(const long long &other) const
{
    return this->toString() == std::to_string(other);
}

/**
 * @brief 
 * @param  other            
 * @return true 
 * @return false 
 */
bool BigInteger::equals(const String &other) const
{
    return this->toString() == other;
}

/**
 * @brief 
 * @return unsigned int 
 */
unsigned int BigInteger::digits()
{
    return this->value.length() - static_cast<int>(this->isNegative());
}

/**
 * @brief 
 * @return true 
 * @return false 
 */
bool BigInteger::isNegative() const { return this->value[0] == '-'; }

/**
 * @brief 
 * @return true 
 * @return false 
 */
bool BigInteger::isPositive() const { return !this->isNegative(); }

/**
 * @brief 
 * @return true 
 * @return false 
 */
bool BigInteger::isEven() const
{
    return this->value[this->value.length() - 1] % 2 == 0;
}

/**
 * @brief 
 * @return true 
 * @return false 
 */
bool BigInteger::isOdd() const { return !this->isEven(); }

/**
 * @brief 
 * @return BigInteger 
 */
BigInteger BigInteger::abs() const
{
    return BigInteger(
            this->value.substr(static_cast<unsigned int>(this->isNegative())));
}

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return BigInteger 
 */
BigInteger operator+(BigInteger b1, const BigInteger &b2) { return b1.add(b2); }

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return BigInteger 
 */
BigInteger operator+(BigInteger b1, const long long &b2)
{
    return b1.addll(b2);
}

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return BigInteger 
 */
BigInteger operator+(BigInteger b1, const String &b2) { return b1.addstr(b2); }

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return BigInteger 
 */
BigInteger operator-(BigInteger b1, const BigInteger &b2)
{
    return b1.subtract(b2);
}

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return BigInteger 
 */
BigInteger operator-(BigInteger b1, const long long &b2)
{
    return b1.subtractll(b2);
}

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return BigInteger 
 */
BigInteger operator-(BigInteger b1, const String &b2)
{
    return b1.subtractstr(b2);
}

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return BigInteger 
 */
BigInteger operator*(BigInteger b1, const BigInteger &b2)
{
    return b1.multiply(b2);
}

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return BigInteger 
 */
BigInteger operator*(BigInteger b1, const long long &b2)
{
    return b1.multiplyll(b2);
}

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return BigInteger 
 */
BigInteger operator*(BigInteger b1, const String &b2)
{
    return b1.multiplystr(b2);
}

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return BigInteger 
 */
BigInteger operator/(BigInteger b1, const BigInteger &b2)
{
    return b1.divide(b2);
}

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return BigInteger 
 */
BigInteger operator/(BigInteger b1, const long long &b2)
{
    return b1.dividell(b2);
}

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return BigInteger 
 */
BigInteger operator/(BigInteger b1, const String &b2)
{
    return b1.dividestr(b2);
}

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return BigInteger 
 */
BigInteger operator^(BigInteger b1, const int &b2) { return b1.pow(b2); }

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return true 
 * @return false 
 */
bool operator==(BigInteger b1, const BigInteger &b2) { return b1.equals(b2); }

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return true 
 * @return false 
 */
bool operator==(BigInteger b1, const long long &b2) { return b1.equals(b2); }

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return true 
 * @return false 
 */
bool operator==(BigInteger b1, const String &b2) { return b1.equals(b2); }

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return true 
 * @return false 
 */
bool operator>(BigInteger b1, const BigInteger &b2)
{
    if (b1.isNegative() || b2.isNegative())
    {
        if (b1.isNegative() && b2.isNegative())
        {
            BigInteger bt = b2;
            b1.value.erase(0, 1);
            bt.value.erase(0, 1);
            return b1 < bt;
        }
        else { return !(b1.isNegative() && !b2.isNegative()); }
    }
    b1 = b1.trimLeadingZeros();
    auto c = BigInteger(b2);
    c = c.trimLeadingZeros();
    if (b1 == c) { return false; }
    if (b1.value.size() > c.value.size()) { return true; }
    else if (c.value.size() > b1.value.size()) { return false; }
    else
    {
        for (unsigned int i = 0; i < b1.value.size(); ++i)
        {
            if (b1[i] == static_cast<unsigned int>(c.value[i] - '0'))
            {
                continue;
            }
            return b1[i] > static_cast<unsigned int>(c.value[i] - '0');
        }
    }
    return false;
}

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return true 
 * @return false 
 */
bool operator<(BigInteger b1, const BigInteger &b2)
{
    return !(b1 == b2) && !(b1 > b2);
}

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return true 
 * @return false 
 */
bool operator>=(BigInteger b1, const BigInteger &b2)
{
    return b1 > b2 || b1 == b2;
}

/**
 * @brief 
 * @param  b1               
 * @param  b2               
 * @return true 
 * @return false 
 */
bool operator<=(BigInteger b1, const BigInteger &b2)
{
    return b1 < b2 || b1 == b2;
}

/**
 * @brief 
 * @param  index            
 * @return unsigned int 
 */
unsigned int BigInteger::operator[](int index)
{
    if (this->value[index] == '-')
    {
        std::cerr << "You cannot get the negative sign from the number"
                  << std::endl;
    }
    return static_cast<unsigned int>(this->value[index] - '0');
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator=(const BigInteger &other)
{
    this->value = other.value;
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator=(const long long &other)
{
    this->value = std::to_string(other);
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator=(const String &other)
{
    this->value = other;
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator+=(const BigInteger &other)
{
    *this = *this + other;
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator+=(const long long &other)
{
    *this = *this + other;
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator+=(const String &other)
{
    *this = *this + other;
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator-=(const BigInteger &other)
{
    *this = *this - other;
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator-=(const long long &other)
{
    *this = *this - other;
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator-=(const String &other)
{
    *this = *this - other;
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator*=(const BigInteger &other)
{
    *this = *this * other;
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator*=(const long long &other)
{
    *this = *this * other;
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator*=(const String &other)
{
    *this = *this * other;
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator/=(const BigInteger &other)
{
    *this = *this / other;
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator/=(const long long &other)
{
    *this = *this / other;
    return *this;
}

/**
 * @brief 
 * @param  other            
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator/=(const String &other)
{
    *this = *this / other;
    return *this;
}

/**
 * @brief 
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator++()
{
    *this += BigInteger("1");
    return *this;
}

/**
 * @brief 
 * @return BigInteger& 
 */
BigInteger &BigInteger::operator--()
{
    *this -= BigInteger("1");
    return *this;
}

/**
 * @brief 
 * @return const BigInteger 
 */
const BigInteger BigInteger::operator++(int)
{
    BigInteger t(this->toString());
    ++(*this);
    return t;
}

/**
 * @brief 
 * @return const BigInteger 
 */
const BigInteger BigInteger::operator--(int)
{
    BigInteger t(this->toString());
    --(*this);
    return t;
}

}// namespace m2