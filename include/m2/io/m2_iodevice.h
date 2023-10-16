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

#ifndef M2_IODEVICE_H_
#define M2_IODEVICE_H_

#include <m2_iobase.h>
#include <m2_string.h>

namespace m2 {

class ByteArray;
class IODevice
{
public:
    IODevice();
    IODevice(OpenModes mode);

    OpenModes openMode() const;
    virtual bool open(OpenModes mode);
    virtual void close();

    bool isOpen() const;
    bool isReadable() const;
    bool isWritable() const;

    virtual int64_t pos() const;
    virtual int64_t size() const;
    virtual bool seek(int64_t pos);
    virtual bool atEnd() const;
    virtual bool reset();

    int64_t read(char *data, int64_t maxlen);
    ByteArray read(int64_t maxlen);
    ByteArray readAll();
    int64_t readLine(char *data, int64_t maxlen);
    ByteArray readLine(int64_t maxlen);

    void ungetChar(char c);
    bool putChar(char c);
    bool getChar(char *c);

    int64_t write(const char *data, int64_t len);
    int64_t write(const char *data);
    int64_t write(const ByteArray &data);

    int64_t peek(char *data, int64_t maxlen);
    ByteArray peek(int64_t maxlen);
    int64_t skip(int64_t maxSize);

    String errorMessage() const;
};

}// namespace m2

#endif//M2_IODEVICE_H_