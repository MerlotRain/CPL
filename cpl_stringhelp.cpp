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

#include <cpl_stringhelp.h>
#include <double-conversion/double-conversion.h>
#include <double-conversion/double-to-string.h>
#include <iconv.h>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace CPL {

std::string CodePageToIconvEncoding(CodePageID cp)
{
    static const std::unordered_map<CodePageID, std::string> encodingMap = {
            {            CP_UTF8,       "UTF-8"},
            {         CP_UTF16LE,    "UTF-16LE"},
            {         CP_UTF16BE,    "UTF-16BE"},
            {         CP_UTF32LE,    "UTF-32LE"},
            {         CP_UTF32BE,    "UTF-32BE"},
            {            CP_UTF7,       "UTF-7"},

            {          CP_GB2312,      "GB2312"},
            {             CP_GBK,         "GBK"},
            {         CP_GB18030,     "GB18030"},
            {            CP_BIG5,        "BIG5"},

            {       CP_SHIFT_JIS,   "SHIFT_JIS"},
            {          CP_EUC_JP,      "EUC-JP"},
            {     CP_ISO_2022_JP, "ISO-2022-JP"},

            {          CP_EUC_KR,      "EUC-KR"},
            {     CP_ISO_2022_KR, "ISO-2022-KR"},

            {    CP_WINDOWS_1258,      "CP1258"},

            {      CP_ISO_8859_1,  "ISO-8859-1"},
            {      CP_ISO_8859_2,  "ISO-8859-2"},
            {      CP_ISO_8859_3,  "ISO-8859-3"},
            {      CP_ISO_8859_4,  "ISO-8859-4"},
            {      CP_ISO_8859_5,  "ISO-8859-5"},
            {      CP_ISO_8859_6,  "ISO-8859-6"},
            {      CP_ISO_8859_7,  "ISO-8859-7"},
            {      CP_ISO_8859_8,  "ISO-8859-8"},
            {      CP_ISO_8859_9,  "ISO-8859-9"},
            {     CP_ISO_8859_10, "ISO-8859-10"},
            {     CP_ISO_8859_11, "ISO-8859-11"},
            {     CP_ISO_8859_13, "ISO-8859-13"},
            {     CP_ISO_8859_14, "ISO-8859-14"},
            {     CP_ISO_8859_15, "ISO-8859-15"},
            {     CP_ISO_8859_16, "ISO-8859-16"},

            {    CP_WINDOWS_1250,      "CP1250"},
            {    CP_WINDOWS_1251,      "CP1251"},
            {    CP_WINDOWS_1252,      "CP1252"},
            {    CP_WINDOWS_1253,      "CP1253"},
            {    CP_WINDOWS_1254,      "CP1254"},
            {    CP_WINDOWS_1255,      "CP1255"},
            {    CP_WINDOWS_1256,      "CP1256"},
            {    CP_WINDOWS_1257,      "CP1257"},

            {          CP_KOI8_R,      "KOI8-R"},
            {          CP_KOI8_U,      "KOI8-U"},
            {          CP_KOI8_T,      "KOI8-T"},

            {       CP_MAC_ROMAN,    "MACROMAN"},
            {    CP_MAC_CYRILLIC, "MACCYRILLIC"},
            {       CP_MAC_GREEK,    "MACGREEK"},
            {     CP_MAC_TURKISH,  "MACTURKISH"},
            {     CP_MAC_ICELAND,  "MACICELAND"},

            {         CP_TIS_620,     "TIS-620"},
            {          CP_VISCII,      "VISCII"},
            {       CP_HZ_GB2312,          "HZ"},

            {CP_ISCII_DEVANAGARI,   "ISCII-DEV"},
            {   CP_ISCII_BENGALI,   "ISCII-BEN"},
            {     CP_ISCII_TAMIL,   "ISCII-TAM"},
            {    CP_ISCII_TELUGU,   "ISCII-TEL"},
            {  CP_ISCII_GUJARATI,   "ISCII-GUJ"},
            { CP_ISCII_MALAYALAM,   "ISCII-MAL"}
    };

    auto it = encodingMap.find(cp);
    if (it != encodingMap.end()) { return it->second; }

    return "";
}

