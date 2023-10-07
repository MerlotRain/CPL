#include <ctime>
#include <random.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <utility>

namespace Lite {
namespace Utility {

static constexpr unsigned long long int drand48_data_a = 0x5deece66dull;

union ieee754_double
{
    double d;

    struct
    {
#if __CPP_LIB_ENDIAN == BIG_ENDIAN
        unsigned int negative : 1;
        unsigned int exponent : 11;
        unsigned int mantissa0 : 20;
        unsigned int mantissa1 : 32;
#endif
#if __CPP_LIB_ENDIAN == LITTLE_ENDIAN
#if __FLOAT_WORD_ORDER == BIG_ENDIAN
        unsigned int mantissa0 : 20;
        unsigned int exponent : 11;
        unsigned int negative : 1;
        unsigned int mantissa1 : 32;
#else
        unsigned int mantissa1 : 32;
        unsigned int mantissa0 : 20;
        unsigned int exponent : 11;
        unsigned int negative : 1;
#endif
#endif
    } ieee;

    struct
    {
#if __CPP_LIB_ENDIAN == BIG_ENDIAN
        unsigned int negative : 1;
        unsigned int exponent : 11;
        unsigned int quiet_nan : 1;
        unsigned int mantissa0 : 19;
        unsigned int mantissa1 : 32;
#else
#if __FLOAT_WORD_ORDER == BIG_ENDIAN
        unsigned int mantissa0 : 19;
        unsigned int quiet_nan : 1;
        unsigned int exponent : 11;
        unsigned int negative : 1;
        unsigned int mantissa1 : 32;
#else
        unsigned int mantissa1 : 32;
        unsigned int mantissa0 : 19;
        unsigned int quiet_nan : 1;
        unsigned int exponent : 11;
        unsigned int negative : 1;
#endif
#endif
    } ieee_nan;
};

static constexpr int IEEE754_DOUBLE_BIAS = 0x3ff;

static int __drand48_iterate(unsigned short int xsubi[3], unsigned short int buffer[7])
{
    uint64_t X;
    uint64_t result;

    X = (uint64_t) xsubi[2] << 32 | (uint32_t) xsubi[1] << 16 | xsubi[0];

    result = X * drand48_data_a + buffer[6];

    xsubi[0] = result & 0xffff;
    xsubi[1] = (result >> 16) & 0xffff;
    xsubi[2] = (result >> 32) & 0xffff;

    return 0;
}

GsRandom::GsRandom()
{
    memset(m_Seed, 0, 7);
    time_t t;
    ctime(&t);
    t &= 0xffffffffl;

    m_Seed[2] = t >> 16;
    m_Seed[1] = t & 0xffffl;
    m_Seed[0] = 0x330e;
    m_Seed[6] = 0xb;
}

GsRandom::GsRandom(int seed)
{
    memset(m_Seed, 0, 7);
    m_Seed[2] = seed >> 16;
    m_Seed[1] = seed & 0xffffl;
    m_Seed[0] = 0x330e;
    m_Seed[6] = 0xb;
}

GsRandom::GsRandom(unsigned short seed[7])
{
    memset(m_Seed, 0, 7);
    memcpy(m_Seed, seed, 7);
}

GsRandom::GsRandom(const GsRandom &rhs)
{
    memcpy(m_Seed, rhs.m_Seed, 7 * sizeof(unsigned short int));
}

GsRandom::GsRandom(GsRandom &&rhs)
{
    std::swap(m_Seed, rhs.m_Seed);
}

GsRandom &GsRandom::operator=(GsRandom &&rhs)
{
    std::swap(m_Seed, rhs.m_Seed);
    return *this;
}

GsRandom &GsRandom::operator=(const GsRandom &rhs)
{
    memcpy(m_Seed, rhs.m_Seed, 7 * sizeof(unsigned short int));
    return *this;
}

GsRandom::~GsRandom()
{
    free(m_Seed);
}

void GsRandom::Swap(GsRandom &rhs)
{
    std::swap(m_Seed, rhs.m_Seed);
}

const unsigned short *GsRandom::Seed() const
{
    return reinterpret_cast<const unsigned short *>(m_Seed);
}

const unsigned short *GsRandom::XSeed() const
{
    unsigned short xseed[3] = {0};
    xseed[0] = m_Seed[0];
    xseed[1] = m_Seed[1];
    xseed[2] = m_Seed[2];
    return xseed;
}

void GsRandom::XSeed(unsigned short seed[3])
{
    memcpy(m_Seed, m_Seed + 3 * sizeof(unsigned short int), 3 * sizeof(unsigned short int));
    m_Seed[2] = seed[2];
    m_Seed[1] = seed[1];
    m_Seed[0] = seed[0];
    m_Seed[6] = 0xb;
}

int GsRandom::LRand48() noexcept
{
    if (!m_Seed)
        return -1;
    unsigned short int xsubi[3] = {m_Seed[0], m_Seed[1], m_Seed[2]};
    return NRand48(xsubi);
}

int GsRandom::NRand48(unsigned short xseed[3]) noexcept
{
    long int result = 0;
    if (__drand48_iterate(xseed, m_Seed) < 0)
        return -1;

    if (sizeof(unsigned short int) == 2)
        result = xseed[2] << 15 | xseed[1] >> 1;
    else
        result = xseed[2] >> 1;

    return result;
}


int GsRandom::MRand48() noexcept
{
    unsigned short int xsubi[3] = {m_Seed[0], m_Seed[1], m_Seed[2]};

    if (__drand48_iterate(xsubi, m_Seed) < 0)
        return -1;

    int result = (int32_t) ((xsubi[2] << 16) | xsubi[1]);

    return result;
}

int GsRandom::JRand48(unsigned short xseed[3]) noexcept
{
    if (__drand48_iterate(xseed, m_Seed) < 0)
        return -1;


    long int result = (int32_t) ((xseed[2] << 16) | xseed[1]);

    return result;
}

double GsRandom::DRand48() noexcept
{
    double result;
    union ieee754_double temp;

    unsigned short int xsubi[3] = {m_Seed[0], m_Seed[1], m_Seed[2]};
    if (__drand48_iterate(xsubi, m_Seed) < 0)
        return -1;

    temp.ieee.negative = 0;
    temp.ieee.exponent = IEEE754_DOUBLE_BIAS;
    temp.ieee.mantissa0 = (xsubi[2] << 4) | (xsubi[1] >> 12);
    temp.ieee.mantissa1 = ((xsubi[1] & 0xfff) << 20) | (xsubi[0] << 4);
    result = temp.d - 1.0;

    return result;
}

double GsRandom::ERand48(unsigned short xseed[3]) noexcept
{
    double result;

    union ieee754_double temp;

    if (__drand48_iterate(xseed, m_Seed) < 0)
        return -1;


    temp.ieee.negative = 0;
    temp.ieee.exponent = IEEE754_DOUBLE_BIAS;
    temp.ieee.mantissa0 = (xseed[2] << 4) | (xseed[1] >> 12);
    temp.ieee.mantissa1 = ((xseed[1] & 0xfff) << 20) | (xseed[0] << 4);

    result = temp.d - 1.0;

    return result;
}


int GsRandom::Next()
{
    return LRand48();
}

int GsRandom::Next(int minValue, int maxValue)
{
    return (LRand48() % (maxValue - minValue)) + minValue;
}

double GsRandom::Next(double minValue, double maxValue)
{
    return DRand48() * (maxValue - minValue) * 0.5;
}

double GsRandom::NextDouble()
{
    return DRand48();
}

void GsRandom::NextBytes(unsigned char *bytes, int nLen)
{
    int num = LRand48();
    memset(bytes, num, nLen);
}

}// namespace Utility
}// namespace Lite
