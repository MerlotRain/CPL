#include <bytebuffer.h>
#include <cryptographichash.h>

// sha1算法
#include "sha1/sha1.cpp"
// md4,md5算法
#include "md4/md4.cpp"
#include "md4/md4.h"
#include "md5/md5.cpp"
#include "md5/md5.h"

typedef unsigned char BitSequence;
typedef unsigned long long DataLength;
typedef enum
{
    SUCCESS = 0,
    FAIL = 1,
    BAD_HASHLEN = 2
} HashReturn;

#ifdef Q_OS_RTEMS
#undef ALIGN
#endif

#include "sha3/KeccakSponge.c"
typedef spongeState hashState;

#include "sha3/KeccakNISTInterface.c"

typedef spongeState SHA3Context;
typedef HashReturn(SHA3Init)(hashState *state, int hashbitlen);
typedef HashReturn(SHA3Update)(hashState *state, const BitSequence *data, DataLength databitlen);
typedef HashReturn(SHA3Final)(hashState *state, BitSequence *hashval);

static SHA3Init *const sha3Init = Init;
static SHA3Update *const sha3Update = Update;
static SHA3Final *const sha3Final = Final;

#ifdef uint64_t
#undef uint64_t
#endif
#define uint64_t unsigned long long

#ifdef uint32_t
#undef uint32_t
#endif
#define uint32_t unsigned int

#ifdef uint8_t
#undef uint8_t
#endif
#define uint8_t unsigned char

#ifdef int_least16_t
#undef int_least16_t
#endif
#define int_least16_t short

#include "rfc6234/sha.h"

static int SHA224_256AddLength(SHA256Context *context, unsigned int length);
static int SHA384_512AddLength(SHA512Context *context, unsigned int length);

#include "rfc6234/sha224-256.c"
#include "rfc6234/sha384-512.c"

#undef uint64_t
#undef uint32_t
#undef uint68_t
#undef int_least16_t

static inline int SHA224_256AddLength(SHA256Context *context, unsigned int length)
{
    unsigned int addTemp;
    return SHA224_256AddLengthM(context, length);
}
static inline int SHA384_512AddLength(SHA512Context *context, unsigned int length)
{
    unsigned long long addTemp;
    return SHA384_512AddLengthM(context, length);
}


