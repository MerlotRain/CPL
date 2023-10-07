/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file image.h
 * @brief
 * @details
 * @date 2023-07-04
 * @author
 *
 ******************************************************************************/

#pragma once

#include "bytebuffer.h"
#include "color.h"
#include "matrix.h"
#include "object.h"
#include "shape.h"

namespace Lite {
namespace Utility {


/// @brief 颜色通道类型
enum GsImageColoType
{
    /// @brief 8bit的灰度图像
    eGRAY8Bit,
    /// @brief BGRA结构，每位占据一个char
    eBGRA32Bit,
    /// @brief ABGR结构，每位占据一个char
    eABGR32Bit,
    /// @brief RGBA结构，每位占据一个char
    eRGBA32Bit,
    /// @brief ARGB结构，每位占据一个char
    eARGB32Bit,
    /// @brief 24位真彩色。每个像素采用3个字节来表示
    eRGB24Bit,
    /// @brief 与RGB格式类似
    eBGR24Bit,
};

/// @brief 图像转换的模式
enum GsImageTransformationMode
{
    /// @brief 快速转换，优先考虑效率
    eFastTransformation,
    /// @brief 平滑转换，像素值变化更加平滑，效率较低
    eSmoothTransformation
};

/// @brief 常见的图像编码方式
/// @details https://docs.fileformat.com/image/
enum class GsImageFormat
{
    eUnknownType,
    ePNG,
    eBMP,
    eXPM,
    eXBM,
    ePPM,
    eDDS,
    eICNS,
    eJP2,
    eMNG,
    eTGA,
    eTIFF,
    eWEBP,
    eGIF,
    eICO,
    eJPEG,
};


/// @brief 图像基类
class UTILITY_EXPORT GsImage
{
public:
    /// @brief 默认析构
    virtual ~GsImage();
    /// @brief 拷贝图像
    /// @param pImage
    /// @return
    virtual bool CopyFrom(GsImage *pImage);
    /// @brief 拷贝外部数据到自身
    /// @param pBuff
    /// @param nLen
    /// @param type
    /// @return
    virtual bool FillImage(const unsigned char *pBuff, int nLen, GsImageColoType type);

    /// @brief 拷贝自身的数据到外部影像
    /// @param pBuff
    /// @param nLen
    /// @param type
    /// @return
    virtual int CopyTo(unsigned char *pBuff, int nLen, GsImageColoType type);

    /// @brief 将自身数据剪裁到目标图像中
    /// @param target 要存储数据的图像
    /// @param rect 要剪裁的数据范围
    /// @param offset 存储到目标数据的偏移位置
    /// @return
    virtual bool CropTo(GsImage *target, const GsRect &rect, const GsPT &offset);

    /// @brief 将自身数据剪裁到目标内存块中
    /// @param target 要存储数据的目标内存
    /// @param nStride 目标数据行字节长度
    /// @param extent 要剪裁的数据范围
    /// @param eType
    /// @return
    virtual bool CropTo(unsigned char *target, int nStride, const GsRect &extent, GsImageColoType eType = GsImageColoType::eRGBA32Bit);

    /// @brief 将自身数据剪裁到目标内存块中
    /// @param target 要存储数据的目标内存
    /// @param nStride 目标数据行字节长度
    /// @param extent 要剪裁的数据范围
    /// @param eType
    /// @return
    virtual bool CropTo(GsByteBuffer *target, int nStride, const GsRect &extent, GsImageColoType eType = GsImageColoType::eRGBA32Bit);

    /// @brief 获取图片颜色格式
    /// @return
    virtual GsImageColoType RGBAType();
    /// @brief 影像的宽和高
    virtual GsSize Size();

    /// @brief 获得宽度
    /// @return
    virtual unsigned int Width() = 0;
    /// @brief 获得高度
    /// @return
    virtual unsigned int Height() = 0;

    /// @brief 获取图像的字节数组，并非所有图像都能够成功
    /// @return
    virtual const unsigned char *Bit() = 0;

    /// @brief 图像缩放，内部会根据大小重采样
    /// @param w
    /// @param h
    /// @param eMode
    /// @return
    virtual GsImage *Scaled(int w, int h, GsImageTransformationMode eMode = GsImageTransformationMode::eFastTransformation);

    unsigned char *ScanLine(int);
    const unsigned char *ScanLine(int) const;
    long long BytesPerLine() const;

    bool Valid(int x, int y) const;
    bool Valid(const GsPT &pt) const;

    int PixelIndex(int x, int y) const;
    int PixelIndex(const GsPT &pt) const;

    GsColor Pixel(int x, int y) const;
    GsColor Pixel(const GsPT &pt) const;

    void Pixel(int x, int y, unsigned int index_or_rgb);
    void Pixel(const GsPT &pt, unsigned int index_or_rgb);

    GsColor PixelColor(int x, int y) const;
    GsColor PixelColor(const GsPT &pt) const;

    void PixelColor(int x, int y, const GsColor &c);
    void PixelColor(const GsPT &pt, const GsColor &c);

    void Fill(unsigned int pixel);
    void Fill(const GsColor &color);
};
GS_SMARTER_PTR(GsImage)


/// @brief 图像读写
class UTILITY_EXPORT GsImageIO
{
public:
    virtual bool CanRead(GsImage *image) = 0;
};

class UTILITY_EXPORT GsBmpImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsPNGImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsGifImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsWebpImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsSvgImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsTiffImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsPpmImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsXbmImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsXpmImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsICOImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsDDSImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsTgaImageIO : public GsImageIO
{
};

class UTILITY_EXPORT GsWbmpImageIO : public GsImageIO
{
};

/// @brief 图像处理
class GsImageProcess
{
public:
    //高斯滤波
    //中值滤波
    //双边滤波

    //Sobel算子
    //Scharr算子
    //拉普拉斯算子
    //Canny算子

    //角点检测
    //ORB算法
    //SIFT算法
    //傅里叶变换
    //二值化
    //图像混合
};


}// namespace Utility
}// namespace Lite
