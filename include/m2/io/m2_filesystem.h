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

#pragma once

#include "datetime.h"
#include "delegate.h"
#include "stringhelp.h"

namespace m2 {


/// @brief 操作系统
enum class OperatorSystemType
{
    /// @brief 未知操作系统
    eUnknown,
    /// @brief Windows操作系统
    eWindows,
    /// @brief Linux操作系统
    eLinux,
    /// @brief MacOSX操作系统
    eMacOSX,
    /// @brief Android操作系统
    eAndroid
};

/// @brief BOM（Byte Order Mark）字节顺序标记
/// @details Windows下的特殊情况，文件不建议使用BOM头。
enum class BOMType
{
    /// @brief 未知或空的BOM标记
    eUnknow,
    /// @brief UTF8标记（EF BB BF）
    eUTF8,
    /// @brief UTF16大端序（FE FF）
    eUTF16_BE,
    /// @brief UTF16小端序（FF FE）
    eUTF16_LE,
    /// @brief UTF32大端序（00 00 FE FF）
    eUTF32_BE,
    /// @brief UTF32小端序（FF FE 00 00）
    eUTF32_LE,
    /// @brief UTF7（2B 2F 76）
    eUTF7,
    /// @brief GB18030（84 31 95 33）
    eGB18030,
};


/// @brief 操作系统环境变量相关
class M2_API OperatorSystemEnvironment
{
public:
    /// @brief 获取当前的操作系统
    /// @return
    static OperatorSystemType CurrentOperatorSystemType();
    /// @brief 环境变量分隔符
    /// @details 多个环境变量如PATH环境变量多个路径的分隔符。linux下为冒号（:）,windows下为分号（;）
    /// @return
    static char EnvironmentVariableSeparator();

    /// @brief 获取环境变量的值
    /// @param name
    /// @return
    static String EnvironmentVariable(const char *name);

    /// @brief 修改环境变量的值
    /// @param name
    /// @param value
    static void ChangeEnvironmentVariable(const char *name, const char *value);

    /// @brief 删除环境变量的值
    /// @param name
    static void RemoveEnvironmentVariable(const char *name);

    /// @brief 删除环境变量中指定的内容，如果存在的话
    /// @param name
    /// @param content
    /// @return
    static String RemoveEnvironmentVariable(const char *name, const char *content);


    /// @brief 向环境变量中插入一段内容。如果存在此内容则不工作任何动作
    /// @param name 环境变量的名称
    /// @param content 要添加的内容
    /// @param bAddToTail 是否添加到尾部，否则就添加到头部
    /// @return 返回添加后的的环境变量内容
    static String AppendEnvironmentVariable(const char *name, const char *content, bool bAddToTail = true);

    /// @brief 添加动态链接库搜索的路径
    /// @details windows下通过AddDllDirectory添加动态库搜索路径，linux下添加LD_LIBRARY_PATH的环境变量
    static bool AppendDLLDirectory(const char *dir);

    /// @brief 删除动态链接库的搜索路径
    static bool RemoveDLLDirectory(const char *dir);
};


class M2_API FileSystem
{
public:
    /// @brief 获取最大文件打开句柄数
    /// @return window 默认512,最大2048,但是建议不要不要超过,
    static long long MaxStdio();

    /// @brief 设置最大文件打开句柄数
    /// @param long long maxIOCount 最大文件打开句柄数
    /// @return 如果返回0 则设置失败, 大于0 设置在成功
    /// @param maxIOCount
    static long long MaxStdio(long long maxIOCount);

    /// @brief 获取应用程序数据目录，Windows下将获取%AppData%目录,Linux下将获取HOME目录。
    static String AppDataFolder();

    /// @brief 系统PATH目录
    /// @return
    static String PathFolder();

    /// @brief 增加搜索路径到系统PATH环境变量中
    /// @param path
    static void AddSearchPath(const char *path);

    /// @brief 合并两个路径字符串
    /// @param path1 第一个路径
    /// @param path2 第二个路径
    /// @return 包含合并的路径的字符串。如果指定的路径之一是零长度字符串，则该方法返回其他路径。如果path2是绝对路径，则该方法返回 path2
    static String Combine(const char *path1, const char *path2);

    /// @brief 比较两个路径是否相等，根据平台决定是否忽略大小写
    static int ComparePath(const char *path1, const char *path2);

    /// @brief 测试字符串头的BOM标记类型
    static BOMType TestBOM(const char *str, int nLen);
    /// @brief 获取BOM标记的标记头长度
    static int BOMLength(BOMType eType);

    /// @brief 路径是否使用utf8字符串
    /// @return
    static bool IsUtf8Path();

