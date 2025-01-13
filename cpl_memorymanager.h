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

#pragma once

#include <cpl_exports.h>
#include "cpl_object.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace CPL {

/// \brief Direct memory block class
class CPL_API ByteBuffer
{
protected:
    /// \brief Protected constructor, only accessible by derived classes
    ByteBuffer();

public:
    /// \brief Virtual destructor
    virtual ~ByteBuffer();

    /// \brief Type conversion operator to unsigned char pointer
    virtual operator unsigned char *() const;

    /// \brief Type conversion operator to char pointer
    virtual operator char *() const;

    /// \brief Type conversion operator to int pointer
    virtual operator int *() const;

    /// \brief Type conversion operator to unsigned int pointer
    virtual operator unsigned int *() const;

    /// \brief Type conversion operator to short pointer
    virtual operator short *() const;

    /// \brief Type conversion operator to unsigned short pointer
    virtual operator unsigned short *() const;

    /// \brief Type conversion operator to long long pointer
    virtual operator long long *() const;

    /// \brief Type conversion operator to unsigned long long pointer
    virtual operator unsigned long long *() const;

    /// \brief Type conversion operator to double pointer
    virtual operator double *() const;

    /// \brief Type conversion operator to float pointer
    virtual operator float *() const;

    /// \brief Type conversion operator to boolean pointer
    virtual operator bool *() const;

    /// \brief Pointer to the start of the buffer, equivalent to BufferHead()
    /// \return Pointer to the beginning of the buffer
    virtual unsigned char *Ptr() const = 0;

    /// \brief Pointer to the end of the buffer
    /// \details Addresses >= this pointer are out of bounds
    /// \return Pointer to the end of the buffer
    virtual unsigned char *EndPtr() const;

    /// \brief Template function to cast the buffer pointer to a specific type
    /// \tparam T The type to cast the buffer pointer to
    /// \return Pointer to the start of the buffer as type T
    template<typename T>
    T *PtrT() const
    {
        return (T *) (Ptr());
    }

    /// \brief Template function to cast the buffer end pointer to a specific type
    /// \tparam T The type to cast the buffer end pointer to
    /// \return Pointer to the end of the buffer as type T
    template<typename T>
    T *EndPtrT() const
    {
        return (T *) (EndPtr());
    }

    /// \brief Pointer to the start of the buffer
    /// \return Pointer to the beginning of the buffer
    virtual unsigned char *BufferHead() const = 0;

    /// \brief Size of the buffer in bytes
    /// \return The buffer size
    virtual unsigned int BufferSize() const = 0;

    /// \brief Number of elements in the buffer based on a specific type
    /// \tparam T The type of the elements
    /// \return The number of elements of type T
    template<typename T>
    unsigned int BufferSizeT() const
    {
        return BufferSize() / sizeof(T);
    }

    /// \brief Set all bytes in the buffer to a specific value
    /// \details Similar to memset
    /// \param nValue The value to set
    /// \return Pointer to the start of the buffer
    virtual unsigned char *SetBufferValue(int nValue) = 0;

    /// \brief Set the buffer with a specific value of a given type
    /// \tparam T The type of the value
    /// \param val The value to set
    /// \return Pointer to the start of the buffer as type T
    template<typename T>
    T *SetBufferValueT(const T &val)
    {
        const unsigned char *pByte = (const unsigned char *) &val;
        bool bIsEqual = true;
        for (int i = 1; i < sizeof(val); i++)
        {
            if (pByte[i] != pByte[0])
            {
                bIsEqual = false;
                break;
            }
        }
        if (bIsEqual) return (T *) SetBufferValue(pByte[0]);
        T *pHead = PtrT<T>();
        T *pEnd = EndPtrT<T>();
        for (; pHead < pEnd; pHead++) { pHead[0] = val; }
        return PtrT<T>();
    }

    /// \brief Append data to the end of the buffer
    /// \param pBuff Pointer to the data
    /// \param nLen Length of the data in bytes
    /// \return Pointer to the start of the buffer
    virtual unsigned char *Append(const unsigned char *pBuff, int nLen) = 0;

    /// \brief Append a string to the end of the buffer
    /// \param pStr Pointer to the string
    /// \return Pointer to the start of the buffer
    virtual unsigned char *Append(const char *pStr) = 0;

