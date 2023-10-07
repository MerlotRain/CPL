/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file sqldatabase.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/


#pragma once

#include "stringhelp.h"
#include "variant.h"


namespace Lite {
namespace Utility {
namespace Data {


/// @brief 数据库字段类型
enum GsSqlFieldType
{
    /// @brief 错误字段类型
    eErrorType,
    /// @brief BOOL类型
    eBoolType,
    /// @brief 32位有符号整型
    eInt32Type,
    /// @brief 32位无符号整型
    eUInt32Type,
    /// @brief 64位有符号整型
    eInt64Type,
    /// @brief 64位无符号整型
    eUInt64Type,
    /// @brief 字符类型
    eStringType,
    /// @brief Float类型
    eFloatType,
    /// @brief Double类型
    eDoubleType,
    /// @brief 日期类型
    eDateType,
    /// @brief 二进制类型
    eBlobType,
    /// @brief 长文本类型
    eClobType,
#ifdef SPATIAL_FEATURE
    /// @brief 几何字段
    eGeometryType,
#endif
};


/// @brief 字段结构
struct UTILITY_EXPORT GsSqlField
{
    /// @brief 字段名称
    GsString Name;
    /// @brief 字段别名
    GsString AliasName;
    /// @brief 字段类型
    GsSqlFieldType Type;
    /// @brief 字段长度
    int Length;
    /// @brief 小数字段精度，整型或字符串字段该值无效
    int Scale;
    /// @brief 字段是否允许为空
    bool IsNullable;
    /// @brief 字段默认值
    GsVariant DefaultValue;

    /// @brief 默认构造
    GsSqlField();
    /// @brief 拷贝构造函数
    /// @param rhs
    GsSqlField(const GsSqlField &rhs);

    /// @brief 从名称和类型构造
    /// @param strName 字段名称
    /// @param eType 字段类型
    /// @param strAliasName 字段别名
    /// @param defaultVal 字段默认值
    GsSqlField(const char *strName, GsSqlFieldType eType, const char *strAliasName = 0,
               const GsVariant &defaultVal = GsVariant());

    /// @brief 从名称和类型、精度和小数L位构造
    /// @param strName 字段名称
    /// @param eType 字段类型
    /// @param nPrecision 字段精度
    /// @param nScale 字段小数位长度
    /// @param strAliasName 字段别名
    /// @param defaultVal 字段默认值，类型需要与字段类型匹配
    GsSqlField(const char *strName, GsSqlFieldType eType, int nPrecision, int nScale = 0,
               const char *strAliasName = 0, const GsVariant &defaultVal = GsVariant());

    /// @brief 将字段信息序列化为xml字符串
    /// @return
    GsString ToXml() const;

    /// @brief 将字段信息序列化为json字符串
    /// @return
    GsString ToJson() const;
    /// @brief 相等操作符
    bool operator==(const GsSqlField &field) const;
    /// @brief 不等操作符
    bool operator!=(const GsSqlField &field) const;
};


/// @brief 字段集合
struct UTILITY_EXPORT GsSqlFields
{
    std::vector<GsSqlField> Fields;

    /// @brief 寻找字段的索引
    /// @param strFieldName
    /// @return
    int FindField(const char *strFieldName) const;

    /// @brief 将字段信息序列化为xml字符串
    /// @return
    GsString ToXml() const;

    /// @brief 将xml字符串序列化为Fields信息
    /// @param strInfo
    bool FromXml(const char *strInfo);

    /// @brief 将字段信息序列化为json字符串
    /// @return
    GsString ToJson() const;

    /// @brief 将json字符串序列化为Fields信息
    /// @param strInfo
    bool FromJson(const char *strInfo);

