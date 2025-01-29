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

#pragma once

#include "cpl_memorymanager.h"
#include <algorithm>
#include <cpl_exports.h>
#include <deque>
#include <iomanip>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace CPL {

/// \brief Encoding IDs for character conversions
enum CodePageID
{
    // Unicode Encodings
    CP_UTF8 = 65001,// UTF-8: Variable-length encoding for Unicode characters.
    CP_UTF16LE =
            1200,// UTF-16 Little Endian: 16-bit encoding with little-endian byte order.
    CP_UTF16BE =
            1201,// UTF-16 Big Endian: 16-bit encoding with big-endian byte order.
    CP_UTF32LE =
            12000,// UTF-32 Little Endian: 32-bit encoding with little-endian byte order.
    CP_UTF32BE =
            12001,// UTF-32 Big Endian: 32-bit encoding with big-endian byte order.
    CP_UTF7 = 65000,// UTF-7: 7-bit encoding mainly used for email transmission.

    // Simplified Chinese Encodings
    CP_GB2312 =
            936,// GB2312: National Standard encoding for Simplified Chinese.
    CP_GBK =
            936,// GBK: Extended version of GB2312, supports more Chinese characters.
    CP_GB18030 =
            54936,// GB18030: Latest Chinese encoding standard, fully compatible with Unicode.

    // Traditional Chinese Encodings
    CP_BIG5 =
            950,// Big5: Traditional Chinese character encoding used in Taiwan and Hong Kong.

    // Japanese Encodings
    CP_SHIFT_JIS =
            932,// Shift JIS: Common encoding for Japanese text, used in Windows and legacy systems.
    CP_EUC_JP =
            20932,// EUC-JP: Encoding used mainly on Unix and Linux systems for Japanese.
    CP_ISO_2022_JP =
            50220,// ISO-2022-JP: 7-bit encoding for Japanese text, often used in emails.

    // Korean Encodings
    CP_EUC_KR = 51949,// EUC-KR: Extended Unix Code for Korean.
    CP_ISO_2022_KR =
            50225,// ISO-2022-KR: 7-bit encoding for Korean, mainly used in emails.

    // ISO 8859 Series (Latin-based Encodings)
    CP_ISO_8859_1 = 28591, // Latin-1 (Western European).
    CP_ISO_8859_2 = 28592, // Latin-2 (Central European).
    CP_ISO_8859_3 = 28593, // Latin-3 (South European).
    CP_ISO_8859_4 = 28594, // Latin-4 (North European).
    CP_ISO_8859_5 = 28595, // Latin/Cyrillic (Russian).
    CP_ISO_8859_6 = 28596, // Latin/Arabic.
    CP_ISO_8859_7 = 28597, // Latin/Greek.
    CP_ISO_8859_8 = 28598, // Latin/Hebrew.
    CP_ISO_8859_9 = 28599, // Latin-5 (Turkish).
    CP_ISO_8859_10 = 28600,// Latin-6 (Nordic).
    CP_ISO_8859_11 = 28601,// Latin/Thai.
    CP_ISO_8859_13 = 28603,// Latin-7 (Baltic).
    CP_ISO_8859_14 = 28604,// Latin-8 (Celtic).
    CP_ISO_8859_15 = 28605,// Latin-9 (Modified Latin-1 with Euro sign).
    CP_ISO_8859_16 = 28606,// Latin-10 (Romanian).

    // Windows Code Pages
    CP_WINDOWS_1250 = 1250,// Windows-1250: Central European languages.
    CP_WINDOWS_1251 =
            1251,// Windows-1251: Cyrillic languages (Russian, Bulgarian, etc.).
    CP_WINDOWS_1252 = 1252,// Windows-1252: Western European languages.
    CP_WINDOWS_1253 = 1253,// Windows-1253: Greek language.
    CP_WINDOWS_1254 = 1254,// Windows-1254: Turkish language.
    CP_WINDOWS_1255 = 1255,// Windows-1255: Hebrew language.
    CP_WINDOWS_1256 = 1256,// Windows-1256: Arabic language.
    CP_WINDOWS_1257 = 1257,// Windows-1257: Baltic languages.
    CP_WINDOWS_1258 = 1258,// Windows-1258: Vietnamese language.

    // Cyrillic Encodings
    CP_KOI8_R = 20866,// KOI8-R: Encoding for Russian text.
    CP_KOI8_U = 21866,// KOI8-U: Encoding for Ukrainian text.
    CP_KOI8_T = 20869,// KOI8-T: Encoding for Tajik text.

