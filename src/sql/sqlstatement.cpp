#include "sqldatabase.h"

namespace m2 {
namespace Data {

GsSqlStatement::GsSqlStatement()
{
}

GsSqlStatement::GsSqlStatement(GsSqlDatabase *db, const char *strSQL)
{
}

GsSqlStatement::~GsSqlStatement()
{
}

GsString GsSqlStatement::SQLString()
{
    return GsString();
}

long long GsSqlStatement::RecordCount()
{
    return 0;
}

int GsSqlStatement::IntValue(int nCol)
{
    return 0;
}

long long GsSqlStatement::Int64Value(int nCol)
{
    return 0;
}

GsString GsSqlStatement::StringValue(int nCol)
{
    return GsString();
}

GsDateTime GsSqlStatement::DataTimeValue(int nCol)
{
    return GsDateTime();
}

const char *GsSqlStatement::StringValuePtr(int nCol)
{
    return nullptr;
}

double GsSqlStatement::DoubleValue(int nCol)
{
    return 0.0;
}

bool GsSqlStatement::IsNullColunm(int n)
{
    return false;
}

int GsSqlStatement::Bind(int nIndex, const unsigned char *pBlob, int nLen)
{
    return 0;
}

int GsSqlStatement::Bind(int nIndex, int nValue)
{
    return 0;
}

int GsSqlStatement::Bind(int nIndex, double nValue)
{
    return 0;
}

int GsSqlStatement::Bind(int nIndex, unsigned long long nValue)
{
    return 0;
}

int GsSqlStatement::Bind(int nIndex)
{
    return 0;
}

int GsSqlStatement::Bind(int nIndex, const char *pStr)
{
    return 0;
}

int GsSqlStatement::Bind(int nIndex, long long nValue, bool bIsDateTime)
{
    return 0;
}

int GsSqlStatement::ExecuteQuery()
{
    return 0;
}

int GsSqlStatement::Execute()
{
    return 0;
}


}// namespace Data
}// namespace m2
