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

#ifndef M2_IMAGE_H_
#define M2_IMAGE_H_

#include <m2_color.h>
#include <m2_rect.h>
#include <m2_size.h>

namespace m2 {

class ImageData;
class M2_API Image
{
public:
    enum Format
    {

    };

    Image() noexcept;
    Image(const Size &size, Format format);
    Image(int width, int height, Format format);
    Image(uint8_t *data, int width, int height, Format format);
    Image(const uint8_t *data, int width, int height, Format format);

    explicit Image(const char *filename, const char *format = nullptr);
    Image(const Image &);
    Image(Image &&) noexcept;
    Image &operator=(const Image &);
    Image &operator==(const Image &);
    void swap(Image &other) noexcept;
    ~Image();

    bool isNull();

    bool operator==(const Image &) const;
    bool operator!=(const Image &) const;
    void detach();

    int width() const;
    int height() const;
    int depth() const;
    int colorCount() const;
    int bitPlaneCount() const;
    Size size() const;
    Rect rect() const;

    rgb32 color(int i) const;
    void setColor(int i, rgb32);
    void setColorCount(int);

    uint8_t *bits();
    const uint8_t *bits() const;
    const uint8_t *constBits() const;

    uint8_t *scanLine();
    const uint8_t *scanLine(int) const;
    const uint8_t *constScanLine(int) const;

private:
    ImageData *d;
};

}// namespace m2

#endif//M2_IMAGE_H_