CodePageID LocalCodePage()
{
#ifdef _WIN32
    return (CodePageID) (GetACP());
#else
    return CP_UTF8;
#endif
}

/* ------------------------------- CW2A impls ------------------------------- */

CW2A::CW2A(const wchar_t *str) { Init(str, "UTF-8"); }

CW2A::CW2A(const wchar_t *str, CodePageID eCodePage) { Init(str, eCodePage); }

CW2A::CW2A(const wchar_t *str, const char *codepage) { Init(str, codepage); }

CW2A::CW2A(const std::wstring &str)
{
    Init(str.c_str(), "UTF-8");// Default to UTF-8 code page
}

CW2A::CW2A(const std::wstring &str, CodePageID eCodePage)
{
    Init(str.c_str(), eCodePage);
}

CW2A::CW2A(const std::wstring &str, const char *codepage)
{
    Init(str.c_str(), codepage);
}

CW2A::~CW2A() throw()
{
    // No dynamic memory allocation to clean up
}

CW2A::operator const char *() const { return m_Str.c_str(); }

CW2A::operator std::string() const { return m_Str; }

bool CW2A::Init(const wchar_t *str, const char *codepage)
{
    // Open iconv descriptor
    iconv_t cd = iconv_open(codepage,
                            sizeof(wchar_t) == 2 ? "UTF-16LE" : "UTF-32LE");
    if (cd == (iconv_t) -1)
    {
        return false;// Failed to open iconv
    }

    // Length of wide-character string in bytes
    size_t inBytes = std::wcslen(str) * sizeof(wchar_t);
    // Assuming the worst case: UTF-8 encoding could take up to 4 times the bytes
    size_t outBytes = inBytes * 4;

    // Allocate buffer for output narrow string
    char *outBuf = new char[outBytes];
    char *inBuf = reinterpret_cast<char *>(const_cast<wchar_t *>(str));

    char *outPtr = outBuf;
    char *inPtr = inBuf;

    // Perform the conversion
    size_t result = iconv(cd, &inPtr, &inBytes, &outPtr, &outBytes);
    if (result == (size_t) -1)
    {
        iconv_close(cd);
        delete[] outBuf;
        return false;// Conversion failed
    }

    // Store the converted string
    m_Str.assign(outBuf, outPtr - outBuf);

    // Clean up
    iconv_close(cd);
    delete[] outBuf;
    return true;
}

bool CW2A::Init(const wchar_t *str, CodePageID eCodePage)
{
    // For simplicity, assume we convert to UTF-8 by default
    return Init(str, "UTF-8");
}

CW2A &CW2A::operator=(const CW2A &rhs)
{
    m_Str = rhs.m_Str;
    return *this;
}

/* ------------------------------- CA2W impls ------------------------------- */

CA2W::CA2W(const char *str)
{
    Init(str, "UTF-8");// Default to UTF-8 code page
}

CA2W::CA2W(const char *str, CodePageID eCodePage) { Init(str, eCodePage); }

CA2W::CA2W(const char *str, const char *codepage) { Init(str, codepage); }

CA2W::CA2W(const std::string &str)
{
    Init(str.c_str(), "UTF-8");// Default to UTF-8 code page
}

CA2W::CA2W(const std::string &str, CodePageID eCodePage)
{
    Init(str.c_str(), eCodePage);
}

CA2W::CA2W(const std::string &str, const char *codepage)
{
    Init(str.c_str(), codepage);
}

CA2W::~CA2W() throw()
{
    // No dynamic memory management is needed here, as all memory is handled in the conversion.
}

CA2W::operator const wchar_t *() const { return m_WStr.c_str(); }

CA2W::operator std::wstring() const { return m_WStr; }

