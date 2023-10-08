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
#include "locker.h"
#include "object.h"
#include "stringhelp.h"
#include "tinyxml2.h"

namespace m2 {


struct GsConfigItem
{
    GsString strName;
    GsString strValue;
    GsString strDescription;
    GsString strType;
};

class GsConfigEngine : public GsRefObject
{
protected:
    GsConfigEngine();

public:
    virtual ~GsConfigEngine();
    /// \brief 数据是否变化了
    /// \return
    virtual bool IsDirty();
    /// \brief 清除数据变化标识
    virtual void ClearDirty();

    /// \brief 获取数据
    /// \param item
    virtual void Assign(GsConfigItem *item) = 0;
    /// \brief 判断是否存在子项
    /// \param name
    /// \param parent
    /// \return
    virtual bool Exists(const char *name, const GsConfigItem *parent = NULL) = 0;
    /// \brief 获取一个配置项的所有子项
    /// \param parent
    /// \return
    virtual std::vector<GsString> Children(const GsConfigItem *parent = NULL) = 0;
    /// \brief 获取一个配置项的所有子项
    /// \param vec
    /// \param parent
    virtual void Children(std::vector<GsConfigItem> &vec, const GsConfigItem *parent = NULL) = 0;
    /// \brief 删除一个子项
    /// \param name
    /// \param parent
    virtual void RemoveChild(const char *name, const GsConfigItem *parent = NULL) = 0;

    /// \brief 获取一个配置项的子项
    /// \param name
    /// \param parent
    /// \return
    virtual GsConfigItem Child(const char *name, const GsConfigItem *parent = NULL) = 0;
    /// \brief 确保一定获取到子项，没有子项则创建子项
    /// \param name
    /// \param parent
    /// \return
    virtual GsConfigItem EnsureChild(const char *name, const GsConfigItem *parent = NULL);


    /// \brief 更新或者添加一个子项
    /// \param child
    /// \param parent
    /// \return
    virtual GsConfigItem UpdateChild(const GsConfigItem &child, const GsConfigItem *parent = NULL) = 0;

    /// \brief 获取一个子项的父
    /// \param child
    /// \return
    virtual GsConfigItem Parent(const GsConfigItem &child) = 0;

    /// \brief 释放一个配置项的资源
    /// \param item
    /// \return
    virtual void FreeItem(GsConfigItem &item);

    /// \brief 拷贝一个配置项资源
    /// \param item
    /// \return
    virtual GsConfigItem CopyItem(const GsConfigItem &item);
};
GS_SMARTER_PTR(GsConfigEngine)

class GsXMLConfigEngine
{
    Utility::GsRWLock m_Lock;
    tinyxml2::XXMLDocument m_Doc;
    tinyxml2::XXMLDocument *m_pDoc;
    bool m_bDirty;
    /// \brief
    void OnDirty();
    /// \brief
    void Init();
    /// \brief 获取数据
    /// \param item
    virtual void InnerAssign(GsConfigItem *item);


public:
    GsXMLConfigEngine();
    /// \brief
    /// \param pEle 配置项目的xml节点
    GsXMLConfigEngine(tinyxml2::XMLElement *pEle);
    /// \brief 从xml文件或者字符串打开配置
    /// \param strXML 字符串或者配置文件路径
    /// \param bIsString 判断strXML是xml字符串还是文件名，true表示strXML为纯的xml字符串
    GsXMLConfigEngine(const char *strXML, bool bIsString = false);
    ~GsXMLConfigEngine();
    /// \brief 数据是否变化了
    /// \return
    virtual bool IsDirty();

    /// \brief 清除数据变化标识
    virtual void ClearDirty();
    /// \brief
    /// \return
    virtual GsString FileName();
    /// \brief 获取数据
    /// \param item
    virtual void Assign(GsConfigItem *item);
    /// \brief 删除一个子项
    /// \param name
    /// \param parent
    virtual void RemoveChild(const char *name, const GsConfigItem *parent = NULL);

