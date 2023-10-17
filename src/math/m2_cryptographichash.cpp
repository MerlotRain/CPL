#include <m2_cryptographichash.h>

// sha1算法
#include "../3rd_party/sha1/sha1.cpp"
// md4,md5算法
#include "../3rd_party/md4/md4.cpp"
#include "../3rd_party/md4/md4.h"
#include "../3rd_party/md5/md5.cpp"
#include "../3rd_party/md5/md5.h"

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

#include "../3rd_party/sha3/KeccakSponge.c"
typedef spongeState hashState;

#include "../3rd_party/sha3/KeccakNISTInterface.c"

typedef spongeState SHA3Context;
typedef HashReturn(SHA3Init)(hashState *state, int hashbitlen);
typedef HashReturn(SHA3Update)(hashState *state, const BitSequence *data,
                               DataLength databitlen);
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

#include "../3rd_party/rfc6234/sha.h"

static int SHA224_256AddLength(SHA256Context *context, unsigned int length);
static int SHA384_512AddLength(SHA512Context *context, unsigned int length);

#include "../3rd_party/rfc6234/sha224-256.c"
#include "../3rd_party/rfc6234/sha384-512.c"

#undef uint64_t
#undef uint32_t
#undef uint68_t
#undef int_least16_t

static inline int SHA224_256AddLength(SHA256Context *context,
                                      unsigned int length)
{
    unsigned int addTemp;
    return SHA224_256AddLengthM(context, length);
}
static inline int SHA384_512AddLength(SHA512Context *context,
                                      unsigned int length)
{
    unsigned long long addTemp;
    return SHA384_512AddLengthM(context, length);
}


namespace m2 {

/*******************************************************************************
 * class CryptographicHashPrivate functions
 *******************************************************************************/

class CryptographicHashPrivate
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
    ByteArray result;
};

void CryptographicHashPrivate::sha3Finish(int bitCount, Sha3Variant sha3Variant)
{
    static const unsigned char sha3FinalSuffix = 0x80;

    result.resize(bitCount / 8);

    SHA3Context copy = sha3Context;

    switch (sha3Variant)
    {
        case Sha3Variant::Sha3:
            sha3Update(&copy,
                       reinterpret_cast<const BitSequence *>(&sha3FinalSuffix),
                       2);
            break;
        case Sha3Variant::Keccak:
            break;
    }

    sha3Final(&copy, reinterpret_cast<BitSequence *>(result.data()));
}

/*******************************************************************************
 * class CryptographicHash functions
 *******************************************************************************/

/**
 * @brief Construct a new Cryptographic Hash:: Cryptographic Hash object
 * @param  algorithm        
 */
CryptographicHash::CryptographicHash(HashAlgorithm algorithm)
    : d(new CryptographicHashPrivate)
{
    d->method = algorithm;
    reset();
}

/**
 * @brief Destroy the Cryptographic Hash:: Cryptographic Hash object
 */
CryptographicHash::~CryptographicHash()
{
    if (d) { delete d; }
    d = nullptr;
}

/**
 * @brief 
 */
void CryptographicHash::reset()
{
    switch (d->method)
    {
        case eSHA1:
            sha1InitState(&d->sha1Context);
            break;
        case eMD4:
            md4_init(&d->md4Context);
            break;
        case eMD5:
            MD5Init(&d->md5Context);
            break;
        case eSHA224:
            SHA224Reset(&d->sha224Context);
            break;
        case eSHA256:
            SHA256Reset(&d->sha256Context);
            break;
        case eSHA384:
            SHA384Reset(&d->sha384Context);
            break;
        case eSHA512:
            SHA512Reset(&d->sha512Context);
            break;
        case eREALSHA3_224:
        case eKECCAK_224:
            sha3Init(&d->sha3Context, 224);
            break;
        case eREALSHA3_256:
        case eKECCAK_256:
            sha3Init(&d->sha3Context, 256);
            break;
        case eREALSHA3_384:
        case eKECCAK_384:
            sha3Init(&d->sha3Context, 384);
            break;
        case eREALSHA3_512:
        case eKECCAK_512:
            sha3Init(&d->sha3Context, 512);
            break;
    }
    d->result.clear();
}

/**
 * @brief 
 * @param  data             
 * @param  length           
 */
