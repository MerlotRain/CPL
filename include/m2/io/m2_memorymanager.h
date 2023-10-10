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

#include "object.h"
#include "stringhelp.h"

namespace m2 {


/// @brief 内存块对象，内存只会增长，不会主动析构
class M2_API ByteBuffer
{
public:
    /// @brief 申请内存块
    /// @param len 内存字节大小
    ByteBuffer(unsigned int len = 0);

    /// @brief
    /// @param buffer
    ByteBuffer(unsigned char *buffer);

    /// @brief
    /// @param buffer
    /// @param len
    ByteBuffer(unsigned char *buffer, int len);

    /// @brief 由字符串构造
    /// @param str
    ByteBuffer(const char *str);

    /// @brief
    /// @param rhs
    ByteBuffer(const ByteBuffer &rhs);

    /// @brief 移动构造，转移所有权，原内存将不可用
    /// @param rhs
    ByteBuffer(ByteBuffer &&rhs) noexcept;

    /// @brief 触发析构函数时会主动释放内存
    /// @details 对于不想析构内存，使用指针管理
    virtual ~ByteBuffer();

    /// @brief 释放内存，传递指针地址
    /// @param buffer
    void Attach(unsigned char *buffer);

    /// @brief 传递指针地址
    /// @return
    unsigned char *Detach();

    /// @brief 类型转换
    explicit operator unsigned char *() const;
    /// @brief 类型转换
    explicit operator char *() const;
    /// @brief 类型转换
    explicit operator int *() const;
    /// @brief 类型转换
    explicit operator unsigned int *() const;
    /// @brief 类型转换
    explicit operator short *() const;
    /// @brief 类型转换
    explicit operator unsigned short *() const;
    /// @brief 类型转换
    explicit operator long long *() const;
    /// @brief 类型转换
    explicit operator unsigned long long *() const;
    /// @brief 类型转换
    explicit operator double *() const;
    /// @brief 类型转换
    explicit operator float *() const;
    /// @brief 类型转换
    explicit operator bool *() const;

    /// @brief 获取数据块头指针
    /// @return
    unsigned char *Ptr() const;
    /// @brief 数据块的尾指针
    /// @return
    virtual unsigned char *EndPtr() const;
    /// @brief
    /// @tparam T
    /// @return
    template<typename T>
    T *PtrT() const
    {
        return (T *) (Ptr());
    }
    /// \brief 函数模板
    template<typename T>
    T *EndPtrT() const
    {
        return (T *) (EndPtr());
    }
    /// @brief 获取头指针
    /// @return
    unsigned char *BufferHead() const;

    /// @brief 获取真实内存块数据块的大小
    /// @return
    unsigned int BufferSize() const;

    template<typename T>
    unsigned int BufferSizeT() const
    {
        return BufferSize() / sizeof(T);
    }

    /// @brief 获取内存块分配的大小，通常来说，BufferLength >= BufferSize
    /// @return
    unsigned int BufferLength() const;

    /// @brief 设置内存整体的值
    /// @param nValue
    /// @return
    unsigned char *SetBufferValue(int nValue);

    template<typename T>
    T *SetBufferValueT(const T &val)
    {
        //获取数据的字节
        const auto *pByte = (const unsigned char *) &val;
        //判断整个数据为重复字节，或者全部为0
        bool bIsEqual = true;
        for (int i = 1; i < sizeof(val); i++)
        {
            if (pByte[i] != pByte[0])
            {
                bIsEqual = false;
                break;
            }
        }
        //如果整个为重复字节。
        if (bIsEqual)
        {
            return (T *) SetBufferValue(pByte[0]);
        }
        //如果是非重复字节这需要逐个赋值
        T *pHead = PtrT<T>();
        T *pEnd = EndPtrT<T>();
        for (; pHead < pEnd; pHead++)
        {
            pHead[0] = val;
        }
        return PtrT<T>();
    }

