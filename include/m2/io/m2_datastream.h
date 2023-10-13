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

#ifndef M2_DATASTREAM_H_
#define M2_DATASTREAM_H_

#include <m2_endian.h>
#include <m2_iobase.h>

namespace m2 {

class DataStream
{
public:
    enum Status
    {
        Ok,
        ReadPastEnd,
        ReadCorruptData,
        WriteFailed
    };


    bool atEnd() const;

    Status status() const;
    void setStatus(Status status);
    void resetStatus();

    Endian byteOrder() const;
    void setByteOrder(Endian);

    DataStream &operator>>(int8_t &i);
    DataStream &operator>>(uint8_t &i);
    DataStream &operator>>(int16_t &i);
    DataStream &operator>>(uint16_t &i);
    DataStream &operator>>(int32_t &i);
    DataStream &operator>>(uint32_t &i);
    DataStream &operator>>(int64_t &i);
    DataStream &operator>>(uint64_t &i);
    DataStream &operator>>(std::nullptr_t &ptr);
    DataStream &operator>>(bool &i);
    DataStream &operator>>(float &f);
    DataStream &operator>>(double &f);
    DataStream &operator>>(char *&str);
    DataStream &operator>>(char16_t &c);
    DataStream &operator>>(char32_t &c);

    DataStream &operator<<(int8_t i);
    DataStream &operator<<(uint8_t i);
    DataStream &operator<<(int16_t i);
    DataStream &operator<<(uint16_t i);
    DataStream &operator<<(int32_t i);
    DataStream &operator<<(uint32_t i);
    DataStream &operator<<(int64_t i);
    DataStream &operator<<(uint64_t i);
    DataStream &operator<<(std::nullptr_t) { return *this; }
    DataStream &operator<<(bool i);
    DataStream &operator<<(float f);
    DataStream &operator<<(double f);
    DataStream &operator<<(const char *str);
    DataStream &operator<<(char16_t c);
    DataStream &operator<<(char32_t c);

    DataStream &readBytes(char *&, uint32_t &len);
    int readRawData(char *, int len);

    DataStream &writeBytes(const char *, uint32_t len);
    int writeRawData(const char *, int len);

    int seek(int len);
};

}// namespace m2

#endif//M2_DATASTREAM_H_