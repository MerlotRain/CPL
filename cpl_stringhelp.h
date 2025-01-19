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

/// \brief A single-byte string class that is compatible with std::string methods.
class CPL_API String : public std::basic_string<char, std::char_traits<char>,
                                                std::allocator<char>>
{
public:
    using StlString = std::basic_string<char>;

    /// \brief Default constructor.
    String();

    /// \brief Copy constructor.
    /// \param str The String object to copy from.
    String(const String &str);

    /// \brief STL string copy constructor.
    /// \param str The STL string object to copy from.
    String(const StlString &str);

    /// \brief Constructor from a pointer to another String object.
    /// \param str The String object to copy from.
    String(String *str);

    /// \brief Constructor that creates a String from any other standard string type.
    /// \param str The standard string object to copy from.
    template<class STD>
    String(const STD &str)
    {
        operator=(str.c_str());
    }

    /// \brief Constructor from a single-byte string (const char*).
    /// \param str The C-string to initialize the String with.
    String(const char *str);

    /// \brief Constructor from a single-byte string (char*).
    /// \param str The C-string to initialize the String with.
    String(char *str);

    /// \brief Constructor from a single-byte string with an offset and length.
    /// \param str The C-string to copy from.
    /// \param off The offset where the copy starts.
    /// \param count The number of characters to copy.
    String(const char *str, int off, int count);

    /// \brief Constructor from a single-byte string with a specified length.
    /// \param str The C-string to copy from.
    /// \param count The number of characters to copy.
    String(const char *str, int count);

    /// \brief Constructor from the start and end pointers of a string.
    /// \param start Pointer to the start of the string.
    /// \param end Pointer to the end of the string.
    String(const char *start, const char *end);

    /// \brief Constructor from arbitrary memory.
    /// \param start Pointer to the start of the memory.
    /// \param end Pointer to the end of the memory.
    String(const unsigned char *start, const unsigned char *end);

    /// \brief Constructor that creates a String by repeating a character.
    /// \param count The number of times to repeat the character.
    /// \param e The character to repeat.
    String(int count, char e);

    /// \brief Constructor using iterators to create a String.
    /// \param first Iterator to the first character.
    /// \param last Iterator to the last character.
    String(String::const_iterator first, String::const_iterator last);

    /// \brief Constructor using iterators to create a String.
    /// \param first Iterator to the first character.
    /// \param last Iterator to the last character.
    String(String::iterator first, String::iterator last);

    /// \brief Constructor using reverse iterators to create a String.
    /// \param first Reverse iterator to the first character.
    /// \param last Reverse iterator to the last character.
    String(String::reverse_iterator first, String::reverse_iterator last);

    /// \brief Constructor using const reverse iterators to create a String.
    /// \param first Reverse iterator to the first character.
    /// \param last Reverse iterator to the last character.
    String(String::const_reverse_iterator first,
           String::const_reverse_iterator last);

    /// \brief Destructor.
    ~String();

    /// \brief Checks if a string is null or empty.
    /// \param str The C-string to check.
    /// \return True if the string is null or empty, false otherwise.
    static bool IsNullOrEmpty(const char *str);

    /// \brief Assignment operator to assign a C-string.
    /// \param str The C-string to assign.
    /// \return Reference to this String object.
    String &operator=(const char *str);

    /// \brief Assignment operator to assign an STL string.
    /// \param str The STL string to assign.
    /// \return Reference to this String object.
    String &operator=(const StlString &str);

    /// \brief Assignment operator to assign another String object.
    /// \param str The String object to assign.
    /// \return Reference to this String object.
    String &operator=(const String &str);

    /// \brief Subscript operator to access a character by index.
    /// \param _Off The index of the character to access.
    /// \return The character at the specified index.
    reference operator[](int _Off);

    /// \brief Const subscript operator to access a character by index.
    /// \param _Off The index of the character to access.
    /// \return The character at the specified index.
    const_reference operator[](int _Off) const;

    /// \brief Conversion operator to bool, checks if the string is empty.
    /// \return True if the string is not empty, false otherwise.
    operator bool() const;

    /// \brief Conversion operator to const char*, returns the C-string.
    /// \return The C-string representation of the string.
    operator const char *() const;

    using StlString::operator+=;

    /// \brief Append operator for any standard string type.
    /// \param str The string to append.
    /// \return Reference to this String object.
    template<class STD>
    String &operator+=(const STD &str)
    {
        StlString::operator+=(str.c_str());
        return *this;
    }

    /// \brief Append operator for a C-string.
    /// \param str The C-string to append.
    /// \return Reference to this String object.
    String &operator+=(const char *str);

    /// \brief Append operator for another String object.
    /// \param str The String object to append.
    /// \return Reference to this String object.
    String &operator+=(const String &str);

    /// \brief Concatenation operator for a C-string.
    /// \param str The C-string to concatenate.
    /// \return A new String object with the concatenated result.
    String operator+(const char *str) const;

    /// \brief Concatenation operator for another String object.
    /// \param str The String object to concatenate.
    /// \return A new String object with the concatenated result.
    String operator+(const String &str) const;

    /// \brief Concatenation operator for an STL string.
    /// \param str The STL string to concatenate.
    /// \return A new String object with the concatenated result.
    String operator+(const StlString &str) const;

    /// \brief Converts the string to uppercase.
    /// \return Reference to this String object with the uppercase result.
    String &ToUpper();

    /// \brief Converts the string to lowercase.
    /// \return Reference to this String object with the lowercase result.
    String &ToLower();

    /// \brief Reverses the string.
    /// \return Reference to this String object with the reversed result.
    String &Reverse();

    /// \brief Removes all trailing whitespace characters.
    /// \return Reference to this String object with the trailing whitespace removed.
    String &TrimRight();

    /// \brief Removes all leading whitespace characters.
    /// \return Reference to this String object with the leading whitespace removed.
    String &TrimLeft();

    /// \brief Removes both leading and trailing whitespace characters.
    /// \return Reference to this String object with both leading and trailing whitespace removed.
    String &Trim();

    /// \brief Splits the string into substrings based on the separator.
    /// \param strSep The separator string to split by.
    /// \return A vector of String objects containing the split substrings.
    std::vector<String> Split(const char *strSep);

    /// \brief Splits the string into substrings based on the separator.
    /// \param strSep The separator string to split by.
    /// \param vecStr The vector to store the resulting substrings.
    void Split(const char *strSep, std::vector<String> &vecStr);
};


