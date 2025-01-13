/**
 * CPL - Common Portability Library
 *
 * Copyright (C) 2024 Merlot.Rain
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <cpl_memorymanager.h>

namespace CPL {

ByteBuffer::ByteBuffer()
{
    // Constructor implementation if necessary
}

ByteBuffer::~ByteBuffer()
{
    // Destructor implementation if necessary
}

ByteBuffer::operator unsigned char *() const { return Ptr(); }

ByteBuffer::operator char *() const { return reinterpret_cast<char *>(Ptr()); }

ByteBuffer::operator int *() const { return reinterpret_cast<int *>(Ptr()); }

ByteBuffer::operator unsigned int *() const
{
    return reinterpret_cast<unsigned int *>(Ptr());
}

ByteBuffer::operator short *() const
{
    return reinterpret_cast<short *>(Ptr());
}

ByteBuffer::operator unsigned short *() const
{
    return reinterpret_cast<unsigned short *>(Ptr());
}

ByteBuffer::operator long long *() const
{
    return reinterpret_cast<long long *>(Ptr());
}

ByteBuffer::operator unsigned long long *() const
{
    return reinterpret_cast<unsigned long long *>(Ptr());
}

ByteBuffer::operator double *() const
{
    return reinterpret_cast<double *>(Ptr());
}

ByteBuffer::operator float *() const
{
    return reinterpret_cast<float *>(Ptr());
}

ByteBuffer::operator bool *() const { return reinterpret_cast<bool *>(Ptr()); }

unsigned char *ByteBuffer::EndPtr() const { return Ptr() + BufferSize(); }

std::string ByteBuffer::ToBase64() const
{
    static const char encode_table[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::ostringstream oss;

    unsigned char *data = Ptr();
    unsigned int size = BufferSize();
    int padding = (3 - size % 3) % 3;// Calculate the padding needed
    size_t length = size + padding;

    // Process the buffer in chunks of 3 bytes
    for (size_t i = 0; i < length; i += 3)
    {
        unsigned char b0 = i < size ? data[i] : 0;
        unsigned char b1 = i + 1 < size ? data[i + 1] : 0;
        unsigned char b2 = i + 2 < size ? data[i + 2] : 0;

        oss.put(encode_table[(b0 >> 2) & 0x3F]);
        oss.put(encode_table[((b0 << 4) | (b1 >> 4)) & 0x3F]);
        oss.put(encode_table[((b1 << 2) | (b2 >> 6)) & 0x3F]);
        oss.put(encode_table[b2 & 0x3F]);
    }

    // Add padding if needed
    for (int i = 0; i < padding; ++i) { oss.put('='); }

    return oss.str();
}

bool ByteBuffer::FromBase64(const char *strBase64)
{
    static const unsigned char decode_table[256] = {
            // Initialize the decode table with values for each Base64 character
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    size_t length = strlen(strBase64);
    size_t padding = 0;

    // Count the number of padding characters
    if (length > 0 && strBase64[length - 1] == '=')
    {
        padding++;
        if (strBase64[length - 2] == '=') { padding++; }
    }

    // Calculate the size of the decoded buffer
    size_t decoded_size = (length * 3) / 4 - padding;
    unsigned char *decoded_buffer = Allocate(decoded_size);

    size_t idx = 0;
    for (size_t i = 0; i < length; i += 4)
    {
        unsigned char c0 = decode_table[(unsigned char) strBase64[i]];
        unsigned char c1 = decode_table[(unsigned char) strBase64[i + 1]];
        unsigned char c2 = decode_table[(unsigned char) strBase64[i + 2]];
        unsigned char c3 = decode_table[(unsigned char) strBase64[i + 3]];

        if (c0 == 0xFF || c1 == 0xFF || c2 == 0xFF || c3 == 0xFF)
        {
            return false;
        }

        decoded_buffer[idx++] = (c0 << 2) | (c1 >> 4);
        if (idx < decoded_size)
        {
            decoded_buffer[idx++] = (c1 << 4) | (c2 >> 2);
        }
        if (idx < decoded_size) { decoded_buffer[idx++] = (c2 << 6) | c3; }
    }

    return true;
}

bool ByteBuffer::IsBase64(const char *strBase64)
{
    size_t length = strlen(strBase64);

    // Base64 strings must be a multiple of 4
    if (length % 4 != 0) { return false; }

    // Ensure all characters are Base64 characters or padding
    for (size_t i = 0; i < length; ++i)
    {
        if (!isalnum(strBase64[i]) && strBase64[i] != '+' &&
            strBase64[i] != '/' && strBase64[i] != '=')
        {
            return false;
        }
    }

    return true;
}

unsigned char *ByteBuffer::Append(const std::string &str)
{
    return Append(reinterpret_cast<const unsigned char *>(str.c_str()),
                  str.size());
}

unsigned char *ByteBuffer::SetBufferValue(int nValue)
{
    unsigned char *pHead = Ptr();
    unsigned char *pEnd = EndPtr();
    for (; pHead < pEnd; ++pHead)
    {
        *pHead = static_cast<unsigned char>(nValue);
    }
    return Ptr();
}


GrowByteBuffer::GrowByteBuffer(int nLen)
{
    m_pBuffer = new unsigned char[nLen + sizeof(*m_pMeta)];
    m_pMeta = reinterpret_cast<decltype(m_pMeta)>(m_pBuffer);
    m_pMeta->Real = 0;
    m_pMeta->Size = nLen;
}

GrowByteBuffer::GrowByteBuffer(unsigned char *pBuffer) { m_pBuffer = pBuffer; }

GrowByteBuffer::GrowByteBuffer(const unsigned char *pBuffer, int nLen)
{
    m_pBuffer = new unsigned char[nLen + sizeof(*m_pMeta)];
    m_pMeta = reinterpret_cast<decltype(m_pMeta)>(m_pBuffer);
    m_pMeta->Real = nLen;
    m_pMeta->Size = nLen;
    std::memcpy(m_pBuffer + sizeof(*m_pMeta), pBuffer, nLen);
}

GrowByteBuffer::GrowByteBuffer(const GrowByteBuffer &rhs)
{
    m_pBuffer = new unsigned char[rhs.BufferSize() + sizeof(*m_pMeta)];
    m_pMeta = reinterpret_cast<decltype(m_pMeta)>(m_pBuffer);
    m_pMeta->Real = rhs.m_pMeta->Real;
    m_pMeta->Size = rhs.m_pMeta->Size;
    std::memcpy(m_pBuffer + sizeof(*m_pMeta), rhs.m_pBuffer + sizeof(*m_pMeta),
                rhs.m_pMeta->Real);
}

GrowByteBuffer::GrowByteBuffer(GrowByteBuffer &&rhs) noexcept
{
    m_pBuffer = rhs.m_pBuffer;
    rhs.m_pBuffer = nullptr;
}

GrowByteBuffer::~GrowByteBuffer()
{
    if (m_pBuffer) { delete[] m_pBuffer; }
}

void GrowByteBuffer::Attach(unsigned char *pBuffer)
{
    if (m_pBuffer) { delete[] m_pBuffer; }
    m_pBuffer = pBuffer;
}

unsigned char *GrowByteBuffer::Detach()
{
    unsigned char *tmp = m_pBuffer;
    m_pBuffer = nullptr;
    return tmp;
}

GrowByteBuffer::operator unsigned char *() const { return Ptr(); }

unsigned char *GrowByteBuffer::Ptr() const
{
    return m_pBuffer + sizeof(*m_pMeta);
}

unsigned char *GrowByteBuffer::BufferHead() const { return m_pBuffer; }

unsigned int GrowByteBuffer::BufferSize() const { return m_pMeta->Size; }

unsigned int GrowByteBuffer::RealSize() const { return m_pMeta->Real; }

unsigned char *GrowByteBuffer::SetBufferValue(int nValue)
{
    unsigned char *pHead = Ptr();
    unsigned char *pEnd = pHead + RealSize();
    for (; pHead < pEnd; ++pHead)
    {
        *pHead = static_cast<unsigned char>(nValue);
    }
    return Ptr();
}

unsigned char *GrowByteBuffer::Append(const unsigned char *pBuff, int nLen)
{
    if (m_pMeta->Real + nLen > m_pMeta->Size)
    {
        unsigned int newSize = (m_pMeta->Real + nLen) * 2;
        unsigned char *newBuffer =
                new unsigned char[newSize + sizeof(*m_pMeta)];
        std::memcpy(newBuffer, m_pBuffer, sizeof(*m_pMeta) + m_pMeta->Real);
        delete[] m_pBuffer;
        m_pBuffer = newBuffer;
        m_pMeta = reinterpret_cast<decltype(m_pMeta)>(m_pBuffer);
        m_pMeta->Size = newSize;
    }
    std::memcpy(Ptr() + m_pMeta->Real, pBuff, nLen);
    m_pMeta->Real += nLen;
    return Ptr();
}

unsigned char *GrowByteBuffer::Append(const char *pStr)
{
    return Append(reinterpret_cast<const unsigned char *>(pStr),
                  std::strlen(pStr));
}

unsigned char *GrowByteBuffer::Insert(unsigned int nPos,
                                      const unsigned char *pStr, int nLen)
{
    if (nPos > m_pMeta->Real) { return nullptr; }
    if (m_pMeta->Real + nLen > m_pMeta->Size)
    {
        unsigned int newSize = (m_pMeta->Real + nLen) * 2;
        unsigned char *newBuffer =
                new unsigned char[newSize + sizeof(*m_pMeta)];
        std::memcpy(newBuffer, m_pBuffer, sizeof(*m_pMeta) + nPos);
        std::memcpy(newBuffer + sizeof(*m_pMeta) + nPos + nLen, Ptr() + nPos,
                    m_pMeta->Real - nPos);
        delete[] m_pBuffer;
        m_pBuffer = newBuffer;
        m_pMeta = reinterpret_cast<decltype(m_pMeta)>(m_pBuffer);
        m_pMeta->Size = newSize;
    }
    else
    {
        std::memmove(Ptr() + nPos + nLen, Ptr() + nPos, m_pMeta->Real - nPos);
    }
    std::memcpy(Ptr() + nPos, pStr, nLen);
    m_pMeta->Real += nLen;
    return Ptr();
}

unsigned char *GrowByteBuffer::Allocate(unsigned int nLen)
{
    if (nLen > m_pMeta->Size)
    {
        unsigned int newSize = nLen * 2;
        unsigned char *newBuffer =
                new unsigned char[newSize + sizeof(*m_pMeta)];
        std::memcpy(newBuffer, m_pBuffer, sizeof(*m_pMeta) + m_pMeta->Real);
        delete[] m_pBuffer;
        m_pBuffer = newBuffer;
        m_pMeta = reinterpret_cast<decltype(m_pMeta)>(m_pBuffer);
        m_pMeta->Size = newSize;
    }
    m_pMeta->Real = nLen;
    return Ptr();
}

void GrowByteBuffer::Clear() { m_pMeta->Real = 0; }

void GrowByteBuffer::Reset()
{
    if (m_pBuffer)
    {
        delete[] m_pBuffer;
        m_pBuffer = nullptr;
    }
}

unsigned char *GrowByteBuffer::Copy(const unsigned char *pBuff, int nLen)
{
    Allocate(nLen);
    std::memcpy(Ptr(), pBuff, nLen);
    m_pMeta->Real = nLen;
    return Ptr();
}

GrowByteBuffer *GrowByteBuffer::Swap(GrowByteBuffer &rhs)
{
    std::swap(m_pBuffer, rhs.m_pBuffer);
    return this;
}

GrowByteBuffer *GrowByteBuffer::Swap(unsigned char *pBuff)
{
    std::swap(m_pBuffer, pBuff);
    return this;
}

GrowByteBuffer &GrowByteBuffer::operator=(const GrowByteBuffer &rhs)
{
    if (this != &rhs)
    {
        if (m_pBuffer) { delete[] m_pBuffer; }
        m_pBuffer = new unsigned char[rhs.BufferSize() + sizeof(*m_pMeta)];
        m_pMeta = reinterpret_cast<decltype(m_pMeta)>(m_pBuffer);
        m_pMeta->Real = rhs.m_pMeta->Real;
        m_pMeta->Size = rhs.m_pMeta->Size;
        std::memcpy(m_pBuffer + sizeof(*m_pMeta),
                    rhs.m_pBuffer + sizeof(*m_pMeta), rhs.m_pMeta->Real);
    }
    return *this;
}

GrowByteBuffer &GrowByteBuffer::operator=(GrowByteBuffer &&rhs) noexcept
{
    if (this != &rhs)
    {
        if (m_pBuffer) { delete[] m_pBuffer; }
        m_pBuffer = rhs.m_pBuffer;
        rhs.m_pBuffer = nullptr;
    }
    return *this;
}


InputStream::~InputStream() {}

InputStream::InputStream() : m_nCapability(0) {}

bool InputStream::TestCapability(GsCapability cap)
{
    return m_nCapability & (1ULL << static_cast<int>(cap));
}

void InputStream::MarkCapability(GsCapability cap)
{
    m_nCapability |= (1ULL << static_cast<int>(cap));
}

int InputStream::Skip(int nLen)
{
    return Seek(nLen, StreamSeekOrigin::eCurrent) ? nLen : 0;
}

int InputStream::RawRead(unsigned char *buff, int nLen)
{
    const unsigned char *pointer = nullptr;
    return RawRead(buff, nLen, &pointer);
}

int InputStream::RawRead(unsigned char *buff, int nLen,
                         const unsigned char **pointer)
{
    if (buff == nullptr && pointer != nullptr)
    {
        // Derived classes with zero-copy capability should  this.
        return 0;
    }
    if (buff != nullptr)
    {
        // Fallback implementation for non-zero-copy classes.
        return 0;
    }
    return 0;
}

long long InputStream::Length() const
{
    return 0;
    // return TestCapability(GsCapability::eLength) ? 0 : -1;
}

bool InputStream::Seek(int offset, StreamSeekOrigin origin)
{
    if (!TestCapability(GsCapability::eSeek)) { return false; }
    // Derived classes should  this.
    return false;
}

bool InputStream::Eof() const { return Offset() >= Length(); }

std::string InputStream::ReadString(int nLen)
{
    std::string result;
    ReadString(nLen, result);
    return result;
}

int InputStream::ReadString(int nLen, std::string &str)
{
    str.resize(nLen);
    int readLen = RawRead(reinterpret_cast<unsigned char *>(&str[0]), nLen);
    str.resize(readLen);
    return readLen;
}

std::string InputStream::ReadLine()
{
    std::string result;
    ReadLine(result);
    return result;
}

bool InputStream::ReadLine(std::string &line)
{
    line.clear();
    char ch;
    while (!Eof())
    {
        ch = ReadInt8();
        if (ch == '\n') { break; }
        line += ch;
    }
    return !line.empty();
}

char InputStream::ReadInt8()
{
    char value;
    ReadT(value);
    return value;
}

unsigned char InputStream::ReadUInt8()
{
    unsigned char value;
    ReadT(value);
    return value;
}

short InputStream::ReadInt16()
{
    short value;
    ReadT(value);
    return value;
}

unsigned short InputStream::ReadUInt16()
{
    unsigned short value;
    ReadT(value);
    return value;
}

int InputStream::ReadInt32()
{
    int value;
    ReadT(value);
    return value;
}

unsigned int InputStream::ReadUInt32()
{
    unsigned int value;
    ReadT(value);
    return value;
}

long long InputStream::ReadInt64()
{
    long long value;
    ReadT(value);
    return value;
}

unsigned long long InputStream::ReadUInt64()
{
    unsigned long long value;
    ReadT(value);
    return value;
}

float InputStream::ReadFloat32()
{
    float value;
    ReadT(value);
    return value;
}

double InputStream::ReadFloat64()
{
    double value;
    ReadT(value);
    return value;
}


MemoryInputStream::MemoryInputStream() { Init(); }

void MemoryInputStream::Init()
{
    m_Head = nullptr;
    m_nOffset = 0;
    m_nLength = 0;
    MarkCapability(GsCapability::eLength);
    MarkCapability(GsCapability::eSeek);
}

MemoryInputStream::MemoryInputStream(const unsigned char *buffer, int nLen,
                                     bool bCopy)
{
    Init();
    if (bCopy)
    {
        m_Buffer.Copy(buffer, nLen);
        m_Head = m_Buffer.Ptr();
    }
    else { m_Head = buffer; }
    m_nLength = nLen;
}

MemoryInputStream::MemoryInputStream(ByteBuffer *buffer, bool bCopy)
{
    Init();
    if (!buffer) { throw std::invalid_argument("buffer cannot be null"); }
    if (bCopy)
    {
        m_Buffer.Copy(buffer->Ptr(), buffer->BufferSize());
        m_Head = m_Buffer.Ptr();
    }
    else { m_Head = buffer->Ptr(); }
    m_nLength = buffer->BufferSize();
}

MemoryInputStream::MemoryInputStream(const char *str, bool bCopy)
    : MemoryInputStream(reinterpret_cast<const unsigned char *>(str),
                        std::strlen(str), bCopy)
{
}

MemoryInputStream::MemoryInputStream(const std::string &str, bool bCopy)
    : MemoryInputStream(reinterpret_cast<const unsigned char *>(str.data()),
                        str.size(), bCopy)
{
}

int MemoryInputStream::RawRead(unsigned char *buff, int nLen,
                               const unsigned char **pointer)
{
    if (m_nOffset >= m_nLength)
    {
        return 0;// End of stream
    }
    int remaining = static_cast<int>(m_nLength - m_nOffset);
    int toRead = std::min(nLen, remaining);
    if (pointer && !buff) { *pointer = m_Head + m_nOffset; }
    else if (buff) { std::memcpy(buff, m_Head + m_nOffset, toRead); }
    m_nOffset += toRead;
    return toRead;
}

long long MemoryInputStream::Length() const
{
    return static_cast<long long>(m_nLength);
}

unsigned long long MemoryInputStream::Offset() const { return m_nOffset; }

bool MemoryInputStream::Seek(int offset, StreamSeekOrigin origin)
{
    unsigned long long newOffset = 0;
    switch (origin)
    {
        case StreamSeekOrigin::eSet:
            newOffset = offset;
            break;
        case StreamSeekOrigin::eCurrent:
            newOffset = m_nOffset + offset;
            break;
        case StreamSeekOrigin::eEnd:
            newOffset = m_nLength + offset;
            break;
        default:
            return false;
    }
    if (newOffset > m_nLength)
    {
        return false;// Out of bounds
    }
    m_nOffset = newOffset;
    return true;
}

bool MemoryInputStream::Close()
{
    m_Head = nullptr;
    m_nOffset = 0;
    m_nLength = 0;
    m_Buffer.Reset();
    return true;
}


void FileInputStream::Init()
{
    if (m_pFile)
    {
        std::fseek(m_pFile, 0, SEEK_END);
        m_nLength = std::ftell(m_pFile);
        std::fseek(m_pFile, 0, SEEK_SET);
        MarkCapability(GsCapability::eLength);
        MarkCapability(GsCapability::eSeek);
    }
}

FileInputStream::FileInputStream(const char *file, bool bBin)
{
    const char *mode = bBin ? "rb" : "r";
    m_pFile = std::fopen(file, mode);
    if (!m_pFile) { throw std::runtime_error("Failed to open file"); }
    Init();
}

FileInputStream::FileInputStream(FILE *file, unsigned long long nLen,
                                 bool bCloseFile)
    : m_pFile(file), m_nLength(nLen), m_bCloseFile(bCloseFile)
{
    if (!m_pFile) { throw std::invalid_argument("file cannot be null"); }
    MarkCapability(GsCapability::eLength);
    MarkCapability(GsCapability::eSeek);
}

FileInputStream::~FileInputStream()
{
    if (m_pFile && m_bCloseFile) { std::fclose(m_pFile); }
}

bool FileInputStream::ReadLine(std::string &line)
{
    line.clear();
    char ch;
    while (!Eof())
    {
        if (std::fread(&ch, 1, 1, m_pFile) != 1) { break; }
        if (ch == '\n') { break; }
        line += ch;
    }
    return !line.empty();
}

int FileInputStream::RawRead(unsigned char *buff, int nLen)
{
    if (!m_pFile || !buff) { return 0; }
    return static_cast<int>(std::fread(buff, 1, nLen, m_pFile));
}

long long FileInputStream::Length() const { return m_nLength; }

unsigned long long FileInputStream::Offset() const
{
    if (!m_pFile) { return 0; }
    return static_cast<unsigned long long>(std::ftell(m_pFile));
}

bool FileInputStream::Seek(int offset, StreamSeekOrigin origin)
{
    if (!m_pFile) { return false; }
    int whence;
    switch (origin)
    {
        case StreamSeekOrigin::eSet:
            whence = SEEK_SET;
            break;
        case StreamSeekOrigin::eCurrent:
            whence = SEEK_CUR;
            break;
        case StreamSeekOrigin::eEnd:
            whence = SEEK_END;
            break;
        default:
            return false;
    }
    return std::fseek(m_pFile, offset, whence) == 0;
}


OutputStream::OutputStream() : m_nCapability(0) {}

OutputStream::~OutputStream() {}

void OutputStream::MarkCapability(GsCapability cap)
{
    m_nCapability |= (1ULL << static_cast<int>(cap));
}

bool OutputStream::TestCapability(GsCapability cap)
{
    return m_nCapability & (1ULL << static_cast<int>(cap));
}

bool OutputStream::Seek(int offset, StreamSeekOrigin origin)
{
    if (!TestCapability(GsCapability::eSeek)) { return false; }
    // Derived classes should  this.
    return false;
}

bool OutputStream::Flush()
{
    // Derived classes can implement flushing if needed.
    return true;
}

bool OutputStream::Close()
{
    // Derived classes can implement closing if needed.
    return true;
}

int OutputStream::WriteString(const char *str, int nLen)
{
    if (nLen < 0) { nLen = std::strlen(str); }
    return RawWrite(reinterpret_cast<const unsigned char *>(str), nLen);
}

int OutputStream::WriteString(const std::string &str)
{
    return WriteString(str.c_str(), static_cast<int>(str.size()));
}

int OutputStream::WriteBuffer(const ByteBuffer *buff)
{
    if (!buff) { return 0; }
    return RawWrite(buff->BufferHead(), static_cast<int>(buff->BufferSize()));
}


MemoryOutputStream::MemoryOutputStream()
{
    m_pByteBufferOutput = &m_InnerBuffer;
}

MemoryOutputStream::MemoryOutputStream(std::stringstream &str)
    : m_pStringStream(&str)
{
}

MemoryOutputStream::MemoryOutputStream(std::string &str) : m_pStringOutput(&str)
{
}

MemoryOutputStream::MemoryOutputStream(std::vector<unsigned char> &vec)
    : m_pVectorOutput(&vec)
{
}

MemoryOutputStream::MemoryOutputStream(ByteBuffer *buff)
    : m_pByteBufferOutput(buff)
{
}

MemoryOutputStream::MemoryOutputStream(unsigned char *fixMem,
                                       unsigned long long nLen)
    : m_FixMemoryHead(fixMem), m_FixeMemoryLength(nLen)
{
}

const ByteBuffer *MemoryOutputStream::Buffer() const
{
    return m_pByteBufferOutput;
}

int MemoryOutputStream::RawWrite(const unsigned char *buff, int nLen)
{
    if (m_FixMemoryHead)
    {
        if (m_Offset + nLen > m_FixeMemoryLength)
        {
            nLen = m_FixeMemoryLength - m_Offset;
        }
        std::memcpy(m_FixMemoryHead + m_Offset, buff, nLen);
        m_Offset += nLen;
        return nLen;
    }
    else if (m_pStringOutput)
    {
        m_pStringOutput->append(reinterpret_cast<const char *>(buff), nLen);
        m_Offset += nLen;
        return nLen;
    }
    else if (m_pVectorOutput)
    {
        m_pVectorOutput->insert(m_pVectorOutput->end(), buff, buff + nLen);
        m_Offset += nLen;
        return nLen;
    }
    else if (m_pStringStream)
    {
        m_pStringStream->write(reinterpret_cast<const char *>(buff), nLen);
        m_Offset += nLen;
        return nLen;
    }
    else if (m_pByteBufferOutput)
    {
        m_pByteBufferOutput->Append(buff, nLen);
        m_Offset += nLen;
        return nLen;
    }
    return 0;
}

unsigned long long MemoryOutputStream::Offset() const { return m_Offset; }

bool MemoryOutputStream::Seek(int offset, StreamSeekOrigin origin)
{
    unsigned long long newOffset = m_Offset;
    switch (origin)
    {
        case StreamSeekOrigin::eSet:
            newOffset = offset;
            break;
        case StreamSeekOrigin::eCurrent:
            newOffset += offset;
            break;
        case StreamSeekOrigin::eEnd:
            if (m_FixMemoryHead) { newOffset = m_FixeMemoryLength + offset; }
            else if (m_pByteBufferOutput)
            {
                newOffset = m_pByteBufferOutput->BufferSize() + offset;
            }
            else { return false; }
            break;
    }

    if (m_FixMemoryHead)
    {
        if (newOffset > m_FixeMemoryLength) { return false; }
    }

    m_Offset = newOffset;
    return true;
}


FileOutputStream::FileOutputStream(const char *path, bool bBinary,
                                   bool bAppend)
    : m_Start(0), m_bCloseOnEnd(true)
{
    const char *mode =
            bBinary ? (bAppend ? "ab" : "wb") : (bAppend ? "a" : "w");
    m_pFile = std::fopen(path, mode);
    if (!m_pFile)
    {
        throw std::runtime_error("Failed to open file: " + std::string(path));
    }
}

FileOutputStream::FileOutputStream(FILE *f, bool bCloseOnEnd)
    : m_pFile(f), m_bCloseOnEnd(bCloseOnEnd), m_Start(0)
{
    if (!m_pFile)
    {
        throw std::invalid_argument("File pointer cannot be null");
    }
}

FileOutputStream::~FileOutputStream()
{
    if (m_bCloseOnEnd && m_pFile) { std::fclose(m_pFile); }
}

int FileOutputStream::RawWrite(const unsigned char *buff, int nLen)
{
    if (!m_pFile) { throw std::runtime_error("File not open"); }
    return static_cast<int>(std::fwrite(buff, 1, nLen, m_pFile));
}

unsigned long long FileOutputStream::Offset() const
{
    if (!m_pFile) { throw std::runtime_error("File not open"); }
    long long offset = std::ftell(m_pFile);
    if (offset == -1L)
    {
        throw std::runtime_error("Failed to get file offset");
    }
    return static_cast<unsigned long long>(offset);
}

bool FileOutputStream::Seek(int offset, StreamSeekOrigin origin)
{
    if (!m_pFile) { throw std::runtime_error("File not open"); }

    int whence;
    switch (origin)
    {
        case StreamSeekOrigin::eSet:
            whence = SEEK_SET;
            break;
        case StreamSeekOrigin::eCurrent:
            whence = SEEK_CUR;
            break;
        case StreamSeekOrigin::eEnd:
            whence = SEEK_END;
            break;
        default:
            return false;
    }

    return std::fseek(m_pFile, offset, whence) == 0;
}

}// namespace CPL