    // EBCDIC Code Pages (IBM Mainframe Encodings)
    CP_EBCDIC_US = 37,      // EBCDIC-US (IBM037): Standard US EBCDIC encoding.
    CP_EBCDIC_DE = 20273,   // EBCDIC German (IBM273).
    CP_EBCDIC_DK_NO = 20277,// EBCDIC Danish/Norwegian (IBM277).
    CP_EBCDIC_FI_SE = 20278,// EBCDIC Finnish/Swedish (IBM278).
    CP_EBCDIC_IT = 20280,   // EBCDIC Italian (IBM280).
    CP_EBCDIC_ES = 20284,   // EBCDIC Spanish (IBM284).
    CP_EBCDIC_PT = 20285,   // EBCDIC Portuguese (IBM285).
    CP_EBCDIC_FR = 20297,   // EBCDIC French (IBM297).
    CP_EBCDIC_JP_KANA = 20290,// EBCDIC Japanese Katakana (IBM290).
    CP_EBCDIC_CP500 = 500,    // EBCDIC Multi-language (IBM500).

    // macOS Code Pages
    CP_MAC_ROMAN = 10000,// macOS Roman: Default encoding on old macOS versions.
    CP_MAC_CYRILLIC =
            10007,// macOS Cyrillic: Used for Russian and other Cyrillic scripts.
    CP_MAC_GREEK = 10006,  // macOS Greek: Encoding for the Greek language.
    CP_MAC_TURKISH = 10081,// macOS Turkish: Encoding for the Turkish language.
    CP_MAC_ICELAND =
            10079,// macOS Icelandic: Encoding for the Icelandic language.

    // Other Encodings
    CP_TIS_620 = 620,// TIS-620: Thai language encoding.
    CP_VISCII = 850, // VISCII: Vietnamese encoding used before Unicode.
    CP_HZ_GB2312 =
            52936,// HZ-GB2312: Simplified Chinese encoding, used mainly for email and USENET.
    CP_ISCII_DEVANAGARI =
            57002,// ISCII Devanagari: Indian script for Hindi, Marathi, and Sanskrit.
    CP_ISCII_BENGALI =
            57003,         // ISCII Bengali: Indian script for Bengali language.
    CP_ISCII_TAMIL = 57004,// ISCII Tamil: Indian script for Tamil language.
    CP_ISCII_TELUGU = 57005,// ISCII Telugu: Indian script for Telugu language.
    CP_ISCII_GUJARATI =
            57010,// ISCII Gujarati: Indian script for Gujarati language.
    CP_ISCII_MALAYALAM =
            57011// ISCII Malayalam: Indian script for Malayalam language.
};


/// \brief Class for converting wide-character strings (wchar_t) to narrow-character strings (char)
/// This class is used to convert wide-character strings (wchar_t) to narrow-character strings (char), supporting different code pages.
class CPL_API CW2A
{
public:
    std::string m_Str;///< The resulting narrow-character string (std::string)

    /// \brief Constructor from a wide-character string (const wchar_t*)
    /// \param str A pointer to the wide-character string to convert.
    CW2A(const wchar_t *str);

    /// \brief Constructor from a wide-character string with a specified code page (CodePageID)
    /// \param str A pointer to the wide-character string to convert.
    /// \param eCodePage The code page to use for the conversion.
    CW2A(const wchar_t *str, CodePageID eCodePage);

    /// \brief Constructor from a wide-character string with a specified code page (string format)
    /// \param str A pointer to the wide-character string to convert.
    /// \param codepage The code page to use for the conversion (as a string).
    CW2A(const wchar_t *str, const char *codepage);

    /// \brief Constructor from a std::wstring object
    /// \param str A std::wstring object to convert to a narrow-character string.
    CW2A(const std::wstring &str);

    /// \brief Constructor from a std::wstring object with a specified code page (CodePageID)
    /// \param str A std::wstring object to convert to a narrow-character string.
    /// \param eCodePage The code page to use for the conversion.
    CW2A(const std::wstring &str, CodePageID eCodePage);

    /// \brief Constructor from a std::wstring object with a specified code page (string format)
    /// \param str A std::wstring object to convert to a narrow-character string.
    /// \param codepage The code page to use for the conversion (as a string).
    CW2A(const std::wstring &str, const char *codepage);

    /// \brief Destructor
    /// The destructor releases any allocated resources.
    ~CW2A() throw();

    /// \brief Conversion operator to a C-style narrow-character string (const char*)
    /// \return A pointer to the resulting narrow-character C-string.
    operator const char *() const;

