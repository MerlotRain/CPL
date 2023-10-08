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

#ifndef M2_STRINGTOKENIZER_H_
#define M2_STRINGTOKENIZER_H_

#include <m2_string.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4251)// warning C4251: needs to have dll-interface to be used by clients of class
#endif

namespace m2 {

class M2_API StringTokenizer
{
public:
    enum TokenizerFlag : int
    {
        TT_EOF,
        TT_EOL,
        TT_NUMBER,
        TT_WORD
    };
    explicit StringTokenizer(const String &txt);
    ~StringTokenizer() {}
    int nextToken();
    int peekNextToken();
    double numberValue() const;
    String stringVal() const;

private:
    StringTokenizer(const StringTokenizer &) = delete;
    StringTokenizer &operator=(const StringTokenizer &) = delete;

private:
    const String &str;
    String stok;
    double ntok;
    String::const_iterator iter;
};

}// namespace m2

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif//M2_STRINGTOKENIZER_H_