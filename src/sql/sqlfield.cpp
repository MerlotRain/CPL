#include "sqldatabase.h"

namespace m2 {
namespace Data {


SqlField::SqlField()
{
}

SqlField::SqlField(const SqlField &rhs)
{
}

SqlField::SqlField(const char *strName, SqlFieldType eType, const char *strAliasName,
                       const Variant &defaultVal)
{
}

SqlField::SqlField(const char *strName, SqlFieldType eType, int nPrecision, int nScale,
                       const char *strAliasName, const Variant &defaultVal)
{
}

String SqlField::ToXml() const
{
    return String();
}

String SqlField::ToJson() const
{
    return String();
}

bool SqlField::operator==(const SqlField &field) const
{
    return false;
}

bool SqlField::operator!=(const SqlField &field) const
{
    return false;
}


/*********************************************************************/


int SqlFields::FindField(const char *strFieldName) const
{
}

String SqlFields::ToXml() const
{
    return String();
}

bool SqlFields::FromXml(const char *strInfo)
{
    return false;
}

String SqlFields::ToJson() const
{
    return String();
}

bool SqlFields::FromJson(const char *strInfo)
{
    return false;
}

const SqlFields &SqlFields::Empty()
{
    // TODO: insert return statement here
}

}// namespace Data
}// namespace m2
