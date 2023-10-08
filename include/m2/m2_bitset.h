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

#include "bytebuffer.h"

namespace m2 {


/// @brief 比特位管理
class UTILITY_EXPORT GsBitset
{
    GsByteBuffer m_Data;
    unsigned int m_Size = 0;

public:
    /// @brief 位引用
    class Reference
    {
        friend class GsBitset;
        GsBitset *m_Bitset = nullptr;
        int m_Pos = 0;
        explicit Reference(GsBitset &bitset, int pos) noexcept;

    public:
        Reference(const Reference &);
        ~Reference();
        Reference &operator=(bool x) noexcept;
        Reference &operator=(const Reference &) noexcept;

        /// @brief 位引用取反
        /// @return
        bool operator~() const noexcept;
        explicit operator bool() const noexcept;
        /// @brief 位引用取反
        /// @return
        Reference &Flip() noexcept;
    };

    /// @brief 构造
    /// @param nSize 比特位长度
    explicit GsBitset(unsigned int nSize = 0);

    /// @brief 根据字符串构造
    /// @param str
    explicit GsBitset(const char *str);

    /// @brief 拷贝构造
    /// @param r
    GsBitset(const GsBitset &r);

    /// @brief 移动构造
    /// @param rr
    GsBitset(GsBitset &&rr) noexcept;

    /// @brief 赋值复制构造
    /// @param r
    /// @return
    GsBitset &operator=(const GsBitset &r);

    /// @brief 赋值移动构造
    /// @param r
    /// @return
    GsBitset &operator=(GsBitset &&r) noexcept;

    /// @brief 交换
    /// @param bit
    void Swap(GsBitset &bit);

    /// @brief 是否相等
    /// @param r
    /// @return
    bool operator==(const GsBitset &r);

    /// @brief 判断不等
    /// @param r
    /// @return
    bool operator!=(const GsBitset &r);

    /// @brief 是否为空
    /// @return
    bool Empty() const;

    /// @brief &=运算
    /// @param r
    /// @return
    GsBitset &operator&=(const GsBitset &r);

    /// @brief |=运算
    /// @param r
    /// @return
    GsBitset &operator|=(const GsBitset &r);

    /// @brief ^=运算
    /// @param r
    /// @return
    GsBitset &operator^=(const GsBitset &r);

    /// @brief <<=运算
    /// @param pos
    /// @return
    GsBitset &operator<<=(size_t pos) noexcept;

    /// @brief >>=运算
    /// @param pos
    /// @return
    GsBitset &operator>>=(size_t pos) noexcept;

    /// @brief <<运算
    /// @param pos
    /// @return
    GsBitset operator<<(size_t pos) const noexcept;

    /// @brief >>运算
    /// @param pos
    /// @return
    GsBitset operator>>(size_t pos) const noexcept;

    /// @brief 设置所有位
    /// @return
    GsBitset &Set() noexcept;

    /// @brief 设置指定位的状态
    /// @param pos
    /// @param val
    /// @return
    GsBitset &Set(size_t pos, bool val = true);

    /// @brief 清空所有位的状态
    /// @return
    GsBitset &Reset() noexcept;

    /// @brief 清空指定位的状态
    /// @param pos
    /// @return
    GsBitset &Reset(size_t pos);

    /// @brief ~运算，位状态取反
    /// @return
    GsBitset operator~() const noexcept;

    /// @brief 位状态取反
    /// @return
    GsBitset &Flip() noexcept;

    /// @brief 特定位置取反
    /// @param pos
    /// @return
    GsBitset &Flip(size_t pos);

    /// @brief 元素访问
    /// @param pos
    /// @return
    bool operator[](size_t pos) const;

    /// @brief 访问引用
    /// @param pos
    /// @return
    Reference operator[](size_t pos);

    /// @brief bit位长度
    /// @return
    static unsigned int Size();

    /// @brief 向尾部添加一个bit位
    /// @param bit
    /// @return
    GsBitset &PushBack(bool bit);

    /// @brief 分配特定长度的容器
    /// @param size
    /// @return
    GsBitset &Resize(int size);

    /// @brief 保留空间
    /// @param size
    /// @return
    GsBitset &Reverse(int size);

    /// @brief 获取bit位状态
    /// @param n
    /// @return
    static bool Test(unsigned int n);

    /// @brief 是否所有位状态为空
    /// @return
    static bool None();

    /// @brief 是否存在任何状态为true
    /// @return
    static bool Any();

    /// @brief 是否所有状态为true
    /// @return
    static bool All();

    /// @brief 状态为true的位数量
    /// @return
    bool Count() const;

    /// @brief 转换成字符串
    /// @return
    GsString ToString() const;
};


}// namespace m2
