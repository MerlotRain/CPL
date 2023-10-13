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

#ifndef M2_FILEINFO_H_
#define M2_FILEINFO_H_

#include <m2_string.h>

namespace m2 {

class DateTime;
class Dir;
class File;
class M2_API FileInfo
{
public:
    FileInfo();
    explicit FileInfo(const String &file);
    explicit FileInfo(const String &dir, const String &file);
    FileInfo(const std::filesystem::path &file);
    FileInfo(const FileInfo &other);
    FileInfo &operator=(const FileInfo &other);
    void swap(FileInfo &other) noexcept;

    bool operator==(const FileInfo &) const;
    bool operator!=(const FileInfo &) const;

    void setFile(const String &file);
    void setFile(const File &file);
    void setFile(const Dir &dir, const String file);
    void setFile(const std::filesystem::path &file);

    String fileName() const;
    String baseNam() const;
    String completeBaseName() const;
    String suffix() const;

    String bundleName() const;
    String completeSuffix() const;

    String path() const;
    String absolutePath() const;
    String canonicalPath() const;

    Dir dir() const;
    Dir absoluteDir() const;

    bool isReadable() const;
    bool isWritable() const;
    bool isExecutable() const;
    bool isHidden() const;
    bool isNativePath() const;

    bool isRelative() const;
    inline bool isAbsolute() const { return !isRelative(); }
    bool makeAbsolute();

    bool isFile() const;
    bool isDir() const;
    bool isSymLink() const;
    bool isSymbolicLink() const;
    bool isShortcut() const;
    bool isAlias() const;
    bool isJunction() const;
    bool isRoot() const;
    bool isBundle() const;

    String owner() const;
    uint32_t ownerId() const;
    String group() const;
    uint32_t groupId() const;

    int64_t size() const;

    DateTime createTime() const;
    DateTime metadataChangeTime() const;
    DateTime lastModified() const;
    DateTime lastRead() const;

    bool caching() const;
    void setCaching(bool on);
};

typedef std::list<FileInfo> FileInfoList;

}// namespace m2

#endif//M2_FILEINFO_H_