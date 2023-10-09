#include <mathhelp.h>
#include <endian.h>
#include <encryption.h>

namespace m2 {

namespace MiscUtils {
inline char toHexUpper(unsigned int value) noexcept
{
    return "0123456789ABCDEF"[value & 0xF];
}

inline char toHexLower(unsigned int value) noexcept
{
    return "0123456789abcdef"[value & 0xF];
}

inline int fromHex(unsigned int c) noexcept
{
    return ((c >= '0') && (c <= '9'))   ? int(c - '0')
           : ((c >= 'A') && (c <= 'F')) ? int(c - 'A' + 10)
           : ((c >= 'a') && (c <= 'f')) ? int(c - 'a' + 10)
                                        :
                                        /* otherwise */ -1;
}

inline char toOct(unsigned int value) noexcept
{
    return '0' + char(value & 0x7);
}

inline int fromOct(unsigned int c) noexcept
{
    return ((c >= '0') && (c <= '7')) ? int(c - '0') : -1;
}
}// namespace MiscUtils

enum
{
    MaxStringUuidLength = 38
};

template<class Integral>
void __toHex(char *&dst, Integral value)
{
    value = EndianConverter::Swap<Integral>(value);

    const char *p = reinterpret_cast<const char *>(&value);

    for (unsigned int i = 0; i < sizeof(Integral); ++i, dst += 2)
    {
        dst[0] = QtMiscUtils::toHexLower((p[i] >> 4) & 0xf);
        dst[1] = QtMiscUtils::toHexLower(p[i] & 0xf);
    }
}

template<class Integral>
bool __fromHex(const char *&src, Integral &value)
{
    value = 0;

    for (unsigned int i = 0; i < sizeof(Integral) * 2; ++i)
    {
        unsigned int ch = *src++;
        int tmp = QtMiscUtils::fromHex(ch);
        if (tmp == -1)
            return false;

        value = value * 16 + tmp;
    }

    return true;
}

static char *__uuidToHex(const UUID &uuid, char *dst, UUID::StringFormat mode = UUID::eHyphens32)
{
    switch (mode)
    {
        case UUID::eHyphens32:
            {
                __toHex(dst, uuid.Data1);
                *dst++ = '-';
                __toHex(dst, uuid.Data2);
                *dst++ = '-';
                __toHex(dst, uuid.Data3);
                *dst++ = '-';
                for (int i = 0; i < 2; i++) __toHex(dst, uuid.Data4[i]);
                *dst++ = '-';
                for (int i = 2; i < 8; i++) __toHex(dst, uuid.Data4[i]);
                break;
            }
        case UUID::eNumber32:
            {
                __toHex(dst, uuid.Data1);
                __toHex(dst, uuid.Data2);
                __toHex(dst, uuid.Data3);
                for (int i = 0; i < 2; i++) __toHex(dst, uuid.Data4[i]);
                for (int i = 2; i < 8; i++) __toHex(dst, uuid.Data4[i]);
                break;
            }
        case UUID::eHyphensBraces:
            {
                *dst++ = '{';
                __toHex(dst, uuid.Data1);
                *dst++ = '-';
                __toHex(dst, uuid.Data2);
                *dst++ = '-';
                __toHex(dst, uuid.Data3);
                *dst++ = '-';
                for (int i = 0; i < 2; i++) __toHex(dst, uuid.Data4[i]);
                *dst++ = '-';
                for (int i = 2; i < 8; i++) __toHex(dst, uuid.Data4[i]);
                *dst++ = '}';
                break;
            }
        case UUID::eHyphensParentheses:
            {
                *dst++ = '(';
                __toHex(dst, uuid.Data1);
                *dst++ = '-';
                __toHex(dst, uuid.Data2);
                *dst++ = '-';
                __toHex(dst, uuid.Data3);
                *dst++ = '-';
                for (int i = 0; i < 2; i++) __toHex(dst, uuid.Data4[i]);
                *dst++ = '-';
                for (int i = 2; i < 8; i++) __toHex(dst, uuid.Data4[i]);
                *dst++ = ')';
                break;
            }
        default:
            break;
    }
    return dst;
}

static UUID __uuidFromHex(const char *src)
{
    unsigned int d1;
    unsigned short d2, d3;
    unsigned char d4[8];

    if (src)
    {
        if (*src == '{')
            src++;
        if (__fromHex(src, d1) && *src++ == '-' && __fromHex(src, d2) && *src++ == '-' &&
            __fromHex(src, d3) && *src++ == '-' && __fromHex(src, d4[0]) && __fromHex(src, d4[1]) &&
            *src++ == '-' && __fromHex(src, d4[2]) && __fromHex(src, d4[3]) && __fromHex(src, d4[4]) &&
            __fromHex(src, d4[5]) && __fromHex(src, d4[6]) && __fromHex(src, d4[7]))
        {
            return UUID(d1, d2, d3, d4[0], d4[1], d4[2], d4[3], d4[4], d4[5], d4[6], d4[7]);
        }
    }

    return UUID();
}

static UUID createFromName(const UUID &ns, const ByteBuffer &baseData,
                             CryptographicHash::HashAlgorithm algorithm, int version)
{
    ByteBuffer hashResult;

    {
        CryptographicHash hash(algorithm);
        hash.AddData(ns.ToRfc4122());
        hash.AddData(baseData);
        hashResult = hash.Result();
    }
    hashResult.ReadSize(16);

    UUID result = UUID::FromRfc4122(hashResult.ReadSize(16));

    result.Data3 &= 0x0FFF;
    result.Data3 |= (version << 12);
    result.Data4[0] &= 0x3F;
    result.Data4[0] |= 0x80;

    return result;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

UUID::UUID() noexcept : Data1(0), Data2(0), Data3(0), Data4{0, 0, 0, 0, 0, 0, 0, 0}
{
}

UUID::UUID(unsigned int l, unsigned short w1, unsigned short w2, unsigned char b1, unsigned char b2,
               unsigned char b3, unsigned char b4, unsigned char b5, unsigned char b6, unsigned char b7,
               unsigned char b8)
    : Data1(l), Data2(w1), Data3(w2), Data4{b1, b2, b3, b4, b5, b6, b7, b8}
{
}

UUID::UUID(const UUID &rhs) noexcept : Data1(rhs.Data1), Data2(rhs.Data2), Data3(rhs.Data3)
{
    std::memcpy(Data4, rhs.Data4, sizeof(Data4));
}

UUID &UUID::operator=(const UUID &rhs) noexcept
{
    if (&rhs != this)
    {
        Data1 = rhs.Data1;
        Data2 = rhs.Data2;
        Data3 = rhs.Data3;
        std::memcpy(Data4, rhs.Data4, sizeof(Data4));
    }
    return *this;
}

bool UUID::operator==(const UUID &orig) const noexcept
{
    if (Data1 != orig.Data1 || Data2 != orig.Data2 || Data3 != orig.Data3)
        return false;

    for (unsigned int i = 0; i < 8; i++)
        if (Data4[i] != orig.Data4[i])
            return false;

    return true;
}

bool UUID::operator!=(const UUID &orig) const noexcept
{
    return !(*this == orig);
}

bool UUID::operator<(const UUID &other) const noexcept
{
    if (Variant() != other.Variant())
        return Variant() < other.Variant();

#define ISLESS(f1, f2) \
    if (f1 != f2)      \
        return (f1 < f2);

    ISLESS(Data1, other.Data1);
    ISLESS(Data2, other.Data2);
    ISLESS(Data3, other.Data3);
    for (int n = 0; n < 8; n++)
    {
        ISLESS(Data4[n], other.Data4[n]);
    }
#undef ISLESS
    return false;
}

bool UUID::operator>(const UUID &other) const noexcept
{
    return other < *this;
}

UUID UUID::CreateUuid()
{
    UUID result;
    unsigned int *data = &(result.Data1);
    enum
    {
        AmountToRead = 4
    };
    Random random;
    result.Data1 = random.LRand48();
    result.Data4[0] = (result.Data4[0] & 0x3F) | 0x80;// UV_DCE
    result.Data3 = (result.Data3 & 0x0FFF) | 0x4000;  // UV_Random

    return result;
}

UUID UUID::CreateUuidV3(const UUID &ns, const String &baseData)
{
    return createFromName(ns, ByteBuffer(baseData.c_str()), CryptographicHash::eMD5, 3);
}

UUID UUID::CreateUuidV5(const UUID &ns, const String &baseData)
{
    return createFromName(ns, ByteBuffer(baseData.c_str()), CryptographicHash::eSHA1, 5);
}

String UUID::ToString(StringFormat format)
{
    char latin1[MaxStringUuidLength];
    const auto end = __uuidToHex(*this, latin1);
    assert(end - latin1 == MaxStringUuidLength);
    return String(latin1, MaxStringUuidLength);
}

bool UUID::IsNull() const noexcept
{
    return Data4[0] == 0 && Data4[1] == 0 && Data4[2] == 0 && Data4[3] == 0 && Data4[4] == 0 &&
           Data4[5] == 0 && Data4[6] == 0 && Data4[7] == 0 && Data1 == 0 && Data2 == 0 && Data3 == 0;
}

UUID::UUIDVariant UUID::Variant() const noexcept
{
    if (IsNull())
        return VarUnknown;
    if ((Data4[0] & 0x80) == 0x00)
        return NCS;
    else if ((Data4[0] & 0xC0) == 0x80)
        return DCE;
    else if ((Data4[0] & 0xE0) == 0xC0)
        return Microsoft;
    else if ((Data4[0] & 0xE0) == 0xE0)
        return Reserved;
    return VarUnknown;
}

UUID::UUIDVersion UUID::Version() const noexcept
{
    UUIDVersion ver = (UUIDVersion) (Data3 >> 12);
    if (IsNull() || (Variant() != DCE) || ver < Time || ver > Sha1)
        return VerUnknown;
    return ver;
}

ByteBuffer UUID::ToRfc4122() const
{
    ByteBuffer buf(16);
    unsigned char *data = reinterpret_cast<unsigned char *>(buf.BufferHead());

    EndianConverter::ToBigEndian(Data1, data);
    data += sizeof(uint32_t);
    EndianConverter::ToBigEndian(Data1, data);
    data += sizeof(uint16_t);
    EndianConverter::ToBigEndian(Data3, data);
    data += sizeof(uint16_t);
    data += sizeof(unsigned short);

    for (int i = 0; i < 8; ++i)
    {
        *(data) = Data4[i];
        data++;
    }

    return buf;
}

UUID UUID::FromRfc4122(const ByteBuffer &bytes)
{
    if (bytes.IsEmpty() || bytes.BufferLength() != 16)
        return UUID();

    unsigned int d1;
    unsigned short d2, d3;
    unsigned char d4[8];

    const unsigned char *data = reinterpret_cast<const unsigned char *>(bytes.BufferHead());

    d1 = EndianConverter::FromBigEndian<uint32_t>(data);
    data += sizeof(unsigned int);
    d2 = EndianConverter::FromBigEndian<uint16_t>(data);
    data += sizeof(unsigned short);
    d3 = EndianConverter::FromBigEndian<uint16_t>(data);
    data += sizeof(unsigned short);

    for (int i = 0; i < 8; ++i)
    {
        d4[i] = *(data);
        data++;
    }

    return UUID(d1, d2, d3, d4[0], d4[1], d4[2], d4[3], d4[4], d4[5], d4[6], d4[7]);
}


}// namespace m2