    /// \brief Conversion operator to a std::string object (std::string)
    /// \return The resulting narrow-character string as a std::string object.
    operator std::string() const;

private:
    /// \brief Initializes the conversion from a wide-character string with a specified code page (string format)
    /// \param str A pointer to the wide-character string to convert.
    /// \param codepage The code page to use for the conversion (as a string).
    bool Init(const wchar_t *str, const char *codepage);

    /// \brief Initializes the conversion from a wide-character string with a specified code page (CodePageID)
    /// \param str A pointer to the wide-character string to convert.
    /// \param eCodePage The code page to use for the conversion.
    bool Init(const wchar_t *str, CodePageID eCodePage);

private:
    /// \brief Copy constructor (private to prevent copying)
    CW2A(const CW2A &);

    /// \brief Assignment operator (private to prevent assignment)
    CW2A &operator=(const CW2A &);
};


/// \brief Class for converting narrow-character strings (char) to wide-character strings (wchar_t)
/// This class is used to convert narrow-character strings (char) to wide-character strings (wchar_t), supporting different code pages.
class CPL_API CA2W
{
public:
    std::wstring m_WStr;///< The resulting wide-character string (std::wstring)

    /// \brief Constructor from a narrow-character string (const char*)
    /// \param str A pointer to the narrow-character string to convert.
    CA2W(const char *str);

    /// \brief Constructor from a narrow-character string with a specified code page (CodePageID)
    /// \param str A pointer to the narrow-character string to convert.
    /// \param eCodePage The code page to use for the conversion.
    CA2W(const char *str, CodePageID eCodePage);

    /// \brief Constructor from a narrow-character string with a specified code page (string format)
    /// \param str A pointer to the narrow-character string to convert.
    /// \param codepage The code page to use for the conversion (as a string).
    CA2W(const char *str, const char *codepage);

    /// \brief Constructor from a std::string object (std::string)
    /// \param str A std::string object to convert to a wide-character string.
    CA2W(const std::string &str);

    /// \brief Constructor from a std::string object with a specified code page (CodePageID)
    /// \param str A std::string object to convert to a wide-character string.
    /// \param eCodePage The code page to use for the conversion.
    CA2W(const std::string &str, CodePageID eCodePage);

    /// \brief Constructor from a std::string object with a specified code page (string format)
    /// \param str A std::string object to convert to a wide-character string.
    /// \param codepage The code page to use for the conversion (as a string).
    CA2W(const std::string &str, const char *codepage);

    /// \brief Destructor
    /// The destructor releases any allocated resources.
    ~CA2W() throw();

    /// \brief Conversion operator to a C-style wide-character string (const wchar_t*)
    /// \return A pointer to the resulting wide-character C-string.
    operator const wchar_t *() const;

    /// \brief Conversion operator to a std::wstring object
    /// \return The resulting wide-character string as a std::wstring object.
    operator std::wstring() const;

private:
    /// \brief Initializes the conversion from a narrow-character string with a specified code page (string format)
    /// \param str A pointer to the narrow-character string to convert.
    /// \param codepage The code page to use for the conversion (as a string).
    bool Init(const char *str, const char *codepage);

    /// \brief Initializes the conversion from a narrow-character string with a specified code page (CodePageID)
    /// \param str A pointer to the narrow-character string to convert.
    /// \param eCodePage The code page to use for the conversion.
    bool Init(const char *str, CodePageID eCodePage);

private:
    /// \brief Copy constructor (private to prevent copying)
    CA2W(const CA2W &);

    /// \brief Assignment operator (private to prevent assignment)
    CA2W &operator=(const CA2W &);
};


/// \brief Implements string encoding-related functionalities
class CPL_API Encoding
{
public:
    Encoding() = default;

    /// \brief Converts a local string to a UTF-8 encoded string.
    /// \return Returns the string converted to UTF-8 encoding.
    static std::string ToUtf8(const char *str);

    /// \brief Converts a local Unicode string to a UTF-8 encoded string.
    /// \return Returns the string converted to UTF-8 encoding.
    static std::string ToUtf8(const wchar_t *str);

    /// \brief Converts a local Unicode string to an MBCS (Multi-Byte Character Set) narrow string.
    /// \return Returns the string converted to MBCS narrow encoding.
    static std::string ToLocal(const wchar_t *str);

    /// \brief Converts a UTF-8 narrow string to a Unicode wide string.
    /// \return Returns the string converted to Unicode wide encoding.
    static std::wstring Utf8ToUnicode(const char *str);

