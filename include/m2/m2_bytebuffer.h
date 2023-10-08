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

#include "stringhelp.h"

namespace m2 {


/// @brief 内存块对象，内存只会增长，不会主动析构
class UTILITY_EXPORT GsByteBuffer
{
public:
    /// @brief 申请内存块
    /// @param len 内存字节大小
    GsByteBuffer(unsigned int len = 0);

    /// @brief
    /// @param buffer
    GsByteBuffer(unsigned char *buffer);

    /// @brief
    /// @param buffer
    /// @param len
    GsByteBuffer(unsigned char *buffer, int len);

    /// @brief 由字符串构造
    /// @param str
    GsByteBuffer(const char *str);

    /// @brief
    /// @param rhs
    GsByteBuffer(const GsByteBuffer &rhs);

    /// @brief 移动构造，转移所有权，原内存将不可用
    /// @param rhs
    GsByteBuffer(GsByteBuffer &&rhs) noexcept;

    /// @brief 触发析构函数时会主动释放内存
    /// @details 对于不想析构内存，使用指针管理
    virtual ~GsByteBuffer();

    /// @brief 释放内存，传递指针地址
    /// @param buffer
    void Attach(unsigned char *buffer);

    /// @brief 传递指针地址
    /// @return
    unsigned char *Detach();

    /// @brief 类型转换
    explicit operator unsigned char *() const;
    /// @brief 类型转换
    explicit operator char *() const;
    /// @brief 类型转换
    explicit operator int *() const;
    /// @brief 类型转换
    explicit operator unsigned int *() const;
    /// @brief 类型转换
    explicit operator short *() const;
    /// @brief 类型转换
    explicit operator unsigned short *() const;
    /// @brief 类型转换
    explicit operator long long *() const;
    /// @brief 类型转换
    explicit operator unsigned long long *() const;
    /// @brief 类型转换
    explicit operator double *() const;
    /// @brief 类型转换
    explicit operator float *() const;
    /// @brief 类型转换
    explicit operator bool *() const;

    /// @brief 获取数据块头指针
    /// @return
    unsigned char *Ptr() const;
    /// @brief 数据块的尾指针
    /// @return
    virtual unsigned char *EndPtr() const;
    /// @brief
    /// @tparam T
    /// @return
    template<typename T>
    T *PtrT() const
    {
        return (T *) (Ptr());
    }
    /// \brief 函数模板
    template<typename T>
    T *EndPtrT() const
    {
        return (T *) (EndPtr());
    }
    /// @brief 获取头指针
    /// @return
    unsigned char *BufferHead() const;

    /// @brief 获取真实内存块数据块的大小
    /// @return
    unsigned int BufferSize() const;

    template<typename T>
    unsigned int BufferSizeT() const
    {
        return BufferSize() / sizeof(T);
    }

    /// @brief 获取内存块分配的大小，通常来说，BufferLength >= BufferSize
    /// @return
    unsigned int BufferLength() const;

    /// @brief 设置内存整体的值
    /// @param nValue
    /// @return
    unsigned char *SetBufferValue(int nValue);

    template<typename T>
    T *SetBufferValueT(const T &val)
    {
        //获取数据的字节
        const auto *pByte = (const unsigned char *) &val;
        //判断整个数据为重复字节，或者全部为0
        bool bIsEqual = true;
        for (int i = 1; i < sizeof(val); i++)
        {
            if (pByte[i] != pByte[0])
            {
                bIsEqual = false;
                break;
            }
        }
        //如果整个为重复字节。
        if (bIsEqual)
        {
            return (T *) SetBufferValue(pByte[0]);
        }
        //如果是非重复字节这需要逐个赋值
        T *pHead = PtrT<T>();
        T *pEnd = EndPtrT<T>();
        for (; pHead < pEnd; pHead++)
        {
            pHead[0] = val;
        }
        return PtrT<T>();
    }

    /// @brief 向尾部添加一段数据
    /// @details 认为，nLen的长度可以完全读取到pBuff的内容
    /// @param pBuff 新内存的首地址
    /// @param nLen 追加的长度
    /// @return
    unsigned char *Append(const unsigned char *pBuff, int nLen);

    /// @brief 向尾部增加一段字符串
    /// @param pStr
    /// @return
    unsigned char *Append(const char *pStr);

    template<typename T>
    unsigned char *AppendT(const T &pBuff)
    {
        return Append((const unsigned char *) &pBuff, sizeof(T));
    }

    /// @brief 插入一段内存，如果原始内存被截断，则 \a nPos 后的内容将会移动
    /// @param nPos 插入的位置
    /// @param pStr 新内存的头指针
    /// @param nLen 新内存的长度
    /// @return
    unsigned char *Insert(unsigned int nPos, const unsigned char *pStr, int nLen);

    /// @brief 分配nLen个字节内存
    /// @param nLen
    /// @return
    unsigned char *Allocate(unsigned int nLen);
    /// @brief 分配nLen个指定类型
    /// @tparam T
    /// @param nLen
    /// @return
    template<typename T>
    T *AllocateT(int nLen)
    {
        Allocate(sizeof(T) * nLen);
        return PtrT<T>();
    }


    /// @brief 重置内存数据
    virtual void Clear();
    /// @brief 释放内存
    virtual void Reset();

    /// @brief 将输入内存的指定长度拷贝到当前内存块
    /// @param pBuff
    /// @param nLen
    /// @return
    unsigned char *Copy(const unsigned char *pBuff, int nLen);

    /// @brief 从当前内存中读取指定长度数据
    /// @param nLen
    /// @return
    GsByteBuffer ReadSize(int nLen);

    /// @brief 内存空间重置
    /// @param nLen
    void Resize(int nLen);

    /// @brief 交换内存
    /// @param rhs
    /// @return
    GsByteBuffer *Swap(GsByteBuffer &rhs);

    /// @brief 交换内存
    /// @param pBuff
    /// @return
    GsByteBuffer *Swap(unsigned char *pBuff);

    /// @brief 判断内存空间是否为空
    /// @return
    bool IsEmpty() const;

    /// @brief 赋值复制构造
    /// @param rsh
    /// @return
    GsByteBuffer &operator=(const GsByteBuffer &rsh);

    /// @brief 赋值移动构造
    /// @param rsh
    /// @return
    GsByteBuffer &operator=(GsByteBuffer &&rsh) noexcept;

    /// @brief 将二进制内存块转换为base64编码字符串
    /// @return
    GsString ToBase64() const;

    /// @brief 从Base64字符串解码成为内存块
    /// @param strBase64
    /// @return
    bool FromBase64(const char *strBase64);

    /// @brief 判断字符串是否是一个base64编码的字符串
    /// @param strBase64
    /// @return
    static bool IsBase64(const char *strBase64);

private:
    unsigned char *m_Buffer;
};


}// namespace m2
