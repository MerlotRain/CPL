/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#include <dwg/utility/stringhelp.h>
#include <iconv.h>
#include <stdexcept>

String::String() : StlString() {}

String::String(const String &str) : StlString(str) {}

String::String(const StlString &str) : StlString(str) {}

String::String(String *str) : StlString(*str) {}

String::String(const char *str) : StlString(str ? str : "") {}

String::String(char *str) : StlString(str ? str : "") {}

String::String(const char *str, int off, int count)
    : StlString(str + off, count)
{
}

String::String(const char *str, int count) : StlString(str, count) {}

String::String(const char *start, const char *end) : StlString(start, end) {}

String::String(const unsigned char *start, const unsigned char *end)
    : StlString(reinterpret_cast<const char *>(start),
                reinterpret_cast<const char *>(end))
{
}

String::String(int count, char e) : StlString(count, e) {}

String::String(String::const_iterator first, String::const_iterator last)
    : StlString(first, last)
{
}

String::String(String::iterator first, String::iterator last)
    : StlString(first, last)
{
}

String::String(String::reverse_iterator first, String::reverse_iterator last)
    : StlString(first.base(), last.base())
{
}

String::String(String::const_reverse_iterator first,
               String::const_reverse_iterator last)
    : StlString(first.base(), last.base())
{
}

String::~String() = default;

// Static utility function
bool String::IsNullOrEmpty(const char *str) { return !str || *str == '\0'; }

// Assignment operators
String &String::operator=(const char *str)
{
    StlString::operator=(str ? str : "");
    return *this;
}

String &String::operator=(const StlString &str)
{
    StlString::operator=(str);
    return *this;
}

String &String::operator=(const String &str)
{
    StlString::operator=(str);
    return *this;
}

// Element access
String::reference String::operator[](int _Off)
{
    return StlString::operator[](_Off);
}

String::const_reference String::operator[](int _Off) const
{
    return StlString::operator[](_Off);
}

// Conversion operators
String::operator bool() const { return !empty(); }

String::operator const char *() const { return c_str(); }

String &String::operator+=(const char *str)
{
    StlString::operator+=(str);
    return *this;
}

String &String::operator+=(const String &str)
{
    StlString::operator+=(str);
    return *this;
}

// Concatenation operators
String String::operator+(const char *str) const { return String(*this) += str; }

String String::operator+(const String &str) const
{
    return String(*this) += str;
}

String String::operator+(const StlString &str) const
{
    return String(*this) += str.c_str();
}

// String manipulation
String &String::ToUpper()
{
    std::transform(begin(), end(), begin(), ::toupper);
    return *this;
}

String &String::ToLower()
{
    std::transform(begin(), end(), begin(), ::tolower);
    return *this;
}

String &String::Reverse()
{
    std::reverse(begin(), end());
    return *this;
}

