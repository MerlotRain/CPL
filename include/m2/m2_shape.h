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

#pragma once

#include "mathhelp.h"
#include "preconfig.h"

namespace m2 {

/// @brief int点结构
struct GsPT
{
    int X;
    int Y;

    /// @brief 默认构造
    constexpr GsPT();
    /// @brief 由x,y坐标构造
    /// @param xpos
    /// @param ypos
    constexpr GsPT(int xpos, int ypos);
    /// @brief 是否为空
    /// @return
    constexpr inline bool IsNull() const;
    /// @brief 获取点的曼哈顿距离
    /// @return
    constexpr inline int ManhattanLength() const;
    /// @brief 坐标转置
    /// @return
    constexpr GsPT Transposed() const noexcept { return {Y, X}; }

    /// @brief 重载+=操作符
    /// @param p
    /// @return
    constexpr inline GsPT &operator+=(const GsPT &p);
    /// @brief 重载-=操作符
    /// @param p
    /// @return
    constexpr inline GsPT &operator-=(const GsPT &p);

    /// @brief 重载*=操作符
    /// @param factor
    /// @return
    constexpr inline GsPT &operator*=(float factor);
    constexpr inline GsPT &operator*=(int factor);

    /// @brief 重载/=操作符
    /// @param divisor
    /// @return
    constexpr inline GsPT &operator/=(float c);
    /// @brief 求两点点积
    /// @param p1
    /// @param p2
    /// @return
    constexpr static inline int DotProduct(const GsPT &p1, const GsPT &p2);

    friend constexpr inline bool operator==(const GsPT &, const GsPT &);
    friend constexpr inline bool operator!=(const GsPT &, const GsPT &);
    friend constexpr inline const GsPT operator+(const GsPT &, const GsPT &);
    friend constexpr inline const GsPT operator-(const GsPT &, const GsPT &);
    friend constexpr inline const GsPT operator*(const GsPT &, float);
    friend constexpr inline const GsPT operator*(float, const GsPT &);
    friend constexpr inline const GsPT operator*(const GsPT &, float);
    friend constexpr inline const GsPT operator*(float, const GsPT &);
    friend constexpr inline const GsPT operator*(const GsPT &, int);
    friend constexpr inline const GsPT operator*(int, const GsPT &);
    friend constexpr inline const GsPT operator+(const GsPT &);
    friend constexpr inline const GsPT operator-(const GsPT &);
    friend constexpr inline const GsPT operator/(const GsPT &, float);
};


/// @brief float点结构
struct GsPTF
{
    float X;
    float Y;

    /// @brief 默认构造
    constexpr GsPTF();
    /// @brief 由整型点结构构造
    /// @param p
    constexpr explicit GsPTF(const GsPT &p);
    /// @brief 由x，y坐标构造
    /// @param xpos
    /// @param ypos
    constexpr GsPTF(float xpos, float ypos);
    /// @brief 获取点的曼哈顿距离
    /// @return
    constexpr inline float ManhattanLength() const;
    /// @brief 是否为空
    /// @return
    inline bool IsNull() const;

    /// @brief 坐标转置
    /// @return
    constexpr GsPTF Transposed() const noexcept { return {Y, X}; }

    constexpr inline GsPTF &operator+=(const GsPTF &p);
    constexpr inline GsPTF &operator-=(const GsPTF &p);
    constexpr inline GsPTF &operator*=(float c);
    constexpr inline GsPTF &operator/=(float divisor);

    /// @brief 求两点点积
    /// @param p1
    /// @param p2
    /// @return
    constexpr static inline float DotProduct(const GsPTF &p1, const GsPTF &p2);

    friend constexpr inline bool operator==(const GsPTF &, const GsPTF &);
    friend constexpr inline bool operator!=(const GsPTF &, const GsPTF &);
    friend constexpr inline const GsPTF operator+(const GsPTF &, const GsPTF &);
    friend constexpr inline const GsPTF operator-(const GsPTF &, const GsPTF &);
    friend constexpr inline const GsPTF operator*(float, const GsPTF &);
    friend constexpr inline const GsPTF operator*(const GsPTF &, float);
    friend constexpr inline const GsPTF operator+(const GsPTF &);
    friend constexpr inline const GsPTF operator-(const GsPTF &);
    friend constexpr inline const GsPTF operator/(const GsPTF &, float);

