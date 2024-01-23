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

#ifndef M2_REGULAREXPRESSION_H_
#define M2_REGULAREXPRESSION_H_

#include <m2_flags.h>
#include <m2_string.h>

namespace m2 {


struct MatchResult
{
    int nStart;
    int nLength;
    String strName;
};

using MatchResults = std::vector<MatchResult>;
using MatchGroup = std::map<int, String>;


class LIBM2_EXPORT RegularExpression
{
    void *m_Handle;
    String m_Description;
    String m_Pattern;

public:
    enum WellknownRegex
    {
        eMatchInt,
        eMatchFloat,
        eMatchNumber,
        eMatchNumberZeroOrStartWithNoneZero,
        eMathNumberWith2Decimal,
        eMatchSignedWith2Decimal,
        eMatchPositiveWith2Decimal,
        eMatchPositiveWith3Decimal,
        eMatchPositiveNotZero,
        eMatchNegativeNotZero,
        eMatchNotNegative,
        eMatchNotPositive,
        eMatchNotPositiveFloat,
        eMatchNotNegativeFloat,
        eMatchNegativeFloat,
        eMatchPositiveFloat,

        eMatchChineseCharacter,
        eMatchEnglishAndNumber,
        eMatchEnglishAlphabet,
        eMatchEnglishAlphabetUppercase,
        eMatchEnglishAlphabetLowercase,
        eMatchChineseEnglishNumberUnderline,
        eMatchChineseEnglishNumberWithoutUnderline,

        eMatchEMailAddress,
        eMatchDomainName,
        eMatchInternetAddress,

        eMathcHandphoneNumber,
        eMathcChinaLandlineNumber,
        eMatchAnyPhoneNumber,

        eMatchBlank,
        eMatchHtmlTag,
        eMatchIPAddress,
        eMatchIPAddress2,

        eMatchIPV4,
        eMatchNetworkMask,
        eMatchIDCard,

        eMatchTencentQQNumber,
        eMatchChinaPostalCode,
        eMatchPassword,
        eMatchStrongPassword,
    };

    enum RegularOption
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
    M2_DECLARE_FLAGS(RegularOptions, RegularOption)

public:
    RegularExpression();
    RegularExpression(const char *pattern,
                      RegularOptions options = RegularOptions());
    RegularExpression(const RegularExpression &);
    RegularExpression &operator=(const RegularExpression &);
    RegularExpression(RegularExpression &&);
    RegularExpression &operator=(RegularExpression &&);
    ~RegularExpression();

    static String WellknownRegex(WellknownRegex eRegex);
    static bool IsMatch(const char *str, const char *strPattern);
    static String WildcardToRegexp(const char *wildcard);

    String description() const;

    void setDescription(const char *desc);
    String pattern() const;

    bool compile(const char *tstring, RegularOptions flag = RegularOptions());
    MatchResult match(const char *tstring,
                      RegularOptions options = RegularOptions()) const;
    MatchResult match(const char *tstring, int start,
                      RegularOptions options = RegularOptions()) const;

    bool operator==(const char *tstring) const;
    bool operator!=(const char *tstring) const;

    int Split(const char *tstring, int start, StringList &strings,
              RegularOptions options = RegularOptions()) const;
    int Substr(char *tstring, const char *replacement,
               RegularOptions options = RegularOptions()) const;
    int Substr(char *tstring, int start, const char *replacement,
               RegularOptions options = RegularOptions()) const;
    static bool Match(const char *tstring, const char *pattern,
                      RegularOptions options = RegularOptions());

    String Replace(const char *tstring, const char *replaceto, int start = -1,
                   int ntimes = -1, MatchResult *result = 0,
                   RegularOptions options = RegularOptions()) const;
    String Replace(const char *tstring, int string_length,
                   const char *replaceto, int to_length, int start = -1,
                   int ntimes = -1, MatchResult *result = 0,
                   RegularOptions options = RegularOptions()) const;

protected:
    int substOne(char *tstring, int start, const char *replacement,
                 RegularOptions options) const;
    static int compileOptions(RegularOptions options);
    static int matchOptions(RegularOptions options);

private:
    MatchGroup _groups;
};

}// namespace m2

#endif//M2_REGULAREXPRESSION_H_