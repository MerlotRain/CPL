#include <crthelp.h>
#include <errno.h>
#include <iconv.h>
#include <logger.h>
#include <string.h>
#include <stringhelp.h>

namespace m2 {

static bool bHaveWarned1 = false;
static bool bHaveWarned2 = false;

static const char *fix_input_encoding(const char *srcEncoding, int nVal)
{
    if (GsCRT::stricmp(srcEncoding, GsTextConverter::ENCODING_UCS2))
        srcEncoding = "UCS-2LE";
    else if (GsCRT::stricmp(srcEncoding, GsTextConverter::ENCODING_UTF16) &&
             nVal != 0xFF && nVal != 0xFE && nVal != 0xFFFE && nVal != 0xFEFF)
    {
        srcEncoding = "UTF-16LE";
    }
    return srcEncoding;
}

static char *Strdup(const char *pszString)

{
    if (pszString == nullptr)
        pszString = "";

    const size_t nLen = strlen(pszString);
    char *pszReturn = static_cast<char *>(malloc(nLen + 1));
    memcpy(pszReturn, pszString, nLen + 1);
    return (pszReturn);
}

static int encoding_char_size(const char *encoding)
{
    if (GsCRT::stricmp(encoding, GsTextConverter::ENCODING_UTF8))
        return 1;
}

constexpr size_t RECODE_DSTBUF_SIZE = 32768;

bool GsTextConverter::Convert(const char *src, const char *srcEncoding, const char *dstEncoding, GsString &dst)
{
    srcEncoding = fix_input_encoding(srcEncoding, static_cast<unsigned char>(src[0]));

    iconv_t conv;
    conv = iconv_open(dstEncoding, srcEncoding);
#ifdef __GUNC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif
    if (conv == (iconv_t) (-1))
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
    {
        GS_W << GsString::Format("Recode from %s to %s failed with the error: \"%s\".",
                                 srcEncoding, dstEncoding, strerror(errno));
        dst = Strdup(src);
        return true;
    }

    const char *pszSrcBuf = const_cast<const char *>(src);
    size_t srcLen = strlen(src);
    size_t dstCurLen = std::max(srcLen, RECODE_DSTBUF_SIZE);
    size_t dstLen = dstCurLen;
    char *pszDestination = static_cast<char *>(calloc(dstCurLen + 1, sizeof(char)));
    char *pszDstBuf = pszDestination;
    while (srcLen > 0)
    {
        size_t nConverted = iconv(conv, &pszSrcBuf, &srcLen, &pszDstBuf, &dstLen);
        if (nConverted == static_cast<size_t>(-1))
        {
            if (errno == EILSEQ)
            {
                if (!bHaveWarned1)
                {
                    bHaveWarned1 = true;
                    GS_W << GsString::Format("One or several characters couldn't be converted "
                                             "correctly from %s to %s.  "
                                             "This warning will not be emitted anymore",
                                             srcEncoding, dstEncoding)
                                    .c_str();
                }
                if (srcLen == 0)
                    break;
                srcLen--;
                pszSrcBuf++;
                continue;
            }
            else if (errno == E2BIG)
            {
                size_t tmp = dstCurLen;
                dstCurLen *= 2;
                pszDestination = static_cast<char *>(realloc(pszDestination, dstCurLen + 1));
                pszDstBuf = pszDestination + tmp - dstLen;
                dstLen += tmp;
                continue;
            }
            else
                break;
        }
    }
    pszDestination[dstCurLen - dstLen] = '\0';
    iconv_close(conv);
    dst.assign(pszDestination);
    return true;
}

bool GsTextConverter::Convert(const GsString &src, const char *srcEncoding, const char *dstEncoding, GsString &dst)
{
    return GsTextConverter::Convert(src.c_str(), srcEncoding, dstEncoding, dst);
}

bool GsTextConverter::Convert(const wchar_t *src, const char *srcEncoding, const char *dstEncoding, GsString &dst)
{
    srcEncoding = fix_input_encoding(srcEncoding, src[0]);
    // source length
    size_t srcLen = 0;
    while (src[srcLen] != 0)
        srcLen++;

    const int nTagCharWidth = encoding_char_size(srcEncoding);
    if (nTagCharWidth < 1)
    {
        GS_W << GsString::Format("Recode from %s with CPLRecodeFromWChar() failed because"
                                 " the width of characters in the encoding are not known.",
                                 srcEncoding)
                        .c_str();
        return false;
    }
    unsigned char *pszIconvSrcBuf = static_cast<unsigned char *>(calloc((srcLen + 1), nTagCharWidth));
    for (unsigned int i = 0; i < srcLen; ++i)
    {
        if (nTagCharWidth == 1)
            pszIconvSrcBuf[i] = static_cast<unsigned char>(src[i]);
        else if (nTagCharWidth == 2)
            (reinterpret_cast<short *>(pszIconvSrcBuf))[i] = static_cast<short>(src[i]);
        else if (nTagCharWidth == 4)
            (reinterpret_cast<int *>(pszIconvSrcBuf))[i] = src[i];
    }

    iconv_t conv;
    conv = iconv_open(dstEncoding, srcEncoding);
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif
    // iconv_t might be a integer or a pointer, so we have to fallback to
    // C-style cast
    if (conv == (iconv_t) (-1))
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
    {
        free(pszIconvSrcBuf);
        GS_W << GsString::Format("Recode from %s to %s failed with the error: \"%s\".",
                                 srcEncoding, dstEncoding, strerror(errno))
                        .c_str();
        return false;
    }

    const char *pszSrcBuf = const_cast<const char *>(reinterpret_cast<char *>(pszIconvSrcBuf));
    srcLen *= nTagCharWidth;

    size_t dstCurLen = std::max(RECODE_DSTBUF_SIZE, srcLen + 1);
    size_t dstLen = dstCurLen;
    char *pszDestination =
            static_cast<char *>(calloc(dstCurLen, sizeof(char)));
    char *pszDstBuf = pszDestination;

    while (srcLen > 0)
    {
        const size_t nConverted =
                iconv(conv, &pszSrcBuf, &srcLen, &pszDstBuf, &dstLen);

        if (nConverted == static_cast<size_t>(-1))
        {
            if (errno == EILSEQ)
            {
                // Skip the invalid sequence in the input string.
                srcLen -= nTagCharWidth;
                pszSrcBuf += nTagCharWidth;
                if (!bHaveWarned2)
                {
                    bHaveWarned2 = true;
                    GS_W << GsString::Format("One or several characters couldn't be converted "
                                             "correctly from %s to %s.  "
                                             "This warning will not be emitted anymore",
                                             srcEncoding, dstEncoding)
                                    .c_str();
                }
                continue;
            }

            else if (errno == E2BIG)
            {
                // We are running out of the output buffer.
                // Dynamically increase the buffer size.
                size_t nTmp = dstCurLen;
                dstCurLen *= 2;
                pszDestination =
                        static_cast<char *>(realloc(pszDestination, dstCurLen));
                pszDstBuf = pszDestination + nTmp - dstLen;
                dstLen += dstCurLen - nTmp;
                continue;
            }

            else
                break;
        }
    }

    if (dstLen == 0)
    {
        ++dstCurLen;
        pszDestination =
                static_cast<char *>(realloc(pszDestination, dstCurLen));
        ++dstLen;
    }
    pszDestination[dstCurLen - dstLen] = '\0';

    iconv_close(conv);
    free(pszIconvSrcBuf);
    dst.assign(pszDestination);
    return true;
}

bool GsTextConverter::Convert(const GsWString &src, const char *srcEncoding, const char *dstEncoding, GsString &dst)
{
    return GsTextConverter::Convert(src.c_str(), srcEncoding, dstEncoding, dst);
}

bool GsTextConverter::Convert(const char *src, const char *srcEncoding, const char *dstEncoding, GsWString &dst)
{
    GsString tmp;
    Convert(src, srcEncoding, dstEncoding, tmp);
    dst.assign(reinterpret_cast<const wchar_t *>(tmp.data()));
}

bool GsTextConverter::Convert(const GsString &src, const char *srcEncoding, const char *dstEncoding, GsWString &dst)
{
    return GsTextConverter::Convert(src.c_str(), srcEncoding, dstEncoding, dst);
}

bool GsTextConverter::Convert(const GsString &str, GsWString &wstr)
{
    return GsTextConverter::Convert(str, GsTextConverter::ENCODING_UTF8, GsTextConverter::ENCODING_UTF16, wstr);
}

bool GsTextConverter::Convert(const char *str, GsWString &wstr)
{
    return GsTextConverter::Convert(str, GsTextConverter::ENCODING_UTF8, GsTextConverter::ENCODING_UTF16, wstr);
}

bool GsTextConverter::Convert(const GsWString &wstr, GsString &str)
{
    return GsTextConverter::Convert(wstr, GsTextConverter::ENCODING_UTF16, GsTextConverter::ENCODING_UTF8, str);
}

bool GsTextConverter::Convert(const wchar_t *wstr, GsString &str)
{
    return GsTextConverter::Convert(wstr, GsTextConverter::ENCODING_UTF16, GsTextConverter::ENCODING_UTF8, str);
}

}// namespace m2