    constexpr GsPT ToPoint() const;
};


/// @brief 缩放横纵比例的变化
enum GsAspectRatioMode
{
    /// @brief 忽略横纵比例，自由缩放
    /// @details 图形可能会产生形变
    eIgnoreAspectRatio,
    /// @brief 大小被缩放为给定矩形内尽可能大的矩形，以保持纵横比
    /// @details 图形不会产生形变，将尽可能保持最大
    eKeepAspectRatio,
    /// @brief 大小被缩放到给定矩形之外尽可能小的矩形，以保持纵横比
    /// @details 图形不会产生形变，将尽可能保持最小
    eKeepAspectRatioByExpanding
};


/// @brief int边距结构
/// @details 在size,rect缩放过程中，需要主动指示正负值，Margins旨在于简化这个操作
/// @details 其中四周边距都是正数，调用ExpandedTo和BoundedTo函数可以快速获取缩放后的结果
struct GsMargins
{
    int Left;
    int Top;
    int Right;
    int Bottom;

    /// @brief 默认构造
    constexpr GsMargins() noexcept;
    /// @brief 由四周边距构造
    /// @param left
    /// @param top
    /// @param right
    /// @param bottom
    constexpr GsMargins(int left, int top, int right, int bottom) noexcept;

    /// @brief 是否为null
    /// @return
    constexpr bool IsNull() const noexcept;

    constexpr GsMargins &operator+=(const GsMargins &margins) noexcept;
    constexpr GsMargins &operator-=(const GsMargins &margins) noexcept;
    constexpr GsMargins &operator+=(int) noexcept;
    constexpr GsMargins &operator-=(int) noexcept;
    constexpr GsMargins &operator*=(int) noexcept;
    constexpr GsMargins &operator/=(int);
    constexpr GsMargins &operator*=(float) noexcept;
    constexpr GsMargins &operator/=(float);

    friend constexpr inline bool operator==(const GsMargins &, const GsMargins &) noexcept;
    friend constexpr inline bool operator!=(const GsMargins &, const GsMargins &) noexcept;
};

/// @brief float类型边距结构
struct GsMarginsF
{
    float Left;
    float Top;
    float Right;
    float Bottom;


    /// @brief 默认构造
    constexpr GsMarginsF() noexcept;
    /// @brief 由四周边距构造
    /// @param left
    /// @param top
    /// @param right
    /// @param bottom
    constexpr GsMarginsF(float left, float top, float right, float bottom) noexcept;
    /// @brief 由整型Mergins构造
    /// @param margins
    constexpr explicit GsMarginsF(const GsMargins &margins) noexcept;

    constexpr bool IsNull() const noexcept;

    constexpr GsMarginsF &operator+=(const GsMarginsF &margins) noexcept;
    constexpr GsMarginsF &operator-=(const GsMarginsF &margins) noexcept;
    constexpr GsMarginsF &operator+=(float addend) noexcept;
    constexpr GsMarginsF &operator-=(float subtrahend) noexcept;
    constexpr GsMarginsF &operator*=(float factor) noexcept;
    constexpr GsMarginsF &operator/=(float divisor);

    constexpr inline GsMargins toMargins() const noexcept;
};


/// @brief 创建int类型的尺寸结构
struct GsSize
{
    int Width;
    int Height;

    /// @brief 默认构造
    constexpr GsSize() noexcept;
    /// @brief 由w,h构造
    /// @param w
    /// @param h
    constexpr GsSize(int w, int h) noexcept;

    /// @brief \a w 和 \a h 为0时判断为null
    /// @return
    constexpr inline bool IsNull() const noexcept;
    /// @brief \a w 和 \a h 其一小于1则判断为空
    /// @return
    constexpr inline bool IsEmpty() const noexcept;
    /// @brief \a w 和 \a h 必须都大于等于0
    /// @return
    constexpr inline bool IsValid() const noexcept;

