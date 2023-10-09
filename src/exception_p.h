
#include "exception.h"

namespace m2 {


/// @brief Utility模块通用的Exception，错误抛出时使用该类型
class UtilityException : public Exception
{
public:
    UtilityException() : Exception("Utility", "")
    {
    }

    UtilityException(const String &msg) : Exception("Utility", msg)
    {
    }

    ~UtilityException() noexcept override
    {
    }
};

}// namespace m2
