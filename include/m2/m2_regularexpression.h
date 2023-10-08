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

#include "flags.h"
#include "stringhelp.h"

namespace m2 {


/// @brief 常用的正则表达式
enum GsWellknownRegex
{
    /// @brief 匹配整数
    eMatchInt,
    /// @brief 匹配浮点数
    eMatchFloat,
    /// @brief 匹配数字
    eMatchNumber,
    /// @brief 零或者非零开头的数字
    eMatchNumberZeroOrStartWithNoneZero,
    /// @brief 非零开头的最多带两位小数的数字
    eMathNumberWith2Decimal,
    /// @brief 带1-2位小数的正数或负数
    eMatchSignedWith2Decimal,
    /// @brief 带2位小数的正数
    eMatchPositiveWith2Decimal,
    /// @brief 带1~3位小数的正数
    eMatchPositiveWith3Decimal,
    /// @brief 非零的正整数
    eMatchPositiveNotZero,
    /// @brief 非零的负整数
    eMatchNegativeNotZero,
    /// @brief 非负整数
    eMatchNotNegative,
    /// @brief 非正整数
    eMatchNotPositive,
    /// @brief 非正浮点数
    eMatchNotPositiveFloat,
    /// @brief 非负浮点数
    eMatchNotNegativeFloat,
    /// @brief 负浮点数
    eMatchNegativeFloat,
    /// @brief 正浮点数
    eMatchPositiveFloat,

    /// @brief 汉字
    eMatchChineseCharacter,
    /// @brief 英文和数字
    eMatchEnglishAndNumber,
    /// @brief 由26个英文字母组成的字符串
    eMatchEnglishAlphabet,
    /// @brief 由26个大写英文字母组成的字符串
    eMatchEnglishAlphabetUppercase,
    /// @brief 由26个小写英文字母组成的字符串
    eMatchEnglishAlphabetLowercase,
    /// @brief 中文、英文、数字包括下划线
    eMatchChineseEnglishNumberUnderline,
    /// @brief 中文、英文、数字但不包括下划线
    eMatchChineseEnglishNumberWithoutUnderline,
    /// @brief 电子邮件地址
    eMatchEMailAddress,
    /// @brief 域名
    eMatchDomainName,
    /// @brief Internet地址
    eMatchInternetAddress,

    /// @brief 手机号码
    eMathcHandphoneNumber,
    /// @brief 中国固定电话号码区号-号码
    eMathcChinaLandlineNumber,
    /// @brief 任意电话号码（支持手机号码，3 - 4位区号，7 - 8位直播号码，1－4位分机号）
    eMatchAnyPhoneNumber,

    /// @brief 空白行
    eMatchBlank,
    /// @brief Html标签
    eMatchHtmlTag,
    /// @brief IP地址(提取IP地址)
    eMatchIPAddress,
    /// @brief IP地址
    eMatchIPAddress2,
    /// @brief 提取IPV4时使用
    eMatchIPV4,
    /// @brief 匹配子网掩码
    eMatchNetworkMask,
    /// @brief 国内身份证号
    eMatchIDCard,
    /// @brief 腾讯QQ号
    eMatchTencentQQNumber,
    /// @brief 中国邮政编码
    eMatchChinaPostalCode,
    /// @brief 密码（以字母开头，长度在6~18之间，只能包含字母、数字和下划线）
    eMatchPassword,
    /// @brief 强密码(必须包含大小写字母和数字的组合，不能使用特殊字符，长度在8-10之间)
    eMatchStrongPassword,

    /**
     * @details 部分需要输入参数的正则表达式不通过枚举提供
     * @details 仅提供示例，根据具体情况书写
     * 
     * @brief n位的数字
     *      ^\d{n}$
     * @brief 至少n位的数字
     *      ^\d{n,}$
     * @brief m-n位的数字
     *      ^\d{m,n}$
     */
};

struct GsMatchResult
{
    int nStart;
    int nLength;
    GsString strName;
};

using GsMatchResults = std::vector<GsMatchResult>;
using GsMatchGroup = std::map<int, GsString>;


class M2_API GsRegularExpression
{
    void *m_Handle;
    GsString m_Description;
    GsString m_Pattern;

public:
    enum GsRegularOption
    {
        eNoFlag = 0,
        eCASELESS = 1 << 0,
        eMULTILINE = 1 << 1,
        eDOTALL = 1 << 2,
        eEXTENDED = 1 << 3,
        eANCHORED = 1 << 4,
        eDOLLAR_ENDONLY = 1 << 5,
        eEXTRA = 1 << 6,
        eNOTBOL = 1 << 7,
        eNOTEOL = 1 << 8,
        eUNGREEDY = 1 << 9,
        eNOTEMPTY = 1 << 10,
        eUTF8 = 1 << 11,
        eNO_AUTO_CAPTURE = 1 << 12,
        eNO_UTF8_CHECK = 1 << 13,
        eFIRSTLINE = 1 << 14,
        eDUPNAMES = 1 << 15,
        eNEWLINE_CR = 1 << 16,
        eNEWLINE_LF = 1 << 17,
        eNEWLINE_CRLF = 1 << 18,
        eNEWLINE_ANY = 1 << 19,
        eNEWLINE_ANYCRLF = 1 << 20,
        eGLOBAL = 1 << 21,
        eNO_VARS = 1 << 22
    };
    GS_DECLARE_FLAGS(GsRegularOptions, GsRegularOption)

public:
    /// @brief 缺省构造
    GsRegularExpression();
    /// @brief 从正则表达式和标识构造
    /// @param pattern 正则表达式，使用 \0 作为结束标志。
    /// @param options 表达式匹配模式。
    GsRegularExpression(const char *pattern, GsRegularOptions options = GsRegularOptions());
    ~GsRegularExpression();