/// \brief + operator for concatenating a String and a std::string
/// This operator allows the concatenation of a String object and a std::string object.
/// It calls the String class's + operator, passing the C-string (char*) from the std::string.
static String operator+(const String &a, const std::string &b)
{
    return a.operator+(b.c_str());
}

/// \brief Class representing a wide-character string (wchar_t)
/// This class is a wrapper around std::basic_string<wchar_t> for wide-character strings.
class CPL_API WString
    : public std::basic_string<wchar_t, std::char_traits<wchar_t>,
                               std::allocator<wchar_t>>
{
public:
    using StlWString = std::basic_string<wchar_t, std::char_traits<wchar_t>,
                                         std::allocator<wchar_t>>;

    /// \brief Default constructor
    WString();

    /// \brief Copy constructor
    WString(const WString &str);

    /// \brief Constructor from STL wide-string (std::wstring)
    WString(const StlWString &str);

    /// \brief Constructor from a generic string (template for various types)
    /// \param str A generic string-like object.
    template<class STD>
    WString(const STD &str)
    {
        operator=(str.c_str());
    }

    /// \brief Constructor from a wide-character string (const wchar_t*)
    WString(const wchar_t *str);

    /// \brief Constructor from a mutable wide-character string (wchar_t*)
    WString(wchar_t *str);

    /// \brief Constructor from a wide-character string with offset and length
    /// \param str A pointer to the wide-character string.
    /// \param off The starting offset.
    /// \param count The number of characters to take.
    WString(const wchar_t *str, int off, int count);

    /// \brief Constructor from a wide-character string with specified length
    /// \param str A pointer to the wide-character string.
    /// \param count The number of characters to take.
    WString(const wchar_t *str, int count);

    /// \brief Constructor from a wide-character string using start and end pointers
    /// \param start A pointer to the beginning of the string.
    /// \param end A pointer to the end of the string.
    WString(const wchar_t *start, const wchar_t *end);

    /// \brief Constructor that repeats a character a specified number of times
    /// \param count The number of times to repeat the character.
    /// \param e The character to repeat.
    WString(int count, wchar_t e);

    /// \brief Constructor using a pair of iterators (forward iterators)
    WString(WString::iterator first, WString::iterator last);

    /// \brief Constructor using a pair of constant iterators (forward iterators)
    WString(WString::const_iterator first, WString::const_iterator last);

    /// \brief Constructor using a pair of reverse iterators
    WString(WString::reverse_iterator first, WString::reverse_iterator last);

    /// \brief Constructor using a pair of constant reverse iterators
    WString(WString::const_reverse_iterator first,
            WString::const_reverse_iterator last);

    /// \brief Destructor
    ~WString();

    /// \brief Check if the string is null or empty
    /// \param str A pointer to a wide-character string.
    /// \return True if the string is null or empty, otherwise false.
    static bool IsNullOrEmpty(const wchar_t *str);

    /// \brief Assignment operator from a wide-character string (const wchar_t*)
    WString &operator=(const wchar_t *str);

    /// \brief Assignment operator from a STL wide-character string (StlWString)
    WString &operator=(const StlWString &str);

    /// \brief Assignment operator from another WString object
    WString &operator=(const WString &str);

    /// \brief Conversion operator to a generic string type (STD)
    /// \param STD A generic string-like type.
    /// \return A new string of type STD containing the wide-character string.
    template<class STD>
    operator STD() const
    {
        return STD(c_str());
    }

    /// \brief Conversion to bool operator
    /// This operator indicates whether the string is empty or not.
    operator bool() const;

    // Inherits operator+= from the STL wide-string type.
    using StlWString::operator+=;

    /// \brief Append a generic string to this WString (template version)
    /// \param str A generic string-like object.
    /// \return The updated WString object.
    template<class STD>
    WString &operator+=(const STD &str)
    {
        StlWString::operator+=(str.c_str());
        return *this;
    }

    /// \brief Append another WString to this WString
    /// \param str Another WString object.
    /// \return The updated WString object.
    WString &operator+=(const WString &str);

    /// \brief Append a wide-character string to this WString
    /// \param str A pointer to a wide-character string.
    /// \return The updated WString object.
    WString &operator+=(const wchar_t *str);

    /// \brief Concatenate a wide-character string to this WString
    /// \param str A pointer to a wide-character string.
    /// \return A new WString object that is the concatenation of the two strings.
    WString operator+(const wchar_t *str) const;

    /// \brief Concatenate an STL wide-character string to this WString
    /// \param str A STL wide-character string (std::wstring).
    /// \return A new WString object that is the concatenation of the two strings.
    WString operator+(const StlWString &str) const;

    /// \brief Concatenate another WString to this WString
    /// \param str Another WString object.
    /// \return A new WString object that is the concatenation of the two strings.
    WString operator+(const WString &str) const;
};