    /// \brief Converts a local MBCS narrow string to a Unicode wide string.
    /// \return Returns the string converted to Unicode wide encoding.
    static std::wstring LocalToUnicode(const char *str);

    /// \brief Converts a UTF-8 string to a local string.
    /// \return Returns the string converted to the local encoding.
    static std::string ToLocal(const char *str);
};

/// \brief A class for converting a string to a UTF-8 encoded string.
class CPL_API Utf8
{
    const char *m_Ori;///< Original string (in its native encoding).
    std::string m_Utf;///< UTF-8 encoded string.

public:
    /// \brief Constructor that initializes with a C-style string (const char *).
    /// \param ori The original string to be converted to UTF-8.
    Utf8(const char *ori);

    /// \brief Constructor that initializes with a std::string object.
    /// \param ori The original std::string object to be converted to UTF-8.
    explicit Utf8(const std::string &ori);

    /// \brief Implicit conversion operator to a C-style string (const char *).
    /// \return Returns the UTF-8 encoded string as a C-style string.
    operator const char *();

    /// \brief Implicit conversion operator to a std::string object.
    /// \return Returns the UTF-8 encoded string as a std::string object.
    operator std::string();

    /// \brief Returns the UTF-8 encoded string.
    /// \return Returns the UTF-8 string stored in the object.
    std::string Str();
};


/// \brief A class for converting a string to the local encoding.
class CPL_API Local
{
    const char *m_Ori;///< Original string (in its native encoding).
    std::string m_Utf;///< Local encoded string.

public:
    /// \brief Constructor that initializes with a C-style string (const char *).
    /// \param ori The original string to be converted to the local encoding.
    Local(const char *ori);

    /// \brief Constructor that initializes with a std::string object.
    /// \param ori The original std::string object to be converted to the local encoding.
    Local(const std::string &ori);

    /// \brief Implicit conversion operator to a C-style string (const char *).
    /// \return Returns the string converted to the local encoding as a C-style string.
    operator const char *();

    /// \brief Implicit conversion operator to a std::string object.
    /// \return Returns the string converted to the local encoding as a std::string object.
    operator std::string();

    /// \brief Returns the string in the local encoding.
    /// \return Returns the string stored in the object, converted to the local encoding.
    std::string Str();
};


/// \brief Provides various utility functions for string manipulation.
class CPL_API StringHelp
{
public:
    /// \brief Compares two strings.
    /// \param strA First string.
    /// \param strB Second string.
    /// \param bIgnoreCase Flag to indicate if comparison should ignore case (default: true).
    /// \return Returns the result of the comparison.
    static int Compare(const char *strA, const char *strB,
                       bool bIgnoreCase = true);

    /// \brief Compares two strings, ignoring case.
    /// \param strA First string.
    /// \param strB Second string.
    /// \return Returns the result of the comparison ignoring case.
    static int CompareNoCase(const char *strA, const char *strB);

    /// \brief Checks if two strings are equal.
    /// \param strA First string.
    /// \param strB Second string.
    /// \param bIgnoreCase Flag to indicate if comparison should ignore case (default: true).
    /// \return Returns true if the strings are equal, false otherwise.
    static bool IsEqual(const char *strA, const char *strB,
                        bool bIgnoreCase = true);

    /// \brief Converts a C-style string to a std::string object.
    /// \param str The C-style string.
    /// \return Returns the std::string object.
    static std::string ToString(const char *str);
    /// \brief Converts a char value to a std::string object.
    /// \param v The char value.
    /// \return Returns the std::string object.
    static std::string ToString(char v);
    /// \brief Converts an unsigned char value to a std::string object.
    /// \param v The unsigned char value.
    /// \return Returns the std::string object.
    static std::string ToString(unsigned char v);
    /// \brief Converts a short value to a std::string object.
    /// \param v The short value.
    /// \return Returns the std::string object.
    static std::string ToString(short v);
    /// \brief Converts an unsigned short value to a std::string object.
    /// \param v The unsigned short value.
    /// \return Returns the std::string object.
    static std::string ToString(unsigned short v);
    /// \brief Converts an int value to a std::string object.
    /// \param v The int value.
    /// \return Returns the std::string object.
    static std::string ToString(int v);
    /// \brief Converts an unsigned int value to a std::string object.
    /// \param v The unsigned int value.
    /// \return Returns the std::string object.
    static std::string ToString(unsigned int v);
    /// \brief Converts a long long value to a std::string object.
    /// \param v The long long value.
    /// \return Returns the std::string object.
    static std::string ToString(long long v);
    /// \brief Converts an unsigned long long value to a std::string object.
    /// \param v The unsigned long long value.
    /// \return Returns the std::string object.
    static std::string ToString(unsigned long long v);

