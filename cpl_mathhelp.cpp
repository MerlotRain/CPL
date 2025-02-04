/**
 * CPL - Common Portability Library
 *
 * Copyright (C) 2024 Merlot.Rain
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "cpl_mathhelp.h"
#include <float.h>
#include <iomanip>
#include <math.h>
#include <numbers>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#include <rpc.h>
#else
#include <uuid/uuid.h>
#endif

namespace CPL {

Guid::Guid()
{
#ifdef _WIN32
    CoCreateGuid(reinterpret_cast<GUID *>(this));// Windows API to create a GUID
#else
    uuid_generate(reinterpret_cast<uuid_t &>(
            this->Data));// Linux/macOS UUID generation
#endif
}

Guid::Guid(const Guid &rhs) { std::memcpy(this->Data, rhs.Data, 16); }

Guid::Guid(Guid &&rhs) noexcept
{
    std::memcpy(this->Data, rhs.Data, 16);
    std::memset(rhs.Data, 0, 16);// Zero out the source
}

bool Guid::operator==(const Guid &guid) const
{
    return std::memcmp(this->Data, guid.Data, 16) == 0;
}

Guid &Guid::operator=(const Guid &guid)
{
    if (this != &guid) { std::memcpy(this->Data, guid.Data, 16); }
    return *this;
}

Guid &Guid::operator=(Guid &&guid) noexcept
{
    if (this != &guid)
    {
        std::memcpy(this->Data, guid.Data, 16);
        std::memset(guid.Data, 0, 16);// Zero out the source
    }
    return *this;
}

void Guid::Swap(Guid &guid)
{
    unsigned char temp[16];
    std::memcpy(temp, this->Data, 16);
    std::memcpy(this->Data, guid.Data, 16);
    std::memcpy(guid.Data, temp, 16);
}

std::string Guid::ToString(Format formatType) const
{
    std::ostringstream oss;

    switch (formatType)
    {
        case Format::eHyphens32:
            {
                // Format: 00000000-0000-0000-0000-000000000000
                oss << std::hex << std::setfill('0') << std::setw(8)
                    << Data128.Data1 << '-' << std::setw(4) << Data128.Data2
                    << '-' << std::setw(4) << Data128.Data3 << '-';
                for (int i = 0; i < 2; ++i)
                {
                    oss << std::setw(2) << (int) Data128.Data4[i];
                }
                oss << '-';
                for (int i = 2; i < 8; ++i)
                {
                    oss << std::setw(2) << (int) Data128.Data4[i];
                }
                break;
            }
        case Format::eNumber32:
            {
                // Format: 00000000000000000000000000000000
                for (int i = 0; i < 16; ++i)
                {
                    oss << std::setw(2) << (int) Data[i];
                }
                break;
            }
        case Format::eHyphensBraces:
            {
                // Format: {00000000-0000-0000-0000-000000000000}
                oss << '{' << std::hex << std::setfill('0') << std::setw(8)
                    << Data128.Data1 << '-' << std::setw(4) << Data128.Data2
                    << '-' << std::setw(4) << Data128.Data3 << '-';
                for (int i = 0; i < 2; ++i)
                {
                    oss << std::setw(2) << (int) Data128.Data4[i];
                }
                oss << '-';
                for (int i = 2; i < 8; ++i)
                {
                    oss << std::setw(2) << (int) Data128.Data4[i];
                }
                oss << '}';
                break;
            }
        case Format::eHyphensParentheses:
            {
                // Format: (00000000-0000-0000-0000-000000000000)
                oss << '(' << std::hex << std::setfill('0') << std::setw(8)
                    << Data128.Data1 << '-' << std::setw(4) << Data128.Data2
                    << '-' << std::setw(4) << Data128.Data3 << '-';
                for (int i = 0; i < 2; ++i)
                {
                    oss << std::setw(2) << (int) Data128.Data4[i];
                }
                oss << '-';
                for (int i = 2; i < 8; ++i)
                {
                    oss << std::setw(2) << (int) Data128.Data4[i];
                }
                oss << ')';
                break;
            }
        case Format::eHexadecimalBraces:
            {
                // Format: {0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
                oss << '{' << "0x" << std::hex << std::setw(8) << Data128.Data1
                    << ", "
                    << "0x" << std::setw(4) << Data128.Data2 << ", "
                    << "0x" << std::setw(4) << Data128.Data3 << ", {";
                for (int i = 0; i < 8; ++i)
                {
                    oss << "0x" << std::setw(2) << (int) Data128.Data4[i];
                    if (i != 7) oss << ", ";
                }
                oss << "}}";
                break;
            }
        default:
            throw std::invalid_argument("Unknown format type");
    }

    return oss.str();
}

/* ------------------------------- Math impls ------------------------------- */

unsigned int Math::RoundUpPowerOf2(unsigned int n)
{
    if (n == 0)
        return 1;// Edge case: 0 is not a power of 2, return the smallest power of 2
    n--;// Decrease by 1 to handle the case where the number is already a power of 2
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;// For 32-bit integers, this ensures we handle up to 2^32
    return n + 1;
}

