#include <mathhelp.h>
#include <cmath>
#include <iostream>
#include <sstream>

namespace m2 {

BigInteger::BigInteger(String number) : m_Value(number)
{
}

BigInteger::BigInteger(long long number) : m_Value(std::to_string(number))
{
}

BigInteger BigInteger::Add(BigInteger other)
{
    BigInteger b1 = other > *this ? other : *this;
    BigInteger b2 = other > *this ? *this : other;
    if (b1.IsNegative() || b2.IsNegative())
    {
        if (b1.IsNegative() && b2.IsNegative())
        {
            return b1.Negate().Add(b2.Negate()).Negate();
        }
        else if (b1.IsNegative() && !b2.IsNegative())
        {
            return b1.Negate().Subtract(b2).Negate();
        }
        else
        {
            return b2.Negate().Subtract(b1).Negate();
        }
    }
    String results;
    int carry = 0;
    int diff = int(b1.m_Value.size() - b2.m_Value.size());
    for (int i = 0; i < diff; ++i)
    {
        b2.m_Value.insert(b2.m_Value.begin(), '0');
    }
    for (int i = int(b1.m_Value.size() - 1); i >= 0; --i)
    {
        int sum = (b1.m_Value[i] - '0') + (b2.m_Value[i] - '0') + carry;
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

BigInteger BigInteger::Addll(const long long &other)
{
    return this->Add(BigInteger(other));
}

BigInteger BigInteger::Addstr(const String &other)
{
    return this->Add(BigInteger(other));
}


BigInteger BigInteger::Subtract(BigInteger other)
{
    BigInteger b1 = *this, b2 = other;
    if (b1.IsNegative() || b2.IsNegative())
    {
        if (b1.IsNegative() && b2.IsNegative())
        {
            return b1.Negate().Add(b2.Negate()).Negate();
        }
        else if (b1.IsNegative() && !b2.IsNegative())
        {
            return b1.Negate().Add(b2).Negate();
        }
        else
        {
            return b2.Negate().Add(b1);
        }
    }
    String results;
    int n = 0, p = 0;
    bool takeOffOne = false;
    bool shouldBeTen = false;

    if (b1 < b2)
    {
        //Negative answer
        String t = b2.Subtract(*this).Negate().ToString();
        for (unsigned int i = 1; i < t.length(); ++i)
        {
            if (t[i] != '0')
                break;
            t.erase(1, 1);
        }
        return BigInteger(t);
    }

    //This next if-block fixes the case where the digit difference is greater than 1
    //100 - 5 is an example. This code adds 0's to make it, for example, 100 - 05, which
    //allows the rest of the subtraction code to work.
    if (b1.m_Value.size() - b2.ToString().size() > 1)
    {
        for (unsigned long i = 0; i < b1.m_Value.size() - b2.ToString().size() - 1; ++i)
        {
            b2.m_Value.insert(b2.m_Value.begin(), '0');
        }
    }
    int i = int(b1.m_Value.size() - 1);
    for (int j = int(b2.m_Value.size() - 1); j >= 0; --j)
    {
        if (((b1.m_Value[i] - '0') < (b2.m_Value[j] - '0')) && i > 0)
        {
            n = char((b1.m_Value[i] - '0') + 10);
            takeOffOne = true;
            if (j > 0 || b1.m_Value[i - 1] != '0')
            {
                p = char((b1.m_Value[i - 1] - '0') - 1);
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
                for (int a = i - 1; (b1.m_Value[a] - '0') == 0; --a)
                {
                    b1.m_Value[a] = static_cast<char>(p + '0');
                    --index;
                }
                int t = (b1.m_Value[index] - '0') - 1;
                b1.m_Value[index] = static_cast<char>(t + '0');
            }
            b1.m_Value[i - 1] = static_cast<char>(p + '0');
            shouldBeTen = false;
        }
        StringStream ss;
        if (((b1.m_Value[i] - '0') == (b2.m_Value[j] - '0')))
        {
            ss << "0";
        }
        else
        {
            if (n <= 0)
            {
                ss << ((b1.m_Value[i] - '0') - (b2.m_Value[j] - '0'));
            }
            else
            {
                ss << (n - (b2.m_Value[j] - '0'));
            }
        }

        results.insert(0, ss.Str());
        --i;
        n = 0;
    }
    if (takeOffOne)
    {
        String number = "";
        for (int j = b1.m_Value.length() - b2.m_Value.length() - 1; j >= 0; --j)
        {
            if (b1.m_Value[j] == '0')
            {
                number += "0";
                continue;
            }
            else
            {
                number.insert(number.begin(), b1.m_Value[j]);
                int t = atoi(number.c_str());
                --t;
                b1.m_Value.replace(0, number.size(), std::to_string(t).c_str());
                break;
            }
        }
    }
    while (i >= 0)
    {
        StringStream ss;
        if (i == 0)
        {
            if (b1.m_Value[i] - '0' != 0)
            {
                ss << (b1.m_Value[i] - '0');
                results.insert(0, ss.Str());
            }
        }
        else
        {
            ss << (b1.m_Value[i] - '0');
            results.insert(0, ss.Str());
        }

        --i;
    }
    //In the case of all 0's, we only want to return one of them
    if (results.find_first_not_of('0') == String::npos)
    {
        results = "0";
    }
    else if (results[0] == '0')
    {
        int index = results.find_first_not_of('0');
        results = results.substr(index, results.length() - 1);
    }
    return BigInteger(results);
}

BigInteger BigInteger::Subtractll(const long long &other)
{
    return this->Subtract(BigInteger(other));
}

BigInteger BigInteger::Subtractstr(const String &other)
{
    return this->Subtract(BigInteger(other));
}

BigInteger BigInteger::Multiply(BigInteger other)
{
    BigInteger b1 = other > *this ? other : *this;
    BigInteger b2 = other > *this ? *this : other;
    if (b1.IsNegative() || b2.IsNegative())
    {
        if (b1.IsNegative() && b2.IsNegative())
        {
            return b1.Negate().Multiply(b2.Negate());
        }
        else if (b1.IsNegative() && !b2.IsNegative())
        {
            return b1.Negate().Multiply(b2).Negate();
        }
        else
        {
            return b2.Negate().Multiply(b1).Negate();
        }
    }
    if (b1 == 0 || b2 == 0)
        return 0;
    int carry = 0;
    int zeroCounter = 0;
    BigInteger b = 0;

    for (unsigned int i = 0; i < b1.m_Value.size() - b2.m_Value.size(); ++i)
    {
        b2.m_Value.insert(b2.m_Value.begin(), '0');
    }
    for (int i = (b2.m_Value.size() - 1); i >= 0; --i)
    {
        String rr;
        for (int j = int(b1.m_Value.size() - 1); j >= 0; --j)
        {
            int val = ((b2.m_Value[i] - '0') * (b1.m_Value[j] - '0')) + carry;
            carry = 0;
            if (val > 9 && j != 0)
            {
                carry = val / 10;
                rr.insert(0, std::to_string(val % 10).c_str());
            }
            else
            {
                rr.insert(0, std::to_string(val).c_str());
            }
        }
        if (zeroCounter > 0)
        {
            for (int x = 0; x < zeroCounter; ++x)
            {
                rr.append("0");
            }
        }
        ++zeroCounter;
        b += BigInteger(rr);
    }
    if (b.m_Value.find_first_not_of('0') != String::npos)
    {
        b.SetString(b.m_Value.erase(0, b.m_Value.find_first_not_of('0')));
    }
    else
    {
        //In the case of all 0's, we only want to return one of them
        b.SetString("0");
    }
    return b;
}

BigInteger BigInteger::Multiplyll(const long long &other)
{
    if (other == 0)
        return 0;
    if (other == 1)
        return *this;
    auto original = *this;
    for (auto i = 0; i < other - 1; ++i)
    {
        *this += original;
    }
    return *this;
}

BigInteger BigInteger::Multiplystr(const String &other)
{
    return this->Multiply(BigInteger(other));
}

BigInteger BigInteger::Divide(BigInteger other)
{
    if (other == 0)
    {
        std::cerr << "You cannot divide by 0!" << std::endl;
    }
    BigInteger b1 = *this, b2 = other;
    bool sign = false;
    if (b1.IsNegative() && b2.IsNegative())
    {
        b1.Negate();
        b2.Negate();
    }
    else if (b1.IsNegative() && !b2.IsNegative())
    {
        b1.Negate();
        sign = true;
    }
    else if (!b1.IsNegative() && b2.IsNegative())
    {
        b2.Negate();
        sign = true;
    }
    BigInteger quotient = 0;
    while (b1 >= b2)
    {
        b1 -= b2;
        ++quotient;
    }
    if (sign)
        quotient.Negate();
    return quotient;
}

BigInteger BigInteger::Dividell(const long long &other)
{
    return this->Divide(BigInteger(other));
}

BigInteger BigInteger::Dividestr(const String &other)
{
    return this->Divide(BigInteger(other));
}

BigInteger BigInteger::Pow(int exponent)
{
    if (exponent < 0)
        std::cerr << "Powers less than 0 are not supported" << std::endl;
    if (exponent == 0)
        return BigInteger("1");
    if (exponent == 1)
        return *this;
    BigInteger result = 1, base = *this;
    while (exponent)
    {
        if (exponent & 1)
        {
            result *= base;
        }
        exponent >>= 1;
        base *= base;
    }
    return result;
}

String BigInteger::ToString()
{
    return this->m_Value;
}

BigInteger BigInteger::SetString(const String &newStr)
{
    this->m_Value = newStr;
    return *this;
}

BigInteger BigInteger::Negate()
{
    if (this->m_Value[0] == '-')
    {
        this->m_Value.erase(0, 1);
    }
    else
    {
        this->m_Value.insert(this->m_Value.begin(), '-');
    }
    return *this;
}

BigInteger BigInteger::TrimLeadingZeros()
{
    BigInteger b = *this;
    if (b.m_Value.find_first_not_of('0') != String::npos)
    {
        b.SetString(b.m_Value.erase(0, b.m_Value.find_first_not_of('0')));
    }
    return b;
}

bool BigInteger::Equals(const BigInteger &other)
{
    return this->m_Value == other.m_Value;
}

bool BigInteger::Equals(const long long &other)
{
    return this->ToString() == std::to_string(other);
}

bool BigInteger::Equals(const String &other)
{
    return this->ToString() == other;
}

unsigned int BigInteger::Digits()
{
    return this->m_Value.length() - static_cast<int>(this->IsNegative());
}

bool BigInteger::IsNegative() const
{
    return this->m_Value[0] == '-';
}

bool BigInteger::isPositive()
{
    return !this->IsNegative();
}

bool BigInteger::IsEven()
{
    return this->m_Value[this->m_Value.length() - 1] % 2 == 0;
}

bool BigInteger::IsOdd()
{
    return !this->IsEven();
}

BigInteger BigInteger::Abs() const
{
    return BigInteger(this->m_Value.substr(static_cast<unsigned int>(this->IsNegative())));
}

BigInteger operator+(BigInteger b1, const BigInteger &b2)
{
    return b1.Add(b2);
}

BigInteger operator+(BigInteger b1, const long long &b2)
{
    return b1.Addll(b2);
}

BigInteger operator+(BigInteger b1, const String &b2)
{
    return b1.Addstr(b2);
}

BigInteger operator-(BigInteger b1, const BigInteger &b2)
{
    return b1.Subtract(b2);
}

BigInteger operator-(BigInteger b1, const long long &b2)
{
    return b1.Subtractll(b2);
}

BigInteger operator-(BigInteger b1, const String &b2)
{
    return b1.Subtractstr(b2);
}

BigInteger operator*(BigInteger b1, const BigInteger &b2)
{
    return b1.Multiply(b2);
}

BigInteger operator*(BigInteger b1, const long long &b2)
{
    return b1.Multiplyll(b2);
}

BigInteger operator*(BigInteger b1, const String &b2)
{
    return b1.Multiplystr(b2);
}

BigInteger operator/(BigInteger b1, const BigInteger &b2)
{
    return b1.Divide(b2);
}

BigInteger operator/(BigInteger b1, const long long &b2)
{
    return b1.Dividell(b2);
}

BigInteger operator/(BigInteger b1, const String &b2)
{
    return b1.Dividestr(b2);
}

BigInteger operator^(BigInteger b1, const int &b2)
{
    return b1.Pow(b2);
}

bool operator==(BigInteger b1, const BigInteger &b2)
{
    return b1.Equals(b2);
}

bool operator==(BigInteger b1, const long long &b2)
{
    return b1.Equals(b2);
}

bool operator==(BigInteger b1, const String &b2)
{
    return b1.Equals(b2);
}

bool operator>(BigInteger b1, const BigInteger &b2)
{
    if (b1.IsNegative() || b2.IsNegative())
    {
        if (b1.IsNegative() && b2.IsNegative())
        {
            BigInteger bt = b2;
            b1.m_Value.erase(0, 1);
            bt.m_Value.erase(0, 1);
            return b1 < bt;
        }
        else
        {
            return !(b1.IsNegative() && !b2.IsNegative());
        }
    }
    b1 = b1.TrimLeadingZeros();
    auto c = BigInteger(b2);
    c = c.TrimLeadingZeros();
    if (b1 == c)
    {
        return false;
    }
    if (b1.m_Value.size() > c.m_Value.size())
    {
        return true;
    }
    else if (c.m_Value.size() > b1.m_Value.size())
    {
        return false;
    }
    else
    {
        for (unsigned int i = 0; i < b1.m_Value.size(); ++i)
        {
            if (b1[i] == static_cast<unsigned int>(c.m_Value[i] - '0'))
            {
                continue;
            }
            return b1[i] > static_cast<unsigned int>(c.m_Value[i] - '0');
        }
    }
    return false;
}

bool operator<(BigInteger b1, const BigInteger &b2)
{
    return !(b1 == b2) && !(b1 > b2);
}

bool operator>=(BigInteger b1, const BigInteger &b2)
{
    return b1 > b2 || b1 == b2;
}

bool operator<=(BigInteger b1, const BigInteger &b2)
{
    return b1 < b2 || b1 == b2;
}

unsigned int BigInteger::operator[](int index)
{
    if (this->m_Value[index] == '-')
    {
        std::cerr << "You cannot get the negative sign from the number" << std::endl;
    }
    return static_cast<unsigned int>(this->m_Value[index] - '0');
}

BigInteger &BigInteger::operator=(const BigInteger &other)
{
    this->m_Value = other.m_Value;
    return *this;
}

BigInteger &BigInteger::operator=(const long long &other)
{
    this->m_Value = std::to_string(other);
    return *this;
}

BigInteger &BigInteger::operator=(const String &other)
{
    this->m_Value = other;
    return *this;
}

BigInteger &BigInteger::operator+=(const BigInteger &other)
{
    *this = *this + other;
    return *this;
}

BigInteger &BigInteger::operator+=(const long long &other)
{
    *this = *this + other;
    return *this;
}

BigInteger &BigInteger::operator+=(const String &other)
{
    *this = *this + other;
    return *this;
}

BigInteger &BigInteger::operator-=(const BigInteger &other)
{
    *this = *this - other;
    return *this;
}

BigInteger &BigInteger::operator-=(const long long &other)
{
    *this = *this - other;
    return *this;
}

BigInteger &BigInteger::operator-=(const String &other)
{
    *this = *this - other;
    return *this;
}

BigInteger &BigInteger::operator*=(const BigInteger &other)
{
    *this = *this * other;
    return *this;
}

BigInteger &BigInteger::operator*=(const long long &other)
{
    *this = *this * other;
    return *this;
}

BigInteger &BigInteger::operator*=(const String &other)
{
    *this = *this * other;
    return *this;
}

BigInteger &BigInteger::operator/=(const BigInteger &other)
{
    *this = *this / other;
    return *this;
}

BigInteger &BigInteger::operator/=(const long long &other)
{
    *this = *this / other;
    return *this;
}

BigInteger &BigInteger::operator/=(const String &other)
{
    *this = *this / other;
    return *this;
}

BigInteger &BigInteger::operator++()
{
    *this += BigInteger("1");
    return *this;
}

BigInteger &BigInteger::operator--()
{
    *this -= BigInteger("1");
    return *this;
}

const BigInteger BigInteger::operator++(int)
{
    BigInteger t(this->ToString());
    ++(*this);
    return t;
}

const BigInteger BigInteger::operator--(int)
{
    BigInteger t(this->ToString());
    --(*this);
    return t;
}

}// namespace m2
