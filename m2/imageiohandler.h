#ifndef M2_IMAGEIOHANDLER_H_
#define M2_IMAGEIOHANDLER_H_

#include <m2_image.h>

namespace m2 {

class ImageIOHandler
{
public:
    ImageIOHandler();
    virtual ~ImageIOHandler();

    virtual bool read(Image *image) = 0;
    virtual bool write(const Image &image) = 0;
};

}// namespace m2

#endif//M2_IMAGEIOHANDLER_H_