    /// \brief Append an array of a specific type to the buffer
    /// \tparam T The type of the array elements
    /// \param pBuff Pointer to the array
    /// \param nLen Length of the array
    /// \return Pointer to the start of the buffer
    template<typename T>
    unsigned char *AppendT(const T *pBuff, int nLen)
    {
        return Append((const unsigned char *) pBuff, nLen * sizeof(T));
    }

    /// \brief Append a single element of a specific type to the buffer
    /// \tparam T The type of the element
    /// \param pBuff Reference to the element
    /// \return Pointer to the start of the buffer
    template<typename T>
    unsigned char *AppendT(const T &pBuff)
    {
        return Append((const unsigned char *) &pBuff, sizeof(T));
    }

    /// \brief Insert data at a specific position in the buffer
    /// \param nPos Position to insert the data
    /// \param pStr Pointer to the data
    /// \param nLen Length of the data in bytes
    /// \return Pointer to the start of the buffer
    virtual unsigned char *Insert(unsigned int nPos, const unsigned char *pStr,
                                  int nLen) = 0;

    /// \brief Allocate memory for the buffer
    /// \param nLen Length of the memory in bytes
    /// \return Pointer to the allocated memory
    virtual unsigned char *Allocate(unsigned int nLen) = 0;

    /// \brief Allocate memory for an array of a specific type
    /// \tparam T The type of the array elements
    /// \param nLen Number of elements
    /// \return Pointer to the allocated memory as type T
    template<typename T>
    T *AllocateT(int nLen)
    {
        Allocate(sizeof(T) * nLen);
        return PtrT<T>();
    }

    /// \brief Clear the buffer data
    virtual void Clear() = 0;

    /// \brief Reset the buffer and release memory
    virtual void Reset() = 0;

    /// \brief Copy a specific length of data to the buffer
    /// \param pBuff Pointer to the data
    /// \param nLen Length of the data in bytes
    /// \return Pointer to the start of the buffer
    virtual unsigned char *Copy(const unsigned char *pBuff, int nLen) = 0;

    /// \brief Convert the binary buffer to a Base64 encoded string
    /// \return The Base64 encoded string
    std::string ToBase64() const;

    /// \brief Decode a Base64 string into the buffer
    /// \param strBase64 The Base64 string
    /// \return True if successful, false otherwise
    bool FromBase64(const char *strBase64);

    /// \brief Check if a string is a valid Base64 encoded string
    /// \param strBase64 The string to check
    /// \return True if the string is Base64, false otherwise
    static bool IsBase64(const char *strBase64);

    /// \brief Append a string to the buffer
    /// \param str The string to append
    /// \return Pointer to the start of the buffer
    virtual unsigned char *Append(const std::string &str);
};

/// \brief Growing direct memory block, memory only increases and does not shrink
class CPL_API GrowByteBuffer : public ByteBuffer
{
    /// \brief Union to manage memory metadata
    union
    {
        unsigned char *m_pBuffer;///< Pointer to the memory buffer
        /// \brief Struct for managing real size and allocated size
        struct
        {
            unsigned int Real;///< Actual size of the buffer in bytes
            unsigned int Size;///< Allocated size of the buffer in bytes
        } *m_pMeta;
    };

public:
    /// \brief Constructor with optional initial buffer size
    /// \param nLen Initial buffer size in bytes (default is 0)
    GrowByteBuffer(int nLen = 0);

    /// \brief Constructor that attaches an existing buffer
    /// \param pBuffer Pointer to the external buffer
    GrowByteBuffer(unsigned char *pBuffer);

    /// \brief Constructor that copies data from an external buffer
    /// \param pBuffer Pointer to the source buffer
    /// \param nLen Size of the source buffer in bytes
    GrowByteBuffer(const unsigned char *pBuffer, int nLen);

    /// \brief Copy constructor
    /// \param rhs Reference to the source object
    GrowByteBuffer(const GrowByteBuffer &rhs);

    /// \brief Move constructor
    /// \param rhs Rvalue reference to the source object
    GrowByteBuffer(GrowByteBuffer &&rhs) noexcept;

