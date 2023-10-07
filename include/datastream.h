/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file datastream.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/


#pragma once

#include "bytebuffer.h"
#include "object.h"
#include "stringhelp.h"

namespace Lite {
namespace Utility {


class UTILITY_EXPORT GsByteBufferStream : public std::iostream
{
public:
    GsByteBufferStream(GsByteBuffer *buffer);

private:
    class GsByteStreamBuf : public std::streambuf
    {
        GsByteBuffer *m_Buffer;

    public:
        GsByteStreamBuf(GsByteBuffer *buffer);

    protected:
        virtual std::streamsize xsputn(const char *s, std::streamsize num);
        virtual pos_type seekpos(pos_type _Pos, ios_base::openmode mode = ios_base::in | ios_base::out);
        virtual pos_type seekoff(off_type, ios_base::seekdir,
                                 ios_base::openmode = ios_base::in | ios_base::out);
    };
    GsByteStreamBuf *m_buf;
};


/// @brief 流查询原点
enum GsStreamSeekOrigin
{
    eBegin,  //!< 从流的起点向后查询
    eCurrent,//!< 从流当前位置向后查询
    eEnd     //!< 从流的尾部向前查询
};

class UTILITY_EXPORT GsInputStream : public GsRefObject
{
public:
    /// @brief
    virtual ~GsInputStream();
    /// @brief
    /// @param nLen
    /// @return
    virtual int Skip(int nLen);
    /// @brief
    /// @param buff
    /// @param nLen
    /// @return
    virtual int Read(unsigned char *buff, int nLen);
    /// @brief
    /// @param buff
    /// @param nLen
    /// @param pointer
    /// @return
    virtual int Read(unsigned char *buff, int nLen, const unsigned char **pointer);
    /// @brief
    /// @return
    virtual long long Length() const;
    /// @brief
    /// @return
    virtual unsigned long long Offset() const = 0;
    /// @brief
    /// @param offset
    /// @param origin
    /// @return
    virtual bool Seek(int offset, GsStreamSeekOrigin origin);
    /// @brief
    /// @return
    virtual bool Eof() const;

    /// @brief
    /// @tparam T
    /// @return
    template<class T>
    T ReadT()
    {
        int nSize = sizeof(T);
        const unsigned char *pointer = NULL;

        int n = Read(NULL, nSize, &pointer);
        if (n == nSize && pointer)
        {
            return *reinterpret_cast<const T *>(pointer);
        }

        T v;
        unsigned char *tmp = (unsigned char *) &v;
        n = Read(tmp, nSize);
        if (n == nSize)
        {
            return v;
        }
        memset(&v, 0, nSize);
        return v;
    }

    /// @brief
    /// @tparam T
    /// @param v
    /// @return
    template<class T>
    bool ReadT(T &v)
    {
        int nSize = sizeof(T);
        unsigned char *tmp = (unsigned char *) &v;
        const unsigned char *pointer = NULL;
        return Read(tmp, nSize, &pointer) == nSize;
    }

    /// @brief
    /// @tparam T
    /// @param v
    /// @return
    template<class T>
    GsInputStream &operator>>(T &v)
    {
        ReadT(v);
        return *this;
    }