    static std::string ToString(float v, int precision = -1, int width = 0,
                                char thSep = 0, char decSep = 0);

    static std::string ToString(double v, int precision = -1, int width = 0,
                                char thSep = 0, char decSep = 0);

    /// \brief Converts a boolean value to a std::string object.
    /// \param v The boolean value.
    /// \return Returns the std::string object.
    static std::string ToString(bool v);

    /// \brief Converts a byte array to a Base64 encoded std::string object.
    /// \param blob The byte array.
    /// \param nLen The length of the byte array.
    /// \return Returns the Base64 encoded std::string object.
    static std::string ToString(const unsigned char *blob, int nLen);

    /// \brief Formats a string according to the specified format and arguments.
    /// \param nMaxLen The maximum length of the resulting string.
    /// \param format The format string.
    /// \return Returns the formatted std::string object.
    static std::string Format(int nMaxLen, const char *format, ...);

    /// \brief Checks if a string is null or empty.
    /// \param str The string to check.
    /// \return Returns true if the string is null or empty, false otherwise.
    static bool IsNullOrEmpty(const char *str);

    /// \brief Checks if a wide string is null or empty.
    /// \param str The wide string to check.
    /// \return Returns true if the wide string is null or empty, false otherwise.
    static bool IsNullOrEmpty(const wchar_t *str);

    /// \brief Splits a string into substrings using a separator.
    /// \param str The string to split.
    /// \param strSep The separator string.
    /// \return Returns a vector of substrings.
    static std::vector<std::string> Split(const char *str, const char *strSep);

    /// \brief Splits a string into substrings using a character separator.
    /// \param str The string to split.
    /// \param sp The separator character.
    /// \return Returns a vector of substrings.
    static std::vector<std::string> Split(const char *str, char sp);

    /// \brief Replaces a substring within a string with a new substring.
    /// \param str The original string.
    /// \param src The substring to be replaced.
    /// \param dst The new substring.
    /// \return Returns the string with replacements.
    static std::string Replace(const char *str, const char *src,
                               const char *dst);

    /// \brief Trims whitespace characters from the beginning of a string.
    /// \param str The string to trim.
    /// \return Returns the trimmed string.
    static std::string Trim(const char *str);

    /// \brief Trims whitespace characters from the left side of a string.
    /// \param str The string to trim.
    /// \return Returns the left-trimmed string.
    static std::string TrimLeft(const char *str);

    /// \brief Trims whitespace characters from the right side of a string.
    /// \param str The string to trim.
    /// \return Returns the right-trimmed string.
    static std::string TrimRight(const char *str);

    /// \brief Checks if a string starts with a specified prefix.
    /// \param str The string to check.
    /// \param strHead The prefix.
    /// \param bIgnoringCase Flag to indicate if comparison should ignore case (default: true).
    /// \return Returns true if the string starts with the specified prefix, false otherwise.
    static bool StartWith(const char *str, const char *strHead,
                          bool bIgnoringCase = true);

    /// \brief Checks if a string ends with a specified suffix.
    /// \param str The string to check.
    /// \param strTail The suffix.
    /// \param bIgnoringCase Flag to indicate if comparison should ignore case (default: true).
    /// \return Returns true if the string ends with the specified suffix, false otherwise.
    static bool EndWith(const char *str, const char *strTail,
                        bool bIgnoringCase = true);

    /// \brief Checks if a string matches a wildcard pattern.
    /// \details The `*` character matches one or more characters, and `?` matches a single character.
    /// \param pattern The wildcard pattern.
    /// \param str The string to match.
    /// \param bIgnoreCase Flag to indicate if comparison should ignore case (default: true).
    /// \return Returns true if the string matches the pattern, false otherwise.
    static bool IsMatch(const char *pattern, const char *str,
                        bool bIgnoreCase = true);

    /// \brief Performs SQL-like wildcard matching, supporting `%` and `_` as wildcards.
    /// \param pattern The pattern with SQL wildcards.
    /// \param str The string to match.
    /// \param chEscape The escape character.
    /// \return Returns true if the string matches the pattern, false otherwise.
    static bool IsLike(const char *pattern, const char *str, char chEscape);