bool CA2W::Init(const char *str, const char *codepage)
{
    // Open iconv descriptor for conversion from narrow string to wide string
    iconv_t cd = iconv_open(sizeof(wchar_t) == 2 ? "UTF-16LE" : "UTF-32LE",
                            codepage);
    if (cd == (iconv_t) -1)
    {
        throw std::runtime_error("Failed to open iconv descriptor");
    }

    size_t inBytes =
            std::strlen(str);// Length of narrow-character string in bytes
    size_t outBytes =
            inBytes * 2;// Assuming worst case for UTF-16 or other encodings

    // Allocate buffer for output wide string (wchar_t)
    char *outBuf = new char[outBytes];
    char *inBuf = const_cast<char *>(str);

    char *outPtr = outBuf;
    char *inPtr = inBuf;

    // Perform the conversion
    size_t result = iconv(cd, &inPtr, &inBytes, &outPtr, &outBytes);
    if (result == (size_t) -1)
    {
        iconv_close(cd);
        delete[] outBuf;
        throw std::runtime_error("iconv conversion failed");
    }

    // Convert the narrow-character result into a wide string (wchar_t)
    size_t wideLen = (outPtr - outBuf) / sizeof(wchar_t);
    m_WStr.assign(reinterpret_cast<wchar_t *>(outBuf), wideLen);

    // Clean up
    iconv_close(cd);
    delete[] outBuf;

    return true;
}

bool CA2W::Init(const char *str, CodePageID eCodePage)
{
    return Init(
            str,
            CodePageToIconvEncoding(eCodePage)
                    .c_str());// Call the other Init method with the actual code page string
}

CA2W &CA2W::operator=(const CA2W &rhs)
{
    m_WStr = rhs.m_WStr;
    return *this;
}

/* -------------------------------- Encoding -------------------------------- */

std::string Encoding::ToUtf8(const char *str)
{
    if (!str) { throw std::invalid_argument("Input string is null"); }

    CodePageID local_id = LocalCodePage();
    std::string toEncoding = CodePageToIconvEncoding(local_id);

    iconv_t cd = iconv_open("UTF-8", toEncoding.c_str());
    if (cd == (iconv_t) -1) { throw std::runtime_error("iconv_open failed"); }

    size_t inBytesLeft = strlen(str);
    size_t outBytesLeft = inBytesLeft * 4 + 4;
    std::vector<char> outputBuffer(outBytesLeft);

    char *inBuf = const_cast<char *>(str);
    char *outBuf = outputBuffer.data();
    char *outBufStart = outBuf;

    if (iconv(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft) == (size_t) -1)
    {
        iconv_close(cd);
        throw std::runtime_error("iconv conversion failed");
    }

    iconv_close(cd);
    return std::string(outBufStart, outBuf - outBufStart);
}

std::string Encoding::ToUtf8(const wchar_t *str)
{
    CW2A cw2a(str);
    return cw2a.m_Str;
}

std::string Encoding::ToLocal(const wchar_t *str)
{
    CW2A cw2a(str);
    return cw2a.m_Str;
}

std::wstring Encoding::Utf8ToUnicode(const char *str)
{
    CA2W ca2w(str);
    return ca2w.m_WStr;
}

std::wstring Encoding::LocalToUnicode(const char *str)
{
    CodePageID local_id = LocalCodePage();
    std::string toEncoding = CodePageToIconvEncoding(local_id);
    CA2W ca2w(str, toEncoding.c_str());
    return ca2w.m_WStr;
}

std::string Encoding::ToLocal(const char *str)
{
    CodePageID local_id = LocalCodePage();
    std::string encoding = CodePageToIconvEncoding(local_id);
    if (!str) { throw std::invalid_argument("Input string is null"); }

    iconv_t cd = iconv_open(encoding.c_str(), "UTF-8");
    if (cd == (iconv_t) -1) { throw std::runtime_error("iconv_open failed"); }

    size_t inBytesLeft = strlen(str);
    size_t outBytesLeft = inBytesLeft * 4 + 4;
    std::vector<char> outputBuffer(outBytesLeft);

    char *inBuf = const_cast<char *>(str);
    char *outBuf = outputBuffer.data();
    char *outBufStart = outBuf;

    if (iconv(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft) == (size_t) -1)
    {
        iconv_close(cd);
        throw std::runtime_error("iconv conversion failed");
    }

    iconv_close(cd);
    return std::string(outBufStart, outBuf - outBufStart);
}

/* ------------------------------- Utf8 impls ------------------------------- */

Utf8::Utf8(const char *ori) : m_Ori(ori) { m_Utf = Encoding::ToUtf8(ori); }

Utf8::Utf8(const std::string &ori) : m_Ori(ori.c_str())
{
    m_Utf = Encoding::ToUtf8(ori.c_str());
}