    /// @brief 向尾部添加一段数据
    /// @details 认为，nLen的长度可以完全读取到pBuff的内容
    /// @param pBuff 新内存的首地址
    /// @param nLen 追加的长度
    /// @return
    unsigned char *Append(const unsigned char *pBuff, int nLen);

    /// @brief 向尾部增加一段字符串
    /// @param pStr
    /// @return
    unsigned char *Append(const char *pStr);

    template<typename T>
    unsigned char *AppendT(const T &pBuff)
    {
        return Append((const unsigned char *) &pBuff, sizeof(T));
    }

    /// @brief 插入一段内存，如果原始内存被截断，则 \a nPos 后的内容将会移动
    /// @param nPos 插入的位置
    /// @param pStr 新内存的头指针
    /// @param nLen 新内存的长度
    /// @return
    unsigned char *Insert(unsigned int nPos, const unsigned char *pStr, int nLen);

    /// @brief 分配nLen个字节内存
    /// @param nLen
    /// @return
    unsigned char *Allocate(unsigned int nLen);
    /// @brief 分配nLen个指定类型
    /// @tparam T
    /// @param nLen
    /// @return
    template<typename T>
    T *AllocateT(int nLen)
    {
        Allocate(sizeof(T) * nLen);
        return PtrT<T>();
    }


    /// @brief 重置内存数据
    virtual void Clear();
    /// @brief 释放内存
    virtual void Reset();

    /// @brief 将输入内存的指定长度拷贝到当前内存块
    /// @param pBuff
    /// @param nLen
    /// @return
    unsigned char *Copy(const unsigned char *pBuff, int nLen);

    /// @brief 从当前内存中读取指定长度数据
    /// @param nLen
    /// @return
    ByteBuffer ReadSize(int nLen);

    /// @brief 内存空间重置
    /// @param nLen
    void Resize(int nLen);

    /// @brief 交换内存
    /// @param rhs
    /// @return
    ByteBuffer *Swap(ByteBuffer &rhs);

    /// @brief 交换内存
    /// @param pBuff
    /// @return
    ByteBuffer *Swap(unsigned char *pBuff);

    /// @brief 判断内存空间是否为空
    /// @return
    bool IsEmpty() const;

    /// @brief 赋值复制构造
    /// @param rsh
    /// @return
    ByteBuffer &operator=(const ByteBuffer &rsh);

    /// @brief 赋值移动构造
    /// @param rsh
    /// @return
    ByteBuffer &operator=(ByteBuffer &&rsh) noexcept;

    /// @brief 将二进制内存块转换为base64编码字符串
    /// @return
    String ToBase64() const;

    /// @brief 从Base64字符串解码成为内存块
    /// @param strBase64
    /// @return
    bool FromBase64(const char *strBase64);

    /// @brief 判断字符串是否是一个base64编码的字符串
    /// @param strBase64
    /// @return
    static bool IsBase64(const char *strBase64);

private:
    unsigned char *m_Buffer;
};


/// @brief 比特位管理
class M2_API Bitset
{
    ByteBuffer m_Data;
    unsigned int m_Size = 0;

public:
    /// @brief 位引用
    class Reference
    {
        friend class Bitset;
        Bitset *m_Bitset = nullptr;
        int m_Pos = 0;
        explicit Reference(Bitset &bitset, int pos) noexcept;

    public:
        Reference(const Reference &);
        ~Reference();
        Reference &operator=(bool x) noexcept;
        Reference &operator=(const Reference &) noexcept;

        /// @brief 位引用取反
        /// @return
        bool operator~() const noexcept;
        explicit operator bool() const noexcept;
        /// @brief 位引用取反
        /// @return
        Reference &Flip() noexcept;
    };

    /// @brief 构造
    /// @param nSize 比特位长度
    explicit Bitset(unsigned int nSize = 0);

    /// @brief 根据字符串构造
    /// @param str
    explicit Bitset(const char *str);