    /// \brief Destructor
    virtual ~GrowByteBuffer();

    /// \brief Attaches an external buffer to the object
    /// \param pBuffer Pointer to the external buffer
    void Attach(unsigned char *pBuffer);

    /// \brief Detaches the internal buffer and returns the pointer
    /// \return Pointer to the detached buffer
    unsigned char *Detach();

    /// \brief Type conversion operator to unsigned char pointer
    virtual operator unsigned char *() const;

    /// \brief Returns a pointer to the start of the buffer
    /// \return Pointer to the buffer
    virtual unsigned char *Ptr() const;

    /// \brief Returns a pointer to the head of the buffer
    /// \return Pointer to the buffer head
    virtual unsigned char *BufferHead() const;

    /// \brief Returns the allocated buffer size
    /// \return Size of the buffer in bytes
    virtual unsigned int BufferSize() const;

    /// \brief Returns the actual size of the buffer used
    /// \return Real size of the buffer in bytes
    virtual unsigned int RealSize() const;

    /// \brief Sets the buffer to a specific integer value
    /// \param nValue Value to set
    /// \return Pointer to the buffer
    virtual unsigned char *SetBufferValue(int nValue);

    /// \brief Appends data to the end of the buffer
    /// \param pBuff Pointer to the data
    /// \param nLen Length of the data in bytes
    /// \return Pointer to the buffer
    virtual unsigned char *Append(const unsigned char *pBuff, int nLen);

    /// \brief Appends a null-terminated string to the buffer
    /// \param pStr Pointer to the string
    /// \return Pointer to the buffer
    virtual unsigned char *Append(const char *pStr);

    /// \brief Inserts data at a specific position in the buffer
    /// \param nPos Position to insert the data
    /// \param pStr Pointer to the data
    /// \param nLen Length of the data in bytes
    /// \return Pointer to the buffer
    virtual unsigned char *Insert(unsigned int nPos, const unsigned char *pStr,
                                  int nLen);

    /// \brief Allocates additional memory for the buffer
    /// \param nLen Size of the memory to allocate in bytes
    /// \return Pointer to the buffer
    virtual unsigned char *Allocate(unsigned int nLen);

    /// \brief Clears the buffer data
    virtual void Clear();

    /// \brief Resets the buffer and releases allocated memory
    virtual void Reset();

    /// \brief Copies data into the buffer
    /// \param pBuff Pointer to the source data
    /// \param nLen Length of the data in bytes
    /// \return Pointer to the buffer
    virtual unsigned char *Copy(const unsigned char *pBuff, int nLen);

    /// \brief Swaps the contents of two buffers
    /// \param rhs Reference to the other buffer
    /// \return Pointer to the current object
    GrowByteBuffer *Swap(GrowByteBuffer &rhs);

    /// \brief Swaps the contents of the buffer with an external buffer
    /// \param pBuff Pointer to the external buffer
    /// \return Pointer to the current object
    GrowByteBuffer *Swap(unsigned char *pBuff);

    /// \brief Assignment operator for copying from another buffer
    /// \param rsh Reference to the source buffer
    /// \return Reference to the current object
    GrowByteBuffer &operator=(const GrowByteBuffer &rsh);

    /// \brief Assignment operator for moving from another buffer
    /// \param rsh Rvalue reference to the source buffer
    /// \return Reference to the current object
    GrowByteBuffer &operator=(GrowByteBuffer &&rsh) noexcept;
};


/// \brief The origin point for stream seeking operations
enum class StreamSeekOrigin : int
{
    /// \brief The beginning of the stream
    eSet,
    /// \brief The current position within the stream
    eCurrent,
    /// \brief The end of the stream
    eEnd,
};

/// \brief Input data stream, derived classes must implement one of the two overloaded RawRead methods
class CPL_API InputStream : public RefObject
{
public:
    /// \brief InputStream capability flags
    enum class GsCapability : int
    {
        /// \brief Supports zero-copy capability
        eZeroCopy = 0,
        /// \brief Can retrieve the length of the stream
        eLength,
        /// \brief Allows seeking
        eSeek,
    };

public:
    virtual ~InputStream();