    /// @brief 交换宽、高值
    void Transpose() noexcept;
    /// @brief 交换宽、高值，返回结果
    /// @return
    GS_REQUIRED_RESULT constexpr inline GsSize Transposed() const noexcept;

    /// @brief 尺寸缩放
    /// @param w
    /// @param h
    /// @param mode
    inline void Scale(int w, int h, GsAspectRatioMode mode) noexcept;
    inline void Scale(const GsSize &s, GsAspectRatioMode mode) noexcept;
    /// @brief 尺寸缩放，将结果返回
    /// @param w
    /// @param h
    /// @param mode
    /// @return
    GS_REQUIRED_RESULT GsSize Scaled(int w, int h, GsAspectRatioMode mode) const noexcept;
    GS_REQUIRED_RESULT GsSize Scaled(const GsSize &s, GsAspectRatioMode mode) const noexcept;

    /// @brief 返回一个大小，该大小包含此大小和给定otherSize的最小宽度和高度
    /// @param
    /// @return
    GS_REQUIRED_RESULT constexpr inline GsSize ExpandedTo(const GsSize &) const noexcept;
    /// @brief 返回一个大小，该大小包含此大小和给定otherSize的最大宽度和高度
    /// @param
    /// @return
    GS_REQUIRED_RESULT constexpr inline GsSize BoundedTo(const GsSize &) const noexcept;

    /// @brief 返回按边距增大此大小所产生的大小
    /// @param m
    /// @return
    GS_REQUIRED_RESULT constexpr GsSize GrownBy(GsMargins m) const noexcept;
    /// @brief 返回按边距缩小此大小的结果
    /// @param m
    /// @return
    GS_REQUIRED_RESULT constexpr GsSize ShrunkBy(GsMargins m) const noexcept;

    /// @brief 尺寸代表的面积
    /// @return
    int Area() const;

    constexpr inline GsSize &operator+=(const GsSize &) noexcept;
    constexpr inline GsSize &operator-=(const GsSize &) noexcept;
    constexpr inline GsSize &operator*=(float c) noexcept;
    inline GsSize &operator/=(float c);

    friend inline constexpr bool operator==(const GsSize &, const GsSize &) noexcept;
    friend inline constexpr bool operator!=(const GsSize &, const GsSize &) noexcept;
    friend inline constexpr const GsSize operator+(const GsSize &, const GsSize &) noexcept;
    friend inline constexpr const GsSize operator-(const GsSize &, const GsSize &) noexcept;
    friend inline constexpr const GsSize operator*(const GsSize &, float) noexcept;
    friend inline constexpr const GsSize operator*(float, const GsSize &) noexcept;
    friend inline const GsSize operator/(const GsSize &, float);
};


/// @brief 创建float类型的尺寸结构
struct GsSizeF
{
    float Width;
    float Height;

    /// @brief 默认构造
    constexpr GsSizeF() noexcept;
    /// @brief 由整型尺寸构造
    /// @param sz
    constexpr explicit GsSizeF(const GsSize &sz) noexcept;
    /// @brief 由宽、高构造
    /// @param w
    /// @param h
    constexpr GsSizeF(float w, float h) noexcept;

    inline bool IsNull() const noexcept;
    constexpr inline bool IsEmpty() const noexcept;
    constexpr inline bool IsValid() const noexcept;

    /// @brief 交换宽、高值
    void Transpose() noexcept;
    /// @brief 交换宽、高值，返回结果
    /// @return
    GS_REQUIRED_RESULT constexpr inline GsSizeF Transposed() const noexcept;

    /// @brief 尺寸缩放
    /// @param w
    /// @param h
    /// @param mode
    inline void Scale(float w, float h, GsAspectRatioMode mode) noexcept;
    inline void Scale(const GsSizeF &s, GsAspectRatioMode mode) noexcept;
    /// @brief 尺寸缩放，将结果返回
    /// @param w
    /// @param h
    /// @param mode
    /// @return
    GS_REQUIRED_RESULT GsSizeF Scaled(float w, float h, GsAspectRatioMode mode) const noexcept;
    GS_REQUIRED_RESULT GsSizeF Scaled(const GsSizeF &s, GsAspectRatioMode mode) const noexcept;

