/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file crthelp.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/

#pragma once

#include "preconfig.h"

namespace Lite {
namespace Utility {

/// @brief 封装不同平台下的C语言运行时函数CRT
class UTILITY_EXPORT GsCRT
{
public:
    /// @brief 计算四舍五入的结果
    /// @param r
    /// @return
    static double round(double r);
    /// @brief 按照进制转换字符串为64位整数
    /// @param str 开始指针
    /// @param endptr 结束指针
    /// @param base 进制2,4,8,10,16等
    /// @return
    static long long strtoll(const char *str, char **endptr, int base);

    /// @brief 判断double是否是无效值
    /// @return 返回1标示是有效的0标示无效
    /// @param x
    static int isnan(double x);
    /// @brief 判断double是否是无穷大、无穷小
    /// @return 返回1标示是无穷大或无穷小的0标示不是
    /// @param x
    static int isinf(double x);

    /// @brief 比较两个字符串第n个字符长的大小，忽略大小写。
    /// @return 返回1或0或-1
    /// @param dst
    /// @param src
    /// @param count
    static int strnicmp(const char *dst, const char *src, int count);

    /// @brief 比较两个字符串第n个字符长的大小
    /// @return 返回1或0或-1
    /// @param dst
    /// @param src
    /// @param count
    static int strncmp(const char *dst, const char *src, int count);

    /// @brief 比较2个常量字符串的大小，忽略大小写
    /// @return 返回1或0或-1
    /// @param string1
    /// @param string2
    static int stricmp(const char *string1, const char *string2);

    /// @brief 把常量字符串转换成long long类型
    /// @return 返回long long类型整数
    /// @param _String
    static long long atoi64(const char *_String);

    /// @brief 把常量字符串转换成double类型
    /// @return 返回double类型浮点
    /// @param _String
    static double atof(const char *_String);

    /// @brief 设定文件或文件夹的访问权限
    /// @return 成功返回0，否则返回-1
    /// @param _Filename
    /// @param _AccessMode
    static int access(const char *_Filename, int _AccessMode);

    /// @brief 转换浮点数据为字符串
    /// @param dblValue 要转换的浮点数
    /// @param nNumOfDigits 要使用的进制[2~16]
    /// @param pDstBuf 存储字符串的缓冲区
    /// @return 返回输入缓冲区的首地址
    static const char *gcvt(double dblValue, int nNumOfDigits, char *pDstBuf);

    /// @brief 转换整数为字符串
    /// @param nVal 要转换的整数数
    /// @param nRadix 要使用的进制[2~16]
    /// @param pDstBuf 存储字符串的缓冲区
    /// @return 返回输入缓冲区的首地址
    static const char *itoa(int nVal, char *pDstBuf, int nRadix);
};

}// namespace Utility
}// namespace Lite