Utf8::operator const char *() { return m_Utf.c_str(); }

Utf8::operator std::string() { return m_Utf; }

std::string Utf8::Str() { return m_Utf; }


Local::Local(const char *ori) : m_Ori(ori) { m_Utf = Encoding::ToLocal(ori); }

Local::Local(const std::string &ori) : m_Ori(ori.c_str())
{
    m_Utf = Encoding::ToLocal(ori.c_str());
}

Local::operator const char *() { return m_Utf.c_str(); }

Local::operator std::string() { return m_Utf; }

std::string Local::Str() { return m_Utf; }

/* ---------------------------- StringHelp impls ---------------------------- */

static void floatToStr(char *buffer, int bufferSize, float value,
                       int lowDec = -std::numeric_limits<float>::digits10,
                       int highDec = std::numeric_limits<float>::digits10)
{
    using namespace double_conversion;

    StringBuilder builder(buffer, bufferSize);
    int flags = DoubleToStringConverter::UNIQUE_ZERO |
                DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;
    DoubleToStringConverter dc(flags, "inf", "nan", 'e', lowDec, highDec, 0, 0);
    dc.ToShortestSingle(value, &builder);
    builder.Finalize();
}

static void doubleToStr(char *buffer, int bufferSize, double value,
                        int lowDec = -std::numeric_limits<double>::digits10,
                        int highDec = std::numeric_limits<double>::digits10)
{
    using namespace double_conversion;

    StringBuilder builder(buffer, bufferSize);
    int flags = DoubleToStringConverter::UNIQUE_ZERO |
                DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;
    DoubleToStringConverter dc(flags, "inf", "nan", 'e', lowDec, highDec, 0, 0);
    dc.ToShortest(value, &builder);
    builder.Finalize();
}

static std::string &replaceInPlace(std::string &str,
                                   const std::string::value_type from,
                                   const std::string::value_type to = 0,
                                   std::string::size_type start = 0)
{
    if (from == to) return str;

    std::string::size_type pos = 0;
    do {
        pos = str.find(from, start);
        if (pos != std::string::npos)
        {
            if (to) str[pos] = to;
            else
                str.erase(pos, 1);
        }
    } while (pos != std::string::npos);

    return str;
}

static void pad(std::string &str, int precision, int width, char prefix = ' ',
                char decSep = '.')
{
    // these cases should never happen, if they do, it's a library bug
    assert(precision > 0);
    assert(str.length());

    std::string::size_type decSepPos = str.find(decSep);
    if (decSepPos == std::string::npos)
    {
        str.append(1, decSep);
        decSepPos = str.size() - 1;
    }

    std::string::size_type frac = str.length() - decSepPos - 1;

    std::string::size_type ePos = str.find_first_of("eE");
    std::unique_ptr<std::string> eStr;
    if (ePos != std::string::npos)
    {
        eStr.reset(new std::string(str.substr(ePos, std::string::npos)));
        frac -= eStr->length();
        str = str.substr(0, str.length() - eStr->length());
    }

    if (frac != precision)
    {
        if (frac < precision) { str.append(precision - frac, '0'); }
        else if ((frac > precision) && (decSepPos != std::string::npos))
        {
            int pos = static_cast<int>(decSepPos) + 1 + precision;
            if (str[pos] >= '5')// we must round up
            {
                char carry = 0;
                if (str[--pos] == '9')
                {
                    str[pos] = '0';
                    carry = 1;
                }
                else
                {
                    ++str[pos];
                    carry = 0;
                }
                while (--pos >= 0)
                {
                    if (str[pos] == decSep) continue;
                    if (carry)
                    {
                        if ((str[pos] + carry) <= '9')
                        {
                            ++str[pos];
                            carry = 0;
                        }
                        else
                        {
                            str[pos] = '0';
                            carry = 1;
                        }
                    }
                }
                if (carry) str.insert(str.begin(), 1, '1');
            }
            str = str.substr(0, decSepPos + 1 + precision);
        }
    }

    if (eStr.get()) str += *eStr;

    if (width && (str.length() < width))
        str.insert(str.begin(), width - str.length(), prefix);
}


