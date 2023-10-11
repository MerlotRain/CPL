/// @brief 图像头信息
struct ImageHeaderInfo
{
    unsigned int Width;       //!< 图像宽度
    unsigned int Height;      //!< 图像高度
    int BitPerPixel;          //!< 像素深度，比特位
    ImageFormat EncodeType; //!< 图像编码方式，确定编码解码方式
    ImageColoType ColorType;//!< 颜色编码方式
};