    /// \brief Converts a string to uppercase.
    /// \param str The string to convert.
    /// \return Returns the uppercase string.
    static std::string ToUpper(const char *str);

    /// \brief Converts a string to lowercase.
    /// \param str The string to convert.
    /// \return Returns the lowercase string.
    static std::string ToLower(const char *str);

    /// \brief Checks if a string consists of integer characters (including a negative sign).
    /// \param str The string to check.
    /// \return Returns true if the string represents an integer, false otherwise.
    static bool IsIntString(const char *str);

    /// \brief Checks if a string consists of numeric characters (including a negative sign).
    /// \param str The string to check.
    /// \return Returns true if the string represents a number, false otherwise.
    static bool IsNumberString(const char *str);

    /// \brief Checks if a string consists of floating-point characters (including a negative sign).
    /// \param str The string to check.
    /// \return Returns true if the string represents a float, false otherwise.
    static bool IsFloatString(const char *str);

    /// \brief Checks if a string represents a boolean value.
    /// \param str The string to check.
    /// \return Returns true if the string represents a boolean, false otherwise.
    static bool IsBoolString(const char *str);

    /// \brief Checks if a string represents a Base64 encoded value.
    /// \param str The string to check.
    /// \return Returns true if the string is Base64 encoded, false otherwise.
    static bool IsBase64String(const char *str);

    /// \brief Converts a hexadecimal string in the AABB00 format to a regular string.
    /// \param str The hexadecimal string.
    /// \return Returns the decoded string.
    static std::string FromHexString(const char *str);

    /// \brief Converts a regular string to a hexadecimal string in the AABB00 format.
    /// \param str The string to encode.
    /// \return Returns the hexadecimal encoded string.
    static std::string ToHexString(const char *str);

    /// \brief Converts a hexadecimal string in the AABB00 format to a binary block.
    /// \param str The hexadecimal string.
    /// \param pOut The output binary buffer.
    /// \return Returns true if conversion is successful, false otherwise.
    static bool FromHexString(const char *str, ByteBuffer *pOut);

    /// \brief Converts a binary block to a hexadecimal string in the AABB00 format.
    /// \param blob The binary data.
    /// \param nLen The length of the binary data.
    /// \return Returns the hexadecimal encoded string.
    static std::string ToHexString(const unsigned char *blob, int nLen);

    /// \brief Parses a boolean value from a string.
    /// \param strValue The string value to parse.
    /// \param bDefault The default value if parsing fails (default: false).
    /// \return Returns the parsed boolean value.
    static bool ParseBool(const char *strValue, bool bDefault = false);

    /// \brief Tries to parse a boolean value from a string.
    /// \param strValue The string value to parse.
    /// \param val The parsed boolean value.
    /// \return Returns true if parsing is successful, false otherwise.
    static bool TryParse(const char *strValue, bool &val);

    /// \brief Parses an integer value from a string.
    /// \param strValue The string value to parse.
    /// \param nDefault The default value if parsing fails (default: 0).
    /// \return Returns the parsed integer value.
    static long long ParseInteger(const char *strValue, long long nDefault = 0);

    /// \brief Tries to parse an integer value from a string.
    /// \param strValue The string value to parse.
    /// \param val The parsed integer value.
    /// \return Returns true if parsing is successful, false otherwise.
    static bool TryParse(const char *strValue, long long &val);

    /// \brief Tries to parse an integer value from a string.
    /// \param strValue The string value to parse.
    /// \param val The parsed integer value.
    /// \return Returns true if parsing is successful, false otherwise.
    static bool TryParse(const char *strValue, int &val);

    /// \brief Parses a float value from a string.
    /// \param strValue The string value to parse.
    /// \param fDefault The default value if parsing fails (default: 0).
    /// \return Returns the parsed float value.
    static double ParseFloat(const char *strValue, double fDefault = 0);

    /// \brief Tries to parse a float value from a string.
    /// \param strValue The string value to parse.
    /// \param val The parsed float value.
    /// \return Returns true if parsing is successful, false otherwise.
    static bool TryParse(const char *strValue, double &val);

    /// \brief Checks if a string contains a specific character.
    /// \param str The string to check.
    /// \param c The character to check for.
    /// \return Returns true if the string contains the character, false otherwise.
    static bool HasContain(const char *str, char c);

    /// \brief Checks if a string contains any character from another string.
    /// \param str The string to check.
    /// \param c The string containing characters to check for.
    /// \return Returns true if the string contains any character, false otherwise.
    static bool HasContainAny(const char *str, const char *c);
};

}// namespace CPL