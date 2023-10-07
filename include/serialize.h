/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file serialize.h
 * @brief
 * @details
 * @date 2023-06-19
 * @author
 *
 ******************************************************************************/

#pragma once

#include "datetime.h"
#include "object.h"
#include "preconfig.h"
#include "stringhelp.h"
#include "variant.h"

namespace Lite {
namespace Utility {

/// @brief 序列化流基类
class GsSerializeStream : public GsRefObject
{
public:
    virtual ~GsSerializeStream() {}

    /// @brief 转换为字符串
    /// @details 根据流类型转换为XML或JSON格式
    /// @return
    virtual GsString ToString() = 0;

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
    virtual void Save(const char *key, GsRefObject *object) = 0;

    /// @brief 设置指定key的指定日期值
    /// @param key 属性名称
    /// @param value 属性值
    virtual void Save(const char *key, GsDateTime dateTime) = 0;

    /// @brief 读取指定key的字符串值
    /// @param key 属性名称
    /// @param defaultValue 默认值
    /// @return
    virtual GsString LoadStringValue(const char *key, const char *defaultValue) = 0;

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
    virtual GsDateTime LoadDateTimeValue(const char *key, const GsDateTime &defaultValue) = 0;

    /// @brief 读取指定key的对象
    /// @param key 属性名称
    /// @param defaultValue 默认值
    /// @return
    virtual GsRefObject *LoadRefObjectValue(const char *key) = 0;

    /// @brief 读取指定key的对象
    /// @tparam T 对象类型
    /// @param key 属性名称
    /// @return
    template<typename T>
    GsSharedPointer<T> LoadRefObjectValueT(const char *key)
    {
        GsRefObject *ref = LoadObjectValue(key);
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
GS_SMARTER_PTR(GsSerializeStream)


/// @brief 序列化接口
class GsSerializeInterface
{
public:
    /// @brief 对象序列化为流
    /// @param pStream
    virtual bool Serialize(GsSerializeStream *pStream) = 0;

    /// @brief 对象反序列化为流
    /// @param pStream
    virtual bool DeSerialize(GsSerializeStream *pStream) = 0;
};

/// @brief 序列化流类型
enum GsSerializeStreamType
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
class GsSerializeStreamFactory
{
public:
    /// @brief 创建序列化流对象
    /// @param type
    /// @return
    static GsSerializeStreamPtr CreateStream(GsSerializeStreamType eType);
};

}// namespace Utility
}// namespace Lite
