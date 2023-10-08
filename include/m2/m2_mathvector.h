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

#include "preconfig.h"
#include "shape.h"

namespace m2 {

class GsVector3D;

/// @brief 二维向量类
class M2_API GsVector2D
{
public:
    /// @brief 默认构造
    GsVector2D() = default;

    /// @brief 根据二维向量的X,Y分量构造
    /// @param x
    /// @param y
    GsVector2D(double x, double y);

    /// @brief 获取向量的反向量
    /// @return
    GsVector2D operator-() const;

    /// @brief 向量扩展
    /// @param scalar
    /// @return
    GsVector2D operator*(double scalar) const;

    /// @brief 向量缩小
    /// @param scalar
    /// @return
    GsVector2D operator/(double scalar) const;
    /// @brief
    /// @param v
    /// @return
    double operator*(GsVector2D v) const;

    /// @brief
    /// @param other
    /// @return
    GsVector2D operator+(GsVector2D other) const;
    /// @brief
    /// @param other
    /// @return
    GsVector2D &operator+=(GsVector2D other);

    /// @brief
    /// @param other
    /// @return
    GsVector2D operator-(GsVector2D other) const;
    /// @brief
    /// @param other
    /// @return
    GsVector2D &operator-=(GsVector2D other);

    /// @brief
    /// @return
    double Length() const;
    /// @brief
    /// @return
    double LengthSquared() const;

    /// @brief
    /// @return
    double X() const;
    /// @brief
    /// @return
    double Y() const;

    /// @brief
    /// @return
    GsVector2D PerpVector() const;

    /// @brief
    /// @return
    double Angle() const;
    /// @brief
    /// @param v
    /// @return
    double Angle(GsVector2D v) const;
    /// @brief 向量
    /// @param v
    /// @return
    double CrossProduct(GsVector2D v) const;

    /// @brief
    /// @param rot
    /// @return
    GsVector2D RotateBy(double rot) const;
    /// @brief
    /// @return
    GsVector2D Normalized() const;

    /// @brief
    /// @param other
    /// @return
    bool operator==(GsVector2D other) const;
    /// @brief
    /// @param other
    /// @return
    bool operator!=(GsVector2D other) const;

private:
    double m_X = 0.0;
    double m_Y = 0.0;
};


/// @brief 三维向量类
class M2_API GsVector3D
{
public:
    GsVector3D() = default;
    /// @brief
    /// @param x
    /// @param y
    /// @param z
    GsVector3D(double x, double y, double z);
    /// @brief
    /// @return
    bool IsNull() const;
    /// @brief 获取X分量
    /// @return
    double X() const;
    /// @brief 获取Y分量
    /// @return
    double Y() const;
    /// @brief 获取Z分量
    /// @return
    double Z() const;
    /// @brief 设置X分量
    /// @param x
    void X(double x);
    /// @brief 设置Y分量
    /// @param y
    void Y(double y);
    /// @brief 设置Z分量
    /// @param z
    void Z(double z);
    /// @brief 设置向量的分量值
    /// @param x
    /// @param y
    /// @param z
    void Set(double x, double y, double z);
    /// @brief 判断向量是否相等
    /// @param other
    /// @return
    bool operator==(const GsVector3D &other) const;
    /// @brief 判断向量是否不等
    /// @param other
    /// @return
    bool operator!=(const GsVector3D &other) const;
    /// @brief 向量相加
    /// @param other
    /// @return
    GsVector3D operator+(const GsVector3D &other) const;
    /// @brief 向量相减
    /// @param other
    /// @return
    GsVector3D operator-(const GsVector3D &other) const;
    /// @brief 向量扩展
    /// @param factor
    /// @return
    GsVector3D operator*(const double factor) const;
    /// @brief 向量缩小
    /// @param factor
    /// @return
    GsVector3D operator/(const double factor) const;
    /// @brief 向量点积
    /// @param v1
    /// @param v2
    /// @return
    static double DotProduct(const GsVector3D &v1, const GsVector3D &v2);
    /// @brief 向量叉乘
    /// @param v1
    /// @param v2
    /// @return
    static GsVector3D CrossProduct(const GsVector3D &v1, const GsVector3D &v2);
    /// @brief 向量长度
    /// @return
    double Length() const;
    /// @brief
    void Normalize();

    /// @brief
    /// @param other
    /// @return
    double Distance(const GsVector3D &other) const;
    /// @brief
    /// @param v1
    /// @param v2
    /// @param vp
    /// @return
    static GsVector3D PerpendicularPoint(const GsVector3D &v1, const GsVector3D &v2, const GsVector3D &vp);

private:
    double m_X = 0, m_Y = 0, m_Z = 0;
};

}// namespace m2
