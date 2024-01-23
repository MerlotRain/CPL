#include <m2_cryptographichash.h>
#include <m2_endian.h>
#include <m2_uuid.h>
#ifdef M2_OS_WIN
#include <Windows.h>
#endif

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

static ByteArray toRfc4122(const UUID &uuid)
{
    ByteArray bytes(16, '\0');
    uint8_t *data = reinterpret_cast<uint8_t *>(bytes.data());

    toBigEndian(uuid.data1, data);
    data += sizeof(uint32_t);
    toBigEndian(uuid.data2, data);
    data += sizeof(uint16_t);
    toBigEndian(uuid.data3, data);
    data += sizeof(uint16_t);

    for (int i = 0; i < 8; ++i)
    {
        *(data) = uuid.data4[i];
        data++;
    }

    return bytes;
}

static UUID fromRfc4122(const ByteArray &bytes)
{
    if (bytes.isEmpty() || bytes.size() != 16) return UUID();

    uint32_t d1;
    uint16_t d2, d3;
    uint8_t d4[8];

    const uint8_t *data = reinterpret_cast<const uint8_t *>(bytes.constData());

    d1 = fromBigEndian<uint32_t>(data);
    data += sizeof(uint32_t);
    d2 = fromBigEndian<uint16_t>(data);
    data += sizeof(uint16_t);
    d3 = fromBigEndian<uint16_t>(data);
    data += sizeof(uint16_t);

    for (int i = 0; i < 8; ++i)
    {
        d4[i] = *(data);
        data++;
    }

    return UUID(d1, d2, d3, d4[0], d4[1], d4[2], d4[3], d4[4], d4[5], d4[6],
                d4[7]);
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
            _m2_fromHex(src, d4[0]) && _m2_fromHex(src, d4[1]) &&
            *src++ == '-' && _m2_fromHex(src, d4[2]) &&
            _m2_fromHex(src, d4[3]) && _m2_fromHex(src, d4[4]) &&
            _m2_fromHex(src, d4[5]) && _m2_fromHex(src, d4[6]) &&
            _m2_fromHex(src, d4[7]))
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
    hash.addData(toRfc4122(ns));
    hash.addData(baseData);
    ByteArray hashResult = hash.result();
    assert(hashResult.size() >= 16);
    hashResult.resize(16);// Sha1 will be too long

    UUID result = fromRfc4122(hashResult);

    result.data3 &= 0x0FFF;
    result.data3 |= (version << 12);
    result.data4[0] &= 0x3F;
    result.data4[0] |= 0x80;

    return result;
}


/*******************************************************************************
 * class UUID functions
 *******************************************************************************/

UUID::UUID() noexcept
    : data1(0), data2(0), data3(0), data4{0, 0, 0, 0, 0, 0, 0, 0}
{
}

UUID::UUID(uint32_t l, uint16_t w1, uint16_t w2, uint8_t b1, uint8_t b2,
           uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7,
           uint8_t b8) noexcept
    : data1(l), data2(w1), data3(w2), data4{b1, b2, b3, b4, b5, b6, b7, b8}
{
}

UUID::UUID(const char *text) : UUID(_m2_uuidFromHex(text)) {}

String UUID::toString() const
{
    char latin1[MAX_UUID_STRING_LENGTH];
    const auto end = _m2_uuidToHex(*this, latin1);
    assert(end - latin1 == MAX_UUID_STRING_LENGTH);
    return String(latin1, MAX_UUID_STRING_LENGTH);
}

String UUID::toString(StringFormat mode) const
{
    char latin1[MAX_UUID_STRING_LENGTH];
    const auto end = _m2_uuidToHex(*this, latin1, mode);
    return String(latin1, end - latin1);
}

ByteArray UUID::toByteArray() const
{
    ByteArray result(MAX_UUID_STRING_LENGTH, '\0');
    const auto end =
            _m2_uuidToHex(*this, const_cast<char *>(result.constData()));
    assert(end - result.constData() == MAX_UUID_STRING_LENGTH);
    return result;
}

ByteArray UUID::toByteArray(StringFormat mode) const
{
    ByteArray result(MAX_UUID_STRING_LENGTH, '\0');
    const auto end =
            _m2_uuidToHex(*this, const_cast<char *>(result.constData()), mode);
    result.resize(end - result.constData());
    return result;
}

bool UUID::isNull() const noexcept
{
    return data4[0] == 0 && data4[1] == 0 && data4[2] == 0 && data4[3] == 0 &&
           data4[4] == 0 && data4[5] == 0 && data4[6] == 0 && data4[7] == 0 &&
           data1 == 0 && data2 == 0 && data3 == 0;
}

bool UUID::operator==(const UUID &orig) const noexcept
{
    if (data1 != orig.data1 || data2 != orig.data2 || data3 != orig.data3)
        return false;

    for (uint32_t i = 0; i < 8; i++)
        if (data4[i] != orig.data4[i]) return false;

    return true;
}

bool UUID::operator!=(const UUID &orig) const noexcept
{
    return !(*this == orig);
}

bool UUID::operator<(const UUID &other) const noexcept
{
    if (variant() != other.variant()) return variant() < other.variant();

#define ISLESS(f1, f2) \
    if (f1 != f2) return (f1 < f2);
    ISLESS(data1, other.data1);
    ISLESS(data2, other.data2);
    ISLESS(data3, other.data3);
    for (int n = 0; n < 8; n++) { ISLESS(data4[n], other.data4[n]); }
#undef ISLESS
    return false;
}

bool UUID::operator>(const UUID &other) const noexcept { return other < *this; }

#ifdef M2_OS_WIN
UUID UUID::createUuid()
{
    GUID guid;
    CoCreateGuid(&guid);
    UUID result;
    result.data1 = guid.Data1;
    result.data2 = guid.Data2;
    result.data3 = guid.Data3;
    for (int i = 0; i < 8; i++) result.data4[i] = guid.Data4[i];
    return result;
}
#else
UUID UUID::createUuid() { return UUID(); }
#endif

UUID::Variant UUID::variant() const noexcept
{
    if (isNull()) return VarUnknown;
    // Check the 3 MSB of data4[0]
    if ((data4[0] & 0x80) == 0x00) return NCS;
    else if ((data4[0] & 0xC0) == 0x80)
        return DCE;
    else if ((data4[0] & 0xE0) == 0xC0)
        return Microsoft;
    else if ((data4[0] & 0xE0) == 0xE0)
        return Reserved;
    return VarUnknown;
}

UUID::Version UUID::version() const noexcept
{
    Version ver = (Version) (data3 >> 12);
    if (isNull() || (variant() != DCE) || ver < Time || ver > Sha1)
        return VerUnknown;
    return ver;
}

}// namespace m2