    /// \brief 判断是否存在子项
    /// \param name
    /// \param parent
    /// \return
    virtual bool Exists(const char *name, const GsConfigItem *parent = NULL);
    /// \brief 获取一个配置项的所有子项
    /// \param parent
    /// \return
    virtual std::vector<GsString> Children(const GsConfigItem *parent = NULL);
    /// \brief 获取一个配置项的所有子项
    /// \param vec
    /// \param parent
    virtual void Children(std::vector<GsConfigItem> &vec, const GsConfigItem *parent = NULL);
    /// \brief 获取一个配置项的子项
    /// \param name
    /// \param parent
    /// \return
    virtual GsConfigItem Child(const char *name, const GsConfigItem *parent = NULL);
    /// \brief 更新或者添加一个子项
    /// \param child
    /// \param parent
    /// \return
    virtual GsConfigItem UpdateChild(const GsConfigItem &child, const GsConfigItem *parent = NULL);

    /// \brief 获取一个子项的父
    /// \param child
    /// \return
    virtual GsConfigItem Parent(const GsConfigItem &child);

    /// \brief 保存到文件
    /// \param file
    /// \return
    virtual bool Save(const char *file = NULL);

    /// \brief 输出成xml字符串
    /// \return
    GsString ToString();
};
GS_SMARTER_PTR(GsXMLConfigEngine)

class GsConfig
{
    GsConfigEnginePtr m_Engine;
    GsConfigItem m_Item;

public:
    /// \brief 构造一个完全空的配置对象
    GsConfig(int i);
    /// \brief 缺省构造,缺省构造内存xml引擎的配置
    GsConfig();

    /// \brief
    /// \param engine
    /// \param item
    GsConfig(GsConfigEngine *engine, const GsConfigItem &item);
    /// \brief
    /// \param engine
    GsConfig(GsConfigEngine *engine);

    /// \brief 拷贝构造函数
    /// \param GsConfig
    /// \return
    GsConfig(const GsConfig &GsConfig);

    /// \brief 拷贝构造函数
    /// \param GsConfig
    /// \return
    GsConfig(GsConfig &&config);


    /// \brief
    /// \param pEle 配置项目的xml节点
    GsConfig(tinyxml2::XMLElement *pEle);
    /// \brief 从xml文件或者字符串打开配置
    /// \param strXML 字符串或者配置文件路径
    /// \param bIsString 判断strXML是xml字符串还是文件名，true表示strXML为纯的xml字符串
    GsConfig(const char *strXML, bool bIsString = false);

    /// \brief 等号赋值操作符。
    /// \brief GsConfig其他配置项
    GsConfig &operator=(const GsConfig &GsConfig);

    /// \brief 析构函数
    virtual ~GsConfig(void);

    /// \brief 获取配置项的内容
    /// \return
    const GsConfigItem &Item() const;

    /// \brief 获取配置文件的文件名
    /// \return
    GsString FileName() const;

    /// \brief 保存到文件中
    /// \param strFile
    /// \return
    bool Save(const char *strFile);

    /// \brief 保存为XML字符串
    /// \return
    GsString Save();

    /// \brief 判断配置是否发生了变化
    /// \return
    bool IsDirty() const;

    /// \brief 清除变化标识
    void ClearDirty();


    /// \brief 获取根配置对象
    /// \return
    GsConfig Root() const;

    /// \brief 是否为根配置
    /// \return
    bool IsRoot() const;

    /// \brief 获取父亲配置对象
    /// \return
    GsConfig Parent() const;

    /// \brief 获取设置配置的名称
    /// \return
    GsString Name() const;
    /// \brief
    /// \param str
    void Name(const GsString &str);
    /// \brief
    /// \param str
    void Name(const char *str);

    /// \brief 获取设置配置项的描述
    /// \return
    GsString Description() const;
    /// \brief
    /// \param str
    void Description(const GsString &str);
    /// \brief
    /// \param str
    void Description(const char *str);

    /// \brief 配置的数据类型
    /// \return
    GsString Type() const;
    /// \brief
    /// \param str
    void Type(const GsString &str);
    /// \brief
    /// \param str
    void Type(const char *str);

    /// \brief 判断配置是否有效
    /// \return
    bool IsValid() const;
    /// \brief
    /// \return
    bool Good() const;
    /// \brief
    /// \return
    bool IsNull() const;
    operator bool() const;


    /// \brief 获取配置的路径
    /// \return
    GsString Path() const;

    /// \brief 选择一个子的配置，如果不存在的话会创建这个子的配置并返回
    /// \param strName
    /// \return
    GsConfig Child(const char *strName);
    /// \brief
    /// \param strName
    /// \return
    GsConfig Child(const GsString &strName);

    /// \brief 是否存在某个子的配置
    /// \param strName
    /// \return
    bool Exist(const char *strName) const;
    /// \brief
    /// \param strName
    /// \return
    bool Exist(const GsString &strName) const;

