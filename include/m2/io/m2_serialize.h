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
#include "preconfig.h"
#include "stringhelp.h"
#include "variant.h"

namespace m2 {

/// @brief 序列化流基类
class SerializeStream : public RefObject
{
public:
    virtual ~SerializeStream() {}

    /// @brief 转换为字符串
    /// @details 根据流类型转换为XML或JSON格式
    /// @return
    virtual String ToString() = 0;

    /// @brief 设置字符串内容，用于内部解析使用
    /// @param str
    virtual void SetString(const char *str) = 0;

    /// @brief 开始一个对象的存储
    /// @param name
    /// @param type
    virtual void BeginEntry(const char *name, const char *type) = 0;

    /// @brief 结束一个对象的存储
    virtual void EndEntry() = 0;

    /// @brief 判断一个属性是否存在
    /// @param name 属性名称
    /// @return
    virtual bool Exists(const char *name) = 0;

    /// @brief 设置指定key的指定字符串值
    /// @param key 属性名称
    /// @param value 属性值
    virtual void Save(const char *key, const char *value) = 0;

    /// @brief 设置指定key的指定int值
    /// @param key 属性名称
    /// @param value 属性值
    virtual void Save(const char *key, int value) = 0;

    /// @brief 设置指定key的指定unsigned int值
    /// @param key 属性名称
    /// @param value 属性值
    virtual void Save(const char *key, unsigned int value) = 0;

    /// @brief 设置指定key的指定long long值
    /// @param key 属性名称
    /// @param value 属性值
    virtual void Save(const char *key, long long value) = 0;

    /// @brief 设置指定key的指定unsigned long long值
    /// @param key 属性名称
    /// @param value 属性值
    virtual void Save(const char *key, unsigned long long value) = 0;

    /// @brief 设置指定key的指定bool值
    /// @param key 属性名称
    /// @param value 属性值
    virtual void Save(const char *key, bool value) = 0;

    /// @brief 设置指定key的指定float值
    /// @param key 属性名称
    /// @param value 属性值
    virtual void Save(const char *key, float value) = 0;

    /// @brief 设置指定key的指定double值
    /// @param key 属性名称
    /// @param value 属性值
    virtual void Save(const char *key, double value) = 0;

    /// @brief 设置指定key的指定对象值
    /// @param key 属性名称
    /// @param value 属性值
    virtual void Save(const char *key, RefObject *object) = 0;

    /// @brief 设置指定key的指定日期值
    /// @param key 属性名称
    /// @param value 属性值
    virtual void Save(const char *key, DateTime dateTime) = 0;

    /// @brief 读取指定key的字符串值
    /// @param key 属性名称
    /// @param defaultValue 默认值
    /// @return
    virtual String LoadStringValue(const char *key, const char *defaultValue) = 0;

    /// @brief 读取指定key的int值
    /// @param key 属性名称
    /// @param defaultValue 默认值
    /// @return
    virtual int LoadInt32Value(const char *key, int defaultValue) = 0;

    /// @brief 读取指定key的unsigned int值
    /// @param key 属性名称
    /// @param defaultValue 默认值
    /// @return
    virtual unsigned int LoadUInt32Value(const char *key, unsigned int defaultValue) = 0;

    /// @brief 读取指定key的long long值
    /// @param key 属性名称
    /// @param defaultValue 默认值
    /// @return
    virtual long long LoadInt64Value(const char *key, long long defaultValue) = 0;

    /// @brief 读取指定key的unsigned long long值
    /// @param key 属性名称
    /// @param defaultValue 默认值
    /// @return
    virtual unsigned long long LoadUInt64Value(const char *key, unsigned long long defaultValue) = 0;

    /// @brief 读取指定key的bool值
    /// @param key 属性名称
    /// @param defaultValue 默认值
    /// @return
    virtual bool LoadBoolValue(const char *key, bool defaultValue) = 0;

    /// @brief 读取指定key的float值
    /// @param key 属性名称
    /// @param defaultValue 默认值
    /// @return
    virtual float LoadFloatValue(const char *key, float defaultValue) = 0;

    /// @brief 读取指定key的double值
    /// @param key 属性名称
    /// @param defaultValue 默认值
    /// @return
    virtual double LoadDoubleValue(const char *key, double defaultValue) = 0;

    /// @brief 读取指定key的日期值
    /// @param key 属性名称
    /// @param defaultValue 默认值
    /// @return
    virtual DateTime LoadDateTimeValue(const char *key, const DateTime &defaultValue) = 0;

    /// @brief 读取指定key的对象
    /// @param key 属性名称
    /// @param defaultValue 默认值
    /// @return
    virtual RefObject *LoadRefObjectValue(const char *key) = 0;

    /// @brief 读取指定key的对象
    /// @tparam T 对象类型
    /// @param key 属性名称
    /// @return
    template<typename T>
    SharedPointer<T> LoadRefObjectValueT(const char *key)
    {
        RefObject *ref = LoadObjectValue(key);
        if (!ref)
        {
            return 0;
        }
        T *o = dynamic_cast<T *>(ref);
        if (!o)
        {
            ref->release();
            return 0;
        }
        return SharedPointer<T>(o, false);
    }
};
GS_SMARTER_PTR(SerializeStream)


/// @brief 序列化接口
class SerializeInterface
{
public:
    /// @brief 对象序列化为流
    /// @param pStream
    virtual bool Serialize(SerializeStream *pStream) = 0;

    /// @brief 对象反序列化为流
    /// @param pStream
    virtual bool DeSerialize(SerializeStream *pStream) = 0;
};

/// @brief 序列化流类型
enum SerializeStreamType
{
    /// @brief XML流
    eXML,
    /// @brief Json流
    eJSON,
    /// @brief Cbor流，物联网数据交换流
    /// @details https://cbor.io/
    eCbor,
};

/// @brief 序列化流工厂
class SerializeStreamFactory
{
public:
    /// @brief 创建序列化流对象
    /// @param type
    /// @return
    static SerializeStreamPtr CreateStream(SerializeStreamType eType);
};

}// namespace m2
