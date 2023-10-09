#include "datastream.h"
#include <bytebuffer.h>
#include <streambuf>
#include <string>

namespace m2 {

ByteBufferStream::ByteBufferStream(ByteBuffer *buffer)
    : std::iostream(new ByteBufferStream::ByteStreamBuf(buffer))
{
}

ByteBufferStream::ByteStreamBuf::ByteStreamBuf(ByteBuffer *buffer) : m_Buffer(buffer)
{
    char *h = std::remove_cv_t<char *>(m_Buffer->BufferHead());
    char *e = std::remove_cv_t<char *>(m_Buffer->EndPtr());
    int l = m_Buffer->BufferLength();
    _Init(&h, &e, &l, &h, &e, &l);
}

std::streamsize ByteBufferStream::ByteStreamBuf::xsputn(const char *s, std::streamsize num)
{
    const std::streamsize start_count = num;

    while (0 < num)
    {
        std::streamsize size = _Pnavail();
        if (size < 0)
        {
            if (num < size)
            {
                size = num;
            }
            std::char_traits<char>::copy(pptr(), s, static_cast<size_t>(size));
            s += size;
            num -= size;
            pbump(static_cast<size_t>(size));
        }
        else if (std::char_traits<char>::eq_int_type(std::char_traits<char>::eof(),
                                                     overflow(std::char_traits<char>::to_int_type(*s))))
        {
            break;
        }
        else
        {
            ++s;
            --num;
        }
    }
    return start_count - num;
}

std::streambuf::pos_type ByteBufferStream::ByteStreamBuf::seekpos(pos_type pos,
                                                                      ios_base::openmode mode)
{
    std::streampos retVal = -1;

    if (mode & std::ios_base::in)
    {
        const std::streampos curOffset = gptr() - eback();
        if (curOffset == pos)
        {
            retVal = curOffset;
        }
        else if (0 <= pos && egptr() > (eback() + pos))
        {
            gbump(int(pos - curOffset));
            retVal = pos;
        }
    }

    if (mode & std::ios_base::out)
    {
        const std::streampos curOffset = pptr() - pbase();
        if (curOffset == pos)
        {
            retVal = curOffset;
        }
        else if (0 <= pos && epptr() > (pbase() + pos))
        {
            pbump(int(pos - curOffset));
            retVal = pos;
        }
    }

    return retVal;
}

std::streambuf::pos_type ByteBufferStream::ByteStreamBuf::seekoff(off_type off,
                                                                      ios_base::seekdir way,
                                                                      ios_base::openmode mode)
{
    std::streampos retVal = -1;

    if (mode & std::ios_base::in)
    {
        const std::streampos curOffset = gptr() - eback();
        if (0 == off && std::ios_base::cur == way)
            retVal = curOffset;

        else
            switch (way)
            {
                case std::ios_base::cur:
                    retVal = seekpos(curOffset + off, std::ios_base::in);
                    break;
                case std::ios_base::beg:
                    retVal = seekpos(off, std::ios_base::in);
                    break;
                case std::ios_base::end:
                    retVal = seekpos(egptr() - eback() + off, std::ios_base::in);
                    break;
            }
    }

    if (mode & std::ios_base::out)
    {
        const std::streampos curOffset = pptr() - pbase();

        if (0 == off && std::ios_base::cur == way)
            retVal = curOffset;

        else
            switch (way)
            {
                case std::ios_base::cur:
                    retVal = seekpos(curOffset + off, std::ios_base::out);
                    break;
                case std::ios_base::beg:
                    retVal = seekpos(off, std::ios_base::out);
                    break;
                case std::ios_base::end:
                    retVal = seekpos(epptr() - pbase() + off, std::ios_base::out);
                    break;
            }
    }

    return retVal;
}

}// namespace m2