static void insertThousandSep(std::string &str, char thSep, char decSep = '.')
{
    assert(decSep != thSep);
    if (str.size() == 0) return;

    std::string::size_type exPos = str.find('e');
    if (exPos == std::string::npos) exPos = str.find('E');
    std::string::size_type decPos = str.find(decSep);
    // there's no rinsert, using forward iterator to go backwards
    std::string::iterator it = str.end();
    if (exPos != std::string::npos) it -= str.size() - exPos;

    if (decPos != std::string::npos)
    {
        while (it != str.begin())
        {
            --it;
            if (*it == decSep) break;
        }
    }
    int thCount = 0;
    if (it == str.end()) --it;
    for (; it != str.begin();)
    {
        std::string::iterator pos = it;
        std::string::value_type chr = *it;
        std::string::value_type prevChr = *--it;

        if (!std::isdigit(chr)) continue;

        if (++thCount == 3 && std::isdigit(prevChr))
            it = str.insert(pos, thSep);

        if (thCount == 3) thCount = 0;
    }
}


int StringHelp::Compare(const char *strA, const char *strB, bool bIgnoreCase)
{
    if (!strA || !strB) { return (strA == strB) ? 0 : (strA ? 1 : -1); }
    if (bIgnoreCase) { return CompareNoCase(strA, strB); }
    return strcmp(strA, strB);
}

int StringHelp::CompareNoCase(const char *strA, const char *strB)
{
#if defined(_WIN32) || defined(_WIN64)
    return _stricmp(strA, strB);
#else
    return strcasecmp(strA, strB);
#endif
}

bool StringHelp::IsEqual(const char *strA, const char *strB, bool bIgnoreCase)
{
    if (!strA || !strB) { return strA == strB; }
    if (bIgnoreCase) { return CompareNoCase(strA, strB) == 0; }
    return strcmp(strA, strB) == 0;
}

std::string StringHelp::ToString(const char *str)
{
    return str ? std::string(str) : std::string();
}

std::string StringHelp::ToString(char v) { return std::string(1, v); }

std::string StringHelp::ToString(unsigned char v)
{
    return std::string(1, static_cast<char>(v));
}

std::string StringHelp::ToString(short v) { return std::to_string(v); }

std::string StringHelp::ToString(unsigned short v) { return std::to_string(v); }

std::string StringHelp::ToString(int v) { return std::to_string(v); }

std::string StringHelp::ToString(unsigned int v) { return std::to_string(v); }

std::string StringHelp::ToString(long long v) { return std::to_string(v); }

std::string StringHelp::ToString(unsigned long long v)
{
    return std::to_string(v);
}

std::string StringHelp::ToString(float v, int precision, int width, char thSep,
                                 char decSep)
{
    std::string str;
    if (!decSep) decSep = '.';
    if (precision == 0) v = std::floor(v);

    char buffer[780];
    floatToStr(buffer, 780, v);
    str = buffer;

    if (decSep && (decSep != '.') && (str.find('.') != std::string::npos))
        replaceInPlace(str, '.', decSep);

    if (thSep) insertThousandSep(str, thSep, decSep);
    if (precision > 0 || width)
        pad(str, precision, width, ' ', decSep ? decSep : '.');
    return str;
}

std::string StringHelp::ToString(double v, int precision, int width, char thSep,
                                 char decSep)
{
    std::string str;
    if (!decSep) decSep = '.';
    if (precision == 0) v = std::floor(v);

    char buffer[780];
    doubleToStr(buffer, 780, v);

    str = buffer;

    if (decSep && (decSep != '.') && (str.find('.') != std::string::npos))
        replaceInPlace(str, '.', decSep);

    if (thSep) insertThousandSep(str, thSep, decSep);
    if (precision > 0 || width)
        pad(str, precision, width, ' ', decSep ? decSep : '.');
    return str;
}

std::string StringHelp::ToString(bool v) { return v ? "true" : "false"; }

std::string StringHelp::ToString(const unsigned char *blob, int nLen)
{
    return std::string(reinterpret_cast<const char *>(blob), nLen);
}

std::string StringHelp::Format(int nMaxLen, const char *format, ...)
{
    if (!format || nMaxLen <= 0) { return ""; }

    std::string result;
    result.resize(nMaxLen);

    va_list args;
    va_start(args, format);
    int len = std::vsnprintf(result.data(), nMaxLen + 1, format, args);
    va_end(args);

    if (len < 0) { return ""; }

    if (len > nMaxLen) { len = nMaxLen; }

    result.resize(len);
    return result;
}