    /// @brief 返回一个大小，该大小包含此大小和给定otherSize的最小宽度和高度
    /// @param
    /// @return
    GS_REQUIRED_RESULT constexpr inline GsSizeF ExpandedTo(const GsSizeF &) const noexcept;
    /// @brief 返回一个大小，该大小包含此大小和给定otherSize的最大宽度和高度
    /// @param
    /// @return
    GS_REQUIRED_RESULT constexpr inline GsSizeF BoundedTo(const GsSizeF &) const noexcept;

    /// @brief 返回按边距增大此大小所产生的大小
    /// @param m
    /// @return
    GS_REQUIRED_RESULT constexpr GsSizeF GrownBy(GsMarginsF m) const noexcept;
    /// @brief 返回按边距缩小此大小的结果
    /// @param m
    /// @return
    GS_REQUIRED_RESULT constexpr GsSizeF ShrunkBy(GsMarginsF m) const noexcept;


    /// @brief 尺寸代表的面积
    /// @return
    float Area() const;

    constexpr inline GsSizeF &operator+=(const GsSizeF &) noexcept;
    constexpr inline GsSizeF &operator-=(const GsSizeF &) noexcept;
    constexpr inline GsSizeF &operator*=(float c) noexcept;
    inline GsSizeF &operator/=(float c);

    friend constexpr inline bool operator==(const GsSizeF &, const GsSizeF &) noexcept;
    friend constexpr inline bool operator!=(const GsSizeF &, const GsSizeF &) noexcept;
    friend constexpr inline const GsSizeF operator+(const GsSizeF &, const GsSizeF &) noexcept;
    friend constexpr inline const GsSizeF operator-(const GsSizeF &, const GsSizeF &) noexcept;
    friend constexpr inline const GsSizeF operator*(const GsSizeF &, float) noexcept;
    friend constexpr inline const GsSizeF operator*(float, const GsSizeF &) noexcept;
    friend inline const GsSizeF operator/(const GsSizeF &, float);

    constexpr inline GsSize toSize() const noexcept;
};


/// @brief int类型矩形结构
struct GsRect
{
    int Left;
    int Top;
    int Right;
    int Bottom;

    /// @brief 默认构造
    constexpr GsRect() noexcept;
    /// @brief 由左上角点和右下角点构造
    /// @param topleft
    /// @param bottomright
    constexpr GsRect(const GsPT &topleft, const GsPT &bottomright) noexcept;
    /// @brief 由左上角点和尺寸构造
    /// @param topleft
    /// @param size
    constexpr GsRect(const GsPT &topleft, const GsSize &size) noexcept;
    /// @brief 由左上角点坐标和矩形宽高构造
    /// @param left
    /// @param top
    /// @param width
    /// @param height
    constexpr GsRect(int left, int top, int width, int height) noexcept;

    constexpr inline bool IsNull() const noexcept;
    constexpr inline bool IsEmpty() const noexcept;
    constexpr inline bool IsValid() const noexcept;

    /// @brief 矩形正则化
    /// @details 返回一个标准化的矩形,即具有非负宽度和高度的矩形
    /// @return
    GS_REQUIRED_RESULT GsRect Normalized() const noexcept;

    /// @brief 设置左上角点
    /// @param p
    constexpr inline void TopLeft(const GsPT &p) noexcept;
    /// @brief 设置右下角点
    /// @param p
    constexpr inline void BottomRight(const GsPT &p) noexcept;
    /// @brief 设置右上角点
    /// @param p
    constexpr inline void TopRight(const GsPT &p) noexcept;
    /// @brief 设置左下角点
    /// @param p
    constexpr inline void BottomLeft(const GsPT &p) noexcept;