namespace m2 {

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

class CryptographicHashData
{
public:
    CryptographicHash::HashAlgorithm method;
    union
    {
        Sha1State sha1Context;
        MD5Context md5Context;
        md4_context md4Context;
        SHA224Context sha224Context;
        SHA256Context sha256Context;
        SHA384Context sha384Context;
        SHA512Context sha512Context;
        SHA3Context sha3Context;
    };
    enum class Sha3Variant
    {
        Sha3,
        Keccak
    };
    void sha3Finish(int bitCount, Sha3Variant sha3Variant);
    ByteBuffer result;
};

void CryptographicHashData::sha3Finish(int bitCount, Sha3Variant sha3Variant)
{
    static const unsigned char sha3FinalSuffix = 0x80;

    result = result.ReadSize(bitCount / 8);

    SHA3Context copy = sha3Context;

    switch (sha3Variant)
    {
        case Sha3Variant::Sha3:
            sha3Update(&copy, reinterpret_cast<const BitSequence *>(&sha3FinalSuffix), 2);
            break;
        case Sha3Variant::Keccak:
            break;
    }

    sha3Final(&copy, reinterpret_cast<BitSequence *>(result.BufferHead()));
}


//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

CryptographicHash::CryptographicHash(HashAlgorithm algorithm) : m_Data(new CryptographicHashData)
{
    m_Data->method = algorithm;
    Reset();
}

CryptographicHash::~CryptographicHash()
{
}

void CryptographicHash::Reset()
{
    switch (m_Data->method)
    {
        case eSHA1:
            sha1InitState(&m_Data->sha1Context);
            break;
        case eMD4:
            md4_init(&m_Data->md4Context);
            break;
        case eMD5:
            MD5Init(&m_Data->md5Context);
            break;
        case eSHA224:
            SHA224Reset(&m_Data->sha224Context);
            break;
        case eSHA256:
            SHA256Reset(&m_Data->sha256Context);
            break;
        case eSHA384:
            SHA384Reset(&m_Data->sha384Context);
            break;
        case eSHA512:
            SHA512Reset(&m_Data->sha512Context);
            break;
        case eREALSHA3_224:
        case eKECCAK_224:
            sha3Init(&m_Data->sha3Context, 224);
            break;
        case eREALSHA3_256:
        case eKECCAK_256:
            sha3Init(&m_Data->sha3Context, 256);
            break;
        case eREALSHA3_384:
        case eKECCAK_384:
            sha3Init(&m_Data->sha3Context, 384);
            break;
        case eREALSHA3_512:
        case eKECCAK_512:
            sha3Init(&m_Data->sha3Context, 512);
            break;
    }
    m_Data->result.Clear();
}

void CryptographicHash::AddData(const char *data, int length)
{
    switch (m_Data->method)
    {
        case eSHA1:
            sha1Update(&m_Data->sha1Context, (const unsigned char *) data, length);
            break;
        case eMD4:
            md4_update(&m_Data->md4Context, (const unsigned char *) data, length);
            break;
        case eMD5:
            MD5Update(&m_Data->md5Context, (const unsigned char *) data, length);
            break;
        case eSHA224:
            SHA224Input(&m_Data->sha224Context, reinterpret_cast<const unsigned char *>(data), length);
            break;
        case eSHA256:
            SHA256Input(&m_Data->sha256Context, reinterpret_cast<const unsigned char *>(data), length);
            break;
        case eSHA384:
            SHA384Input(&m_Data->sha384Context, reinterpret_cast<const unsigned char *>(data), length);
            break;
        case eSHA512:
            SHA512Input(&m_Data->sha512Context, reinterpret_cast<const unsigned char *>(data), length);
            break;
        case eREALSHA3_224:
        case eKECCAK_224:
            sha3Update(&m_Data->sha3Context, reinterpret_cast<const BitSequence *>(data),
                       unsigned long long(length) * 8);
            break;
        case eREALSHA3_256:
        case eKECCAK_256:
            sha3Update(&m_Data->sha3Context, reinterpret_cast<const BitSequence *>(data),
                       unsigned long long(length) * 8);
            break;
        case eREALSHA3_384:
        case eKECCAK_384:
            sha3Update(&m_Data->sha3Context, reinterpret_cast<const BitSequence *>(data),
                       unsigned long long(length) * 8);
            break;
        case eREALSHA3_512:
        case eKECCAK_512:
            sha3Update(&m_Data->sha3Context, reinterpret_cast<const BitSequence *>(data),
                       unsigned long long(length) * 8);
            break;
    }
    m_Data->result.Clear();
}

void CryptographicHash::AddData(const ByteBuffer &data)
{
    AddData(reinterpret_cast<const char *>(data.BufferHead()), data.BufferLength());
}

void CryptographicHash::AddData(const String &str)
{
    AddData(str.data(), str.length());
}

ByteBuffer CryptographicHash::Result() const
{
    if (!m_Data->result.IsEmpty())
        return m_Data->result;

    switch (m_Data->method)
    {
        case eSHA1:
            {
                Sha1State copy = m_Data->sha1Context;
                m_Data->result = m_Data->result.ReadSize(20);
                sha1FinalizeState(&copy);
                sha1ToHash(&copy, (unsigned char *) m_Data->result.BufferHead());
                break;
            }
        case eMD4:
            {
                md4_context copy = m_Data->md4Context;
                m_Data->result = m_Data->result.ReadSize(MD4_RESULTLEN);
                md4_final(&copy, (unsigned char *) m_Data->result.BufferHead());
                break;
            }
        case eMD5:
            {
                MD5Context copy = m_Data->md5Context;
                m_Data->result = m_Data->result.ReadSize(16);
                MD5Final(&copy, (unsigned char *) m_Data->result.BufferHead());
                break;
            }
        case eSHA224:
            {
                SHA224Context copy = m_Data->sha224Context;
                m_Data->result = m_Data->result.ReadSize(SHA224HashSize);
                SHA224Result(&copy, reinterpret_cast<unsigned char *>(m_Data->result.BufferHead()));
                break;
            }
        case eSHA256:
            {
                SHA256Context copy = m_Data->sha256Context;
                m_Data->result = m_Data->result.ReadSize(SHA256HashSize);
                SHA256Result(&copy, reinterpret_cast<unsigned char *>(m_Data->result.BufferHead()));
                break;
            }
        case eSHA384:
            {
                SHA384Context copy = m_Data->sha384Context;
                m_Data->result = m_Data->result.ReadSize(SHA384HashSize);
                SHA384Result(&copy, reinterpret_cast<unsigned char *>(m_Data->result.BufferHead()));
                break;
            }
        case eSHA512:
            {
                SHA512Context copy = m_Data->sha512Context;
                m_Data->result = m_Data->result.ReadSize(SHA512HashSize);
                SHA512Result(&copy, reinterpret_cast<unsigned char *>(m_Data->result.BufferHead()));
                break;
            }
        case eREALSHA3_224:
            {
                m_Data->sha3Finish(224, CryptographicHashData::Sha3Variant::Sha3);
                break;
            }
        case eREALSHA3_256:
            {
                m_Data->sha3Finish(256, CryptographicHashData::Sha3Variant::Sha3);
                break;
            }
        case eREALSHA3_384:
            {
                m_Data->sha3Finish(384, CryptographicHashData::Sha3Variant::Sha3);
                break;
            }
        case eREALSHA3_512:
            {
                m_Data->sha3Finish(512, CryptographicHashData::Sha3Variant::Sha3);
                break;
            }
        case eKECCAK_224:
            {
                m_Data->sha3Finish(224, CryptographicHashData::Sha3Variant::Keccak);
                break;
            }
        case eKECCAK_256:
            {
                m_Data->sha3Finish(256, CryptographicHashData::Sha3Variant::Keccak);
                break;
            }
        case eKECCAK_384:
            {
                m_Data->sha3Finish(384, CryptographicHashData::Sha3Variant::Keccak);
                break;
            }
        case eKECCAK_512:
            {
                m_Data->sha3Finish(512, CryptographicHashData::Sha3Variant::Keccak);
                break;
            }
    }
    return m_Data->result;
}

ByteBuffer CryptographicHash::Hash(const ByteBuffer &data, HashAlgorithm method)
{
    CryptographicHash hash(method);
    hash.AddData(data);
    return hash.Result();
}

int CryptographicHash::HashLength(HashAlgorithm method)
{
    switch (method)
    {
        case CryptographicHash::eSHA1:
            return 20;
        case CryptographicHash::eMD4:
            return 16;
        case CryptographicHash::eMD5:
            return 16;
        case CryptographicHash::eSHA224:
            return SHA224HashSize;
        case CryptographicHash::eSHA256:
            return SHA256HashSize;
        case CryptographicHash::eSHA384:
            return SHA384HashSize;
        case CryptographicHash::eSHA512:
            return SHA512HashSize;
        case CryptographicHash::eREALSHA3_224:
        case CryptographicHash::eKECCAK_224:
            return 224 / 8;
        case CryptographicHash::eREALSHA3_256:
        case CryptographicHash::eKECCAK_256:
            return 256 / 8;
        case CryptographicHash::eREALSHA3_384:
        case CryptographicHash::eKECCAK_384:
            return 384 / 8;
        case CryptographicHash::eREALSHA3_512:
        case CryptographicHash::eKECCAK_512:
            return 512 / 8;
    }
    return 0;
}


}// namespace m2
