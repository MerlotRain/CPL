#include <ctime>
#include <m2_random.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <utility>

/**
 * @brief Random
 * 
 *  These functions generate pseudo-random numbers using the linear
 *  congruential algorithm and 48-bit integer arithmetic.
 *
 *  The drand48() and erand48() functions return nonnegative double-
 *  precision floating-point values uniformly distributed over the
 *  interval [0.0, 1.0).
 *
 *  The lrand48() and nrand48() functions return nonnegative long
 *  integers uniformly distributed over the interval [0, 2^31).
 *
 *  The mrand48() and jrand48() functions return signed long integers
 *  uniformly distributed over the interval [-2^31, 2^31).
 *
 *  The srand48(), seed48(), and lcong48() functions are
 *  initialization functions, one of which should be called before
 *  using drand48(), lrand48(), or mrand48().  The functions
 *  erand48(), nrand48(), and jrand48() do not require an
 *  initialization function to be called first.
 *
 *  All the functions work by generating a sequence of 48-bit
 *  integers, Xi, according to the linear congruential formula:
 *
 *      Xn+1 = (aXn + c) mod m, where n >= 0
 *
 *  The parameter m = 2^48, hence 48-bit integer arithmetic is
 *  performed.  Unless lcong48() is called, a and c are given by:
 *
 *      a = 0x5DEECE66D
 *      c = 0xB
 *
 *  The value returned by any of the functions drand48(), erand48(),
 *  lrand48(), nrand48(), mrand48(), or jrand48() is computed by
 *  first generating the next 48-bit Xi in the sequence.  Then the
 *  appropriate number of bits, according to the type of data item to
 *  be returned, is copied from the high-order bits of Xi and
 *  transformed into the returned value.
 *
 *  The functions drand48(), lrand48(), and mrand48() store the last
 *  48-bit Xi generated in an internal buffer.  The functions
 *  erand48(), nrand48(), and jrand48() require the calling program
 *  to provide storage for the successive Xi values in the array
 *  argument xsubi.  The functions are initialized by placing the
 *  initial value of Xi into the array before calling the function
 *  for the first time.
 *
 *  The initializer function srand48() sets the high order 32-bits of
 *  Xi to the argument seedval.  The low order 16-bits are set to the
 *  arbitrary value 0x330E.
 *
 *  The initializer function seed48() sets the value of Xi to the
 *  48-bit value specified in the array argument seed16v.  The
 *  previous value of Xi is copied into an internal buffer and a
 *  pointer to this buffer is returned by seed48().
 *
 *  The initialization function lcong48() allows the user to specify
 *  initial values for Xi, a, and c.  Array argument elements
 *  param[0-2] specify Xi, param[3-5] specify a, and param[6]
 *  specifies c.  After lcong48() has been called, a subsequent call
 *  to either srand48() or seed48() will restore the standard values
 *  of a and c.
 */