/// \brief + operator for concatenating a WString and a std::wstring
/// This operator allows the concatenation of a WString object and a std::wstring object.
/// It calls the WString class's + operator, passing the C-string (const wchar_t*) from the std::wstring.
static WString operator+(const WString &a, const std::wstring &b)
{
    return a.operator+(b.c_str());
}


/// \brief Encoding IDs for character conversions
enum CodePageID
{
    CP_ACP = 0,       ///< Default system code page (ANSI)
    CP_GBK = 936,     ///< GBK (Simplified Chinese)
    CP_UTF16 = 1200,  ///< UTF-16
    CP_UTF7 = 65000,  ///< UTF-7
    CP_UTF8 = 65001,  ///< UTF-8
    CP_GB2312 = 20936,///< GB2312 (Simplified Chinese)
    CP_GB18030 =
            54936,///< GB18030 (Simplified Chinese, extended version of GB2312)
    CP_WINDOWS1252 = 1252,///< Windows-1252 (Western European)
    CP_ISO8859_1 = 28592, ///< ISO-8859-1 (Latin-1, Western European)
};


/// \brief Class for converting wide-character strings (wchar_t) to narrow-character strings (char)
/// This class is used to convert wide-character strings (wchar_t) to narrow-character strings (char), supporting different code pages.
class CPL_API CW2A
{
public:
    String m_Str;///< The resulting narrow-character string (std::string)

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

    /// \brief Constructor from a WString object
    /// \param str A WString object to convert to a narrow-character string.
    CW2A(const WString &str);

    /// \brief Constructor from a WString object with a specified code page (CodePageID)
    /// \param str A WString object to convert to a narrow-character string.
    /// \param eCodePage The code page to use for the conversion.
    CW2A(const WString &str, CodePageID eCodePage);

    /// \brief Constructor from a WString object with a specified code page (string format)
    /// \param str A WString object to convert to a narrow-character string.
    /// \param codepage The code page to use for the conversion (as a string).
    CW2A(const WString &str, const char *codepage);

    /// \brief Destructor
    /// The destructor releases any allocated resources.
    ~CW2A() throw();

    /// \brief Conversion operator to a C-style narrow-character string (const char*)
    /// \return A pointer to the resulting narrow-character C-string.
    operator const char *() const;

