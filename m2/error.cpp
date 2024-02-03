#include "error.h"
#include <textconvertor.h>
#ifdef _WIN32
#include <Windows.h>
#else
#endif


#ifdef _WIN32

int Error::lastError() { return static_cast<int>(GetLastError()); }

std::string Error::message(int code)
{
    std::string errMsg;
    DWORD dwFlg = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS;
    LPWSTR lpMsgBuf = 0;
    if (FormatMessageW(dwFlg, 0, (DWORD) code, 0, (LPWSTR) &lpMsgBuf, 0, NULL))
    {
        TextConverter::convert(lpMsgBuf, errMsg);
    }
    LocalFree(lpMsgBuf);
    return errMsg;
}

#else

int Error::lastError() { return errno; }

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

    ~StrErrorHelper() {}

    const std::string &message() const { return _message; }

protected:
    void setMessage(int rc) { _message = _buffer; }

    void setMessage(const char *msg) { _message = msg; }

private:
    char _buffer[256];
    std::string _message;
};

std::string Error::message(int code)
{
    StrErrorHelper helper(code);
    return helper.message();
}

#endif
