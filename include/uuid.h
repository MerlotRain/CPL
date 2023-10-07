
/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file uuid.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/

#pragma once

#include "bytebuffer.h"
#include "stringhelp.h"

namespace Lite {
namespace Utility {


struct UTILITY_EXPORT GsUUID
{
    unsigned int Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned short Data4[8];

    enum UUIDVariant
    {
        VarUnknown = -1,
        NCS = 0,      // 0 - -
        DCE = 2,      // 1 0 -
        Microsoft = 6,// 1 1 0
        Reserved = 7  // 1 1 1
    };

    enum StringFormat
    {
        /// @brief 32的数字连字符分隔
        /// @details 00000000-0000-0000-0000-000000000000
        eHyphens32 = 'D',
        /// @brief 32位数
        /// @details 00000000000000000000000000000000
        eNumber32 = 'N',
        /// @brief 32的数字连字符分隔包含在大括号中
        /// @details {00000000-0000-0000-0000-000000000000}
        eHyphensBraces = 'B',
        /// @brief 32的数字连字符分隔包含在圆括号中
        /// @details (00000000-0000-0000-0000-000000000000)
        eHyphensParentheses = 'P'
    };

    enum UUIDVersion
    {
        /// @brief 未知的版本
        VerUnknown = -1,
        /// @brief timestamp + MAC地址。
        Time = 1,
        /// @brief 基于 v1 的基础上优化了下，更安全。
        EmbeddedPOSIX = 2,
        /// @brief 基于 namespace + 输入内容 进行MD5
        Md5 = 3,
        Name = Md5,
        /// @brief 基于随机数
        Random = 4,
        /// @brief 使用SHA1计算
        Sha1 = 5
        ///
    };

    /// @brief 默认使用随机数生成Uuid
    /// @param version
    GsUUID() noexcept;
    GsUUID(unsigned int l, unsigned short w1, unsigned short w2, unsigned char b1, unsigned char b2, unsigned char b3,
           unsigned char b4, unsigned char b5, unsigned char b6, unsigned char b7, unsigned char b8);

    /// @brief 拷贝构造
    /// @param
    GsUUID(const GsUUID &) noexcept;

    /// @brief 赋值复制构造
    /// @param
    /// @return
    GsUUID &operator=(const GsUUID &) noexcept;

    /// @brief 判断两个uuid是否相等
    /// @param ths
    /// @return
    bool operator==(const GsUUID &ths) const noexcept;
    /// @brief 判断两个uuid不相等
    /// @param orig
    /// @return
    bool operator!=(const GsUUID &orig) const noexcept;
    /// @brief 比较两个uuid
    /// @param other
    /// @return
    bool operator<(const GsUUID &other) const noexcept;
    bool operator>(const GsUUID &other) const noexcept;

    /// @brief 创建基于随机数的UUID
    /// @return
    static GsUUID CreateUuid();

    /// @brief 创建基于MD5算法的UUID
    /// @param ns
    /// @param baseData
    /// @return
    static GsUUID CreateUuidV3(const GsUUID &ns, const GsString &baseData);

    /// @brief 创建基于SHA1算法的UUID
    /// @param ns
    /// @param baseData
    /// @return
    static GsUUID CreateUuidV5(const GsUUID &ns, const GsString &baseData);

    /// @brief 转换为字符串
    /// @param format
    /// @return
    GsString ToString(StringFormat format = StringFormat::eHyphens32);

    bool IsNull() const noexcept;

    GsUUID::UUIDVariant Variant() const noexcept;
    GsUUID::UUIDVersion Version() const noexcept;

    GsByteBuffer ToRfc4122() const;
    static GsUUID FromRfc4122(const GsByteBuffer &);
};

inline bool operator<=(const GsUUID &lhs, const GsUUID &rhs) noexcept
{
    return !(rhs < lhs);
}
inline bool operator>=(const GsUUID &lhs, const GsUUID &rhs) noexcept
{
    return !(lhs < rhs);
}

}// namespace Utility
}// namespace Lite