    /// \brief Conversion operator to a String object (std::string)
    /// \return The resulting narrow-character string as a String object.
    operator String() const;

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
    WString m_WStr;///< The resulting wide-character string (WString)

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

    /// \brief Constructor from a String object (std::string)
    /// \param str A String object to convert to a wide-character string.
    CA2W(const String &str);

    /// \brief Constructor from a String object with a specified code page (CodePageID)
    /// \param str A String object to convert to a wide-character string.
    /// \param eCodePage The code page to use for the conversion.
    CA2W(const String &str, CodePageID eCodePage);

    /// \brief Constructor from a String object with a specified code page (string format)
    /// \param str A String object to convert to a wide-character string.
    /// \param codepage The code page to use for the conversion (as a string).
    CA2W(const String &str, const char *codepage);

    /// \brief Destructor
    /// The destructor releases any allocated resources.
    ~CA2W() throw();

    /// \brief Conversion operator to a C-style wide-character string (const wchar_t*)
    /// \return A pointer to the resulting wide-character C-string.
    operator const wchar_t *() const;

    /// \brief Conversion operator to a WString object
    /// \return The resulting wide-character string as a WString object.
    operator WString() const;

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
    static String ToUtf8(const char *str);

    /// \brief Converts a local Unicode string to a UTF-8 encoded string.
    /// \return Returns the string converted to UTF-8 encoding.
    static String ToUtf8(const wchar_t *str);

    /// \brief Converts a local Unicode string to an MBCS (Multi-Byte Character Set) narrow string.
    /// \return Returns the string converted to MBCS narrow encoding.
    static String ToLocal(const wchar_t *str);

    /// \brief Converts a UTF-8 narrow string to a Unicode wide string.
    /// \return Returns the string converted to Unicode wide encoding.
    static WString Utf8ToUnicode(const char *str);

    /// \brief Converts a local MBCS narrow string to a Unicode wide string.
    /// \return Returns the string converted to Unicode wide encoding.
    static WString LocalToUnicode(const char *str);

    /// \brief Converts a UTF-8 string to a local string.
    /// \return Returns the string converted to the local encoding.
    static String ToLocal(const char *str);

private:
    static String ConvertEncoding(const char *str, const char *fromEncoding,
                                  const char *toEncoding);
    static WString ConvertEncoding(const wchar_t *str, const char *fromEncoding,
                                   const char *toEncoding);
};

/// \brief A class for converting a string to a UTF-8 encoded string.
class CPL_API Utf8
{
    const char *m_Ori;///< Original string (in its native encoding).
    String m_Utf;     ///< UTF-8 encoded string.

public:
    /// \brief Constructor that initializes with a C-style string (const char *).
    /// \param ori The original string to be converted to UTF-8.
    Utf8(const char *ori);

    /// \brief Constructor that initializes with a String object.
    /// \param ori The original String object to be converted to UTF-8.
    explicit Utf8(const String &ori);

    /// \brief Implicit conversion operator to a C-style string (const char *).
    /// \return Returns the UTF-8 encoded string as a C-style string.
    operator const char *();

    /// \brief Implicit conversion operator to a String object.
    /// \return Returns the UTF-8 encoded string as a String object.
    operator String();

    /// \brief Returns the UTF-8 encoded string.
    /// \return Returns the UTF-8 string stored in the object.
    String Str();
};


/// \brief A class for converting a string to the local encoding.
class CPL_API Local
{
    const char *m_Ori;///< Original string (in its native encoding).
    String m_Utf;     ///< Local encoded string.

public:
    /// \brief Constructor that initializes with a C-style string (const char *).
    /// \param ori The original string to be converted to the local encoding.
    Local(const char *ori);

    /// \brief Constructor that initializes with a String object.
    /// \param ori The original String object to be converted to the local encoding.
    Local(const String &ori);

    /// \brief Implicit conversion operator to a C-style string (const char *).
    /// \return Returns the string converted to the local encoding as a C-style string.
    operator const char *();

    /// \brief Implicit conversion operator to a String object.
    /// \return Returns the string converted to the local encoding as a String object.
    operator String();

    /// \brief Returns the string in the local encoding.
    /// \return Returns the string stored in the object, converted to the local encoding.
    String Str();
};


/// \brief Provides various utility functions for string manipulation.
class CPL_API StringHelp
{
public:
    /// \brief Returns an empty string.
    /// \return An empty string.
    static String EmptyString();

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