    /// @brief 获取左上角点
    /// @return
    constexpr inline GsPT TopLeft() const noexcept;
    /// @brief 获取右下角点
    /// @return
    constexpr inline GsPT BottomRight() const noexcept;
    /// @brief 获取右上角点
    /// @return
    constexpr inline GsPT TopRight() const noexcept;
    /// @brief 获取左下角点
    /// @return
    constexpr inline GsPT BottomLeft() const noexcept;
    /// @brief 获取中心点
    /// @return
    constexpr inline GsPT Center() const noexcept;

    /// @brief 水平移动矩形，使矩形的左边缘位于给定的x坐标处
    /// @param pos
    constexpr inline void MoveLeft(int pos) noexcept;
    /// @brief 垂直移动矩形，使矩形的上边缘位于给定的y坐标处
    /// @param pos
    constexpr inline void MoveTop(int pos) noexcept;
    /// @brief 水平移动矩形，使矩形的右边缘位于给定的x坐标处
    /// @param pos
    constexpr inline void MoveRight(int pos) noexcept;
    /// @brief 垂直移动矩形，使矩形的底边位于给定的y坐标处
    /// @param pos
    constexpr inline void MoveBottom(int pos) noexcept;
    /// @brief 移动矩形，将左上角留在指定位置
    /// @param p
    constexpr inline void MoveTopLeft(const GsPT &p) noexcept;
    /// @brief 移动矩形，将右下角留在指定位置
    /// @param p
    constexpr inline void MoveBottomRight(const GsPT &p) noexcept;
    /// @brief 移动矩形，将右上角留在指定位置
    /// @param p
    constexpr inline void MoveTopRight(const GsPT &p) noexcept;
    /// @brief 移动矩形，将右下角留在指定位置
    /// @param p
    constexpr inline void MoveBottomLeft(const GsPT &p) noexcept;
    /// @brief 移动矩形，将中心点留在给定位置
    /// @param p
    constexpr inline void MoveCenter(const GsPT &p) noexcept;

    /// @brief 相对于当前位置，沿x轴移动矩形dx，沿y轴移动矩形dy
    /// @param dx
    /// @param dy
    constexpr inline void Translate(int dx, int dy) noexcept;
    constexpr inline void Translate(const GsPT &p) noexcept;
    /// @brief 返回相对于当前位置沿x轴平移dx、沿y轴平移dy的矩形副本
    /// @param dx
    /// @param dy
    /// @return
    GS_REQUIRED_RESULT constexpr inline GsRect Translated(int dx, int dy) const noexcept;
    /// @brief 返回相对于当前位置沿x轴平移dx、沿y轴平移dy的矩形副本
    /// @param p
    /// @return
    GS_REQUIRED_RESULT constexpr inline GsRect Translated(const GsPT &p) const noexcept;
    /// @brief 返回交换了宽度和高度的矩形的副本
    /// @return
    GS_REQUIRED_RESULT constexpr inline GsRect Transposed() const noexcept;

    /// @brief 移动矩形，将左上角留在给定位置
    /// @param x
    /// @param t
    constexpr inline void MoveTo(int x, int ay) noexcept;
    constexpr inline void MoveTo(const GsPT &p) noexcept;

    /// @brief 将矩形左上角的坐标设置为（x，y），并将其大小设置为给定的宽度和高度
    /// @param x
    /// @param y
    /// @param w
    /// @param h
    constexpr inline void Rect(int x, int y, int w, int h) noexcept;
    /// @brief 将矩形左上角的位置提取为*x和*y，将其尺寸提取为*width和*height
    /// @param x
    /// @param y
    /// @param w
    /// @param h
    constexpr inline void Rect(int *x, int *y, int *w, int *h) const;

    /// @brief 将矩形左上角的坐标设置为（x1，y1），右下角的坐标设定为（x2，y2）
    /// @param x1
    /// @param y1
    /// @param x2
    /// @param y2
    constexpr inline void Coords(int x1, int y1, int x2, int y2) noexcept;
    /// @brief 将矩形左上角的位置提取为*x1和*y1，将右下角的位置抽取为*x2和*y2
    /// @param x1
    /// @param y1
    /// @param x2
    /// @param y2
    constexpr inline void Coords(int *x1, int *y1, int *x2, int *y2) const;

