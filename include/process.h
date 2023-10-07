/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file process.h
 * @brief
 * @details
 * @date 2023-08-23
 * @author
 *
 ******************************************************************************/


#pragma once

#include "stringhelp.h"

namespace Lite {
namespace Utility {

/// @brief 匿名管道
class UTILITY_EXPORT GsPipe
{
public:
    enum class GsPipeCloseMode
    {
        eCloseRead,
        eCloseWrite,
        eCloseAll,
    };

    /// @brief 默认构造
    GsPipe();
    /// @brief 拷贝构造
    /// @param pipe
    GsPipe(const GsPipe &pipe);
    /// @brief 默认析构
    ~GsPipe();
    /// @brief 赋值复制构造
    /// @param pipe
    /// @return
    GsPipe &operator=(const GsPipe &pipe);
    /// @brief 写入一段数据
    /// @param pBuffer
    /// @param nLen
    /// @return
    int Write(const unsigned char *pBuffer, int nLen);
    /// @brief 读取一段数据
    /// @param pBuffer
    /// @param nLen
    /// @return
    int Read(unsigned char *pBuffer, int nLen);
    /// @brief 关闭管道
    /// @param mode
    void Close(GsPipeCloseMode mode = GsPipeCloseMode::eCloseAll);
    /// @brief 获取句柄对象
    /// @return
    void *Handle();

private:
    void *m_Handle;
};

/// @brief 进程操作
class UTILITY_EXPORT GsProcessHandle
{
    friend class GsProcess;
    GsProcessHandle();

public:
    GsProcessHandle(void *handle);
    GsProcessHandle(const GsProcessHandle &);
    GsProcessHandle &operator=(const GsProcessHandle &);
    virtual ~GsProcessHandle();
    /// @brief 获取进程PID
    /// @return
    virtual unsigned int PID() const;
    /// @brief 进程等待
    /// @return
    virtual int Wait() const;
    /// @brief 尝试等待
    /// @return
    virtual int TryWait() const;

protected:
    void *m_Handle;
};

/// @brief 进程
class UTILITY_EXPORT GsProcess
{
public:
    /// @brief 获取当前进程的PID
    /// @return
    static unsigned int PID();
    /// @brief 返回当前进程在用户和内核模式下花费的秒数
    /// @param userTime
    /// @param kernelTime
    static void Times(long &userTime, long &kernelTime);

    /// @brief 创建一个新的进程
    /// @param command 命名
    /// @param args 参数列表
    /// @param option 其他操作
    /// @return
    static GsProcessHandle Launch(const char *command, const GsStringList &args,
                                  int option = 0);

    /// @brief 创建一个新的进程
    /// @param command
    /// @param args
    /// @param initialDirectory
    /// @param option
    /// @return
    static GsProcessHandle Launch(const char *command, const GsStringList &args,
                                  const char *initialDirectory, int option = 0);

    /// @brief 创建一个新的进程
    /// @param command
    /// @param args
    /// @param in
    /// @param out
    /// @param error
    /// @param option
    /// @return
    static GsProcessHandle Launch(const char *command, const GsStringList &args,
                                  GsPipe *in, GsPipe *out, GsPipe *error, int option = 0);

    /// @brief 创建一个新的进程
    /// @param command
    /// @param args
    /// @param initialDirectory
    /// @param in
    /// @param out
    /// @param error
    /// @param option
    /// @return
    static GsProcessHandle Launch(const char *command, const GsStringList &args,
                                  const char *initialDirectory, GsPipe *in, GsPipe *out, GsPipe *error, int option = 0);

    /// @brief 创建一个新的进程
    /// @param command
    /// @param args
    /// @param in
    /// @param out
    /// @param error
    /// @param env
    /// @param option
    /// @return
    static GsProcessHandle Launch(const char *command, const GsStringList &args,
                                  GsPipe *in, GsPipe *out, GsPipe *error,
                                  const std::map<GsString, GsString> &env, int option = 0);

    /// @brief 创建一个新的进程
    /// @param command
    /// @param args
    /// @param initialDirectory
    /// @param in
    /// @param out
    /// @param error
    /// @param env
    /// @param option
    /// @return
    static GsProcessHandle Launch(const char *command, const GsStringList &args,
                                  const char *initialDirectory, GsPipe *in, GsPipe *out, GsPipe *error,
                                  const std::map<GsString, GsString> &env, int option = 0);

    /// @brief 进程等待
    /// @param handle
    /// @return
    static int Wait(const GsProcessHandle &handle);

    static int TryWait(const GsProcessHandle &handle);

    /// @brief 进程是否还在执行中
    /// @param handle
    /// @return
    static bool IsRunning(const GsProcessHandle &handle);
    /// @brief 进程是否还在执行中
    /// @param pid
    /// @return
    static bool IsRunning(unsigned int pid);
    /// @brief 杀死进程
    /// @param handle
    static void Kill(GsProcessHandle &handle);
    /// @brief 杀死进程
    /// @param pid
    static void Kill(unsigned int pid);

    /// @brief 请求终止进程
    /// @param pid
    static void RequestTermination(unsigned int pid);
};


}// namespace Utility
}// namespace Lite
