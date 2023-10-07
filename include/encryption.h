/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file encryption.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/

#pragma once

#include "bytebuffer.h"
#include "object.h"

namespace Lite {
namespace Utility {

// 考虑调用openssl实现

/// @brief 加密解密对象
class GsEncryption : public GsRefObject
{
protected:
    GsEncryption();

public:
    virtual ~GsEncryption();

    virtual int Encrypt(const unsigned char *pBlob, int nLen, GsByteBuffer *pOutBuff) = 0;

    virtual int Decrypt(const unsigned char *pBlob, int nLen, GsByteBuffer *pOutBuff) = 0;
};

}// namespace Utility
}// namespace Lite