    /// \brief Tests the capabilities of the input stream
    /// \param cap The capability to test
    /// \return True if the capability is supported, otherwise false
    bool TestCapability(GsCapability cap);

    /// \brief Skips a specified length of data
    /// \param nLen The number of bytes to skip
    /// \return The actual number of bytes skipped
    virtual int Skip(int nLen);

    /// \brief Reads a block of data
    /// \details Reads a block of data with the specified length. Returns the actual length of data read.
    /// Derived classes without zero-copy capability should override this method.
    /// \param buff The buffer to store the read data
    /// \param nLen The number of bytes to read
    /// \return The actual number of bytes read
    virtual int RawRead(unsigned char *buff, int nLen);

    /// \brief Reads a block of data
    /// \details Reads a block of data with the specified length. Returns the actual length of data read.
    /// `pointer` provides the original pointer to the data if available. Derived classes with zero-copy capability should override this method.
    /// \param buff The buffer to store the read data, or nullptr if `pointer` is used
    /// \param nLen The number of bytes to read
    /// \param pointer Pointer to the original data storage (nullptr for file-based streams)
    /// \return The actual number of bytes read
    virtual int RawRead(unsigned char *buff, int nLen,
                        const unsigned char **pointer);

    /// \brief Gets the length of the data stream
    /// \details If the stream does not support the eLength capability, the length is -1.
    /// Derived classes supporting this capability should override this method.
    /// \return The length of the data stream, or -1 if unsupported
    virtual long long Length() const;

    /// \brief Gets the current offset in the input stream
    /// \return The current offset
    virtual unsigned long long Offset() const = 0;

    /// \brief Sets the input stream offset
    /// \param offset The new offset
    /// \param origin The reference point for the offset
    /// \return True if successful, otherwise false
    virtual bool Seek(int offset, StreamSeekOrigin origin);

    /// \brief Checks if the end of the stream has been reached
    /// \return True if at the end of the stream, otherwise false
    virtual bool Eof() const;

    /// \brief Reads a value of a specific type
    template<class T>
    T ReadT()
    {
        int nSize = sizeof(T);
        const unsigned char *pointer = NULL;

        int n = RawRead(NULL, nSize, &pointer);
        if (n == nSize && pointer) return *reinterpret_cast<const T *>(pointer);

        T v;
        unsigned char *tmp = (unsigned char *) &v;
        n = RawRead(tmp, nSize);
        if (n == nSize) return v;
        memset(&v, 0, nSize);
        return v;
    }

    /// \brief Reads a value of a specific type
    template<class T>
    bool ReadT(T &v)
    {
        int nSize = sizeof(T);
        unsigned char *tmp = (unsigned char *) &v;
        const unsigned char *pointer = NULL;
        return RawRead(tmp, nSize, &pointer) == nSize;
    }

    /// \brief Reads a value of a specific type
    template<class T>
    InputStream &operator>>(T &v)
    {
        ReadT(v);
        return *this;
    }

    /// \brief Reads a string of a specified length
    /// \param nLen The length of the string to read
    /// \return The read string
    std::string ReadString(int nLen);

    /// \brief Reads a string of a specified length
    /// \param nLen The length of the string to read
    /// \param str The output string
    /// \return The length of the string actually read
    int ReadString(int nLen, std::string &str);

    /// \brief Reads a single line from the input stream
    /// \return The read line as a string
    std::string ReadLine();

    /// \brief Reads a single line from the input stream
    /// \param line The output string containing the line
    /// \return True if a line is read successfully, otherwise false
    bool ReadLine(std::string &line);

    /// \brief Reads a signed 8-bit integer
    char ReadInt8();

    /// \brief Reads an unsigned 8-bit integer
    unsigned char ReadUInt8();

    /// \brief Reads a signed 16-bit integer
    short ReadInt16();

    /// \brief Reads an unsigned 16-bit integer
    unsigned short ReadUInt16();

    /// \brief Reads a signed 32-bit integer
    int ReadInt32();

    /// \brief Reads an unsigned 32-bit integer
    unsigned int ReadUInt32();

    /// \brief Reads a signed 64-bit integer
    long long ReadInt64();

    /// \brief Reads an unsigned 64-bit integer
    unsigned long long ReadUInt64();