    /// @brief 路径是否是大小写敏感
    /// @return 返回true标识大小写敏感
    static bool IsPathCaseSensitivity();

    /// @brief 文件路径的的分隔符
    /// @return
    static char PathSeparator();

    /// @brief 判断文件路径、目录路径是否存在
    /// @param strPath 文件或者目录的路径
    /// @return 返回路径是或否存在
    static bool Exists(const char *strPath);

    /// @brief 系统临时目录
    /// @return
    static String TemporaryFolder();

    /// @brief 当前应用程序的运行路径
    /// @return
    static String CurrentFolder();

    /// @brief 获取当前用户的主目录
    /// @return
    static String HomeFolder();

    /// @brief 获取当前用户目录下的Config目录
    /// @return
    static String ConfigHomeFolder();

    /// @brief 获取当前用户目录下的数据陌路
    /// @return
    static String DataHomeFolder();

    /// @brief 获取当前用户目录下的临时目录
    /// @return
    static String TempHomeFolder();

    /// @brief 获取当前用户目录下的缓存目录
    /// @return
    static String CacheHomeFolder();

    /// @brief 获取临时目录
    /// @return
    static String TempFolder();

    /// @brief 获取配置文件目录
    /// @details UNIX /etc/
    /// @return
    static String ConfigFolder();
};


class Dir;

/// @brief 文件
class M2_API File
{
    String m_strPath;

public:
    /// @brief 默认构造
    File();
    /// @brief 文件的完整路径构造对象
    /// @param path 文件完整路径
    File(const char *path);
    /// @brief 拷贝构造函数
    /// @param rhs
    File(const File &rhs);
    /// @brief 默认析构
    virtual ~File();

    /// @brief 赋值复制构造
    /// @param file
    /// @return
    File &operator=(const File &file);
    /// @brief 赋值
    /// @param file 其他文件
    /// @return 自身
    File &operator=(const char *file);
    /// @brief 赋值
    /// @param file 其他文件
    /// @return 自身
    File &operator=(const String &file);

    /// @brief 获取文件完整路径
    /// @return
    const String &Path() const;

    /// @brief 获取文件名称，不包含路径
    /// @param bHasExtension 是否包含后缀
    /// @return
    const String &Name(bool bHasExtension = true) const;

    /// @brief 文件所在的目录
    /// @return 返回文件所在的目录
    Dir Parent() const;

    /// @brief 判断文件是否存在
    /// @return
    bool Exists() const;

    /// @brief 文件的扩展名，(不带.)
    /// @return 返回文件的扩展名
    String Extension() const;

    /// @brief 改变文件路径的扩展名
    /// @details 注意并非修改文件的扩展名。
    /// @param strExt 新的扩展名，(不带.)
    /// @return 返回文件的扩展名
    String ChangeExtension(const char *strExt);

    /// @brief 判断文件是否刻度
    /// @return
    bool CanRead() const;
    /// @brief 判断文件是否可写入
    /// @return
    bool CanWrite() const;
    /// @brief 判断文件是否是可执行文件
    /// @return
    bool CanExecute() const;
    /// @brief 是否是一个文件链接
    /// @return
    bool IsLink() const;
    /// @brief 文件是否是隐藏的
    /// @return
    bool IsHidden() const;
    /// @brief 文件创建时间
    /// @return
    Timestamp Created() const;
    /// @brief 获取文件最后一次修改时间
    /// @return
    Timestamp LastModified() const;
    /// @brief 设置文件修改时间
    /// @param ts
    /// @return
    File &LastModified(const Timestamp &ts);
    /// @brief 获取文件的大小
    /// @return
    unsigned long long Size() const;
    /// @brief 设置文件的大小
    /// @param size
    /// @return
    File &Size(unsigned long long size);

    /// @brief 设置文件是否可写入
    /// @param flag
    /// @return
    File &Writeable(bool flag = true);

    /// @brief 设置文件是否只读
    /// @param flag
    /// @return
    File &ReadOnly(bool flag = true);

    /// @brief 设置文件是否可执行
    /// @param flag
    /// @return
    File &Executable(bool flag = true);

    /// @brief 将文件拷贝到指定位置
    /// @param path 目标文件路径
    /// @param overwrite 存在是否覆盖
    bool CopyTo(const char *path, bool overwrite = false) const;

    /// @brief 将文件移动到指定位置
    /// @param path 目标文件路径
    /// @param overwrite 存在是否覆盖
    bool MoveTo(const char *path, bool overwrite = false);

    /// @brief 文件重命名
    /// @param path 目标文件路径
    /// @param options 存在是否覆盖
    bool RenameTo(const char *path, bool overwrite = false);

    /// @brief 给文件创建链接
    /// @param path 链接文件路径
    void LinkTo(const char *path) const;

