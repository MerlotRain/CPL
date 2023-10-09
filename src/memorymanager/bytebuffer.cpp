#include <bytebuffer.h>
#include <mathhelp.h>
#include <stdint.h>

/**
 * @brief m_Buffer对象结构的说明
 * | uint32_t | uint32_t  | unsigned char* |
 * |   size   |   real    | buffer         |
 * m_Buffer由三部分组成
 * 1)size
 *      表示申请的内存大小。
 * 2)real
 *      表示已经使用的内存大小，因为在图像等特殊的内存块中存在'\0'值，但这并不是内存结束的标识，
 *      故需要用real值处理来获取真实的内存大小.
 * 3)buffer
 *      真实的数据块
 *
 * |01100100|00111110|....
 * 表示申请了100字节的内存，使用了62字节内存
 * 当追加的内存超出已申请的内存时，会重新分配内存。
 *
 */

namespace m2 {

static constexpr auto bytebuffer_meta_size = sizeof(uint32_t);
ByteBuffer::ByteBuffer(unsigned int len)
{
    // 预留额外的内存空间
    int nSize = len;
    m_Buffer = (unsigned char *) malloc(bytebuffer_meta_size * 2 + nSize);
    memset(m_Buffer + sizeof(uint32_t), 0, bytebuffer_meta_size + nSize);

    memcpy(m_Buffer, &nSize, sizeof(uint32_t));
}

ByteBuffer::ByteBuffer(unsigned char *buffer)
{
    int nLen = 0;
    while (*buffer != 0)
    {
        nLen++;
        buffer++;
    }
    // 预留额外的内存空间
    int nSize = nLen;
    m_Buffer = (unsigned char *) malloc(bytebuffer_meta_size * 2 + nSize);
    // 初始化内存
    memset(m_Buffer, 0, bytebuffer_meta_size * 2 + nSize);

    memcpy(m_Buffer, &nSize, bytebuffer_meta_size);
    memcpy(m_Buffer + bytebuffer_meta_size, &nLen, bytebuffer_meta_size);
    memcpy(m_Buffer + bytebuffer_meta_size * 2, buffer, nLen);
}

ByteBuffer::ByteBuffer(unsigned char *buffer, int len)
{
    // 预留额外的空间
    int nSize = Math::NextPowerOfTwo(len);
    m_Buffer = (unsigned char *) malloc(bytebuffer_meta_size * 2 + nSize);
    // 初始化内存
    memset(m_Buffer, 0, bytebuffer_meta_size * 2 + nSize);

    memcpy(m_Buffer, &nSize, bytebuffer_meta_size);
    memcpy(m_Buffer + bytebuffer_meta_size, &len, bytebuffer_meta_size);
    memcpy(m_Buffer + bytebuffer_meta_size * 2, buffer, len);
}

ByteBuffer::ByteBuffer(const char *str)
{
    int nLen = 0;
    while (*str != 0)
    {
        nLen++;
        str++;
    }
    int nSize = nLen;
    m_Buffer = (unsigned char *) malloc(bytebuffer_meta_size * 2 + nSize);
    // 初始化内存
    memset(m_Buffer, 0, bytebuffer_meta_size * 2 + nSize);

    memcpy(m_Buffer, &nSize, bytebuffer_meta_size);
    memcpy(m_Buffer + bytebuffer_meta_size, &nLen, bytebuffer_meta_size);
    memcpy(m_Buffer + bytebuffer_meta_size * 2, str, nLen);
}

ByteBuffer::ByteBuffer(const ByteBuffer &rhs)
{
    if (nullptr == rhs.m_Buffer)
    {
        return;
    }

    unsigned int nSize = rhs.BufferLength();
    m_Buffer = (unsigned char *) malloc(nSize + bytebuffer_meta_size * 2);
    memcpy(m_Buffer, rhs.m_Buffer, nSize + bytebuffer_meta_size * 2);
}

ByteBuffer::ByteBuffer(ByteBuffer &&rhs)
{
    m_Buffer = std::move(rhs.m_Buffer);
    rhs.m_Buffer = nullptr;
}

ByteBuffer::~ByteBuffer() { free(m_Buffer); }

void ByteBuffer::Attach(unsigned char *buffer) {}

unsigned char *ByteBuffer::Detach() { return nullptr; }

ByteBuffer::operator unsigned char *() const
{
    return m_Buffer + bytebuffer_meta_size * 2;
}

ByteBuffer::operator char *() const
{
    return reinterpret_cast<char *>(m_Buffer + bytebuffer_meta_size * 2);
}

ByteBuffer::operator int *() const
{
    return reinterpret_cast<int *>(m_Buffer + bytebuffer_meta_size * 2);
}

ByteBuffer::operator unsigned int *() const
{
    return reinterpret_cast<unsigned int *>(m_Buffer + bytebuffer_meta_size * 2);
}

ByteBuffer::operator short *() const
{
    return reinterpret_cast<short *>(m_Buffer + bytebuffer_meta_size * 2);
}

ByteBuffer::operator unsigned short *() const
{
    return reinterpret_cast<unsigned short *>(m_Buffer +
                                              bytebuffer_meta_size * 2);
}

ByteBuffer::operator long long *() const
{
    return reinterpret_cast<long long *>(m_Buffer + bytebuffer_meta_size * 2);
}

ByteBuffer::operator unsigned long long *() const
{
    return reinterpret_cast<unsigned long long *>(m_Buffer +
                                                  bytebuffer_meta_size * 2);
}

ByteBuffer::operator double *() const
{
    return reinterpret_cast<double *>(m_Buffer + bytebuffer_meta_size * 2);
}

ByteBuffer::operator float *() const
{
    return reinterpret_cast<float *>(m_Buffer + bytebuffer_meta_size * 2);
}

ByteBuffer::operator bool *() const
{
    return reinterpret_cast<bool *>(m_Buffer + bytebuffer_meta_size * 2);
}

unsigned char *ByteBuffer::Ptr() const
{
    return m_Buffer + bytebuffer_meta_size * 2;
}

unsigned char *ByteBuffer::EndPtr() const { return Ptr() + BufferSize(); }

unsigned char *ByteBuffer::BufferHead() const
{
    return m_Buffer + bytebuffer_meta_size * 2;
}

unsigned int ByteBuffer::BufferSize() const
{
    unsigned int size = reinterpret_cast<unsigned int>(m_Buffer);
    return size;
}

unsigned int ByteBuffer::BufferLength() const
{
    unsigned int length = (unsigned int) (m_Buffer + bytebuffer_meta_size);
    return length;
}

unsigned char *ByteBuffer::SetBufferValue(int nValue)
{
    unsigned int size = BufferSize();
    memset(m_Buffer + bytebuffer_meta_size * 2, nValue, size);
    return nullptr;
}

unsigned char *ByteBuffer::Append(const unsigned char *pBuff, int nLen)
{
    unsigned int nSize = BufferSize();
    unsigned int nLength = BufferLength();
    if (nSize + nLen > nLength)
    {
        // 内存无法容纳，直接分配新内存
        unsigned int newLength = nSize + nLen;
        newLength = Math::NextPowerOfTwo(newLength);
        m_Buffer = (unsigned char *) realloc(m_Buffer,
                                             newLength + bytebuffer_meta_size * 2);
        memset(this->EndPtr(), 0, newLength - nLen);
    }
    else
    {
        memcpy(this->EndPtr(), pBuff, nLen);
    }
    return this->Ptr();
}

unsigned char *ByteBuffer::Append(const char *pStr)
{
    unsigned int nLen = 0;
    while (*pStr != 0)
    {
        nLen++;
        pStr++;
    }

    return nullptr;
}

unsigned char *ByteBuffer::Insert(unsigned int nPos,
                                    const unsigned char *pStr, int nLen)
{
    unsigned int size = BufferSize();
    unsigned int length = BufferLength();
    if (length + nLen > size)
    {
        unsigned int newLength = length + nLen;
        unsigned char *newBuffer = (unsigned char *) realloc(
                m_Buffer, newLength + bytebuffer_meta_size * 2);
        memset(newBuffer, 0, newLength + bytebuffer_meta_size * 2);
        memcpy(newBuffer, m_Buffer, size + bytebuffer_meta_size * 2);
        free(m_Buffer);
        m_Buffer = newBuffer;
    }

    if (nPos >= length)
    {
        memcpy(BufferHead() + nPos, pStr, nLen);
    }
    else
    {
        // 原内存被截断，后面部分往后移动
        memmove(BufferHead() + nPos + nLen, BufferHead(), length - nPos);
        memcpy(BufferHead() + nPos, pStr, nLen);
    }

    return BufferHead();
}

unsigned char *ByteBuffer::Allocate(unsigned int nLen)
{
    unsigned length = BufferLength();
    if (length < nLen)
    {
        m_Buffer = (unsigned char *) malloc(nLen + bytebuffer_meta_size * 2);
        memset(m_Buffer, 0, nLen + bytebuffer_meta_size * 2);
        memcpy(m_Buffer, &nLen, sizeof(unsigned int));
    }
    return m_Buffer;
}

void ByteBuffer::Clear() { memset(BufferHead(), 0, BufferLength()); }

void ByteBuffer::Reset() { free(m_Buffer); }

unsigned char *ByteBuffer::Copy(const unsigned char *pBuff, int nLen)
{
    int length = BufferLength();
    if (nLen > length)
    {
        Allocate(nLen);
    }
    memcpy(BufferHead(), pBuff, nLen);
    return BufferHead();
}

ByteBuffer ByteBuffer::ReadSize(int nLen)
{
    ByteBuffer buf(nLen);
    memcpy(buf.BufferHead(), this->BufferHead(),
           nLen < this->BufferLength() ? nLen : this->BufferLength());
    return buf;
}

void ByteBuffer::Resize(int nLen)
{
    if (BufferLength() >= nLen)
    {
    }
    else
    {
    }
}

ByteBuffer *ByteBuffer::Swap(ByteBuffer &rhs)
{
    std::swap(m_Buffer, rhs.m_Buffer);
    return this;
}

ByteBuffer *ByteBuffer::Swap(unsigned char *pBuff)
{
    unsigned int nLen = 0;
    while (*pBuff != 0)
    {
        nLen++;
        pBuff++;
    }

    if (nLen > BufferSize())
    {
        Allocate(nLen);
        memcpy(BufferHead(), pBuff, nLen);
    }
    else
    {
        memcpy(BufferHead(), pBuff, nLen);
        memcpy(m_Buffer + bytebuffer_meta_size, &nLen, sizeof(unsigned int));
    }
    return this;
}

bool ByteBuffer::IsEmpty() const { return this->BufferSize() == 0; }

ByteBuffer &ByteBuffer::operator=(const ByteBuffer &rsh)
{
    free(m_Buffer);
    m_Buffer = (unsigned char *) malloc(rsh.BufferLength());
    memcpy(m_Buffer, rsh.m_Buffer, rsh.BufferLength());
    return *this;
}

ByteBuffer &ByteBuffer::operator=(ByteBuffer &&rsh)
{
    free(m_Buffer);
    m_Buffer = std::move(rsh.m_Buffer);
    rsh.m_Buffer = nullptr;
    return *this;
}

String ByteBuffer::ToBase64() const { return String(); }

bool ByteBuffer::FromBase64(const char *strBase64) { return false; }

bool ByteBuffer::IsBase64(const char *strBase64) { return false; }

}// namespace m2
