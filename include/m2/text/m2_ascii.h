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
** copy of this software and associated documentation files (the "Software"), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
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

#ifndef M2_ASCII_H
#define M2_ASCII_H

#include <preconfig.h>

namespace m2 {

class LIBM2_EXPORT Ascii
{
public:
    static int properties(int ch);
    static bool hasSomeProperties(int ch, int properties);
    static bool hasProperties(int ch, int properties);
    static bool isAscii(int ch);
    static bool isSpace(int ch);
    static bool isDigit(int ch);
    static bool isHexDigit(int ch);
    static bool isPunctuation(int ch);
    static bool isAlpha(int ch);
    static bool isAlphaNumeric(int ch);
    static bool isLower(int ch);
    static bool isUpper(int ch);
    static bool isPrintable(int ch);
    static int toLower(int ch);
    static int toUpper(int ch);
};

}// namespace m2

#endif//M2_ASCII_H