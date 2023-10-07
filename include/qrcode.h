/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file qrcode.h
 * @brief
 * @details
 * @date 2023-06-19
 * @author
 *
 ******************************************************************************/

#pragma once

#include "preconfig.h"
#include <vector>

namespace Lite {
namespace Utility {

/// @brief 二维码对象
class GsQRCodePage
{
    void *m_QRCode;

public:
    GsQRCodePage(void *code = nullptr);
    ~GsQRCodePage();
    GsQRCodePage(const GsQRCodePage &rhs);

    GsQRCodePage &operator=(const GsQRCodePage &rhs);
    int Size();
    bool IsSet(int r, int c);
};

/// @brief 二维码生成的级别
enum GsQREncodeLevel
{
    eQR_ECLEVEL_L = 0,///< lowest
    eQR_ECLEVEL_M,
    eQR_ECLEVEL_Q,
    eQR_ECLEVEL_H///< highest
};

/// @brief 二维码编码模式
enum GsQREncodeMode
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
enum GsQRCodeDataType
{
    eQRCodeUnknown,//!< 未知类型，错误类型
    eQRCodeString, //!< 字符串二维编码
    eQRCodeBinary, //!< 任意二进制数据
};


/// @brief 二维码生成
class GsQRCode
{
public:
    GsQRCode();
    GsQRCode(const char *strData);
    GsQRCode(const unsigned char *pData, int nLen);
    virtual ~GsQRCode();
    GsQREncodeLevel Level();
    void Level(GsQREncodeLevel eLevel);
    GsQREncodeMode Mode();
    void Mode(GsQREncodeMode mode);
    bool Encode(const char *strData);
    bool Encode(const unsigned char *pData, int nLen);
    int PageCount();
    GsQRCodePage CodePage(int i);
    void Reset();

private:
    void *m_QRCodeList;
    std::vector<GsQRCodePage> m_Pages;
    GsQREncodeLevel m_eLevel;
    GsQREncodeMode m_eMode;
};

}// namespace Utility
}// namespace Lite