    /// @brief 拷贝构造
    /// @param r
    Bitset(const Bitset &r);

    /// @brief 移动构造
    /// @param rr
    Bitset(Bitset &&rr) noexcept;

    /// @brief 赋值复制构造
    /// @param r
    /// @return
    Bitset &operator=(const Bitset &r);

    /// @brief 赋值移动构造
    /// @param r
    /// @return
    Bitset &operator=(Bitset &&r) noexcept;

    /// @brief 交换
    /// @param bit
    void Swap(Bitset &bit);

    /// @brief 是否相等
    /// @param r
    /// @return
    bool operator==(const Bitset &r);

    /// @brief 判断不等
    /// @param r
    /// @return
    bool operator!=(const Bitset &r);

    /// @brief 是否为空
    /// @return
    bool Empty() const;

    /// @brief &=运算
    /// @param r
    /// @return
    Bitset &operator&=(const Bitset &r);

    /// @brief |=运算
    /// @param r
    /// @return
    Bitset &operator|=(const Bitset &r);

    /// @brief ^=运算
    /// @param r
    /// @return
    Bitset &operator^=(const Bitset &r);

    /// @brief <<=运算
    /// @param pos
    /// @return
    Bitset &operator<<=(size_t pos) noexcept;

    /// @brief >>=运算
    /// @param pos
    /// @return
    Bitset &operator>>=(size_t pos) noexcept;

    /// @brief <<运算
    /// @param pos
    /// @return
    Bitset operator<<(size_t pos) const noexcept;

    /// @brief >>运算
    /// @param pos
    /// @return
    Bitset operator>>(size_t pos) const noexcept;

    /// @brief 设置所有位
    /// @return
    Bitset &Set() noexcept;

    /// @brief 设置指定位的状态
    /// @param pos
    /// @param val
    /// @return
    Bitset &Set(size_t pos, bool val = true);

    /// @brief 清空所有位的状态
    /// @return
    Bitset &Reset() noexcept;

    /// @brief 清空指定位的状态
    /// @param pos
    /// @return
    Bitset &Reset(size_t pos);

    /// @brief ~运算，位状态取反
    /// @return
    Bitset operator~() const noexcept;

    /// @brief 位状态取反
    /// @return
    Bitset &Flip() noexcept;

    /// @brief 特定位置取反
    /// @param pos
    /// @return
    Bitset &Flip(size_t pos);

    /// @brief 元素访问
    /// @param pos
    /// @return
    bool operator[](size_t pos) const;

    /// @brief 访问引用
    /// @param pos
    /// @return
    Reference operator[](size_t pos);

    /// @brief bit位长度
    /// @return
    static unsigned int Size();

    /// @brief 向尾部添加一个bit位
    /// @param bit
    /// @return
    Bitset &PushBack(bool bit);

    /// @brief 分配特定长度的容器
    /// @param size
    /// @return
    Bitset &Resize(int size);

    /// @brief 保留空间
    /// @param size
    /// @return
    Bitset &Reverse(int size);

    /// @brief 获取bit位状态
    /// @param n
    /// @return
    static bool Test(unsigned int n);

    /// @brief 是否所有位状态为空
    /// @return
    static bool None();

    /// @brief 是否存在任何状态为true
    /// @return
    static bool Any();

    /// @brief 是否所有状态为true
    /// @return
    static bool All();

    /// @brief 状态为true的位数量
    /// @return
    bool Count() const;

    /// @brief 转换成字符串
    /// @return
    String ToString() const;
};


class M2_API ByteBufferStream : public std::iostream
{
public:
    ByteBufferStream(ByteBuffer *buffer);

private:
    class ByteStreamBuf : public std::streambuf
    {
        ByteBuffer *m_Buffer;

    public:
        ByteStreamBuf(ByteBuffer *buffer);

