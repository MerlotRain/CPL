/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file error.h
 * @brief
 * @details
 * @date 2023-06-19
 * @author
 *
 ******************************************************************************/


#pragma once

#include "stringhelp.h"

namespace Lite {
namespace Utility {

/// @brief 错误信息
/// @details 用于捕获平台抛出的错误代码和错误信息
/// @details 仅Utility模块使用，其余模块应脱离系统函数，或将需要的系统函数封装到Utility模块中
/// @details 所有错误信息都会被写入到日志中
class UTILITY_EXPORT GsError
{
public:
    /// @brief 获取系统最近的错误编码
    /// @return
    static int LastError();

    /// @brief 获取错误编码对应的错误信息
    /// @param code
    /// @return
    static GsString Message(int code);
};

}// namespace Utility
}// namespace Lite
