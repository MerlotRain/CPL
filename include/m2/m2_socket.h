/****************************************************************************
**
** Copyright (C) 2023 MerlotRain
** Github:https://github.com/MerlotRain
**
** M2 is a cross platform C++basic library that encapsulates commonly 
** used C++ classes and functional modules, shields system functions from 
** the outside, and provides a unified interface.
**
** $M2_BEGIN_LICENSE:MIT$
** Permission is hereby granted, free of charge, to any person obtaining a 
** copy of this software and associated documentation files (the “Software”), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
** DEALINGS IN THE SOFTWARE.
** 
** $M2_END_LICENSE$
**
****************************************************************************/

#pragma once

#include "stringhelp.h"

namespace m2 {
namespace Network {


/// @brief 网卡信息
struct M2_API GsNetworkAdpterInfomation
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


}// namespace m2