    /// @brief 空字段
    static const GsSqlFields &Empty();
};


class GsSqlStatement;
class GsSqlTransaction;

/// @brief 可直接执行sql语句的普通数据库对象
/// @details 不使用智能指针封装，对GsGeoDatabase模块，GsSqlDatabase指针由内部管理
/// @details 目前仅对外暴露sqlite数据库的封装
/// @details 当应用层获取该指针执行sql时，无需析构
class UTILITY_EXPORT GsSqlDatabase : private GsNonCopyable
{
public:
    /// @brief 默认析构
    virtual ~GsSqlDatabase() = default;
    /// @brief 打开数据库
    /// @return
    virtual bool Open() = 0;
    /// @brief 判断数据库是否处于打开的状态
    /// @return
    virtual bool IsOpen() const;
    /// @brief 关闭数据库
    /// @return
    virtual bool Close() = 0;
    /// @brief 开启事务
    /// @return
    virtual GsSqlTransaction *Transaction() = 0;
    /// @brief 最后一条错误信息
    /// @return
    virtual GsString ErrorMessage();
    /// @brief 错误代码
    /// @return
    virtual long long ErrorCode() = 0;
    /// @brief 创建Statement对象用于复杂执行
    /// @return
    virtual GsSqlStatement *CreateStatement() = 0;
    /// @brief 执行sql语句
    /// @return
    virtual int Execute(const char *sql) = 0;

protected:
    void OpenError(bool b);
    void LastError(const char *errmsg);

protected:
    bool m_isOpen = false;
    bool m_isOpenError = false;
    GsString m_strErrMsg;
};


/// @brief 数据库执行Statement对象
class UTILITY_EXPORT GsSqlStatement : private GsNonCopyable
{
protected:
    GsSqlDatabase *m_pDB;
    GsString m_strSQL;

public:
    /// @brief 缺省构造函数
    GsSqlStatement();
    /// @brief 重载构造函数，创建数据库指针
    GsSqlStatement(GsSqlDatabase *db, const char *strSQL);
    virtual ~GsSqlStatement();
    virtual bool Prepare(GsSqlDatabase *db, const char *sql) = 0;
    /// @brief 将本地字符串转化为数据库字符串
    virtual GsString SQLString();
    /// @brief 返回-1
    virtual long long RecordCount();
    /// @brief 读取32位，nCol从0开始，下同
    virtual int IntValue(int nCol);
    /// @brief 读取64位
    virtual long long Int64Value(int nCol);
    /// @brief 读取字符串
    virtual GsString StringValue(int nCol);
    /// @brief 读取日期
    virtual GsDateTime DataTimeValue(int nCol);
    /// @brief 读取无符号字符常量
    virtual const char *StringValuePtr(int nCol);
    /// @brief 读取double类型数据
    virtual double DoubleValue(int nCol);
    /// @brief 判断列是否是空值
    virtual bool IsNullColunm(int n);

    /// @brief 绑定无符号字符, nIndex从0开始
    virtual int Bind(int nIndex, const unsigned char *pBlob, int nLen);
    /// @brief 绑定32位整数
    virtual int Bind(int nIndex, int nValue);
    /// @brief 绑定64位浮点数
    virtual int Bind(int nIndex, double nValue);
    /// @brief 绑定64位无符号整数
    virtual int Bind(int nIndex, unsigned long long nValue);
    /// @brief 绑定空值
    virtual int Bind(int nIndex);
    /// @brief 绑定字符常量
    virtual int Bind(int nIndex, const char *pStr);
    /// @brief 绑定64位整数或者日期
    virtual int Bind(int nIndex, long long nValue, bool bIsDateTime = false);

public:
    /// @brief 执行读取，返回1个结果
    virtual int ExecuteQuery();
    /// @brief 执行读取，返回多个结果
    virtual int Execute();
    /// @brief 返回下1条数据
    virtual bool MoveNext() = 0;
    /// @brief 读取无符号字符数据
    virtual const unsigned char *BlobValue(int nCol) = 0;
    /// @brief 返回当前列的值
    virtual int ValueLength(int nCol) = 0;
    /// @brief 绑定索引,nIndex 从0开始
    virtual int BindValue(int nIndex, const unsigned char *pBlob, int nLen, GsSqlFieldType eType) = 0;
    /// @brief 释放内存
    virtual int Reset() = 0;
    /// @brief 获取查询结果的列数
    virtual int ColumnCount() = 0;
    /// @brief 获取列的类型
    virtual GsSqlFieldType ColunmType(int n) = 0;
    /// @brief 获取列的名称
    virtual GsString ColunmName(int n) = 0;
};


/// @brief 数据库事务对象
class UTILITY_EXPORT GsSqlTransaction : public GsRefObject
{
public:
    /// @brief 默认析构
    virtual ~GsSqlTransaction() {}
    /// @brief 是否处于事务中
    /// @return 返回是否处于事务中
    virtual bool IsTransaction() = 0;
    /// @brief 启动事务
    /// @return 返回是否成功启动
    virtual bool StartTransaction() = 0;
    /// @brief 提交事务
    /// @return 返回是否提交成功
    virtual bool CommitTransaction() = 0;
    /// @brief 取消事务
    /// @return 返回是否取消成功
    virtual bool RollbackTransaction() = 0;

protected:
    /// @brief 默认构造
    GsSqlTransaction() {}
};
GS_SMARTER_PTR(GsSqlTransaction)


}// namespace Data
}// namespace Utility
}// namespace Lite