    /// \brief 是否存在子的配置
    /// \return
    bool HasChildren() const;
    /// \brief 是否为同一配置节点
    bool operator==(const GsConfig &config) const;

    /// \brief 所有的子对象列表
    /// \return
    std::vector<GsConfig> Children() const;
    /// \brief
    /// \param vec
    void Children(std::vector<GsConfig> &vec) const;

    /// \brief 子配置的名称
    /// \return
    std::vector<GsString> ChildrenName() const;
    /// \brief
    /// \param vec
    void ChildrenName(std::vector<GsString> &vec) const;

    /// \brief 选择一个子的配置，如果不存在的话并不会创建
    /// \param strName
    /// \return
    GsConfig Peek(const char *strName) const;
    /// \brief
    /// \param strName
    /// \return
    GsConfig Peek(const GsString &strName) const;

    /// \brief 方括号操作符，设计调用Peek方法
    GsConfig operator[](const char *strName) const;
    GsConfig operator[](const GsString &strName) const;

    /// \brief 配置的值
    /// \return
    GsString Value() const;
    /// \brief 设置配置的值
    /// \param strValue
    void Value(const char *strValue);
    /// \brief
    /// \param strValue
    void Value(const GsString &strValue);
    /// \brief
    /// \param value
    void Value(int value);
    /// \brief
    /// \param value
    void Value(unsigned int value);
    /// \brief
    /// \param value
    void Value(long long value);
    /// \brief
    /// \param value
    void Value(unsigned long long value);

    /// \brief
    /// \param value
    void Value(bool value);

    /// \brief
    /// \param value
    void Value(float value);
    /// \brief
    /// \param value
    void Value(double value);

    /// \brief 获取字符串值，不存在则返回缺省值
    /// \param strDefaultValue
    /// \return
    GsString StringValue(const char *strDefaultValue) const;
    /// \brief
    /// \param strDefaultValue
    /// \return
    GsString StringValue(const GsString &strDefaultValue) const;
    /// \brief
    /// \return
    const char *ValuePtr() const;

    /// \brief 判断是否为特定值类型
    /// \return
    bool IsNumberValue() const;
    /// \brief
    /// \return
    bool IsIntValue() const;
    /// \brief
    /// \return
    bool IsFloatValue() const;
    /// \brief
    /// \return
    bool IsBooleanValue() const;

    /// \brief 获取特定类型的值
    /// \param nValue
    /// \return
    int IntValue(int nValue) const;
    /// \brief
    /// \param nValue
    /// \return
    long long Int64Value(long long nValue) const;
    /// \brief
    /// \param bValue
    /// \return
    bool BoolValue(bool bValue) const;
    /// \brief
    /// \param bFloat
    /// \return
    double FloatValue(double bFloat) const;

    /// \brief 类型重载操作符
    operator const char *() const;
    operator int() const;
    operator long long() const;
    operator double() const;
    operator float() const;
    operator unsigned int() const;
    operator unsigned long long() const;

    /// \brief 将另外的分支添加到这个GsConfig中
    /// \param config
    void Append(const GsConfig &config);

    /// \brief 清空所有的子配置
    void Clear();

    /// \brief 删除一个子配置
    /// \param childName
    void Remove(const char *childName);
    /// \brief 删除一个子配置
    /// \param childName
    void Remove(const GsString &childName);

    /// \brief 交换两个节点的内容
    /// \param other
    /// \return
    GsConfig &Swap(GsConfig &other);

    /// \brief 获取配置的存储引擎
    /// \return
    GsConfigEngine *Engine();
};


class GsGlobalConfig
{
public:
    /// \brief 全局的配置类根对象
    /// \return
    static GsConfig &Instance();

    /// \brief 将全局的配置保存为文件
    /// \param strFile
    /// \return
    static bool Save(const char *strFile);

    /// \brief 将全局的配置保存为字符串
    /// \return
    static GsString Save();

    /// \brief 从xml或者配置中load配置信息
    /// \param strFileOrXML 文件路径或者xml串
    /// \param bFile 是否是文件
    /// \return 返回是否加载成功
    static bool Load(const char *strFileOrXML, bool bFile = true);
};


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
        GsRefObject *ref = LoadRefObjectValue(key);
        if (!ref)
        {
            return 0;
        }
        T *o = dynamic_cast<T *>(ref);
        if (!o)
        {
            ref->Release();
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


}// namespace m2
