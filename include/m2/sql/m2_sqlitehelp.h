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

#include "sqldatabase.h"
#include "sqlite3.h"

namespace m2 {
namespace Data {
namespace Sqlite {


/// @brief sqlite数据库加密方式
enum SqliteCodecType
{
    /// @brief 未知加密方法
    eCodecUnknow = -1,
    /// @brief 未使用加密
    eCodecNone,
    /// @brief 使用wxsqlite的加密方法
    eCodecWxSqlite,
    /// @brief 使用sqlcipher1.1.8版本的加密方法
    eCodecSqlCipher1_1_8,
    /// @brief 使用sqlcipher2.0beta版本的加密方法
    eCodecSqlCipher2_0_beta,
    /// @brief 使用sqlcipher2.0be版本的加密方法
    eCodecSqlCipher2_0_be,
    /// @brief 使用sqlcipher2.0le版本的加密方法
    eCodecSqlCipher2_0_le,
    /// @brief 使用sqlcipher3.0版本的加密方法
    eCodecSqlCipher3_0,
    /// @brief 使用sqlcipher4.0版本的加密方法
    eCodecSqlCipher4_0,
};

/// @brief sqlite数据库封装
class SqliteDatabase : public SqlDatabase
{
    SqliteCodecType m_eCodecType;
    sqlite3 *m_pDB;

public:
    /// @brief 默认构造
    SqliteDatabase();
    /// @brief 构造
    /// @param filename
    SqliteDatabase(const char *filename);
    /// @brief 使用密码和指定的加密技术打开或创建加密数据库
    /// @details 打开数据库时如果没有明确指定加密技术则会试探每种技术
    /// @details 创建数据库时如果没有明确指定加密技术则会使用eCodecSqlCipher4_0加密技术
    /// @details SqlCipher加密技术创建数据库时eCodecSqlCipher4_0版本
    /// @param filename
    /// @param pwd
    /// @param eCodeType
    SqliteDatabase(const char *filename, const char *pwd, SqliteCodecType eCodeType);

    /// @brief 获取加密方法
    /// @return
    SqliteCodecType CodecType();

    /// @brief 探测sqlite的加密方法
    /// @param filename 文件名(包括文件路径)
    /// @param pwd 密码
    /// @return 返回探测到的加密方式
    static SqliteCodecType DetectCodecType(const char *filename, const char *pwd);

    virtual ~SqliteDatabase();
    /// @brief 转化成数据库指针
    operator sqlite3 *() const;
    /// @brief 返回指针地址
    /// @return
    sqlite3 *DB() const;
    virtual void Attach(sqlite3 *db);
    /// @brief 判断是否打开文件
    /// @return
    virtual bool IsOpen() const;
    /// @brief 执行操作
    /// @return 返回0 代表执行成功。
    /// @param strSQL
    virtual int Execute(const char *strSQL);
    /// @brief 执行操作
    /// @param strSQL SQL语句 参见sqlite3_create_function使用方法
    /// @param strFuncName 要绑定的函数名
    /// @param SqliteCallback 绑定的函数
    /// @param pUserParam 传入的参数
    virtual int Execute(const char *strSQL, const char *strFuncName, const void *SqliteCallback, void *pUserParam);
    /// @brief 插入最后1行
    /// @return
    virtual long long LastInsertRowID() const;
    /// @brief 判断是否关闭
    virtual bool Close();
    /// @brief 最后的消息
    /// @return
    virtual String ErrorMessage();
    /// @brief 错误编号
    /// @return
    virtual long long ErrorCode();
    /// @brief 判断是否读取失败
    /// @param nErrorCode
    /// @return
    static bool Error(long long nErrorCode);
    /// @brief 打断正在运行中的数据库命令
    /// @return 不支持打断操作的能力则返回false，成功打断或者无须打断都返回true
    virtual bool Interrupt();

    /// @brief 函数模板
    template<class T>
    /// @brief
    /// @param nErrorCode
    /// @param bOkValue
    /// @param bFailValue
    /// @return
    T Error(int nErrorCode, T bOkValue, T bFailValue)
    {
        /// @brief 如果读取成功，返回成功的消息
        if (!Error(nErrorCode))
        {
            return bOkValue;
        }
        /// @brief 如果读取失败，返回失败的消息
        const char *strError = sqlite3_errmsg(m_pDB);
        std::cout << strError << std::endl;
        return bFailValue;
    }
    /// @brief 判断表是否存在
    /// @param tbName
    /// @return
    bool ExistTable(const char *tbName);

    /// @brief 判断索引是否存在
    /// @brief 索引名称
    /// @param strIndexName
    /// @return
    bool ExistIndex(const char *strIndexName);

    /// @brief 创建一个 Statement
    /// @return Statement对象由各数据源实现
    virtual SqlStatement *CreateStatement() override;
};


}// namespace Sqlite
}// namespace Data
}// namespace m2