    protected:
        virtual std::streamsize xsputn(const char *s, std::streamsize num);
        virtual pos_type seekpos(pos_type _Pos, ios_base::openmode mode = ios_base::in | ios_base::out);
        virtual pos_type seekoff(off_type, ios_base::seekdir,
                                 ios_base::openmode = ios_base::in | ios_base::out);
    };
    ByteStreamBuf *m_buf;
};


/// @brief 流查询原点
enum StreamSeekOrigin
{
    eBegin,  //!< 从流的起点向后查询
    eCurrent,//!< 从流当前位置向后查询
    eEnd     //!< 从流的尾部向前查询
};

class M2_API InputStream : public RefObject
{
public:
    /// @brief
    virtual ~InputStream();
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
    virtual bool Seek(int offset, StreamSeekOrigin origin);
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
    InputStream &operator>>(T &v)
    {
        ReadT(v);
        return *this;
    }

    /// @brief
    /// @param nLen
    /// @return
    String ReadString(int nLen);
    /// @brief
    /// @param nLen
    /// @param str
    /// @return
    int ReadString(int nLen, String &str);
    /// @brief
    /// @return
    String ReadLine();
    /// @brief
    /// @param line
    /// @return
    bool ReadLine(String &line);
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
    InputStream();
};


/// @brief 写入内存
class M2_API MemoryInputStream : public InputStream
{
public:
    /// @brief
    /// @param buffer
    /// @param nLen
    /// @param bCopy
    MemoryInputStream(const unsigned char *buffer, int nLen, bool bCopy = false);
    /// @brief
    /// @param buffer
    /// @param bCopy
    MemoryInputStream(ByteBuffer *buffer, bool bCopy = false);
    /// @brief
    /// @param str
    /// @param bCopy
    MemoryInputStream(const char *str, bool bCopy = false);
    /// @brief
    /// @param str
    /// @param bCopy
    MemoryInputStream(const String &str, bool bCopy = false);
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
    virtual bool Seek(int offset, StreamSeekOrigin origin);

    /// @brief 关闭流
    virtual bool Close();

protected:
    unsigned long long m_nOffset = 0;
    unsigned long long m_nLength = 0;
    const unsigned char *m_Head = NULL;
    ByteBuffer m_Buffer;
    void Init();
    MemoryInputStream();
};
M2_SMARTER_PTR(MemoryInputStream)


/// @brief 读文件
class M2_API FileInputStream : public InputStream
{
    FILE *m_pFile = NULL;
    unsigned long long m_nLength = 0;
    bool m_bCloseFile = true;
    void Init();

public:
    /// @brief 从文件路径构造
    /// @param  file 文件路径
    /// @param  bBin 是否以二进制方式打开文件
    FileInputStream(const char *file, bool bBin = true);

    /// @brief 从文件句柄构造
    /// @param file 文件句柄
    /// @param nLen 文件的长度
    /// @param bCloseFile 在对象析构时是否关闭文件
    FileInputStream(FILE *file, unsigned long long nLen, bool bCloseFile = false);

    virtual ~FileInputStream();

    using InputStream::ReadLine;
    /// @brief 读取一行字符串
    /// @param  line
    /// @return
    bool ReadLine(String &line);

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
    virtual bool Seek(int offset, StreamSeekOrigin origin);
};
M2_SMARTER_PTR(FileInputStream)


/// @brief 写出流
class M2_API OutputStream : public RefObject
{
protected:
    OutputStream();

public:
    virtual ~OutputStream();
    virtual int RawWrite(const unsigned char *buff, int nLen) = 0;
    /// @brief 下次写入的偏移，即已经写入的长度，子类必须实现
    virtual unsigned long long Offset() const = 0;
    /// @brief 定位写入偏移。允许定位的输出流子类必须实现。
    virtual bool Seek(int offset, StreamSeekOrigin origin);
    /// @brief 如果存在缓存，提交缓存中未写入的内容。
    virtual bool Flush();

    /// @brief 关闭流。
    virtual bool Close();