    /// @brief 将dx1、dy1、dx2和dy2分别添加到矩形的现有坐标
    /// @param x1
    /// @param y1
    /// @param x2
    /// @param y2
    constexpr inline void Adjust(int x1, int y1, int x2, int y2) noexcept;
    /// @brief 返回一个新矩形，其中dx1、dy1、dx2和dy2分别添加到此矩形的现有坐标
    /// @param x1
    /// @param y1
    /// @param x2
    /// @param y2
    /// @return
    GS_REQUIRED_RESULT constexpr inline GsRect Adjusted(int x1, int y1, int x2, int y2) const noexcept;

    constexpr inline GsSize Size() const noexcept;
    constexpr inline void Size(const GsSize &s) noexcept;
    constexpr inline int Width() const noexcept;
    constexpr inline int Height() const noexcept;
    constexpr inline void Width(int w) noexcept;
    constexpr inline void Height(int h) noexcept;

    /// @brief 返回此矩形和给定矩形的边界矩形
    /// @param r
    /// @return
    GsRect operator|(const GsRect &r) const noexcept;
    /// @brief 返回此矩形与给定矩形的交集如果没有交集，则返回一个空矩形
    /// @param r
    /// @return
    GsRect operator&(const GsRect &r) const noexcept;
    inline GsRect &operator|=(const GsRect &r) noexcept;
    inline GsRect &operator&=(const GsRect &r) noexcept;

    /// @brief 如果给定点位于矩形内部或边缘，则返回true，否则返回false
    /// @details 如果 \a proper 为true，则仅当给定点在矩形内部（即，不在边上）时，此函数才返回true
    /// @param r
    /// @param proper
    /// @return
    bool Contains(const GsRect &r, bool proper = false) const noexcept;
    bool Contains(const GsPT &p, bool proper = false) const noexcept;
    inline bool Contains(int x, int y) const noexcept;
    inline bool Contains(int x, int y, bool proper) const noexcept;
    /// @brief 返回两个矩形合并之后的大矩形
    /// @param other
    /// @return
    GS_REQUIRED_RESULT inline GsRect United(const GsRect &other) const noexcept;
    /// @brief 返回两个矩形相交部分，如果不相交则返回空矩形
    /// @param other
    /// @return
    GS_REQUIRED_RESULT inline GsRect Intersected(const GsRect &other) const noexcept;
    /// @brief 判断两个几何是否相交
    /// @param r
    /// @return
    bool Intersects(const GsRect &r) const noexcept;

    /// @brief 返回按边距增长的矩形
    /// @param margins
    /// @return
    constexpr inline GsRect MarginsAdded(const GsMargins &margins) const noexcept;
    /// @brief 返回按边距减少的矩形
    /// @param margins
    /// @return
    constexpr inline GsRect MarginsRemoved(const GsMargins &margins) const noexcept;
    constexpr inline GsRect &operator+=(const GsMargins &margins) noexcept;
    constexpr inline GsRect &operator-=(const GsMargins &margins) noexcept;

    friend constexpr inline bool operator==(const GsRect &, const GsRect &) noexcept;
    friend constexpr inline bool operator!=(const GsRect &, const GsRect &) noexcept;
};


/// @brief float矩形结构
struct GsRectF
{
    float Left;
    float Top;
    float Right;
    float Bottom;

    /// @brief 默认构造
    constexpr GsRectF() noexcept;
    /// @brief 由左上角点和右下角点构造
    /// @param topleft
    /// @param bottomRight
    constexpr GsRectF(const GsPTF &topleft, const GsPTF &bottomRight) noexcept;
    /// @brief 由左上角点和尺寸构造
    /// @param topleft
    /// @param size
    constexpr GsRectF(const GsPTF &topleft, const GsSizeF &size) noexcept;
    /// @brief 由左上角点坐标和矩形宽高构造
    /// @param left
    /// @param top
    /// @param width
    /// @param height
    constexpr GsRectF(float left, float top, float width, float height) noexcept;
    /// @brief 由整型矩形构造
    /// @param rect
    constexpr GsRectF(const GsRect &rect) noexcept;

