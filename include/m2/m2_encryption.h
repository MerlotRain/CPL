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

#include "memorymanager.h"
#include "object.h"

namespace m2 {


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

}// namespace m2
