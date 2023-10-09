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

#include "preconfig.h"
#include <vector>

namespace m2 {

/// @brief 二维码对象
class QRCodePage
{
    void *m_QRCode;

public:
    QRCodePage(void *code = nullptr);
    ~QRCodePage();
    QRCodePage(const QRCodePage &rhs);

    QRCodePage &operator=(const QRCodePage &rhs);
    int Size();
    bool IsSet(int r, int c);
};

/// @brief 二维码生成的级别
enum QREncodeLevel
{
    eQR_ECLEVEL_L = 0,///< lowest
    eQR_ECLEVEL_M,
    eQR_ECLEVEL_Q,
    eQR_ECLEVEL_H///< highest
};

/// @brief 二维码编码模式
enum QREncodeMode
{
    eQR_MODE_NUL = -1,  ///< Terminator (NUL character). Internal use only
    eQR_MODE_NUM = 0,   ///< Numeric mode
    eQR_MODE_AN,        ///< Alphabet-numeric mode
    eQR_MODE_8,         ///< 8-bit data mode
    eQR_MODE_KANJI,     ///< Kanji (shift-jis) mode
    eQR_MODE_STRUCTURE, ///< Internal use only
    eQR_MODE_ECI,       ///< ECI mode
    eQR_MODE_FNC1FIRST, ///< FNC1, first position
    eQR_MODE_FNC1SECOND,///< FNC1, second position
};


/// @brief 二维码编码数据类型
enum QRCodeDataType
{
    eQRCodeUnknown,//!< 未知类型，错误类型
    eQRCodeString, //!< 字符串二维编码
    eQRCodeBinary, //!< 任意二进制数据
};


/// @brief 二维码生成
class QRCode
{
public:
    QRCode();
    QRCode(const char *strData);
    QRCode(const unsigned char *pData, int nLen);
    virtual ~QRCode();
    QREncodeLevel Level();
    void Level(QREncodeLevel eLevel);
    QREncodeMode Mode();
    void Mode(QREncodeMode mode);
    bool Encode(const char *strData);
    bool Encode(const unsigned char *pData, int nLen);
    int PageCount();
    QRCodePage CodePage(int i);
    void Reset();

private:
    void *m_QRCodeList;
    std::vector<QRCodePage> m_Pages;
    QREncodeLevel m_eLevel;
    QREncodeMode m_eMode;
};

}// namespace m2