    constexpr inline bool IsNull() const noexcept;
    constexpr inline bool IsEmpty() const noexcept;
    constexpr inline bool IsValid() const noexcept;

    /// @brief 矩形正则化
    /// @details 返回一个标准化的矩形,即具有非负宽度和高度的矩形
    /// @return
    GS_REQUIRED_RESULT GsRectF Normalized() const noexcept;

    /// @brief 获取左上角点
    /// @return
    constexpr inline GsPTF TopLeft() const noexcept;
    /// @brief 获取右下角点
    /// @return
    constexpr inline GsPTF BottomRight() const noexcept;
    /// @brief 获取右上角点
    /// @return
    constexpr inline GsPTF TopRight() const noexcept;
    /// @brief 获取左下角点
    /// @return
    constexpr inline GsPTF BottomLeft() const noexcept;
    /// @brief 获取中心点
    /// @return
    constexpr inline GsPTF Center() const noexcept;

    /// @brief 设置左上角点
    /// @param p
    constexpr inline void TopLeft(const GsPTF &p) noexcept;
    /// @brief 设置右下角点
    /// @param p
    constexpr inline void BottomRight(const GsPTF &p) noexcept;
    /// @brief 设置右上角点
    /// @param p
    constexpr inline void TopRight(const GsPTF &p) noexcept;
    /// @brief 设置左下角点
    /// @param p
    constexpr inline void BottomLeft(const GsPTF &p) noexcept;

    /// @brief 水平移动矩形，使矩形的左边缘位于给定的x坐标处
    /// @param pos
    constexpr inline void MoveLeft(float pos) noexcept;
    /// @brief 垂直移动矩形，使矩形的上边缘位于给定的y坐标处
    /// @param pos
    constexpr inline void MoveTop(float pos) noexcept;
    /// @brief 水平移动矩形，使矩形的右边缘位于给定的x坐标处
    /// @param pos
    constexpr inline void MoveRight(float pos) noexcept;
    /// @brief 垂直移动矩形，使矩形的底边位于给定的y坐标处
    /// @param pos
    constexpr inline void MoveBottom(float pos) noexcept;
    /// @brief 移动矩形，将左上角留在指定位置
    /// @param p
    constexpr inline void MoveTopLeft(const GsPTF &p) noexcept;
    /// @brief 移动矩形，将右下角留在指定位置
    /// @param p
    constexpr inline void MoveBottomRight(const GsPTF &p) noexcept;
    /// @brief 移动矩形，将右上角留在指定位置
    /// @param p
    constexpr inline void MoveTopRight(const GsPTF &p) noexcept;
    /// @brief 移动矩形，将右下角留在指定位置
    /// @param p
    constexpr inline void MoveBottomLeft(const GsPTF &p) noexcept;
    /// @brief 移动矩形，将中心点留在给定位置
    /// @param p
    constexpr inline void MoveCenter(const GsPTF &p) noexcept;

    /// @brief 相对于当前位置，沿x轴移动矩形dx，沿y轴移动矩形dy
    /// @param dx
    /// @param dy
    constexpr inline void Translate(float dx, float dy) noexcept;
    constexpr inline void Translate(const GsPTF &p) noexcept;

    /// @brief 返回相对于当前位置沿x轴平移dx、沿y轴平移dy的矩形副本
    /// @param dx
    /// @param dy
    /// @return
    GS_REQUIRED_RESULT constexpr inline GsRectF Translated(float dx, float dy) const noexcept;
    GS_REQUIRED_RESULT constexpr inline GsRectF Translated(const GsPTF &p) const noexcept;
    GS_REQUIRED_RESULT constexpr inline GsRectF Transposed() const noexcept;

