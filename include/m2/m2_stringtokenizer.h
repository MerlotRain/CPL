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

#pragma once

#include "stringhelp.h"

namespace m2 {

/// @brief 单字节字符串,按照词组,数字 符号 读取方法
class M2_API GsStringTokenizer
{
public:
    enum TokenizerFlag : int
    {
        TT_EOF,
        TT_EOL,
        TT_NUMBER,
        TT_WORD
    };
    /// @brief 构造
    explicit GsStringTokenizer(const GsString &txt);
    ~GsStringTokenizer() {}
    /// @brief 获取下一个Token 值 有可能是 GsTokenFlag  有可能是'(' 或者')'或者 ';'
    int NextToken();
    /// @brief 获取下一个Token 值 有可能是 GsTokenFlag  有可能是'(' 或者')'或者 ';'
    int PeekNextToken();
    /// @brief 获取一个double
    double GetNVal() const;
    /// @brief 获取一个字符串
    GsString GetSVal() const;

private:
    GsStringTokenizer(const GsStringTokenizer &) = delete;
    GsStringTokenizer &operator=(const GsStringTokenizer &) = delete;

private:
    const GsString &m_str;
    GsString m_stok;
    double m_ntok;
    GsString::const_iterator m_iter;
};

}// namespace m2
