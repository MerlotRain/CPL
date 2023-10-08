#include <image.h>
#include <mathhelp.h>

namespace m2 {

struct BMP_FILEHDR
{                  // BMP file header
    char bfType[2];// "BM"
    int bfSize;    // size of file
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;// pointer to the pixmap bits
};

struct BMP_INFOHDR
{                       // BMP information header
    int biSize;         // size of this struct
    int biWidth;        // pixmap width
    int biHeight;       // pixmap height
    short biPlanes;     // should be 1
    short biBitCount;   // number of bits per pixel
    int biCompression;  // compression method
    int biSizeImage;    // size of image
    int biXPelsPerMeter;// horizontal resolution
    int biYPelsPerMeter;// vertical resolution
    int biClrUsed;      // number of colors used
    int biClrImportant; // number of important colors
    // V4:
    unsigned int biRedMask;
    unsigned int biGreenMask;
    unsigned int biBlueMask;
    unsigned int biAlphaMask;
    int biCSType;
    int biEndpoints[9];
    int biGammaRed;
    int biGammaGreen;
    int biGammaBlue;
    // V5:
    int biIntent;
    int biProfileData;
    int biProfileSize;
    int biReserved;
};

const int BMP_OLD = 12;  // old Windows/OS2 BMP size
const int BMP_WIN = 40;  // Windows BMP v3 size
const int BMP_OS2 = 64;  // new OS/2 BMP size
const int BMP_WIN4 = 108;// Windows BMP v4 size
const int BMP_WIN5 = 124;// Windows BMP v5 size

const int BMP_RGB = 0;           // no compression
const int BMP_RLE8 = 1;          // run-length encoded, 8 bits
const int BMP_RLE4 = 2;          // run-length encoded, 4 bits
const int BMP_BITFIELDS = 3;     // RGB values encoded in data as bit-fields
const int BMP_ALPHABITFIELDS = 4;// RGBA values encoded in data as bit-fields


static bool read_dib_fileheader(GsInputStream &s, BMP_FILEHDR &bf)
{
    s >> bf;

    if (strncmp(bf.bfType, "BM", 2) != 0)
        return false;

    return true;
}

static bool read_dib_infoheader(GsInputStream &s, BMP_INFOHDR &bi)
{
    s >> bi;

    int nbits = bi.biBitCount;
    int comp = bi.biCompression;
    if (!(nbits == 1 || nbits == 4 || nbits == 8 || nbits == 16 || nbits == 24 || nbits == 32) ||
        bi.biPlanes != 1 || comp > BMP_BITFIELDS)
        return false;// weird BMP image
    if (!(comp == BMP_RGB || (nbits == 4 && comp == BMP_RLE4) ||
          (nbits == 8 && comp == BMP_RLE8) || ((nbits == 16 || nbits == 32) && comp == BMP_BITFIELDS)))
        return false;// weird compression type
    if (bi.biHeight == INT_MIN)
        return false;// out of range for positive int
    if (bi.biWidth <= 0 || !bi.biHeight || (unsigned long long) (bi.biWidth) * Math::Abs(bi.biHeight) > 16384 * 16384)
        return false;

    return true;
}

GsBmpImageIO::GsBmpImageIO(GsBmpFormat format)
{
}

}// namespace m2