    /// \brief Reads a 32-bit floating-point number
    float ReadFloat32();

    /// \brief Reads a 64-bit floating-point number
    double ReadFloat64();

protected:
    InputStream();

    /// \brief Marks a capability for the input stream
    /// \param cap The capability to mark
    void MarkCapability(GsCapability cap);

private:
    /// \brief Capability flags
    unsigned long long m_nCapability = 0;
};
CPL_SMARTER_PTR(InputStream);

/// \brief Memory-based input stream
class CPL_API MemoryInputStream : public InputStream
{
protected:
    /// \brief Current offset in the memory stream
    unsigned long long m_nOffset = 0;

    /// \brief Total length of the memory stream
    unsigned long long m_nLength = 0;

    /// \brief Pointer to the start of the memory buffer
    const unsigned char *m_Head = NULL;

    /// \brief Internal buffer for managing data
    GrowByteBuffer m_Buffer;

    /// \brief Initializes the memory input stream
    void Init();

    /// \brief Default constructor (protected)
    MemoryInputStream();

public:
    /// \brief Constructor for creating a memory stream from a raw buffer
    /// \param buffer Pointer to the input buffer
    /// \param nLen Length of the input buffer
    /// \param bCopy Whether to copy the input buffer (true) or use it directly (false)
    MemoryInputStream(const unsigned char *buffer, int nLen,
                      bool bCopy = false);

    /// \brief Constructor for creating a memory stream from a ByteBuffer
    /// \param buffer Pointer to the ByteBuffer object
    /// \param bCopy Whether to copy the buffer data (true) or use it directly (false)
    MemoryInputStream(ByteBuffer *buffer, bool bCopy = false);

    /// \brief Constructor for creating a memory stream from a C-style string
    /// \param str Pointer to the C-style string
    /// \param bCopy Whether to copy the string data (true) or use it directly (false)
    MemoryInputStream(const char *str, bool bCopy = false);

    /// \brief Constructor for creating a memory stream from an std::string
    /// \param str Reference to the std::string object
    /// \param bCopy Whether to copy the string data (true) or use it directly (false)
    MemoryInputStream(const std::string &str, bool bCopy = false);

    /// \brief Reads a block of data from the memory stream
    /// \details Reads a block of data of the specified length. Returns the actual length of data read.
    /// If the stream supports zero-copy, the `pointer` parameter provides direct access to the data.
    /// \param buff The buffer to store the read data, or nullptr if using `pointer`
    /// \param nLen The number of bytes to read
    /// \param pointer Pointer to the original memory data, or nullptr if not available
    /// \return The actual number of bytes read
    virtual int RawRead(unsigned char *buff, int nLen,
                        const unsigned char **pointer);

    /// \brief Gets the length of the memory stream
    /// \details Returns the total length of the memory stream. This method overrides the base class implementation.
    /// \return The length of the memory stream
    virtual long long Length() const;

    /// \brief Gets the current offset in the memory stream
    /// \return The current offset
    virtual unsigned long long Offset() const;

    /// \brief Sets the offset in the memory stream
    /// \param offset The new offset to set
    /// \param origin The reference point for the offset (beginning, current position, or end)
    /// \return True if the offset was successfully set, otherwise false
    virtual bool Seek(int offset, StreamSeekOrigin origin);

    /// \brief Closes the memory stream
    /// \return True if the stream was successfully closed, otherwise false
    virtual bool Close();
};
CPL_SMARTER_PTR(MemoryInputStream)

/// \brief File input stream
class CPL_API FileInputStream : public InputStream
{
    FILE *m_pFile = NULL;            ///< Pointer to the file handle
    unsigned long long m_nLength = 0;///< Length of the file
    bool m_bCloseFile = true;///< Whether to close the file upon destruction
    void Init();             ///< Initialization method

public:
    /// \brief Constructor from file path
    /// \param file File path
    /// \param bBin Whether to open the file in binary mode
    FileInputStream(const char *file, bool bBin = true);

    /// \brief Constructor from file handle
    /// \param file File handle
    /// \param nLen Length of the file
    /// \param bCloseFile Whether to close the file when the object is destroyed
    FileInputStream(FILE *file, unsigned long long nLen,
                    bool bCloseFile = false);