void CryptographicHash::addData(const char *data, int length)
{
    switch (d->method)
    {
        case eSHA1:
            sha1Update(&d->sha1Context, (const unsigned char *) data, length);
            break;
        case eMD4:
            md4_update(&d->md4Context, (const unsigned char *) data, length);
            break;
        case eMD5:
            MD5Update(&d->md5Context, (const unsigned char *) data, length);
            break;
        case eSHA224:
            SHA224Input(&d->sha224Context,
                        reinterpret_cast<const unsigned char *>(data), length);
            break;
        case eSHA256:
            SHA256Input(&d->sha256Context,
                        reinterpret_cast<const unsigned char *>(data), length);
            break;
        case eSHA384:
            SHA384Input(&d->sha384Context,
                        reinterpret_cast<const unsigned char *>(data), length);
            break;
        case eSHA512:
            SHA512Input(&d->sha512Context,
                        reinterpret_cast<const unsigned char *>(data), length);
            break;
        case eREALSHA3_224:
        case eKECCAK_224:
            sha3Update(&d->sha3Context,
                       reinterpret_cast<const BitSequence *>(data),
                       unsigned long long(length) * 8);
            break;
        case eREALSHA3_256:
        case eKECCAK_256:
            sha3Update(&d->sha3Context,
                       reinterpret_cast<const BitSequence *>(data),
                       unsigned long long(length) * 8);
            break;
        case eREALSHA3_384:
        case eKECCAK_384:
            sha3Update(&d->sha3Context,
                       reinterpret_cast<const BitSequence *>(data),
                       unsigned long long(length) * 8);
            break;
        case eREALSHA3_512:
        case eKECCAK_512:
            sha3Update(&d->sha3Context,
                       reinterpret_cast<const BitSequence *>(data),
                       unsigned long long(length) * 8);
            break;
    }
    d->result.clear();
}

/**
 * @brief 
 * @param  data             
 */
void CryptographicHash::addData(const ByteArray &data)
{
    addData(reinterpret_cast<const char *>(data.constData()), data.size());
}

/**
 * @brief 
 * @param  str              
 */
void CryptographicHash::addData(const String &str)
{
    addData(str.data(), str.length());
}

/**
 * @brief 
 * @return ByteArray 
 */
ByteArray CryptographicHash::result() const
{
    if (!d->result.isEmpty()) return d->result;

    switch (d->method)
    {
        case eSHA1:
            {
                Sha1State copy = d->sha1Context;
                d->result.resize(20);
                sha1FinalizeState(&copy);
                sha1ToHash(&copy, (unsigned char *) d->result.data());
                break;
            }
        case eMD4:
            {
                md4_context copy = d->md4Context;
                d->result.resize(MD4_RESULTLEN);
                md4_final(&copy, (unsigned char *) d->result.data());
                break;
            }
        case eMD5:
            {
                MD5Context copy = d->md5Context;
                d->result.resize(16);
                MD5Final(&copy, (unsigned char *) d->result.data());
                break;
            }
        case eSHA224:
            {
                SHA224Context copy = d->sha224Context;
                d->result.resize(SHA224HashSize);
                SHA224Result(&copy, reinterpret_cast<unsigned char *>(
                                            d->result.data()));
                break;
            }
        case eSHA256:
            {
                SHA256Context copy = d->sha256Context;
                d->result.resize(SHA256HashSize);
                SHA256Result(&copy, reinterpret_cast<unsigned char *>(
                                            d->result.data()));
                break;
            }
        case eSHA384:
            {
                SHA384Context copy = d->sha384Context;
                d->result.resize(SHA384HashSize);
                SHA384Result(&copy, reinterpret_cast<unsigned char *>(
                                            d->result.data()));
                break;
            }
        case eSHA512:
            {
                SHA512Context copy = d->sha512Context;
                d->result.resize(SHA512HashSize);
                SHA512Result(&copy, reinterpret_cast<unsigned char *>(
                                            d->result.data()));
                break;
            }
        case eREALSHA3_224:
            {
                d->sha3Finish(224, CryptographicHashPrivate::Sha3Variant::Sha3);
                break;
            }
        case eREALSHA3_256:
            {
                d->sha3Finish(256, CryptographicHashPrivate::Sha3Variant::Sha3);
                break;
            }
        case eREALSHA3_384:
            {
                d->sha3Finish(384, CryptographicHashPrivate::Sha3Variant::Sha3);
                break;
            }
        case eREALSHA3_512:
            {
                d->sha3Finish(512, CryptographicHashPrivate::Sha3Variant::Sha3);
                break;
            }
        case eKECCAK_224:
            {
                d->sha3Finish(224,
                              CryptographicHashPrivate::Sha3Variant::Keccak);
                break;
            }
        case eKECCAK_256:
            {
                d->sha3Finish(256,
                              CryptographicHashPrivate::Sha3Variant::Keccak);
                break;
            }
        case eKECCAK_384:
            {
                d->sha3Finish(384,
                              CryptographicHashPrivate::Sha3Variant::Keccak);
                break;
            }
        case eKECCAK_512:
            {
                d->sha3Finish(512,
                              CryptographicHashPrivate::Sha3Variant::Keccak);
                break;
            }
    }
    return d->result;
}

/**
 * @brief 
 * @param  data             
 * @param  method           
 * @return ByteArray 
 */
ByteArray CryptographicHash::hash(const ByteArray &data, HashAlgorithm method)
{
    CryptographicHash hash(method);
    hash.addData(data);
    return hash.result();
}

/**
 * @brief 
 * @param  method           
 * @return int 
 */
int CryptographicHash::hashLength(HashAlgorithm method)
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