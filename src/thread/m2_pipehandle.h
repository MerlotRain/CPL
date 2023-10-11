#ifndef UTILITY_PIPEHANDLE_H
#define UTILITY_PIPEHANDLE_H

#include <object.h>
#ifdef _WIN32
#include <Windows.h>
#endif


namespace m2 {

/******************************************* PipeImpl *******************************************/

class PipeImpl : public RefObject
{
public:
    PipeImpl();
    ~PipeImpl();
    int Write(const unsigned char *buf, int len);
    int Read(unsigned char *buf, int len);

    void CloseWrite();
    void CloseRead();

#ifdef _WIN32
    HANDLE readHandle;
    HANDLE writeHandle;
#else
    int readHandle;
    int writeHandle;
#endif
};

#define PIPE_HANDLE(x) (static_cast<PipeImpl *>(x))

}// namespace m2


#endif//UTILITY_PIPEHANDLE_H