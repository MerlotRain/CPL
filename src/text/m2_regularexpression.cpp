#include <m2_regularexpression.h>
#include <pcre2.h>
#include <pcre2posix.h>

namespace m2 {

RegularExpression::RegularExpression() {}

RegularExpression::RegularExpression(const char *pattern,
                                     RegularOptions options)
{
}

RegularExpression::~RegularExpression() {}

String RegularExpression::WellknownRegex(WellknownRegex eRegex)
{
    switch (eRegex)
    {
        ///@brief 匹配整数
        case eMatchInt:
            return "^[0-32]*$";
        ///@brief 匹配浮点数
        case eMatchFloat:
            return "^-?([1-9]\d*\.\d*|0\.\d*[1-9]\d*|0?\.0+|0)$";
        ///@brief 匹配数字
        case eMatchNumber:
            return "^[0-9]*$";
        ///@brief 零或者非零开头的数字
        case eMatchNumberZeroOrStartWithNoneZero:
            return "^(0|[1-9][0-9]*)$";
        ///@brief 非零开头的最多带两位小数的数字
        case eMathNumberWith2Decimal:
            return "^([1-9][0-9]*)+(.[0-9]{1,2})?$";
        ///@brief 带1-2位小数的正数或负数
        case eMatchSignedWith2Decimal:
            return "^(\-)?\d+(\.\d{1,2})?$";
        ///@brief 带2位小数的正数
        case eMatchPositiveWith2Decimal:
            return "^[0-9]+(.[0-9]{2})?$";
        ///@brief 带1~3位小数的正数
        case eMatchPositiveWith3Decimal:
            return "^[0-9]+(.[0-9]{1,3})?$";
        ///@brief 非零的正整数
        case eMatchPositiveNotZero:
            return "^[1-9]\d*$";
        ///@brief 非零的负整数
        case eMatchNegativeNotZero:
            return "^-[1-9]\d*$";
        ///@brief 非负整数
        case eMatchNotNegative:
            return "^[1-9]\d*|0$";
        ///@brief 非正整数
        case eMatchNotPositive:
            return " ^((-\d+)|(0+))$";
        ///@brief 非正浮点数
        case eMatchNotPositiveFloat:
            return "^(-([1-9]\d*\.\d*|0\.\d*[1-9]\d*))|0?\.0+|0$";
        ///@brief 非负浮点数
        case eMatchNotNegativeFloat:
            return "^[1-9]\d*\.\d*|0\.\d*[1-9]\d*|0?\.0+|0$";
        ///@brief 负浮点数
        case eMatchNegativeFloat:
            return "^(-(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)"
                   "|([0-9]*[1-9][0-9]*)))$";
        ///@brief 正浮点数
        case eMatchPositiveFloat:
            return "^(([0-9]+\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\.[0-9]+)|("
                   "[0-9]*[1-9][0-9]*))$";
        ///@brief 汉字
        case eMatchChineseCharacter:
            return "^[\u4e00-\u9fa5]{0,}$";
        ///@brief 英文和数字
        case eMatchEnglishAndNumber:
            return "^[A-Za-z0-9]+$";
        ///@brief 由26个英文字母组成的字符串
        case eMatchEnglishAlphabet:
            return "^[A-Za-z]+$";
        ///@brief 由26个大写英文字母组成的字符串
        case eMatchEnglishAlphabetUppercase:
            return "^[A-Z]+$";
        ///@brief 由26个小写英文字母组成的字符串
        case eMatchEnglishAlphabetLowercase:
            return "^[a-z]+$";
        ///@brief 中文、英文、数字包括下划线
        case eMatchChineseEnglishNumberUnderline:
            return "^[\u4E00-\u9FA5A-Za-z0-9_]+$";
        /// @brief 中文、英文、数字但不包括下划线
        case eMatchChineseEnglishNumberWithoutUnderline:
            return "^[\u4E00-\u9FA5A-Za-z0-9]+$";
        ///@brief 电子邮件地址
        case eMatchEMailAddress:
            return "^\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$";
        ///@brief 域名
        case eMatchDomainName:
            return "[a-zA-Z0-9][-a-zA-Z0-9]{0,62}(/"
                   ".[a-zA-Z0-9][-a-zA-Z0-9]{0,62})+/.?";
        ///@brief Internet地址
        case eMatchInternetAddress:
            return "[a-zA-z]+://[^\s]* 或 "
                   "^http://([\w-]+\.)+[\w-]+(/[\w-./?%&=]*)?$";
        ///@brief 手机号码
        case eMathcHandphoneNumber:
            return "^(13[0-9]|14[5|7]|15[0|1|2|3|5|6|7|8|9]|18[0|1|2|3|5|6|7|8|"
                   "9])\d{8}$";
        ///@brief 中国固定电话号码区号-号码
        case eMathcChinaLandlineNumber:
            return "\d{3}-\d{8}|\d{4}-\d{7}";
        ///@brief 任意电话号码（支持手机号码，3 - 4位区号，7 - 8位直播号码，1－4位分机号）
        case eMatchAnyPhoneNumber:
            return "^(\(\d{3,4}-)|\d{3.4}-)?\d{7,8}$";
        ///@brief 空白行
        case eMatchBlank:
            return "\n\s*\r";
        ///@brief Html标签
        case eMatchHtmlTag:
            return "<(\S*?)[^>]*>.*?</\1>|<.*? />";
        ///@brief IP地址
        case eMatchIPAddress:
            return "\d+\.\d+\.\d+\.\d+";
        /// @brief IP地址
        case eMatchIPAddress2:
            return "((?:(?:25[0-5]|2[0-4]\\d|[01]?\\d?\\d)\\.){3}(?:25[0-5]|2["
                   "0-4]\\d|[01]?\\d?\\d))";
        /// @brief 提取IPV4时使用
        case eMatchIPV4:
            return "\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25["
                   "0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b";
        /// @brief 匹配子网掩码
        case eMatchNetworkMask:
            return "((?:(?:25[0-5]|2[0-4]\\d|[01]?\\d?\\d)\\.){3}(?:25[0-5]|2["
                   "0-4]\\d|[01]?\\d?\\d))";
        /// @brief 国内身份证号
        case eMatchIDCard:
            return "^\d{15}|\d{18}$";
        /// @brief 腾讯QQ号
        case eMatchTencentQQNumber:
            return "[1-9][0-9]{4,}";
        /// @brief 中国邮政编码
        case eMatchChinaPostalCode:
            return "[1-9]\d{5}(?!\d)";
        /// @brief 密码（以字母开头，长度在6~18之间，只能包含字母、数字和下划线）
        case eMatchPassword:
            return "^[a-zA-Z]\w{5,17}$";
        /// @brief 强密码(必须包含大小写字母和数字的组合，不能使用特殊字符，长度在8-10之间)
        case eMatchStrongPassword:
            return "^(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{8,10}$";
        default:
            break;
    }
    return String();
}

bool RegularExpression::IsMatch(const char *str, const char *strPattern)
{
    return false;
}

String RegularExpression::WildcardToRegexp(const char *wildcard)
{
    return String();
}

String RegularExpression::Description() const { return String(); }

void RegularExpression::Description(const char *desc) {}

String RegularExpression::Pattern() const { return String(); }

bool RegularExpression::Compile(const char *tstring, RegularOptions flag)
{
    return false;
}

MatchResult RegularExpression::Match(const char *tstring,
                                     RegularOptions options) const
{
    return MatchResult();
}

MatchResult RegularExpression::Match(const char *tstring, int start,
                                     RegularOptions options) const
{
    return MatchResult();
}

bool RegularExpression::operator==(const char *tstring) const { return false; }

bool RegularExpression::operator!=(const char *tstring) const { return false; }

int RegularExpression::Split(const char *tstring, int start,
                             StringList &strings, RegularOptions options) const
{
    return 0;
}

int RegularExpression::Substr(char *tstring, const char *replacement,
                              RegularOptions options) const
{
    return 0;
}

int RegularExpression::Substr(char *tstring, int start, const char *replacement,
                              RegularOptions options) const
{
    return 0;
}

bool RegularExpression::Match(const char *tstring, const char *pattern,
                              RegularOptions options)
{
    return false;
}

int RegularExpression::substOne(char *tstring, int start,
                                const char *replacement,
                                RegularOptions options) const
{
    return 0;
}

int RegularExpression::compileOptions(RegularOptions options) { return 0; }

int RegularExpression::matchOptions(RegularOptions options) { return 0; }


}// namespace m2
