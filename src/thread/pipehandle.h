#ifndef UTILITY_PIPEHANDLE_H
#define UTILITY_PIPEHANDLE_H

#include <object.h>
#ifdef _WIN32
#include <Windows.h>
#endif


namespace Lite {
namespace Utility {

/******************************************* GsPipeImpl *******************************************/

class GsPipeImpl : public GsRefObject
{
public:
    GsPipeImpl();
    ~GsPipeImpl();
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

#define PIPE_HANDLE(x) (static_cast<GsPipeImpl *>(x))

}// namespace Utility
}// namespace Lite


#endif//UTILITY_PIPEHANDLE_H