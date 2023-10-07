#include "sqldatabase.h"

namespace Lite {
namespace Utility {
namespace Data {


GsSqlField::GsSqlField()
{
}

GsSqlField::GsSqlField(const GsSqlField &rhs)
{
}

GsSqlField::GsSqlField(const char *strName, GsSqlFieldType eType, const char *strAliasName,
                       const GsVariant &defaultVal)
{
}

GsSqlField::GsSqlField(const char *strName, GsSqlFieldType eType, int nPrecision, int nScale,
                       const char *strAliasName, const GsVariant &defaultVal)
{
}

GsString GsSqlField::ToXml() const
{
    return GsString();
}

GsString GsSqlField::ToJson() const
{
    return GsString();
}

bool GsSqlField::operator==(const GsSqlField &field) const
{
    return false;
}

bool GsSqlField::operator!=(const GsSqlField &field) const
{
    return false;
}


/*********************************************************************/


int GsSqlFields::FindField(const char *strFieldName) const
{
}

GsString GsSqlFields::ToXml() const
{
    return GsString();
}

bool GsSqlFields::FromXml(const char *strInfo)
{
    return false;
}

GsString GsSqlFields::ToJson() const
{
    return GsString();
}

bool GsSqlFields::FromJson(const char *strInfo)
{
    return false;
}

const GsSqlFields &GsSqlFields::Empty()
{
    // TODO: insert return statement here
}

}// namespace Data
}// namespace Utility
}// namespace Lite
