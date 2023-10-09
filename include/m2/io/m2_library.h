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

#ifndef M2_LIBRARY_H_
#define M2_LIBRARY_H_

namespace m2 {

class Library
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
    Library() = default;

    /// @brief 根据路径打开动态库
    /// @param path
    explicit Library(const char *path);

    /// @brief 根据路径和标识打开动态库
    /// @param path
    /// @param flags
    Library(const char *path, int flags);
    /// @brief 默认析构
    /// @details 析构时不会主动释放动态库句柄，需要手动管理
    virtual ~Library();

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
    const String &Path() const;

    /// @brief 获取当前平台下库文件后缀
    /// @return
    static String Suffix();
    /// @brief 动态库搜索路径，设置后可仅通过名称加载动态库
    /// @param path
    /// @return
    static bool SearchPath(const String &path);

private:
    GS_DISABLE_COPY(Library)

    String m_strPath;
    void *m_Handle;
    static RecursiveMutex m_mutex;
};

}// namespace m2

#endif//M2_LIBRARY_H_