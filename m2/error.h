#ifndef M2_ERROR_H_
#define M2_ERROR_H_

#include <string>

class Error
{
public:
    static int lastError();
    static std::string message(int code);
};

#endif//M2_ERROR_H_