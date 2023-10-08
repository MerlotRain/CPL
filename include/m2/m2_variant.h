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

#include "datetime.h"
#include "object.h"
#include "stringhelp.h"

namespace m2 {

/// @brief Variant对象的数据类型
enum GsVarType
{
    /// @brief 未知数据
    eUnknownVarType = -2,
    /// @brief 空数据
    eEmpty = -1,
    /// @brief char
    eI1 = 0,
    /// @brief short
    eI2,
    /// @brief int
    eI4,
    /// @brief long long
    eI8,
    /// @brief unsigned char
    eUI1,
    /// @brief unsigned short
    eUI2,
    /// @brief unsigned int
    eUI4,
    /// @brief unsigned long long
    eUI8,
    /// @brief float
    eR4,
    /// @brief double
    eR8,
    /// @brief const char*
    eString,
    /// @brief bool
    eBool,
    /// @brief GsRefObject*
    eObject,
    /// @brief 二进制数据
    eBlob,

    /// @brief 时间日期类型
    eDateTime,
};


class GsVariant
{
public:
    GsVarType Type;
    union
    {
        char cVal;
        unsigned char ucVal;
        short sVal;
        unsigned short usVal;
        int iVal;
        unsigned int uiVal;
        long long llVal;
        unsigned long long ullVal;
        float fltVal;
        double dblVal;
        bool boolVal;
        GsRefObject *objVal;
        char *strVal;
        unsigned char *blbVal;
        long long dateVal;
    };

    virtual ~GsVariant();

    /// @brief 构造函数重载
    GsVariant();
    /// @brief 单字符构造函数
    /// @param v
    GsVariant(char v);
    /// @brief 无符号字符构造函数
    /// @param v
    GsVariant(unsigned char v);
    /// @brief 16位的构造函数
    /// @param v
    GsVariant(short v);
    /// @brief 无符号16位的构造函数
    /// @param v
    GsVariant(unsigned short v);
    /// @brief 32位的构造函数
    /// @param v
    GsVariant(int v);
    /// @brief 无符号32位的构造函数
    /// @param v
    GsVariant(unsigned int v);
    /// @brief 64位的构造函数
    /// @param v
    /// @param bDateTime
    GsVariant(long long v, bool bDateTime = false);
    /// @brief 无符号64位的构造函数
    /// @param v
    GsVariant(unsigned long long v);
    /// @brief 32位浮点构造函数
    /// @param v
    GsVariant(float v);
    /// @brief 64位浮点构造函数
    /// @param v
    GsVariant(double v);
    /// @brief bool类型构造函数
    /// @param v
    GsVariant(bool v);
    /// @brief GsRefObject类指针的构造函数
    /// @param v
    GsVariant(GsRefObject *v);
    /// @brief 字符常量构造函数
    /// @param v
    GsVariant(const char *v);
    /// @brief 字符常量构造函数
    /// @param str
    GsVariant(const GsString &str);

    /// @brief 无符号字符常量构造函数
    /// @param v
    /// @param nLen
    GsVariant(const unsigned char *v, int nLen);
    /// @brief 类引用构造函数
    /// @param rhs
    GsVariant(const GsVariant &rhs);
    /// @brief 移动构造
    /// @param rhs
    GsVariant(GsVariant &&rhs);

    /// @brief 构造指定类型的空数据
    /// @param rhs
    GsVariant(GsVarType type);

    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(const GsVariant &rhs);
    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(char v);
    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(unsigned char v);
    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(short v);
    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(unsigned short v);
    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(int v);
    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(unsigned int v);
    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(long long v);
    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(unsigned long long v);
    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(float v);
    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(double v);
    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(bool v);
    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(const char *v);
    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(const GsString &str);

    /// @brief 符号重载，返回引用类型
    GsVariant &operator=(GsRefObject *v);

    /// @brief 移动赋值
    GsVariant &operator=(GsVariant &&v);

    /// @brief 是否相等
    bool operator==(const GsVariant &o) const;
    /// @brief 是否相等
    bool operator!=(const GsVariant &o) const;

    /// \brief
    void Clear();

    /// @brief 获取字符
    char AsChar() const;
    /// @brief 获取无符号字符
    unsigned char AsUChar() const;
    /// @brief 获取短整型数
    short AsShort() const;
    /// @brief 获取16位短整型数
    unsigned short AsUShort() const;
    /// @brief 获取32位整数
    int AsInt() const;
    /// @brief 获取32位无符号整数
    unsigned int AsUInt() const;
    /// @brief 获取64位整数
    long long AsLongLong() const;
    /// @brief 获取64位无符号整数
    unsigned long long AsULongLong() const;
    /// @brief 获取32位浮点数
    float AsFloat() const;
    /// @brief 获取64位浮点数
    double AsDouble() const;
    /// @brief 获取bool的值
    bool AsBool() const;
    /// @brief 获取GsRefObject类
    GsRefObject *AsObject() const;
    /// @brief 获取字符串
    char *AsString() const;
    /// @brief 获取二进制数据块
    /// @param bBlob
    int AsBlob(unsigned char *bBlob) const;

    /// @brief 类型转换
    operator char() const;
    /// @brief 类型转换
    operator unsigned char() const;
    /// @brief 类型转换
    operator short() const;
    /// @brief 类型转换
    operator unsigned short() const;
    /// @brief 类型转换
    operator int() const;
    /// @brief 类型转换
    operator unsigned int() const;
    /// @brief 类型转换
    operator long long() const;
    /// @brief 类型转换
    operator unsigned long long() const;
    /// @brief 类型转换
    operator bool() const;
    /// @brief 类型转换
    operator float() const;
    /// @brief 类型转换
    operator double() const;
    /// @brief 类型转换
    operator const char *() const;
    /// @brief 类型转换
    operator GsRefObject *();

    /// @brief 设置blob数据
    /// @param bBlob
    /// @param nLen
    void Set(const unsigned char *bBlob, int nLen);
    /// @brief 设置字符串数据
    /// @param str
    /// @param nLen
    void Set(const char *str, int nLen);

    /// @brief 分配空的blob空间，并设置类型为blob
    /// @param nLen
    /// @return
    unsigned char *AllocBlob(int nLen);

    /// @brief 数据的大小
    /// @return 返回数据的长度
    int ValueSize() const;

    /// @brief 数据的头指针
    /// @return 返回数据的头指针地址
    const void *ValuePtr() const;

    /// @brief 计算对象的哈希值
    /// @return 返回哈希值
    unsigned long long HashCode() const;

    /// @brief 数据的文本
    /// @return 返回数据的文本内容
    GsString ToString() const;

    /// @brief 交换数据
    void Swap(GsVariant &rhs);

    /// @brief 空对象
    static const GsVariant &Empty();
};


}// namespace m2