    /// \brief Destructor
    virtual ~FileInputStream();

    using InputStream::ReadLine;
    /// \brief Reads a line of string
    /// \param line Reference to a string where the line will be stored
    /// \return True if successful, false otherwise
    bool ReadLine(std::string &line);

    /// \brief Reads a block of data
    /// \details Reads a block of data of a specified length from the input stream. Returns the actual length of data read. Derived classes without zero-copy capability should override this function.
    /// \param buff Buffer to store the read data
    /// \param nLen Length of data to read
    /// \return Actual length of data read
    virtual int RawRead(unsigned char *buff, int nLen);

    /// \brief Gets the length of the data stream
    /// \details If the stream does not support the `eLength` capability, the length will be -1. Derived classes that support the `eLength` capability should override this method.
    /// \return Length of the data stream, or -1 if not supported
    virtual long long Length() const;

    /// \brief Gets the current offset of the input stream
    /// \return Current offset in the input stream
    virtual unsigned long long Offset() const;

    /// \brief Seeks to a specific offset in the input stream
    /// \param offset Offset to move to
    /// \param origin Origin for the seek operation (beginning, current position, or end)
    /// \return True if successful, false otherwise
    virtual bool Seek(int offset, StreamSeekOrigin origin);
};
CPL_SMARTER_PTR(FileInputStream)


/// \brief Base class for output data streams
class CPL_API OutputStream : public RefObject
{
    unsigned long long m_nCapability = 0;

public:
    /// \brief Enum for OutputStream capabilities
    enum class GsCapability : int
    {
        /// \brief Supports seeking in the stream
        eSeek = 0,
    };

protected:
    OutputStream();
    /// \brief Marks the capability of the output stream
    void MarkCapability(GsCapability cap);

public:
    virtual ~OutputStream();
    /// \brief Tests the capabilities of the output stream
    bool TestCapability(GsCapability cap);
    /// \brief Writes a block of data to the output stream. Derived classes must implement this method.
    virtual int RawWrite(const unsigned char *buff, int nLen) = 0;
    /// \brief Returns the offset of the next write, i.e., the length of data already written. Derived classes must implement this method.
    virtual unsigned long long Offset() const = 0;
    /// \brief Seeks to a specified position in the output stream. Derived classes supporting seeking must implement this method.
    virtual bool Seek(int offset, StreamSeekOrigin origin);
    /// \brief Flushes the output stream, committing any cached but unwritten data.
    virtual bool Flush();

    /// \brief Closes the output stream.
    virtual bool Close();

    /// \brief Template method for writing data of type T
    template<class T>
    OutputStream &WriteT(const T &val)
    {
        RawWrite((const unsigned char *) &val, sizeof(T));
        return *this;
    }
    /// \brief Output stream operator for writing values
    template<class T>
    OutputStream &operator<<(const T &val)
    {
        return WriteT(val);
    }
    /// \brief Writes a string to the output stream
    /// \param str The string to be written
    /// \param nLen The length of the string to write. If less than 0, the length is automatically calculated
    int WriteString(const char *str, int nLen = -1);
    /// \brief Writes a string to the output stream
    int WriteString(const std::string &str);

    /// \brief Writes a block of memory to the output stream
    int WriteBuffer(const ByteBuffer *buff);
};
CPL_SMARTER_PTR(OutputStream)

/// \brief Output stream that writes data to in-memory storage
class CPL_API MemoryOutputStream : public OutputStream
{
    unsigned long long m_Offset = 0;///< Current offset in the output stream
    unsigned char *m_FixMemoryHead =
            NULL;///< Pointer to fixed memory for output
    unsigned long long m_FixeMemoryLength =
            0;///< Length of the fixed memory block

    unsigned long long m_Start = 0;///< Start position for output data
    std::vector<unsigned char> *m_pVectorOutput =
            NULL;///< Pointer to vector for storing output
    std::string *m_pStringOutput =
            NULL;///< Pointer to string for storing output
    ByteBuffer *m_pByteBufferOutput =
            NULL;///< Pointer to ByteBuffer for storing output
    std::stringstream *m_pStringStream =
            NULL;                ///< Pointer to string stream for output
    GrowByteBuffer m_InnerBuffer;///< Internal buffer for data storage

public:
    /// \brief Default constructor that outputs data to an internal ByteBuffer.
    /// \details The stored data can be accessed via the `Buffer` method.
    MemoryOutputStream();