    /// @brief
    /// @param nLen
    /// @return
    GsString ReadString(int nLen);
    /// @brief
    /// @param nLen
    /// @param str
    /// @return
    int ReadString(int nLen, GsString &str);
    /// @brief
    /// @return
    GsString ReadLine();
    /// @brief
    /// @param line
    /// @return
    bool ReadLine(GsString &line);
    /// @brief
    /// @return
    char ReadInt8();
    /// @brief
    /// @return
    unsigned char ReadUInt8();
    /// @brief
    /// @return
    short ReadInt16();
    /// @brief
    /// @return
    unsigned short ReadUInt16();
    /// @brief
    /// @return
    int ReadInt32();
    /// @brief
    /// @return
    unsigned int ReadUInt32();
    /// @brief
    /// @return
    long long ReadInt64();
    /// @brief
    /// @return
    unsigned long long ReadUInt64();
    /// @brief
    /// @return
    float ReadFloat32();
    /// @brief
    /// @return
    double ReadFloat64();

protected:
    GsInputStream();
};


/// @brief 写入内存
class UTILITY_EXPORT GsMemoryInputStream : public GsInputStream
{
public:
    /// @brief
    /// @param buffer
    /// @param nLen
    /// @param bCopy
    GsMemoryInputStream(const unsigned char *buffer, int nLen, bool bCopy = false);
    /// @brief
    /// @param buffer
    /// @param bCopy
    GsMemoryInputStream(GsByteBuffer *buffer, bool bCopy = false);
    /// @brief
    /// @param str
    /// @param bCopy
    GsMemoryInputStream(const char *str, bool bCopy = false);
    /// @brief
    /// @param str
    /// @param bCopy
    GsMemoryInputStream(const GsString &str, bool bCopy = false);
    /// @brief 读取一块数据
    /// @details 从输入流读出一块特定长度的数据，返回实际读取的数据长度，pointer返回存储数据的原始指针，如果存在的话。具备0拷贝能力的派生类覆盖此函数
    /// @param buff 要存储读取数据的缓冲区，buff和pointer二者只允许一个为空
    /// @param nLen 要读取的数据长度
    /// @param pointer 返回存储数据的指针，对于文件则返回空指针，对于固定内存返回内存地址
    virtual int RawRead(unsigned char *buff, int nLen, const unsigned char **pointer);
    /// @brief 获取数据流的长度
    /// @details 如果流不支持eLength能力，则长度为-1，如果流支持eLength能力，则派生类应该覆盖此方法。
    virtual long long Length() const;

    /// @brief 获取输入流偏移位置
    virtual unsigned long long Offset() const;

    /// @brief 定位输入流偏移位置
    virtual bool Seek(int offset, GsStreamSeekOrigin origin);

    /// @brief 关闭流
    virtual bool Close();

protected:
    unsigned long long m_nOffset = 0;
    unsigned long long m_nLength = 0;
    const unsigned char *m_Head = NULL;
    GsByteBuffer m_Buffer;
    void Init();
    GsMemoryInputStream();
};
GS_SMARTER_PTR(GsMemoryInputStream)


/// @brief 读文件
class UTILITY_EXPORT GsFileInputStream : public GsInputStream
{
    FILE *m_pFile = NULL;
    unsigned long long m_nLength = 0;
    bool m_bCloseFile = true;
    void Init();

public:
    /// @brief 从文件路径构造
    /// @param  file 文件路径
    /// @param  bBin 是否以二进制方式打开文件
    GsFileInputStream(const char *file, bool bBin = true);

    /// @brief 从文件句柄构造
    /// @param file 文件句柄
    /// @param nLen 文件的长度
    /// @param bCloseFile 在对象析构时是否关闭文件
    GsFileInputStream(FILE *file, unsigned long long nLen, bool bCloseFile = false);

    virtual ~GsFileInputStream();

    using GsInputStream::ReadLine;
    /// @brief 读取一行字符串
    /// @param  line
    /// @return
    bool ReadLine(GsString &line);

    /// @brief 读取一块数据
    /// @details 从输入流读出一块特定长度的数据，返回实际读取的数据长度，不具备0拷贝能力的派生类覆盖此函数
    /// @param  buff
    /// @param  nLen
    /// @return
    virtual int RawRead(unsigned char *buff, int nLen);

    /// @brief 获取数据流的长度
    /// @details 如果流不支持eLength能力，则长度为-1，如果流支持eLength能力，则派生类应该覆盖此方法。
    /// @return
    virtual long long Length() const;

    /// @brief 获取输入流偏移位置
    /// @return
    virtual unsigned long long Offset() const;

    /// @brief 定位输入流偏移位置
    /// @param  offset 偏移量
    /// @param  origin 定位原点
    /// @return
    virtual bool Seek(int offset, GsStreamSeekOrigin origin);
};
GS_SMARTER_PTR(GsFileInputStream)


/// @brief 写出流
class UTILITY_EXPORT GsOutputStream : public GsRefObject
{
protected:
    GsOutputStream();

public:
    virtual ~GsOutputStream();
    virtual int RawWrite(const unsigned char *buff, int nLen) = 0;
    /// @brief 下次写入的偏移，即已经写入的长度，子类必须实现
    virtual unsigned long long Offset() const = 0;
    /// @brief 定位写入偏移。允许定位的输出流子类必须实现。
    virtual bool Seek(int offset, GsStreamSeekOrigin origin);
    /// @brief 如果存在缓存，提交缓存中未写入的内容。
    virtual bool Flush();