    /// @brief 删除文件
    void Remove();

    /// @brief 返回当前文件所在盘符分区的总空间大小
    /// @return 字节值
    unsigned long long TotalSpace() const;

    /// @brief 返回当前文件所在盘符分区的已经使用的大小
    /// @return 字节值
    unsigned long long UsableSpace() const;

    /// @brief 返回当前文件所在盘符分区的空闲的大小
    /// @return 字节值
    unsigned long long FreeSpace() const;

protected:
    void copyDirectory(const String &path, int options = 0) const;
};


/// @brief 文件系统的目录
class M2_API Dir
{
    String m_strPath;

public:
    /// @brief  默认函数
    Dir();
    /// @brief 拷贝构造函数
    /// @param pDir 拷贝的对象
    Dir(const Dir &pDir);
    /// @brief 目录的完整路径构造对象
    /// @param strDirPath 目录完整路径
    Dir(const char *strDirPath);
    virtual ~Dir();
    /// @brief 获取目录的内部字符串路径
    /// @return 返回目录字符串指针
    String Path() const;

    /// @brief 如果文件夹不存在则创建文件夹
    /// @return
    bool Create();

    /// @brief 目录的名称
    /// @return 返回目录的名称
    String Name() const;

    /// @brief 目录的完整路径（UTF-8）
    /// @return 返回目录的完整路径
    String FullPath() const;
    /// @brief 目录是否存在
    /// @return 返回目录是否存在
    bool Exists() const;

    /// @brief 是否为根目录
    /// @return 返回目录是否是跟目录
    bool IsRoot() const;

    /// @brief 返回父目录
    /// @return 返回父目录
    Dir Parent() const;
    /// @brief 以回调遍历所有的文件
    void ForEachFiles(Delegate<bool(const char *, void *)> &onFileCallBack, void *context = NULL, const char *searchPattern = NULL);

    /// @brief 目录下所有的文件
    /// @param searchPattern 搜索条件，比如*.txt
    /// @return 返回目录下的所有文件对象
    std::vector<File> Files(const char *searchPattern = NULL) const;

    /// @brief 目录下所有的文件
    /// @param files 保存文件对象的集合
    /// @return 返回保存集合的指针
    std::vector<File> *Files(std::vector<File> &files) const;

    /// @brief 获取子目录
    /// @return 返回子目录对象
    /// @param subName
    Dir SubDir(const char *subName) const;

    /// @brief 获取目录下的文件
    /// @return 目录下的文件
    /// @param fileName
    File File(const char *fileName) const;

    /// @brief 以回调遍历所有的目录
    /// @details 参数1
    void ForEachDirs(Delegate<bool(const char *, void *)> &onFileCallBack, void *context = NULL);

    /// @brief 目录下所有的子目录
    /// @return 返回目录下的所有子目录对象
    std::vector<Dir> Dirs() const;

    /// @brief 目录下所有的子目录
    /// @param files
    /// @return 返回目录下的所有子目录对象
    std::vector<Dir> *Dirs(std::vector<Dir> &files) const;

    /// @brief 判断目录是否为同一个目录
    /// @brief rhs 其他目录
    /// @return 传入目录是否和本目录为同一个文件
    bool operator==(const Dir &rhs) const;

    /// @brief 赋值
    /// @param rhs 对象
    /// @return 自身
    Dir &operator=(const Dir &rhs);

    /// @brief 赋值
    /// @brief strDirPath 对象
    /// @return 自身
    Dir &operator=(const char *strDirPath);

    /// @brief 赋值
    /// @param strDirPath 对象
    /// @return 自身
    Dir &operator=(const String &strDirPath);

    /// @brief bool操作符
    operator bool();
    /// @brief 重命名目录
    bool Rename(const char *name);

    /// @brief 删除当前目录
    /// @param recursive 是否删除子目录
    /// @return 返回是否成功
    bool Remove(bool recursive = true);

    /// @brief 删除一个目录
    /// @return 返回是否删除成功
    /// @param path
    /// @param recursive
    static bool Remove(const char *path, bool recursive = true);
    /// @brief 获取本地所有盘符
    /// @return 返回盘符列表,非windows返回/
    static std::vector<String> Drives();

    /// @brief 返回当前文件所在盘符分区的总空间大小
    /// @return 字节值
    unsigned long long TotalSpace() const;

    /// @brief 返回当前文件所在盘符分区的已经使用的大小
    /// @return 字节值
    unsigned long long UsableSpace() const;

    /// @brief 返回当前文件所在盘符分区的空闲的大小
    /// @return 字节值
    unsigned long long FreeSpace() const;
};

}// namespace m2