unsigned int Math::NextPowerOfTwo(unsigned int v)
{
    if (v == 0) return 1;
    return RoundUpPowerOf2(v);// Reusing the previous function
}

unsigned long long Math::NextPowerOfTwo(unsigned long long v)
{
    if (v == 0) return 1;
    return RoundUpPowerOf2(static_cast<unsigned int>(
            v));// Assuming you cast and use the 32-bit version
}

bool Math::IsPowerOfTwo(unsigned long long n)
{
    return (n > 0) &&
           ((n & (n - 1)) == 0);// If n is a power of 2, n & (n - 1) should be 0
}

bool Math::IsEqual(double d1, double d2)
{
    return IsEqual(d1, d2, DBL_EPSILON);
}

bool Math::IsEqual(float f1, float f2) { return IsEqual(f1, f2, FLT_EPSILON); }

bool Math::IsEqual(double d1, double d2, double tol)
{
    return std::fabs(d1 - d2) <=
           tol;// Compare the absolute difference against the tolerance
}

bool Math::IsEqual(float f1, float f2, float tol)
{
    return std::fabs(f1 - f2) <= tol;
}

double Math::Round(double r, unsigned int place)
{
    double scale = std::pow(10.0, place);
    return std::round(r * scale) / scale;
}

float Math::Round(float r, unsigned int place)
{
    float scale = std::pow(10.0f, place);
    return std::round(r * scale) / scale;
}

double Math::ToRadian(double degree)
{
    return degree * M_PI / 180.0;// Conversion factor: π / 180
}

double Math::ToDegree(double radian)
{
    return radian * 180.0 / M_PI;// Conversion factor: 180 / π
}

double Math::NaN() { return std::numeric_limits<double>::quiet_NaN(); }

float Math::NaNF() { return std::numeric_limits<float>::quiet_NaN(); }

bool Math::IsNaN(double val)
{
    return std::isnan(val);// Standard library function to check for NaN
}

double Math::Pi() { return M_PI; }

std::string Math::NewGUID()
{
    Uuid uuid;
    return uuid.ToString();
}

double Math::Log(double val)
{
    if (val <= 0.0)
    {
        return NaN();// Log of non-positive values is undefined
    }
    return std::log(val);// Natural logarithm function from <cmath>
}

/* ------------------------------ Random impls ------------------------------ */

Random::Random()
{
    srand48(time(nullptr));
    seed48(m_Seed);
}

Random::Random(int seed)
{
    m_Seed[0] = static_cast<unsigned short>(seed & 0xFFFF);
    m_Seed[1] = static_cast<unsigned short>((seed >> 16) & 0xFFFF);
    m_Seed[2] = static_cast<unsigned short>(seed >> 32);
    seed48(m_Seed);
}

Random::Random(unsigned short seed[7])
{
    std::memcpy(m_Seed, seed, sizeof(m_Seed));
    seed48(m_Seed);
}

Random::Random(const Random &rhs)
{
    std::memcpy(m_Seed, rhs.m_Seed, sizeof(m_Seed));
}

Random::Random(Random &&rhs) noexcept
{
    std::memcpy(m_Seed, rhs.m_Seed, sizeof(m_Seed));
}

void Random::Swap(Random &rhs) { std::swap(m_Seed, rhs.m_Seed); }

Random &Random::operator=(Random &&rhs) noexcept
{
    if (this != &rhs) { std::memcpy(m_Seed, rhs.m_Seed, sizeof(m_Seed)); }
    return *this;
}

Random &Random::operator=(const Random &rhs)
{
    if (this != &rhs) { std::memcpy(m_Seed, rhs.m_Seed, sizeof(m_Seed)); }
    return *this;
}

void Random::XSeed(unsigned short seed[3])
{
    std::memcpy(seed, m_Seed, sizeof(m_Seed));
    seed48(m_Seed);
}

const unsigned short *Random::Seed() const { return m_Seed; }

const unsigned short *Random::XSeed() const { return m_Seed; }

int Random::NRand(unsigned short xseed[3]) { return nrand48(xseed); }

int Random::LRand() { return lrand48(); }

int Random::JRand(unsigned short xseed[3]) { return jrand48(xseed); }

int Random::MRand() { return mrand48(); }

double Random::ERand(unsigned short xseed[3]) { return erand48(xseed); }

double Random::DRand() { return drand48(); }

int Random::Next() { return LRand(); }

int Random::Next(int minValue, int maxValue)
{
    return minValue + (Next() % (maxValue - minValue));
}

double Random::Next(double minValue, double maxValue)
{
    return minValue + DRand() * (maxValue - minValue);
}

void Random::NextBytes(unsigned char *bytes, int nLen)
{
    for (int i = 0; i < nLen; ++i)
    {
        bytes[i] = static_cast<unsigned char>(Next(0, 256));
    }
}

double Random::NextDouble() { return DRand(); }

}// namespace CPL