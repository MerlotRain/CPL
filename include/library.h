/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file library.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/

#pragma once

#include "stringhelp.h"

namespace Lite {
namespace Utility {

/// @brief 动态库模块
/// @details 不继承引用对象，将内存管理权限交给用户
class GsLibrary
{
public:
    /// @brief linux动态库加载标识
    enum Flags
    {
        /// @brief 标识此共享对象定义的符号将可用于后续加载的共享对象的符号解析
        SHLIB_GLOBAL = 1,
        /// @brief 标识此共享对象定义的符号不可用于后续加载的共享对象中的引用
        SHLIB_LOCAL = 2
    };

    /// @brief 默认构造
    GsLibrary() = default;

    /// @brief 根据路径打开动态库
    /// @param path
    explicit GsLibrary(const char *path);

    /// @brief 根据路径和标识打开动态库
    /// @param path
    /// @param flags
    GsLibrary(const char *path, int flags);
    /// @brief 默认析构
    /// @details 析构时不会主动释放动态库句柄，需要手动管理
    virtual ~GsLibrary();

    /// @brief 加载动态库
    /// @details 加载失败时会抛出异常
    /// @param path
    void Load(const char *path);
    /// @brief 加载动态库
    /// @details 加载失败时会抛出异常
    /// @param path
    /// @param flags
    void Load(const char *path, int flags);

    /// @brief 卸载动态库
    void Unload();
    /// @brief 判断动态库是否加载
    /// @return
    bool IsLoaded() const;

    /// @brief 是否存在指定符号
    /// @param name
    /// @return
    bool HasSymbol(const char *name);

    /// @brief 获取给定名称的带有符号的地址
    /// @param name
    /// @return
    void *Symbol(const char *name);

    /// @brief 动态库路径
    /// @return
    const GsString &Path() const;

    /// @brief 获取当前平台下库文件后缀
    /// @return
    static GsString Suffix();
    /// @brief 动态库搜索路径，设置后可仅通过名称加载动态库
    /// @param path
    /// @return
    static bool SearchPath(const GsString &path);

private:
    GS_DISABLE_COPY(GsLibrary)

    GsString m_strPath;
    void *m_Handle;
    static std::mutex m_mutex;
};


}// namespace Utility
}// namespace Lite
