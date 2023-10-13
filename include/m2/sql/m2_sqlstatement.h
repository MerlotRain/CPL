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

#ifndef M2_SQLSTATEMENT_H_
#define M2_SQLSTATEMENT_H_

#include <m2_sqldatabase.h>

namespace m2 {

class ByteBuffer;
class SqlStatementPrivate;
class SqlStatement
{
protected:
    SqlDatabase *m_pDB;
    String m_strSQL;

public:
    SqlStatement();
    SqlStatement(SqlDatabase *db, const char *strSQL);
    virtual ~SqlStatement();
    virtual bool prepare(SqlDatabase *db, const char *sql) = 0;
    String sqlString();
    long long recordCount();
    Variant value(int n) const;
    Variant value(const String &name) const;

    bool isNullColunm(int n);

    int bindValue(int nIndex, const unsigned char *pBlob, int nLen);
    int bindValue(int nIndex, int nValue);
    int bindValue(int nIndex, double nValue);
    int bindValue(int nIndex, unsigned long long nValue);
    int bindValue(int nIndex);
    int bindValue(int nIndex, const char *pStr);
    int bindValue(int nIndex, long long nValue, bool bIsDateTime = false);

    int bindValue(const String &placeholder, const unsigned char *pBlob,
                  int nLen);
    int bindValue(const String &placeholder, int nValue);
    int bindValue(const String &placeholder, double nValue);
    int bindValue(const String &placeholder, unsigned long long nValue);
    int bindValue(const String &placeholder);
    int bindValue(const String &placeholder, const char *pStr);
    int bindValue(const String &placeholder, long long nValue,
                  bool bIsDateTime = false);

public:
    bool exec();
    bool next();
    bool previous();
    bool first();
    bool last();
    int reset();

    virtual int columnCount() = 0;
    virtual SqlField::Type colunmType(int n) = 0;
    virtual String colunmName(int n) = 0;
};

}// namespace m2

#endif//M2_SQLSTATEMENT_H_