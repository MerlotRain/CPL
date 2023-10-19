#include "m2_sqlstatement.h"

namespace m2 {

SqlStatement::SqlStatement() {}

SqlStatement::SqlStatement(SqlDatabase *db, const char *strSQL) {}

SqlStatement::~SqlStatement() {}

bool SqlStatement::prepare(SqlDatabase *db, const char *sql) { return false; }

String SqlStatement::sqlString() { return String(); }

long long SqlStatement::recordCount() { return 0; }

Variant SqlStatement::value(int n) const { return Variant(); }

Variant SqlStatement::value(const String &name) const { return Variant(); }

bool SqlStatement::isNullColunm(int n) { return false; }

int SqlStatement::bindValue(int nIndex, const unsigned char *pBlob, int nLen)
{
    return 0;
}

int SqlStatement::bindValue(int nIndex, int nValue) { return 0; }

int SqlStatement::bindValue(int nIndex, double nValue) { return 0; }

int SqlStatement::bindValue(int nIndex, unsigned long long nValue) { return 0; }

int SqlStatement::bindValue(int nIndex) { return 0; }

int SqlStatement::bindValue(int nIndex, const char *pStr) { return 0; }

int SqlStatement::bindValue(int nIndex, long long nValue, bool bIsDateTime)
{
    return 0;
}

int SqlStatement::bindValue(const String &placeholder,
                            const unsigned char *pBlob, int nLen)
{
    return 0;
}

int SqlStatement::bindValue(const String &placeholder, int nValue) { return 0; }

int SqlStatement::bindValue(const String &placeholder, double nValue)
{
    return 0;
}

int SqlStatement::bindValue(const String &placeholder,
                            unsigned long long nValue)
{
    return 0;
}

int SqlStatement::bindValue(const String &placeholder) { return 0; }

int SqlStatement::bindValue(const String &placeholder, const char *pStr)
{
    return 0;
}

int SqlStatement::bindValue(const String &placeholder, long long nValue,
                            bool bIsDateTime)
{
    return 0;
}

bool SqlStatement::exec() { return false; }

bool SqlStatement::next() { return false; }

bool SqlStatement::previous() { return false; }

bool SqlStatement::first() { return false; }

bool SqlStatement::last() { return false; }

int SqlStatement::reset() { return 0; }

int SqlStatement::columnCount() { return 0; }

SqlField::Type SqlStatement::colunmType(int n) { return SqlField::Type(); }

String SqlStatement::colunmName(int n) { return String(); }

}// namespace m2