#include "sqldatabase.h"

namespace m2 {
namespace Data {

SqlStatement::SqlStatement()
{
}

SqlStatement::SqlStatement(SqlDatabase *db, const char *strSQL)
{
}

SqlStatement::~SqlStatement()
{
}

String SqlStatement::SQLString()
{
    return String();
}

long long SqlStatement::RecordCount()
{
    return 0;
}

int SqlStatement::IntValue(int nCol)
{
    return 0;
}

long long SqlStatement::Int64Value(int nCol)
{
    return 0;
}

String SqlStatement::StringValue(int nCol)
{
    return String();
}

DateTime SqlStatement::DataTimeValue(int nCol)
{
    return DateTime();
}

const char *SqlStatement::StringValuePtr(int nCol)
{
    return nullptr;
}

double SqlStatement::DoubleValue(int nCol)
{
    return 0.0;
}

bool SqlStatement::IsNullColunm(int n)
{
    return false;
}

int SqlStatement::Bind(int nIndex, const unsigned char *pBlob, int nLen)
{
    return 0;
}

int SqlStatement::Bind(int nIndex, int nValue)
{
    return 0;
}

int SqlStatement::Bind(int nIndex, double nValue)
{
    return 0;
}

int SqlStatement::Bind(int nIndex, unsigned long long nValue)
{
    return 0;
}

int SqlStatement::Bind(int nIndex)
{
    return 0;
}

int SqlStatement::Bind(int nIndex, const char *pStr)
{
    return 0;
}

int SqlStatement::Bind(int nIndex, long long nValue, bool bIsDateTime)
{
    return 0;
}

int SqlStatement::ExecuteQuery()
{
    return 0;
}

int SqlStatement::Execute()
{
    return 0;
}


}// namespace Data
}// namespace m2
