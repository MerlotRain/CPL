/****************************************************************************
**
** Copyright (C) 2023 MerlotRain
** Github:https://github.com/MerlotRain
**
** M2 is a cross platform C++basic library that encapsulates commonly 
** used C++ classes and functional modules, shields system functions from 
** the outside, and provides a unified interface.
**
** $M2_BEGIN_LICENSE:MIT$
** Permission is hereby granted, free of charge, to any person obtaining a 
** copy of this software and associated documentation files (the “Software”), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
** DEALINGS IN THE SOFTWARE.
** 
** $M2_END_LICENSE$
**
****************************************************************************/

#ifndef M2_TEXTCONVERTOR_H_
#define M2_TEXTCONVERTOR_H_

#include <preconfig.h>

namespace m2 {

class String;
class WString;

class M2_API TextConverter
{
public:
    static constexpr auto ENCODING_LOCALE = "";
    static constexpr auto ENCODING_UTF7 = "UTF-7";
    static constexpr auto ENCODING_UTF8 = "UTF-8";
    static constexpr auto ENCODING_UTF16 = "UTF-16";
    static constexpr auto ENCODING_UTF32 = "UTF-32";
    static constexpr auto ENCODING_UCS2 = "UCS-2";
    static constexpr auto ENCODING_UCS4 = "UCS-4";
    static constexpr auto ENCODING_ASCII = "ASCII";
    static constexpr auto ENCODING_ISO8859_1 = "ISO-8859-1";
    static constexpr auto ENCODING_GB2312 = "GBK";
    static constexpr auto ENCODING_GB18030 = "GB18030";

public:
    static bool convert(const char *src, const char *srcEncoding,
                        const char *dstEncoding, String &dst);
    static bool convert(const String &src, const char *srcEncoding,
                        const char *dstEncoding, String &dst);

    static bool convert(const wchar_t *src, const char *srcEncoding,
                        const char *dstEncoding, String &dst);
    static bool convert(const WString &src, const char *srcEncoding,
                        const char *dstEncoding, String &dst);

    static bool convert(const char *src, const char *srcEncoding,
                        const char *dstEncoding, WString &dst);
    static bool convert(const String &src, const char *srcEncoding,
                        const char *dstEncoding, WString &dst);

    static bool convert(const String &utf8, WString &utf16);
    static bool convert(const char *utf8, WString &utf16);

    static bool convert(const WString &utf16, String &utf8);
    static bool convert(const wchar_t *utf16, String &utf8);
};

}// namespace m2

#endif//