    /// @brief 关闭流。
    virtual bool Close();

    /// @brief 模板写入
    template<class T>
    GsOutputStream &WriteT(const T &val)
    {
        RawWrite((const unsigned char *) &val, sizeof(T));
        return *this;
    }
    /// @brief <<输出操作符
    template<class T>
    GsOutputStream &operator<<(const T &val)
    {
        return WriteT(val);
    }
    /// @brief 输出字符串
    /// @param str 要输出的字符串
    /// @param nLen 要输出的字符串长度，如果长度小于0，则自动计算
    int WriteString(const char *str, int nLen = -1);
    /// @brief 输出字符串
    int WriteString(const GsString &str);

    /// @brief 写入整块内存
    int WriteBuffer(const GsByteBuffer *buff);
};
GS_SMARTER_PTR(GsOutputStream)


/// @brief 写入内存
class UTILITY_EXPORT GsMemoryOutputStream : public GsOutputStream
{
public:
    /// @brief 缺省构造，将数据输出到内部ByteBuffer中，通过Buffer方法获取存储数据的对象。
    GsMemoryOutputStream();

    /// @brief 将数据输出到std::stringstream中存储。
    GsMemoryOutputStream(std::stringstream &str);

    /// @brief 将数据输出到GsString中存储。
    GsMemoryOutputStream(GsString &str);

    /// @brief 将数据输出到Vector中存储
    GsMemoryOutputStream(std::vector<unsigned char> &vec);

    /// @brief 将数据输出到ByteBuffer中存储
    GsMemoryOutputStream(GsByteBuffer *buff);

    /// @brief 将数据输出到固定长度的内存块中
    GsMemoryOutputStream(unsigned char *fixMem, unsigned long long nLen);

    /// @brief 获取存储数据的Buffer
    const GsByteBuffer *Buffer() const;

    /// @brief 向输出流中写入一块数据，子类必须实现。
    virtual int RawWrite(const unsigned char *buff, int nLen);

    /// @brief 下次写入的偏移，即已经写入的长度，子类必须实现
    virtual unsigned long long Offset() const;

    /// @brief 定位写入偏移。允许定位的输出流子类必须实现。
    virtual bool Seek(int offset, GsStreamSeekOrigin origin);

private:
    unsigned long long m_Offset = 0;
    unsigned char *m_FixMemoryHead = NULL;
    unsigned long long m_FixeMemoryLength = 0;

    unsigned long long m_Start = 0;
    std::vector<unsigned char> *m_pVectorOutput = NULL;
    GsString *m_pStringOutput = NULL;
    GsByteBuffer *m_pByteBufferOutput = NULL;
    std::stringstream *m_pStringStream = NULL;
    GsByteBuffer m_InnerBuffer;
};
GS_SMARTER_PTR(GsMemoryOutputStream)


/// @brief 写入文件
class UTILITY_EXPORT GsFileOutputStream : public GsOutputStream
{
    unsigned long long m_Start;
    FILE *m_pFile = NULL;
    bool m_bCloseOnEnd = true;

public:
    /// @brief 从文件名构造
    /// @param path 文件路径
    /// @param bBinary 是否以二进制方式打开文件
    /// @param bAppend 是否以追加的方式打开文件,如果为false，当文件存在时会被覆盖。
    GsFileOutputStream(const char *path, bool bBinary = true, bool bAppend = false);
    /// @brief 从已有的文件句柄构造
    /// @param f 已经打开的文件句柄
    /// @param bCloseOnEnd 在输出流关闭的是否是否自动关闭文件句柄
    GsFileOutputStream(FILE *f, bool bCloseOnEnd = true);
    ~GsFileOutputStream();

    /// @brief 向输出流中写入一块数据，子类必须实现。
    virtual int RawWrite(const unsigned char *buff, int nLen);

    /// @brief 下次写入的偏移，即已经写入的长度，子类必须实现
    virtual unsigned long long Offset() const;

    /// @brief 定位写入偏移。允许定位的输出流子类必须实现。
    virtual bool Seek(int offset, GsStreamSeekOrigin origin);
};
GS_SMARTER_PTR(GsFileOutputStream)


}// namespace Utility
}// namespace Lite