bool StringHelp::IsNullOrEmpty(const char *str)
{
    return str == nullptr || *str == '\0';
}

bool StringHelp::IsNullOrEmpty(const wchar_t *str)
{
    return str == nullptr || *str == L'\0';
}

std::vector<std::string> StringHelp::Split(const char *str, const char *strSep)
{
    std::vector<std::string> result;

    if (!str || !strSep || *str == '\0' || *strSep == '\0') { return result; }

    const char *start = str;
    const char *pos = nullptr;

    while ((pos = std::strstr(start, strSep)) != nullptr)
    {
        result.emplace_back(start, pos - start);
        start = pos + std::strlen(strSep);
    }

    result.emplace_back(start);
    return result;
}

std::vector<std::string> StringHelp::Split(const char *str, char sp)
{
    std::vector<std::string> result;

    if (!str || *str == '\0') { return result; }

    const char *start = str;
    const char *pos = nullptr;

    while ((pos = std::strchr(start, sp)) != nullptr)
    {
        result.emplace_back(start, pos - start);
        start = pos + 1;
    }

    result.emplace_back(start);
    return result;
}

std::string StringHelp::Replace(const char *str, const char *src,
                                const char *dst)
{
    if (!str || !src || !dst || *str == '\0' || *src == '\0')
    {
        return str ? std::string(str) : std::string();
    }

    std::string result;
    const char *start = str;
    const char *pos = nullptr;
    size_t srcLen = std::strlen(src);
    size_t dstLen = std::strlen(dst);

    while ((pos = std::strstr(start, src)) != nullptr)
    {
        result.append(start, pos - start);
        result.append(dst);
        start = pos + srcLen;
    }

    result.append(start);
    return result;
}

std::string StringHelp::Trim(const char *str) { return std::string(); }

std::string StringHelp::TrimLeft(const char *str) { return std::string(); }

std::string StringHelp::TrimRight(const char *str) { return std::string(); }

bool StringHelp::StartWith(const char *str, const char *strHead,
                           bool bIgnoringCase)
{
    return false;
}

bool StringHelp::EndWith(const char *str, const char *strTail,
                         bool bIgnoringCase)
{
    return false;
}

bool StringHelp::IsMatch(const char *pattern, const char *str, bool bIgnoreCase)
{
    return false;
}

bool StringHelp::IsLike(const char *pattern, const char *str, char chEscape)
{
    return false;
}

std::string StringHelp::ToUpper(const char *str) { return std::string(); }

std::string StringHelp::ToLower(const char *str) { return std::string(); }

bool StringHelp::IsIntString(const char *str) { return false; }

bool StringHelp::IsNumberString(const char *str) { return false; }

bool StringHelp::IsFloatString(const char *str) { return false; }

bool StringHelp::IsBoolString(const char *str) { return false; }

bool StringHelp::IsBase64String(const char *str) { return false; }

std::string StringHelp::FromHexString(const char *str) { return std::string(); }

std::string StringHelp::ToHexString(const char *str) { return std::string(); }

bool StringHelp::FromHexString(const char *str, ByteBuffer *pOut)
{
    return false;
}

std::string StringHelp::ToHexString(const unsigned char *blob, int nLen)
{
    return std::string();
}

bool StringHelp::ParseBool(const char *strValue, bool bDefault)
{
    return false;
}

bool StringHelp::TryParse(const char *strValue, bool &val) { return false; }

long long StringHelp::ParseInteger(const char *strValue, long long nDefault)
{
    return 0;
}

bool StringHelp::TryParse(const char *strValue, long long &val)
{
    return false;
}

bool StringHelp::TryParse(const char *strValue, int &val) { return false; }

double StringHelp::ParseFloat(const char *strValue, double fDefault)
{
    return 0.0;
}

bool StringHelp::TryParse(const char *strValue, double &val) { return false; }

bool StringHelp::HasContain(const char *str, char c) { return false; }

bool StringHelp::HasContainAny(const char *str, const char *c) { return false; }

}// namespace CPL