    /// \brief Converts a C-style string to a String object.
    /// \param str The C-style string.
    /// \return Returns the String object.
    static String ToString(const char *str);
    /// \brief Converts a char value to a String object.
    /// \param v The char value.
    /// \return Returns the String object.
    static String ToString(char v);
    /// \brief Converts an unsigned char value to a String object.
    /// \param v The unsigned char value.
    /// \return Returns the String object.
    static String ToString(unsigned char v);
    /// \brief Converts a short value to a String object.
    /// \param v The short value.
    /// \return Returns the String object.
    static String ToString(short v);
    /// \brief Converts an unsigned short value to a String object.
    /// \param v The unsigned short value.
    /// \return Returns the String object.
    static String ToString(unsigned short v);
    /// \brief Converts an int value to a String object.
    /// \param v The int value.
    /// \return Returns the String object.
    static String ToString(int v);
    /// \brief Converts an unsigned int value to a String object.
    /// \param v The unsigned int value.
    /// \return Returns the String object.
    static String ToString(unsigned int v);
    /// \brief Converts a long long value to a String object.
    /// \param v The long long value.
    /// \return Returns the String object.
    static String ToString(long long v);
    /// \brief Converts an unsigned long long value to a String object.
    /// \param v The unsigned long long value.
    /// \return Returns the String object.
    static String ToString(unsigned long long v);
    /// \brief Converts a float value to a String object with a specified maximum digit count.
    /// \param v The float value.
    /// \param maxDigitCount The maximum number of digits (default: 6).
    /// \return Returns the String object.
    static String ToString(float v, int maxDigitCount = 6);
    /// \brief Converts a double value to a String object with a specified maximum digit count.
    /// \param v The double value.
    /// \param maxDigitCount The maximum number of digits (default: 15).
    /// \return Returns the String object.
    static String ToString(double v, int maxDigitCount = 15);

    /// \brief Converts a boolean value to a String object.
    /// \param v The boolean value.
    /// \return Returns the String object.
    static String ToString(bool v);

    /// \brief Converts a byte array to a Base64 encoded String object.
    /// \param blob The byte array.
    /// \param nLen The length of the byte array.
    /// \return Returns the Base64 encoded String object.
    static String ToString(const unsigned char *blob, int nLen);

    /// \brief Formats a string according to the specified format and arguments.
    /// \param nMaxLen The maximum length of the resulting string.
    /// \param format The format string.
    /// \return Returns the formatted String object.
    static String Format(int nMaxLen, const char *format, ...);

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
    static std::vector<String> Split(const char *str, const char *strSep);

    /// \brief Splits a string into substrings using a character separator.
    /// \param str The string to split.
    /// \param sp The separator character.
    /// \return Returns a vector of substrings.
    static std::vector<String> Split(const char *str, char sp);

    /// \brief Replaces a substring within a string with a new substring.
    /// \param str The original string.
    /// \param src The substring to be replaced.
    /// \param dst The new substring.
    /// \return Returns the string with replacements.
    static String Replace(const char *str, const char *src, const char *dst);

    /// \brief Trims whitespace characters from the beginning of a string.
    /// \param str The string to trim.
    /// \return Returns the trimmed string.
    static String Trim(const char *str);

    /// \brief Trims whitespace characters from the left side of a string.
    /// \param str The string to trim.
    /// \return Returns the left-trimmed string.
    static String TrimLeft(const char *str);

    /// \brief Trims whitespace characters from the right side of a string.
    /// \param str The string to trim.
    /// \return Returns the right-trimmed string.
    static String TrimRight(const char *str);

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
    static String ToUpper(const char *str);

    /// \brief Converts a string to lowercase.
    /// \param str The string to convert.
    /// \return Returns the lowercase string.
    static String ToLower(const char *str);

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
    static String FromHexString(const char *str);

    /// \brief Converts a regular string to a hexadecimal string in the AABB00 format.
    /// \param str The string to encode.
    /// \return Returns the hexadecimal encoded string.
    static String ToHexString(const char *str);

    /// \brief Converts a hexadecimal string in the AABB00 format to a binary block.
    /// \param str The hexadecimal string.
    /// \param pOut The output binary buffer.
    /// \return Returns true if conversion is successful, false otherwise.
    static bool FromHexString(const char *str, ByteBuffer *pOut);

    /// \brief Converts a binary block to a hexadecimal string in the AABB00 format.
    /// \param blob The binary data.
    /// \param nLen The length of the binary data.
    /// \return Returns the hexadecimal encoded string.
    static String ToHexString(const unsigned char *blob, int nLen);

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