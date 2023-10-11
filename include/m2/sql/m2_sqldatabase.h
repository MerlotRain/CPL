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

#ifndef M2_SQLDATABASE_H_
#define M2_SQLDATABASE_H_

#include <m2_string.h>
#include <m2_variant.h>

namespace m2 {

class SqlStatement;
class SqlDatabasePrivate;

enum SqlDataSourceType
{
    Oracle,
    MySql,
    SQLite,
    PostgreSQL,
    ODBC,
    MSSql,
};

struct SqlConnectionProperty
{
    String strServer;
    String strDatabase;
    String strUser;
    String strPassword;
    int nPort;
    String strOption;
    int nVersion;
    SqlDataSourceType dataSourceType;
};
typedef void *SqlDatabaseDriver_Handle_t;

struct SqlField
{
    enum Type
    {
        eErrorType,
        eBoolType,
        eInt32Type,
        eUInt32Type,
        eInt64Type,
        eUInt64Type,
        eStringType,
        eFloatType,
        eDoubleType,
        eDateType,
        eBlobType,
        eClobType,
    };

    String strName;
    String strAliasName;
    Type eType;
    int nLength;
    int nScale;
    bool isNullable;
    Variant vDefaultValue;

    SqlField();
    SqlField(const SqlField &rhs);
    SqlField(const char *strName, Type eType, const char *strAliasName = 0,
             const Variant &defaultVal = Variant());
    SqlField(const char *strName, Type eType, int nPrecision, int nScale = 0,
             const char *strAliasName = 0, const Variant &defaultVal = Variant());

    String toXml() const;
    String toJson() const;
    bool operator==(const SqlField &field) const;
    bool operator!=(const SqlField &field) const;
};

struct SqlFields
{
    std::vector<SqlField> Fields;

    int findField(const char *strFieldName) const;
    String toXml() const;
    bool fromXml(const char *strInfo);
    String toJson() const;
    bool fromJson(const char *strInfo);
    static const SqlFields &empty();
};

class SqlDatabase
{
public:
    ~SqlDatabase() = default;
    bool open(const SqlConnectionProperty &cp);
    bool isOpen() const;
    bool close();
    bool isOpen() const;
    bool isOpenError() const;

    SqlConnectionProperty connectionProperty() const;
    String lastError() const;
    SqlStatement exec(const char *sql = nullptr);

    bool transaction();
    bool commit();
    bool rollback();

    static SqlDatabase openDatabase(const SqlConnectionProperty &cp);
    static SqlDatabase closeDatabase(const SqlConnectionProperty &cp);
    static void removeDatabase(const SqlConnectionProperty &cp);

    static void registerSqlDrivers(SqlDatabaseDriver_Handle_t t);

    static String createTableSql(const SqlFields &fields, const char *tablename, SqlDataSourceType datasource);

private:
    SqlDatabasePrivate *d;
};

}// namespace m2

#endif//M2_SQLDATABASE_H_