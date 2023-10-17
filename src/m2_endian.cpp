#include <m2_endian.h>

namespace m2 {

template<typename T>
static M2_ALWAYS_INLINE size_t simdSwapLoop(const unsigned char *, size_t,
                                            unsigned char *) noexcept
{
    return 0;
}

template<typename T>
static M2_ALWAYS_INLINE void *bswapLoop(const unsigned char *src, size_t n,
                                        unsigned char *dst) noexcept
{
    if (src != dst)
    {
        size_t s = size_t(src);
        size_t d = size_t(dst);
        if (s < d) assert(s + n <= d);
        else
            assert(d + n <= s);
    }

    size_t i = simdSwapLoop<T>(src, n, dst);

    for (; i < n; i += sizeof(T)) byteSwap(FromUnaligned<T>(src + i), dst + i);
    return dst + i;
}

template<>
void *byteSwap<2>(const void *source, int64_t n, void *dest) noexcept
{
    const unsigned char *src = reinterpret_cast<const unsigned char *>(source);
    unsigned char *dst = reinterpret_cast<unsigned char *>(dest);

    return bswapLoop<uint16_t>(src, n << 1, dst);
}

template<>
void *byteSwap<4>(const void *source, int64_t n, void *dest) noexcept
{
    const unsigned char *src = reinterpret_cast<const unsigned char *>(source);
    unsigned char *dst = reinterpret_cast<unsigned char *>(dest);

    return bswapLoop<uint32_t>(src, n << 2, dst);
}

template<>
void *byteSwap<8>(const void *source, int64_t n, void *dest) noexcept
{
    const unsigned char *src = reinterpret_cast<const unsigned char *>(source);
    unsigned char *dst = reinterpret_cast<unsigned char *>(dest);

    return bswapLoop<uint64_t>(src, n << 3, dst);
}

}// namespace m2
