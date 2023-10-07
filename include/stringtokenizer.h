/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file stringtokenizer.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/

#pragma once

#include "stringhelp.h"

namespace Lite {
namespace Utility {

/// @brief 单字节字符串,按照词组,数字 符号 读取方法
class UTILITY_EXPORT GsStringTokenizer
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

}// namespace Utility
}// namespace Lite
