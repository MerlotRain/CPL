/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file exception.h
 * @brief
 * @details
 * @date 2023-06-19
 * @author
 *
 ******************************************************************************/

#pragma once

#include "preconfig.h"
#include "stringhelp.h"
#include <stdexcept>
#include <string>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)
#endif

namespace Lite {
namespace Utility {


/// @brief 异常
class UTILITY_EXPORT GsException : public std::runtime_error
{
public:
    GsException() : std::runtime_error("Unknown error") {}

    explicit GsException(GsString const &msg) : std::runtime_error(msg) {}

    GsException(GsString const &name, GsString const &msg)
        : std::runtime_error(name + ": " + msg)
    {
    }
};

/// @brief 参数错误的异常
class UTILITY_EXPORT GsIllegalArgumentException : public GsException
{
public:
    GsIllegalArgumentException()
        : GsException("IllegalArgumentException", "")
    {
    }

    explicit GsIllegalArgumentException(const std::string &msg)
        : GsException("IllegalArgumentException", msg)
    {
    }

    ~GsIllegalArgumentException() noexcept override = default;
};

}// namespace Utility
}// namespace Lite


#ifdef _MSC_VER
#pragma warning(pop)
#endif
