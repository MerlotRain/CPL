
#include "exception.h"

namespace Lite {
namespace Utility {


/// @brief Utility模块通用的Exception，错误抛出时使用该类型
class GsUtilityException : public GsException
{
public:
    GsUtilityException() : GsException("Utility", "")
    {
    }

    GsUtilityException(const GsString &msg) : GsException("Utility", msg)
    {
    }

    ~GsUtilityException() noexcept override
    {
    }
};

}// namespace Utility
}// namespace Lite
