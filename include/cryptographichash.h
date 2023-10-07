/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file cryptographichash.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/

#pragma once

#include "bytebuffer.h"
#include "stringhelp.h"

namespace Lite {
namespace Utility {


/// @brief hash算法库
class GsCryptographicHashData;
class GsCryptographicHash
{
public:
    enum GsHashAlgorithm
    {
        eMD4,
        eMD5,
        eSHA1,

        eSHA224,
        eSHA256,
        eSHA384,
        eSHA512,

        eKECCAK_224 = 7,
        eKECCAK_256,
        eKECCAK_384,
        eKECCAK_512,
        eREALSHA3_224 = 11,
        eREALSHA3_256,
        eREALSHA3_384,
        eREALSHA3_512,
        eSHA3_224 = eREALSHA3_224,
        eSHA3_256 = eREALSHA3_256,
        eSHA3_384 = eREALSHA3_384,
        eSHA3_512 = eREALSHA3_512

    };

public:
    /// @brief 根据算法类型构造hash函数
    /// @param algorithm
    explicit GsCryptographicHash(GsHashAlgorithm algorithm);

    /// @brief 默认析构
    ~GsCryptographicHash();

    /// @brief 重置hash结果
    void Reset();

    /// @brief 添加hash数据
    /// @param data
    /// @param length
    void AddData(const char *data, int length);
    void AddData(const GsByteBuffer &data);
    void AddData(const GsString &str);

    /// @brief 求hash结果
    /// @return
    GsByteBuffer Result() const;

    /// @brief 求hash结果
    /// @param data
    /// @param algorithm
    /// @return
    static GsByteBuffer Hash(const GsByteBuffer &data, GsHashAlgorithm algorithm);

    /// @brief 获取hash长度
    /// @param algorithm 算法
    static int HashLength(GsHashAlgorithm algorithm);

private:
    GsCryptographicHashData *m_Data;
};


}// namespace Utility
}// namespace Lite