namespace m2 {

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

static int __drand48_iterate(unsigned short int xsubi[3],
                             unsigned short int buffer[7])
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

/*******************************************************************************
 * class Random functions
 *******************************************************************************/

/**
 * @brief Construct a new Random:: Random object
 */
Random::Random()
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

/**
 * @brief Construct a new Random:: Random object
 * @param  seed             
 */
Random::Random(int seed)
{
    memset(m_Seed, 0, 7);
    m_Seed[2] = seed >> 16;
    m_Seed[1] = seed & 0xffffl;
    m_Seed[0] = 0x330e;
    m_Seed[6] = 0xb;
}

/**
 * @brief Construct a new Random:: Random object
 * @param  seed             
 */
Random::Random(unsigned short seed[7])
{
    memset(m_Seed, 0, 7);
    memcpy(m_Seed, seed, 7);
}

/**
 * @brief Construct a new Random:: Random object
 * @param  rhs              
 */
Random::Random(const Random &rhs)
{
    memcpy(m_Seed, rhs.m_Seed, 7 * sizeof(unsigned short int));
}

/**
 * @brief Construct a new Random:: Random object
 * @param  rhs              
 */
Random::Random(Random &&rhs) noexcept { std::swap(m_Seed, rhs.m_Seed); }

/**
 * @brief 
 * @param  rhs              
 * @return Random& 
 */
Random &Random::operator=(Random &&rhs) noexcept
{
    std::swap(m_Seed, rhs.m_Seed);
    return *this;
}

/**
 * @brief 
 * @param  rhs              
 * @return Random& 
 */
Random &Random::operator=(const Random &rhs)
{
    memcpy(m_Seed, rhs.m_Seed, 7 * sizeof(unsigned short int));
    return *this;
}

/**
 * @brief Destroy the Random:: Random object
 */
Random::~Random() { free(m_Seed); }

/**
 * @brief 
 * @param  rhs              
 */
void Random::swap(Random &rhs) { std::swap(m_Seed, rhs.m_Seed); }

/**
 * @brief 
 * @return const unsigned short* 
 */
const unsigned short *Random::seed() const
{
    return reinterpret_cast<const unsigned short *>(m_Seed);
}

/**
 * @brief 
 * @return const unsigned short* 
 */
const unsigned short *Random::xseed() const
{
    unsigned short xseed[3] = {0};
    xseed[0] = m_Seed[0];
    xseed[1] = m_Seed[1];
    xseed[2] = m_Seed[2];
    return xseed;
}

/**
 * @brief 
 * @param  seed             
 */
void Random::xseed(unsigned short seed[3])
{
    memcpy(m_Seed, m_Seed + 3 * sizeof(unsigned short int),
           3 * sizeof(unsigned short int));
    m_Seed[2] = seed[2];
    m_Seed[1] = seed[1];
    m_Seed[0] = seed[0];
    m_Seed[6] = 0xb;
}

/**
 * @brief 
 * @return int 
 */
int Random::lRand48() noexcept
{
    if (!m_Seed) return -1;
    unsigned short int xsubi[3] = {m_Seed[0], m_Seed[1], m_Seed[2]};
    return nRand48(xsubi);
}

/**
 * @brief 
 * @param  xseed            
 * @return int 
 */
int Random::nRand48(unsigned short xseed[3]) noexcept
{
    long int result = 0;
    if (__drand48_iterate(xseed, m_Seed) < 0) return -1;

    if (sizeof(unsigned short int) == 2)
        result = xseed[2] << 15 | xseed[1] >> 1;
    else
        result = xseed[2] >> 1;

    return result;
}

/**
 * @brief 
 * @return int 
 */
int Random::mRand48() noexcept
{
    unsigned short int xsubi[3] = {m_Seed[0], m_Seed[1], m_Seed[2]};

    if (__drand48_iterate(xsubi, m_Seed) < 0) return -1;

    int result = (int32_t) ((xsubi[2] << 16) | xsubi[1]);

    return result;
}

/**
 * @brief 
 * @param  xseed            
 * @return int 
 */
int Random::jRand48(unsigned short xseed[3]) noexcept
{
    if (__drand48_iterate(xseed, m_Seed) < 0) return -1;


    long int result = (int32_t) ((xseed[2] << 16) | xseed[1]);

    return result;
}

/**
 * @brief 
 * @return double 
 */
double Random::dRand48() noexcept
{
    double result;
    union ieee754_double temp;

    unsigned short int xsubi[3] = {m_Seed[0], m_Seed[1], m_Seed[2]};
    if (__drand48_iterate(xsubi, m_Seed) < 0) return -1;

    temp.ieee.negative = 0;
    temp.ieee.exponent = IEEE754_DOUBLE_BIAS;
    temp.ieee.mantissa0 = (xsubi[2] << 4) | (xsubi[1] >> 12);
    temp.ieee.mantissa1 = ((xsubi[1] & 0xfff) << 20) | (xsubi[0] << 4);
    result = temp.d - 1.0;

    return result;
}

/**
 * @brief 
 * @param  xseed            
 * @return double 
 */
double Random::eRand48(unsigned short xseed[3]) noexcept
{
    double result;

    union ieee754_double temp;

    if (__drand48_iterate(xseed, m_Seed) < 0) return -1;


    temp.ieee.negative = 0;
    temp.ieee.exponent = IEEE754_DOUBLE_BIAS;
    temp.ieee.mantissa0 = (xseed[2] << 4) | (xseed[1] >> 12);
    temp.ieee.mantissa1 = ((xseed[1] & 0xfff) << 20) | (xseed[0] << 4);

    result = temp.d - 1.0;

    return result;
}

/**
 * @brief 
 * @return int 
 */
int Random::next() { return lRand48(); }

/**
 * @brief 
 * @param  minValue         
 * @param  maxValue         
 * @return int 
 */
int Random::next(int minValue, int maxValue)
{
    return (lRand48() % (maxValue - minValue)) + minValue;
}

/**
 * @brief 
 * @param  minValue         
 * @param  maxValue         
 * @return double 
 */
double Random::next(double minValue, double maxValue)
{
    return dRand48() * (maxValue - minValue) * 0.5;
}

/**
 * @brief 
 * @return double 
 */
double Random::nextDouble() { return dRand48(); }

/**
 * @brief 
 * @param  bytes            
 * @param  nLen             
 */
void Random::nextBytes(unsigned char *bytes, int nLen)
{
    int num = lRand48();
    memset(bytes, num, nLen);
}

}// namespace m2
