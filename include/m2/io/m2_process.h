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

#ifndef M2_PROCESS_H_
#define M2_PROCESS_H_

#include <m2_string.h>

namespace m2 {

class LIBM2_EXPORT Pipe
{
public:
    enum class PipeCloseMode
    {
        eCloseRead,
        eCloseWrite,
        eCloseAll,
    };
    Pipe();
    Pipe(const Pipe &pipe);
    Pipe &operator=(const Pipe &);
    Pipe(Pipe &&);
    Pipe &operator=(Pipe &&);
    ~Pipe();

    Pipe &operator=(const Pipe &pipe);
    int write(const unsigned char *pBuffer, int nLen);
    int read(unsigned char *pBuffer, int nLen);
    void close(PipeCloseMode mode = PipeCloseMode::eCloseAll);
    void *handle();

private:
    void *m_Handle;
};


class LIBM2_EXPORT ProcessHandle
{
    friend class Process;
    ProcessHandle();

public:
    explicit ProcessHandle(void *handle);
    ProcessHandle(const ProcessHandle &);
    ProcessHandle &operator=(const ProcessHandle &);
    ProcessHandle(ProcessHandle &&);
    ProcessHandle &operator=(ProcessHandle &&);
    virtual ~ProcessHandle();

    virtual unsigned int pid() const;
    virtual int wait() const;
    virtual int tryWait() const;

protected:
    void *m_Handle;
};

class LIBM2_EXPORT Process
{
public:
    static unsigned int pid();
    static void times(long &userTime, long &kernelTime);
    static ProcessHandle launch(const char *command, const StringList &args,
                                int option = 0);
    static ProcessHandle launch(const char *command, const StringList &args,
                                const char *initialDirectory, int option = 0);
    static ProcessHandle launch(const char *command, const StringList &args,
                                Pipe *in, Pipe *out, Pipe *error,
                                int option = 0);
    static ProcessHandle launch(const char *command, const StringList &args,
                                const char *initialDirectory, Pipe *in,
                                Pipe *out, Pipe *error, int option = 0);
    static ProcessHandle launch(const char *command, const StringList &args,
                                Pipe *in, Pipe *out, Pipe *error,
                                const std::map<String, String> &env,
                                int option = 0);
    static ProcessHandle launch(const char *command, const StringList &args,
                                const char *initialDirectory, Pipe *in,
                                Pipe *out, Pipe *error,
                                const std::map<String, String> &env,
                                int option = 0);
    static int wait(const ProcessHandle &handle);
    static int tryWait(const ProcessHandle &handle);
    static bool isRunning(const ProcessHandle &handle);
    static bool isRunning(unsigned int pid);
    static void kill(ProcessHandle &handle);
    static void kill(unsigned int pid);
    static void requestTermination(unsigned int pid);
};

}// namespace m2

#endif//M2_PROCESS_H_