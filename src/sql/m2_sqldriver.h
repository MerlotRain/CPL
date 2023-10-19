#ifndef M2_SQLDRIVER_H_
#define M2_SQLDRIVER_H_

#include <m2_sqldatabase.h>

namespace m2 {

class SqlDriver
{
public:
    virtual bool open(const SqlConnectionProperty &cp) = 0;
    virtual bool close() = 0;
    virtual bool hasFeature() = 0;
};

}// namespace m2

#endif//M2_SQLDRIVER_H_