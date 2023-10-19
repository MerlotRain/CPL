#include <m2_sqldatabase.h>

namespace m2 {

/*******************************************************************************
 * Struct SqlField functions
 *******************************************************************************/

SqlField::SqlField() {}

SqlField::SqlField(const SqlField &rhs) {}

SqlField::SqlField(const char *strName, Type eType, const char *strAliasName,
                   const Variant &defaultVal)
{
}

SqlField::SqlField(const char *strName, Type eType, int nPrecision, int nScale,
                   const char *strAliasName, const Variant &defaultVal)
{
}

String SqlField::toXml() const { return String(); }

String SqlField::toJson() const { return String(); }

bool SqlField::operator==(const SqlField &field) const { return false; }

bool SqlField::operator!=(const SqlField &field) const { return false; }

/*******************************************************************************
 * Struct SqlFields functions
 *******************************************************************************/

int SqlFields::findField(const char *strFieldName) const { return 0; }

String SqlFields::toXml() const { return String(); }

bool SqlFields::fromXml(const char *strInfo) { return false; }

String SqlFields::toJson() const { return String(); }

bool SqlFields::fromJson(const char *strInfo) { return false; }

const SqlFields &SqlFields::empty()
{
    // TODO: insert return statement here
}

}// namespace m2
