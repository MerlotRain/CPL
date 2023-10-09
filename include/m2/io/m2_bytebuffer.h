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

#ifndef M2_BYTEBUFFER_H_
#define M2_BYTEBUFFER_H_

#include <m2_string.h>

namespace m2 {

class M2_API ByteBuffer
{
public:
    ByteBuffer(unsigned int len = 0);
    ByteBuffer(unsigned char *buffer);
    ByteBuffer(unsigned char *buffer, int len);
    ByteBuffer(const char *str);
    ByteBuffer(const ByteBuffer &rhs);
    ByteBuffer(ByteBuffer &&rhs) noexcept;
    virtual ~ByteBuffer();

    void Attach(unsigned char *buffer);
    unsigned char *Detach();

    explicit operator unsigned char *() const;
    explicit operator char *() const;
    explicit operator int *() const;
    explicit operator unsigned int *() const;
    explicit operator short *() const;
    explicit operator unsigned short *() const;
    explicit operator long long *() const;
    explicit operator unsigned long long *() const;
    explicit operator double *() const;
    explicit operator float *() const;
    explicit operator bool *() const;

    unsigned char *Ptr() const;
    virtual unsigned char *EndPtr() const;
    template<typename T>
    T *PtrT() const
    {
        return (T *) (Ptr());
    }
    template<typename T>
    T *EndPtrT() const
    {
        return (T *) (EndPtr());
    }

    unsigned char *BufferHead() const;
    unsigned int BufferSize() const;
    template<typename T>
    unsigned int BufferSizeT() const
    {
        return BufferSize() / sizeof(T);
    }

    unsigned int BufferLength() const;
    unsigned char *SetBufferValue(int nValue);

    template<typename T>
    T *SetBufferValueT(const T &val)
    {
        const auto *pByte = (const unsigned char *) &val;
        bool bIsEqual = true;
        for (int i = 1; i < sizeof(val); i++)
        {
            if (pByte[i] != pByte[0])
            {
                bIsEqual = false;
                break;
            }
        }
        if (bIsEqual)
        {
            return (T *) SetBufferValue(pByte[0]);
        }
        T *pHead = PtrT<T>();
        T *pEnd = EndPtrT<T>();
        for (; pHead < pEnd; pHead++)
        {
            pHead[0] = val;
        }
        return PtrT<T>();
    }

    unsigned char *Append(const unsigned char *pBuff, int nLen);
    unsigned char *Append(const char *pStr);

    template<typename T>
    unsigned char *AppendT(const T &pBuff)
    {
        return Append((const unsigned char *) &pBuff, sizeof(T));
    }

    unsigned char *Insert(unsigned int nPos, const unsigned char *pStr, int nLen);
    unsigned char *Allocate(unsigned int nLen);
    template<typename T>
    T *AllocateT(int nLen)
    {
        Allocate(sizeof(T) * nLen);
        return PtrT<T>();
    }

    virtual void Clear();
    virtual void Reset();
    unsigned char *Copy(const unsigned char *pBuff, int nLen);
    ByteBuffer ReadSize(int nLen);
    void Resize(int nLen);
    ByteBuffer *Swap(ByteBuffer &rhs);
    ByteBuffer *Swap(unsigned char *pBuff);
    bool IsEmpty() const;
    ByteBuffer &operator=(const ByteBuffer &rsh);
    ByteBuffer &operator=(ByteBuffer &&rsh) noexcept;
    String ToBase64() const;
    bool FromBase64(const char *strBase64);
    static bool IsBase64(const char *strBase64);

private:
    unsigned char *m_Buffer;
};

}// namespace m2

#endif//M2_BYTEBUFFER_H_
