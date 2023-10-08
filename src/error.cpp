﻿#include "error.h"

#ifdef _WIN32
#include <Windows.h>
#else
#endif

namespace m2 {

#ifdef _WIN32

int GsError::LastError()
{
    return static_cast<int>(GetLastError());
}

GsString GsError::Message(int code)
{
    GsString errMsg;
    DWORD dwFlg = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS;
    LPWSTR lpMsgBuf = 0;
    if (FormatMessageW(dwFlg, 0, (DWORD) code, 0, (LPWSTR) &lpMsgBuf, 0, NULL))
    {
        GsCW2A cw2a(lpMsgBuf);
        errMsg = cw2a.m_Str;
    }
    LocalFree(lpMsgBuf);
    return errMsg;
}

#else

int GsError::LastError()
{
    return errno;
}

class StrErrorHelper
{
public:
    explicit StrErrorHelper(int err)
    {
        _buffer[0] = 0;

#if (_XOPEN_SOURCE >= 600) || POCO_OS == POCO_OS_ANDROID || __APPLE__
        setMessage(strerror_r(err, _buffer, sizeof(_buffer)));
#elif _GNU_SOURCE
        setMessage(strerror_r(err, _buffer, sizeof(_buffer)));
#else
        setMessage(strerror(err));
#endif
    }

    ~StrErrorHelper()
    {
    }

    const GsString &message() const
    {
        return _message;
    }

protected:
    void setMessage(int rc)
    {
        _message = _buffer;
    }

    void setMessage(const char *msg)
    {
        _message = msg;
    }

private:
    char _buffer[256];
    GsString _message;
};

GsString GsError::Message(int code)
{
    StrErrorHelper helper(code);
    return helper.message();
}

#endif


}// namespace m2