    /// @brief 模板写入
    template<class T>
    OutputStream &WriteT(const T &val)
    {
        RawWrite((const unsigned char *) &val, sizeof(T));
        return *this;
    }
    /// @brief <<输出操作符
    template<class T>
    OutputStream &operator<<(const T &val)
    {
        return WriteT(val);
    }
    /// @brief 输出字符串
    /// @param str 要输出的字符串
    /// @param nLen 要输出的字符串长度，如果长度小于0，则自动计算
    int WriteString(const char *str, int nLen = -1);
    /// @brief 输出字符串
    int WriteString(const String &str);

    /// @brief 写入整块内存
    int WriteBuffer(const ByteBuffer *buff);
};
M2_SMARTER_PTR(OutputStream)


/// @brief 写入内存
class M2_API MemoryOutputStream : public OutputStream
{
public:
    /// @brief 缺省构造，将数据输出到内部ByteBuffer中，通过Buffer方法获取存储数据的对象。
    MemoryOutputStream();

    /// @brief 将数据输出到std::stringstream中存储。
    MemoryOutputStream(std::stringstream &str);

    /// @brief 将数据输出到String中存储。
    MemoryOutputStream(String &str);

    /// @brief 将数据输出到Vector中存储
    MemoryOutputStream(std::vector<unsigned char> &vec);

    /// @brief 将数据输出到ByteBuffer中存储
    MemoryOutputStream(ByteBuffer *buff);

    /// @brief 将数据输出到固定长度的内存块中
    MemoryOutputStream(unsigned char *fixMem, unsigned long long nLen);

    /// @brief 获取存储数据的Buffer
    const ByteBuffer *Buffer() const;

    /// @brief 向输出流中写入一块数据，子类必须实现。
    virtual int RawWrite(const unsigned char *buff, int nLen);

    /// @brief 下次写入的偏移，即已经写入的长度，子类必须实现
    virtual unsigned long long Offset() const;

    /// @brief 定位写入偏移。允许定位的输出流子类必须实现。
    virtual bool Seek(int offset, StreamSeekOrigin origin);

private:
    unsigned long long m_Offset = 0;
    unsigned char *m_FixMemoryHead = NULL;
    unsigned long long m_FixeMemoryLength = 0;

    unsigned long long m_Start = 0;
    std::vector<unsigned char> *m_pVectorOutput = NULL;
    String *m_pStringOutput = NULL;
    ByteBuffer *m_pByteBufferOutput = NULL;
    std::stringstream *m_pStringStream = NULL;
    ByteBuffer m_InnerBuffer;
};
M2_SMARTER_PTR(MemoryOutputStream)


/// @brief 写入文件
class M2_API FileOutputStream : public OutputStream
{
    unsigned long long m_Start;
    FILE *m_pFile = NULL;
    bool m_bCloseOnEnd = true;

public:
    /// @brief 从文件名构造
    /// @param path 文件路径
    /// @param bBinary 是否以二进制方式打开文件
    /// @param bAppend 是否以追加的方式打开文件,如果为false，当文件存在时会被覆盖。
    FileOutputStream(const char *path, bool bBinary = true, bool bAppend = false);
    /// @brief 从已有的文件句柄构造
    /// @param f 已经打开的文件句柄
    /// @param bCloseOnEnd 在输出流关闭的是否是否自动关闭文件句柄
    FileOutputStream(FILE *f, bool bCloseOnEnd = true);
    ~FileOutputStream();

    /// @brief 向输出流中写入一块数据，子类必须实现。
    virtual int RawWrite(const unsigned char *buff, int nLen);

    /// @brief 下次写入的偏移，即已经写入的长度，子类必须实现
    virtual unsigned long long Offset() const;

    /// @brief 定位写入偏移。允许定位的输出流子类必须实现。
    virtual bool Seek(int offset, StreamSeekOrigin origin);
};
M2_SMARTER_PTR(FileOutputStream)


}// namespace m2
