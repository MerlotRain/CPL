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

#ifndef M2_UUID_H_
#define M2_UUID_H_

#include <m2_bytebuffer.h>
#include <preconfig.h>

namespace m2 {

class M2_API UUID
{
public:
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
    UUID() noexcept;
    UUID(unsigned int l, unsigned short w1, unsigned short w2, unsigned char b1, unsigned char b2, unsigned char b3,
         unsigned char b4, unsigned char b5, unsigned char b6, unsigned char b7, unsigned char b8);

    /// @brief 拷贝构造
    /// @param
    UUID(const UUID &) noexcept;

    /// @brief 赋值复制构造
    /// @param
    /// @return
    UUID &operator=(const UUID &) noexcept;

    /// @brief 判断两个uuid是否相等
    /// @param ths
    /// @return
    bool operator==(const UUID &ths) const noexcept;
    /// @brief 判断两个uuid不相等
    /// @param orig
    /// @return
    bool operator!=(const UUID &orig) const noexcept;
    /// @brief 比较两个uuid
    /// @param other
    /// @return
    bool operator<(const UUID &other) const noexcept;
    bool operator>(const UUID &other) const noexcept;

    /// @brief 创建基于随机数的UUID
    /// @return
    static UUID CreateUuid();

    /// @brief 创建基于MD5算法的UUID
    /// @param ns
    /// @param baseData
    /// @return
    static UUID CreateUuidV3(const UUID &ns, const String &baseData);

    /// @brief 创建基于SHA1算法的UUID
    /// @param ns
    /// @param baseData
    /// @return
    static UUID CreateUuidV5(const UUID &ns, const String &baseData);

    /// @brief 转换为字符串
    /// @param format
    /// @return
    String ToString(StringFormat format = StringFormat::eHyphens32);

    bool IsNull() const noexcept;

    UUID::UUIDVariant Variant() const noexcept;
    UUID::UUIDVersion Version() const noexcept;

    ByteBuffer ToRfc4122() const;
    static UUID FromRfc4122(const ByteBuffer &);
};

inline bool operator<=(const UUID &lhs, const UUID &rhs) noexcept
{
    return !(rhs < lhs);
}
inline bool operator>=(const UUID &lhs, const UUID &rhs) noexcept
{
    return !(lhs < rhs);
}


}// namespace m2

#endif//M2_UUID_H_