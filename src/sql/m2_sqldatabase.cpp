#include <m2_sqldatabase.h>
#include <m2_sqlstatement.h>

namespace m2 {
bool SqlDatabase::open(const SqlConnectionProperty &cp) { return false; }

bool SqlDatabase::isOpen() const { return false; }

bool SqlDatabase::close()
{
return false;
}

bool SqlDatabase::isOpenError() const { return false; }

SqlConnectionProperty SqlDatabase::connectionProperty() const
{
    return SqlConnectionProperty();
}

String SqlDatabase::lastError() const { return String(); }

SqlStatement SqlDatabase::exec(const char *sql) { return SqlStatement(); }

bool SqlDatabase::transaction() { return false; }

bool SqlDatabase::commit() { return false; }

bool SqlDatabase::rollback() { return false; }

SqlDatabase SqlDatabase::openDatabase(const SqlConnectionProperty &cp)
{
    return SqlDatabase();
}

SqlDatabase SqlDatabase::closeDatabase(const SqlConnectionProperty &cp)
{
    return SqlDatabase();
}

void SqlDatabase::removeDatabase(const SqlConnectionProperty &cp) {}

void SqlDatabase::registerSqlDrivers(SqlDatabaseDriver_Handle_t t) {}

String SqlDatabase::createTableSql(const SqlFields &fields,
                                   const char *tablename,
                                   SqlDataSourceType datasource)
{
    return String();
}

}// namespace m2