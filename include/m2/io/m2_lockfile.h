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

#ifndef M2_LOCKFILE_H_
#define M2_LOCKFILE_H_

#include <m2_string.h>

namespace m2 {

class LockFilePrivate;
class LockFile
{
public:
    LockFile(const String &filename);
    ~LockFile();

    String fileName() const;

    bool lock();
    bool tryLock(int timeout = 0);
    void unlock();

    void setStaleLockTime(int);
    int staleLockTime() const;

    bool tryLock(std::chrono::milliseconds timeout)
    {
        return tryLock(int(timeout.count()));
    }

    void setStaleLockTime(std::chrono::milliseconds value)
    {
        setStaleLockTime(int(value.count()));
    }

    std::chrono::milliseconds staleLockTimeAsDuration() const
    {
        return std::chrono::milliseconds(staleLockTime());
    }

    bool isLocked() const;
    bool getLockInfo(int64_t *pid, String *hostname, String *appname) const;
    bool removeStaleLockFile();

    enum LockError
    {
        NoError = 0,
        LockFailedError = 1,
        PermissionError = 2,
        UnknownError = 3
    };
    LockError error() const;

private:
    LockFile(const LockFile &) = delete;
    LockFile &operator=(const LockFile &) = delete;

    LockFilePrivate *d;
};

}// namespace m2

#endif//M2_LOCKFILE_H_