#include <m2_cryptographichash.h>
#include <m2_endian.h>
#include <m2_uuid.h>


namespace MiscUtils {
constexpr inline char toHexUpper(uint32_t value) noexcept
{
    return "0123456789ABCDEF"[value & 0xF];
}

constexpr inline char toHexLower(uint32_t value) noexcept
{
    return "0123456789abcdef"[value & 0xF];
}

constexpr inline int fromHex(uint32_t c) noexcept
{
    return ((c >= '0') && (c <= '9'))   ? int(c - '0')
           : ((c >= 'A') && (c <= 'F')) ? int(c - 'A' + 10)
           : ((c >= 'a') && (c <= 'f')) ? int(c - 'a' + 10)
                                        :
                                        /* otherwise */ -1;
}

constexpr inline char toOct(uint32_t value) noexcept
{
    return char('0' + (value & 0x7));
}

constexpr inline int fromOct(uint32_t c) noexcept
{
    return ((c >= '0') && (c <= '7')) ? int(c - '0') : -1;
}

constexpr inline char toAsciiLower(char ch) noexcept
{
    return (ch >= 'A' && ch <= 'Z') ? ch - 'A' + 'a' : ch;
}

constexpr inline char toAsciiUpper(char ch) noexcept
{
    return (ch >= 'a' && ch <= 'z') ? ch - 'a' + 'A' : ch;
}

constexpr inline int caseCompareAscii(char lhs, char rhs) noexcept
{
    const char lhsLower = MiscUtils::toAsciiLower(lhs);
    const char rhsLower = MiscUtils::toAsciiLower(rhs);
    return int(uint8_t(lhsLower)) - int(uint8_t(rhsLower));
}


}// namespace MiscUtils


namespace m2 {

#define MAX_UUID_STRING_LENGTH 38

template<class Integral>
void _m2_toHex(char *&dst, Integral value)
{
    value = toBigEndian(value);

    const char *p = reinterpret_cast<const char *>(&value);

    for (uint32_t i = 0; i < sizeof(Integral); ++i, dst += 2)
    {
        dst[0] = MiscUtils::toHexLower((p[i] >> 4) & 0xf);
        dst[1] = MiscUtils::toHexLower(p[i] & 0xf);
    }
}

template<class Integral>
bool _m2_fromHex(const char *&src, Integral &value)
{
    value = 0;

    for (uint32_t i = 0; i < sizeof(Integral) * 2; ++i)
    {
        uint32_t ch = *src++;
        int tmp = MiscUtils::fromHex(ch);
        if (tmp == -1) return false;

        value = value * 16 + tmp;
    }

    return true;
}

static char *_m2_uuidToHex(const UUID &uuid, char *dst,
                          UUID::StringFormat mode = UUID::WithBraces)
{
    if ((mode & UUID::WithoutBraces) == 0) *dst++ = '{';
    _m2_toHex(dst, uuid.data1);
    if ((mode & UUID::Id128) != UUID::Id128) *dst++ = '-';
    _m2_toHex(dst, uuid.data2);
    if ((mode & UUID::Id128) != UUID::Id128) *dst++ = '-';
    _m2_toHex(dst, uuid.data3);
    if ((mode & UUID::Id128) != UUID::Id128) *dst++ = '-';
    for (int i = 0; i < 2; i++) _m2_toHex(dst, uuid.data4[i]);
    if ((mode & UUID::Id128) != UUID::Id128) *dst++ = '-';
    for (int i = 2; i < 8; i++) _m2_toHex(dst, uuid.data4[i]);
    if ((mode & UUID::WithoutBraces) == 0) *dst++ = '}';
    return dst;
}

static UUID _m2_uuidFromHex(const char *src)
{
    uint32_t d1;
    uint16_t d2, d3;
    uint8_t d4[8];

    if (src)
    {
        if (*src == '{') src++;
        if (_m2_fromHex(src, d1) && *src++ == '-' && _m2_fromHex(src, d2) &&
            *src++ == '-' && _m2_fromHex(src, d3) && *src++ == '-' &&
            _m2_fromHex(src, d4[0]) && _m2_fromHex(src, d4[1]) && *src++ == '-' &&
            _m2_fromHex(src, d4[2]) && _m2_fromHex(src, d4[3]) &&
            _m2_fromHex(src, d4[4]) && _m2_fromHex(src, d4[5]) &&
            _m2_fromHex(src, d4[6]) && _m2_fromHex(src, d4[7]))
        {
            return UUID(d1, d2, d3, d4[0], d4[1], d4[2], d4[3], d4[4], d4[5],
                        d4[6], d4[7]);
        }
    }

    return UUID();
}

static UUID createFromName(const UUID &ns, const ByteArray &baseData,
                           CryptographicHash::HashAlgorithm algorithm,
                           int version)
{
    CryptographicHash hash(algorithm);
    hash.addData(ns.toRfc4122());
    hash.addData(baseData);
    ByteArray hashResult = hash.result();
    assert(hashResult.size() >= 16);
    hashResult.truncate(16);// Sha1 will be too long

    UUID result = UUID::fromRfc4122(hashResult);

    result.data3 &= 0x0FFF;
    result.data3 |= (version << 12);
    result.data4[0] &= 0x3F;
    result.data4[0] |= 0x80;

    return result;
}


}// namespace m2