String &String::TrimRight()
{
    erase(std::find_if(rbegin(), rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
                  .base(),
          end());
    return *this;
}

String &String::TrimLeft()
{
    erase(begin(), std::find_if(begin(), end(), [](unsigned char ch) {
              return !std::isspace(ch);
          }));
    return *this;
}

String &String::Trim() { return TrimLeft().TrimRight(); }

// Splitting
std::vector<String> String::Split(const char *strSep)
{
    std::vector<String> result;
    Split(strSep, result);
    return result;
}

void String::Split(const char *strSep, std::vector<String> &vecStr)
{
    vecStr.clear();
    const char *start = c_str();
    const char *pos = nullptr;
    size_t sepLen = std::strlen(strSep);

    while ((pos = std::strstr(start, strSep)) != nullptr)
    {
        vecStr.emplace_back(start, pos);
        start = pos + sepLen;
    }

    if (*start) { vecStr.emplace_back(start); }
}


WString::WString() : StlWString() {}

WString::WString(const WString &str) : StlWString(str) {}

WString::WString(const StlWString &str) : StlWString(str) {}

WString::WString(const wchar_t *str) : StlWString(str) {}

WString::WString(wchar_t *str) : StlWString(str) {}

WString::WString(const wchar_t *str, int off, int count)
    : StlWString(str + off, count)
{
}

WString::WString(const wchar_t *str, int count) : StlWString(str, count) {}

WString::WString(const wchar_t *start, const wchar_t *end)
    : StlWString(start, end)
{
}

WString::WString(int count, wchar_t e) : StlWString(count, e) {}

WString::WString(WString::iterator first, WString::iterator last)
    : StlWString(first, last)
{
}

WString::WString(WString::const_iterator first, WString::const_iterator last)
    : StlWString(first, last)
{
}

WString::WString(WString::reverse_iterator first,
                 WString::reverse_iterator last)
    : StlWString(first, last)
{
}

WString::WString(WString::const_reverse_iterator first,
                 WString::const_reverse_iterator last)
    : StlWString(first, last)
{
}

WString::~WString() {}

bool WString::IsNullOrEmpty(const wchar_t *str)
{
    return str == nullptr || *str == L'\0';
}

WString &WString::operator=(const wchar_t *str)
{
    StlWString::operator=(str);
    return *this;
}

WString &WString::operator=(const StlWString &str)
{
    StlWString::operator=(str);
    return *this;
}

WString &WString::operator=(const WString &str)
{
    StlWString::operator=(str);
    return *this;
}

WString::operator bool() const { return !empty(); }

WString &WString::operator+=(const WString &str)
{
    StlWString::operator+=(str);
    return *this;
}

WString &WString::operator+=(const wchar_t *str)
{
    StlWString::operator+=(str);
    return *this;
}

WString WString::operator+(const wchar_t *str) const
{
    return WString(*this) += str;
}

WString WString::operator+(const StlWString &str) const
{
    return WString(*this) += str;
}

WString WString::operator+(const WString &str) const
{
    return WString(*this) += str;
}


CW2A::CW2A(const wchar_t *str)
{
    Init(str, "UTF-8");// Default to UTF-8 code page
}

CW2A::CW2A(const wchar_t *str, CodePageID eCodePage) { Init(str, eCodePage); }

CW2A::CW2A(const wchar_t *str, const char *codepage) { Init(str, codepage); }

CW2A::CW2A(const WString &str)
{
    Init(str.c_str(), "UTF-8");// Default to UTF-8 code page
}

CW2A::CW2A(const WString &str, CodePageID eCodePage)
{
    Init(str.c_str(), eCodePage);
}

CW2A::CW2A(const WString &str, const char *codepage)
{
    Init(str.c_str(), codepage);
}

CW2A::~CW2A() throw()
{
    // No dynamic memory allocation to clean up
}

CW2A::operator const char *() const { return m_Str.c_str(); }

CW2A::operator String() const { return m_Str; }

bool CW2A::Init(const wchar_t *str, const char *codepage)
{
    // Open iconv descriptor
    iconv_t cd = iconv_open(codepage, "WCHAR_T");
    if (cd == (iconv_t) -1)
    {
        return false;// Failed to open iconv
    }

    size_t inBytes = std::wcslen(str) *
                     sizeof(wchar_t);// Length of wide-character string in bytes
    size_t outBytes =
            inBytes *
            4;// Assuming the worst case: UTF-8 encoding could take up to 4 times the bytes

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


CA2W::CA2W(const char *str)
{
    Init(str, "UTF-8");// Default to UTF-8 code page
}

CA2W::CA2W(const char *str, CodePageID eCodePage) { Init(str, eCodePage); }

CA2W::CA2W(const char *str, const char *codepage) { Init(str, codepage); }

CA2W::CA2W(const String &str)
{
    Init(str.c_str(), "UTF-8");// Default to UTF-8 code page
}

CA2W::CA2W(const String &str, CodePageID eCodePage)
{
    Init(str.c_str(), eCodePage);
}

CA2W::CA2W(const String &str, const char *codepage)
{
    Init(str.c_str(), codepage);
}

CA2W::~CA2W() throw()
{
    // No dynamic memory management is needed here, as all memory is handled in the conversion.
}

CA2W::operator const wchar_t *() const { return m_WStr.c_str(); }

CA2W::operator WString() const { return m_WStr; }

bool CA2W::Init(const char *str, const char *codepage)
{
    // Open iconv descriptor for conversion from narrow string to wide string
    iconv_t cd = iconv_open("WCHAR_T", codepage);
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
    // Convert CodePageID to actual codepage string, assuming some predefined mappings
    const char *codepage = "UTF-8";// Default conversion to UTF-8

    // You can add more mappings if needed (for example, to handle different platforms or custom codepages)
    switch (eCodePage)
    {
        case CP_UTF8:// Just an example, assuming CP_UTF8 is a defined enum for UTF-8
            codepage = "UTF-8";
            break;
        case CP_WINDOWS1252:
            codepage = "Windows-1252";
            break;
        case CP_ISO8859_1:
            codepage = "ISO-8859-1";
            break;
            // Add other cases as necessary
    }

    return Init(
            str,
            codepage);// Call the other Init method with the actual code page string
}

CA2W &CA2W::operator=(const CA2W &rhs)
{
    m_WStr = rhs.m_WStr;
    return *this;
}


String Encoding::ToUtf8(const char *str)
{
    return ConvertEncoding(str, "MBCS", "UTF-8");
}

String Encoding::ToUtf8(const wchar_t *str)
{
    return ConvertEncoding(str, "WCHAR_T", "UTF-8");
}

String Encoding::ToLocal(const wchar_t *str)
{
    return ConvertEncoding(str, "WCHAR_T", "MBCS");
}

WString Encoding::Utf8ToUnicode(const char *str)
{
    return ConvertEncoding(str, "UTF-8", "WCHAR_T");
}

WString Encoding::LocalToUnicode(const char *str)
{
    return ConvertEncoding(str, "MBCS", "WCHAR_T");
}

String Encoding::ToLocal(const char *str)
{
    return ConvertEncoding(str, "UTF-8", "MBCS");
}

String Encoding::ConvertEncoding(const char *str, const char *fromEncoding,
                                 const char *toEncoding)
{
    iconv_t conv_desc = iconv_open(toEncoding, fromEncoding);
    if (conv_desc == (iconv_t) -1)
    {
        throw std::runtime_error("Failed to open iconv descriptor");
    }

    size_t inBytesLeft = std::strlen(str);
    size_t outBytesLeft =
            inBytesLeft *
            4;// Allocate sufficient space for the converted string

    std::vector<char> outBuffer(outBytesLeft, 0);
    char *inBuffer = const_cast<char *>(str);
    char *outBufferPtr = outBuffer.data();

    size_t result = iconv(conv_desc, &inBuffer, &inBytesLeft, &outBufferPtr,
                          &outBytesLeft);
    if (result == (size_t) -1)
    {
        iconv_close(conv_desc);
        throw std::runtime_error("iconv conversion failed");
    }

    iconv_close(conv_desc);

    // Return the converted string
    return String(outBuffer.data(), outBuffer.size() - outBytesLeft);
}

WString Encoding::ConvertEncoding(const wchar_t *str, const char *fromEncoding,
                                  const char *toEncoding)
{
    iconv_t conv_desc = iconv_open(toEncoding, fromEncoding);
    if (conv_desc == (iconv_t) -1)
    {
        throw std::runtime_error("Failed to open iconv descriptor");
    }

    size_t inBytesLeft = std::wcslen(str) * sizeof(wchar_t);
    size_t outBytesLeft =
            inBytesLeft *
            2;// Allocate sufficient space for the converted string

    std::vector<char> outBuffer(outBytesLeft, 0);
    char *inBuffer = reinterpret_cast<char *>(const_cast<wchar_t *>(str));
    char *outBufferPtr = outBuffer.data();

    size_t result = iconv(conv_desc, &inBuffer, &inBytesLeft, &outBufferPtr,
                          &outBytesLeft);
    if (result == (size_t) -1)
    {
        iconv_close(conv_desc);
        throw std::runtime_error("iconv conversion failed");
    }

    iconv_close(conv_desc);

    // Return the converted wide string
    return WString(reinterpret_cast<wchar_t *>(outBuffer.data()));
}


Utf8::Utf8(const char *ori) : m_Ori(ori) { m_Utf = Encoding::ToUtf8(ori); }

Utf8::Utf8(const String &ori) : m_Ori(ori.c_str())
{
    m_Utf = Encoding::ToUtf8(ori);
}

Utf8::operator const char *() { return m_Utf.c_str(); }

Utf8::operator String() { return m_Utf; }

String Utf8::Str() { return m_Utf; }


Local::Local(const char *ori) : m_Ori(ori) { m_Utf = Encoding::ToLocal(ori); }

Local::Local(const String &ori) : m_Ori(ori.c_str())
{
    m_Utf = Encoding::ToLocal(ori.c_str());
}

Local::operator const char *() { return m_Utf.c_str(); }

Local::operator String() { return m_Utf; }

String Local::Str() { return m_Utf; }