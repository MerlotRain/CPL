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

#ifndef M2_CRYTOGRAPHICHASH_H_
#define M2_CRYTOGRAPHICHASH_H_

#include <m2_bytebuffer.h>
#include <m2_string.h>

namespace m2 {

/// @brief hash算法库
class CryptographicHashPrivate;
class CryptographicHash
{
public:
    enum HashAlgorithm
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
    explicit CryptographicHash(HashAlgorithm algorithm);
    ~CryptographicHash();
    void reset();
    void addData(const char *data, int length);
    void addData(const ByteBuffer &data);
    void addData(const String &str);
    ByteBuffer result() const;
    static ByteBuffer hash(const ByteBuffer &data, HashAlgorithm algorithm);
    static int hashLength(HashAlgorithm algorithm);

private:
    CryptographicHashPrivate *d;
};

}// namespace m2

#endif//M2_CRYTOGRAPHICHASH_H_