    /// \brief Constructs an output stream that writes to a `std::stringstream`.
    /// \param str The stringstream to write data to.
    MemoryOutputStream(std::stringstream &str);

    /// \brief Constructs an output stream that writes to a `std::string`.
    /// \param str The string to write data to.
    MemoryOutputStream(std::string &str);

    /// \brief Constructs an output stream that writes to a `std::vector<unsigned char>`.
    /// \param vec The vector to write data to.
    MemoryOutputStream(std::vector<unsigned char> &vec);

    /// \brief Constructs an output stream that writes to a `ByteBuffer`.
    /// \param buff The ByteBuffer to write data to.
    MemoryOutputStream(ByteBuffer *buff);

    /// \brief Constructs an output stream that writes to a fixed-length memory block.
    /// \param fixMem Pointer to the fixed memory block.
    /// \param nLen Length of the memory block.
    MemoryOutputStream(unsigned char *fixMem, unsigned long long nLen);

    /// \brief Gets the buffer storing the output data.
    /// \return A pointer to the stored `ByteBuffer`.
    const ByteBuffer *Buffer() const;

    /// \brief Writes a block of data to the output stream. Derived classes must implement this method.
    /// \param buff Pointer to the data to write.
    /// \param nLen Length of the data to write.
    virtual int RawWrite(const unsigned char *buff, int nLen);

    /// \brief Returns the offset of the next write, i.e., the length of data already written.
    /// \details Derived classes must implement this method.
    /// \return The current offset in the output stream.
    virtual unsigned long long Offset() const;

    /// \brief Seeks to a specified position in the output stream.
    /// \details Derived classes supporting seeking must implement this method.
    /// \param offset The position to seek to.
    /// \param origin The origin for seeking (e.g., start, current, end).
    /// \return `true` if the seek operation was successful, `false` otherwise.
    virtual bool Seek(int offset, StreamSeekOrigin origin);
};
CPL_SMARTER_PTR(MemoryOutputStream)

/// \brief Output stream that writes data to a file storage
class CPL_API FileOutputStream : public OutputStream
{
    unsigned long long m_Start;///< Start position for output data
    FILE *m_pFile = NULL;      ///< Pointer to the file for output
    bool m_bCloseOnEnd =
            true;///< Flag indicating whether the file should be closed when the stream is closed

public:
    /// \brief Constructs an output stream that writes data to a file.
    /// \param path The path of the file to open.
    /// \param bBinary Whether to open the file in binary mode (default: true).
    /// \param bAppend Whether to append to the file if it exists (default: false, meaning overwrite the file if it exists).
    FileOutputStream(const char *path, bool bBinary = true,
                     bool bAppend = false);

    /// \brief Constructs an output stream that writes data to an already opened file handle.
    /// \param f The already opened file handle.
    /// \param bCloseOnEnd Whether to automatically close the file handle when the output stream is closed (default: true).
    FileOutputStream(FILE *f, bool bCloseOnEnd = true);

    /// \brief Destructor for the FileOutputStream class. Closes the file if necessary.
    ~FileOutputStream();

    /// \brief Writes a block of data to the output stream. Derived classes must implement this method.
    /// \param buff Pointer to the data to write.
    /// \param nLen Length of the data to write.
    /// \return The number of bytes written.
    virtual int RawWrite(const unsigned char *buff, int nLen);

    /// \brief Returns the offset of the next write, i.e., the length of data already written.
    /// \details Derived classes must implement this method.
    /// \return The current offset in the output stream.
    virtual unsigned long long Offset() const;

    /// \brief Seeks to a specified position in the output stream.
    /// \details Derived classes supporting seeking must implement this method.
    /// \param offset The position to seek to.
    /// \param origin The origin for seeking (e.g., start, current, end).
    /// \return `true` if the seek operation was successful, `false` otherwise.
    virtual bool Seek(int offset, StreamSeekOrigin origin);
};
CPL_SMARTER_PTR(FileOutputStream)

}// namespace CPL