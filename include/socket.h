/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file socket.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/

#pragma once

#include "stringhelp.h"

namespace Lite {
namespace Utility {
namespace Network {


/// @brief 网卡信息
struct UTILITY_EXPORT GsNetworkAdpterInfomation
{
    /// @brief 网卡名称
    GsString AdpterName;
    /// @brief 网卡描述
    GsString AdpterDescription;
    /// @brief ip地址
    GsString IPAddress;
    /// @brief 子网掩码
    GsString Mask;
    /// @brief 网关
    GsString Gateway;
    /// @brief mac地址
    unsigned char Mac[8];
};

/// @brief 获取所有网卡信息，ipconfig效果
/// @return
static std::vector<GsNetworkAdpterInfomation> NetworkAdpterInfomations();

/// @brief ping xx.xx.xx.xx
/// @param ip
/// @param timeout
/// @return
static bool Ping(const char *ip, const int timeout = 500);


}// namespace Network


class GsSocket;
class GsSocketAddress;
class GsSocketAcceptor;


}// namespace Utility
}// namespace Lite
