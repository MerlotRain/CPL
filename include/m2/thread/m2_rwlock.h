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

#ifndef M2_RWLOCK_H_
#define M2_RWLOCK_H_

#include <preconfig.h>

namespace m2 {

class LIBM2_EXPORT RWLock
{
public:
    RWLock();
    ~RWLock();
    RWLock(const RWLock &) noexcept;
    RWLock &operator=(const RWLock &) noexcept;
    RWLock(RWLock &&) noexcept;
    RWLock &operator=(RWLock &&) noexcept;

    void ReadLock();
    bool TryReadLock();
    void WriteLock();
    bool TryWriteLock();
    void Unlock();

private:
    void *m_Handle;
};

class LIBM2_EXPORT ScopedRWLock
{
public:
    explicit ScopedRWLock(RWLock &l, bool write = false);
    ~ScopedRWLock();

private:
    ScopedRWLock(const ScopedRWLock &) = delete;
    ScopedRWLock &operator=(const ScopedRWLock &) = delete;
    ScopedRWLock(ScopedRWLock &&) = delete;
    ScopedRWLock &operator=(ScopedRWLock &&) = delete;

    RWLock &m_lock;
};

class LIBM2_EXPORT ScopedReadRWLock : public ScopedRWLock
{
public:
    explicit ScopedReadRWLock(RWLock &l);
    ~ScopedReadRWLock();
};

class LIBM2_EXPORT ScopedWriteRWLock : public ScopedRWLock
{
public:
    explicit ScopedWriteRWLock(RWLock &l);
    ~ScopedWriteRWLock();
};


}// namespace m2


#endif//M2_RWLOCK_H_