    /// @brief 获取常用的正则表达式匹配串
    /// @param eRegex
    /// @return
    static GsString WellknownRegex(GsWellknownRegex eRegex);

    /// @brief 判断字符串是否符合正则表达式的模式
    static bool IsMatch(const char *str, const char *strPattern);
    /// @brief 将*?来模糊搜索通配符转换为正则表达式
    static GsString WildcardToRegexp(const char *wildcard);

    /// @brief 正则表达式的描述
    GsString Description() const;
    /// @brief 正则表达式的描述
    void Description(const char *desc);
    /// @brief 模式定义字符串
    GsString Pattern() const;

    /// @brief 重新设置正则表达式
    bool Compile(const char *tstring, GsRegularOptions flag = GsRegularOptions());

    /// @brief 匹配 (仅仅匹配一次)
    /// @param tstring 进行匹配的字符串，使用 \0 作为结束标志
    /// @param options 匹配标识
    /// @return
    GsMatchResult Match(const char *tstring, GsRegularOptions options = GsRegularOptions()) const;
    /// @brief 匹配 (仅仅匹配一次)
    /// @param tstring 进行匹配的字符串，使用 \0 作为结束标志
    /// @param start 开始查找匹配的位置
    /// @param options 匹配标识
    /// @return
    GsMatchResult Match(const char *tstring, int start, GsRegularOptions options = GsRegularOptions()) const;

    bool operator==(const char *tstring) const;

    bool operator!=(const char *tstring) const;

    int Split(const char *tstring, int start, GsStringList &strings, GsRegularOptions options = GsRegularOptions()) const;

    int Substr(char *tstring, const char *replacement, GsRegularOptions options = GsRegularOptions()) const;

    int Substr(char *tstring, int start, const char *replacement, GsRegularOptions options = GsRegularOptions()) const;

    static bool Match(const char *tstring, const char *pattern, GsRegularOptions options = GsRegularOptions());

    /// @brief 进行文本替换操作。
    /// @param tstring 被替换的原始字符串，使用 \0 作为结束标志。
    /// @param replaceto “替换为”字符串，将匹配到的子字符串替换成 replaceto 字符串。
    /// @param start 进行查找替换的开始位置。默认(-1)表示根据是否是 RIGHTTOLEFT 自动决定开始位置。
    /// @param ntimes 指定进行替换的次数。默认(-1)表示替换所有匹配。
    /// @param result 匹配结果 GsMatchResult 对象
    /// @param options
    /// @return 替换后得到的新字符串。
    GsString Replace(const char *tstring, const char *replaceto, int start = -1, int ntimes = -1,
                     GsMatchResult *result = 0, GsRegularOptions options = GsRegularOptions()) const;
    /// @brief 进行文本替换操作。
    /// @param tstring 被替换的原始字符串，使用 string_length 数量为结束标志。
    /// @param string_length 被替换的原始字符串，取(0,string_length)子串当做原始字符串
    /// @param replaceto “替换为”字符串，将匹配到的子字符串替换成 replaceto 字符串。
    /// @param to_length “替换为”字符串，取(0,to_length)子串当做“替换为”字符串
    /// @param start 行查找替换的开始位置。默认(-1)表示根据是否是 RIGHTTOLEFT 自动决定开始位置。
    /// @param ntimes 指定进行替换的次数。默认(-1)表示替换所有匹配。
    /// @param result 匹配结果 GsMatchResult 对象
    /// @param options
    /// @return 替换后得到的新字符串。
    GsString Replace(const char *tstring, int string_length, const char *replaceto, int to_length,
                     int start = -1, int ntimes = -1, GsMatchResult *result = 0, GsRegularOptions options = GsRegularOptions()) const;


protected:
    int substOne(char *tstring, int start, const char *replacement, GsRegularOptions options) const;
    static int compileOptions(GsRegularOptions options);
    static int matchOptions(GsRegularOptions options);

private:
    GsMatchGroup _groups;
};


}// namespace m2