    /// @brief 返回交换了宽度和高度的矩形的副本
    /// @param x
    /// @param y
    constexpr inline void MoveTo(float x, float y) noexcept;
    constexpr inline void MoveTo(const GsPTF &p) noexcept;
    /// @brief 将矩形左上角的坐标设置为（x，y），并将其大小设置为给定的宽度和高度
    /// @param x
    /// @param y
    /// @param w
    /// @param h
    constexpr inline void Rect(float x, float y, float w, float h) noexcept;
    /// @brief 将矩形左上角的位置提取为*x和*y，将其尺寸提取为*width和*height
    /// @param x
    /// @param y
    /// @param w
    /// @param h
    constexpr inline void Rect(float *x, float *y, float *w, float *h) const;
    /// @brief 将矩形左上角的坐标设置为（x1，y1），右下角的坐标设定为（x2，y2）
    /// @param x1
    /// @param y1
    /// @param x2
    /// @param y2
    constexpr inline void Coords(float x1, float y1, float x2, float y2) noexcept;
    constexpr inline void Coords(float *x1, float *y1, float *x2, float *y2) const;

    /// @brief 将dx1、dy1、dx2和dy2分别添加到矩形的现有坐标
    /// @param x1
    /// @param y1
    /// @param x2
    /// @param y2
    constexpr inline void Adjust(float x1, float y1, float x2, float y2) noexcept;
    /// @brief 返回一个新矩形，其中dx1、dy1、dx2和dy2分别添加到此矩形的现有坐标
    /// @param x1
    /// @param y1
    /// @param x2
    /// @param y2
    /// @return
    GS_REQUIRED_RESULT constexpr inline GsRectF Adjusted(float x1, float y1, float x2, float y2) const noexcept;

    constexpr inline GsSizeF Size() const noexcept;
    constexpr inline void Size(const GsSizeF &s) noexcept;
    constexpr inline float Width() const noexcept;
    constexpr inline float Height() const noexcept;
    constexpr inline void Width(float w) noexcept;
    constexpr inline void Height(float h) noexcept;

    /// @brief 返回此矩形和给定矩形的边界矩形
    /// @param r
    /// @return
    GsRectF operator|(const GsRectF &r) const noexcept;
    GsRectF operator&(const GsRectF &r) const noexcept;
    /// @brief 返回此矩形与给定矩形的交集如果没有交集，则返回一个空矩形
    /// @param r
    /// @return
    inline GsRectF &operator|=(const GsRectF &r) noexcept;
    inline GsRectF &operator&=(const GsRectF &r) noexcept;

    /// @brief 如果给定点位于矩形内部或边缘，则返回true，否则返回false
    /// @param r
    /// @return
    bool Contains(const GsRectF &r) const noexcept;
    bool Contains(const GsPTF &p) const noexcept;
    inline bool Contains(float x, float y) const noexcept;
    /// @brief 返回两个矩形合并之后的大矩形
    /// @param other
    /// @return
    GS_REQUIRED_RESULT inline GsRectF United(const GsRectF &other) const noexcept;
    /// @brief 返回两个矩形相交部分，如果不相交则返回空矩形
    /// @param other
    /// @return
    GS_REQUIRED_RESULT inline GsRectF Intersected(const GsRectF &other) const noexcept;
    /// @brief 判断两个几何是否相交
    /// @param r
    /// @return
    bool Intersects(const GsRectF &r) const noexcept;

    /// @brief 返回按边距增长的矩形
    /// @param margins
    /// @return
    constexpr inline GsRectF MarginsAdded(const GsMarginsF &margins) const noexcept;
    /// @brief 返回按边距减少的矩形
    /// @param margins
    /// @return
    constexpr inline GsRectF MarginsRemoved(const GsMarginsF &margins) const noexcept;
    constexpr inline GsRectF &operator+=(const GsMarginsF &margins) noexcept;
    constexpr inline GsRectF &operator-=(const GsMarginsF &margins) noexcept;

    friend constexpr inline bool operator==(const GsRectF &, const GsRectF &) noexcept;
    friend constexpr inline bool operator!=(const GsRectF &, const GsRectF &) noexcept;

    /// @brief 转换为整型矩形
    /// @return
    GS_REQUIRED_RESULT constexpr inline GsRect ToRect() const noexcept;
    GS_REQUIRED_RESULT GsRect ToAlignedRect() const noexcept;
};


}// namespace m2


#include "shape.inl"
