/******************************************************************************
 *    ______ ____ _____     ______               _
 *   / ____//  _// ___/    / ____/____   ____ _ (_)____   ___
 *  / / __  / /  \__ \    / __/  / __ \ / __ `// // __ \ / _ \
 * / /_/ /_/ /  ___/ /   / /___ / / / // /_/ // // / / //  __/
 * \____//___/ /____/   /_____//_/ /_/ \__, //_//_/ /_/ \___/
 *                                    /____/
 * @file matrix.h
 * @brief
 * @details
 * @date 2023-06-19
 * @author
 *
 ******************************************************************************/

#pragma once

#include "delegate.h"
#include "mathhelp.h"
#include "preconfig.h"

namespace Lite {
namespace Utility {


/// @brief 基于模板的二维矩阵，仿射坐标转换
/// @tparam T
/// @details 仿射变换公式
/// @details x_new = m11 * x + m21 * y + dx;
/// @details y_new = m12 * x + m22 * y + dy;
/// @details 反射变换矩阵常规表达
/// @details [m11,m12,0]
/// @details [m21,m22,0]
/// @details [dx ,dy ,1]
template<typename T = float>
class GsMatrixT
{
protected:
    union
    {
        T m_m[6];
        struct
        {
            T m_m11, m_m12, m_m21, m_m22, m_dx, m_dy;
        };
    };

public:
    GsMatrixT()
    {
        Elements(1, 0, 0, 1, 0, 0);
    }

    /// @brief 由矩阵构造矩阵
    /// @param rhs
    GsMatrixT(const GsMatrixT &rhs)
    {
        memcpy(m_m, rhs.m_m, 6 * sizeof(T));
    }

    /// @brief 构造矩阵6元素
    /// @param m11
    /// @param m12
    /// @param m21
    /// @param m22
    /// @param dx
    /// @param dy
    /// @return
    GsMatrixT(T m11, T m12, T m21, T m22, T dx, T dy)
    {
        m_m11 = m11;
        m_m12 = m12;
        m_m21 = m21;
        m_m22 = m22;
        m_dx = dx;
        m_dy = dy;
    }

    /// @brief 此方法初始化新矩阵，这样它表示从 source 参数指定的矩形映射到 target 参数中的三个浮点型点定义的平行四边形的几何变换。
    /// @param source
    /// @param target
    /// @return
    GsMatrixT(T *source, T *target)
    {
        GsMatrixT src(source[2] - source[0], source[3] - source[1], source[4] - source[0], source[5] - source[1], source[0], source[1]);
        GsMatrixT tar(target[2] - target[0], target[3] - target[1], target[4] - target[0], target[5] - target[1], target[0], target[1]);

        src.Invert();
        src.Multiply(tar);

        m_m11 = src.m_m11;
        m_m12 = src.m_m12;
        m_m21 = src.m_m21;
        m_m22 = src.m_m22;
        m_dx = src.m_dx;
        m_dy = src.m_dy;
    }

    /// @brief 平移矩阵
    /// @param offset
    GsMatrixT(T *offset)
    {
        Elements(1, 0, 0, 1, 0, 0);
        Translate(offset[0], offset[1]);
    }

    /// @brief 旋转矩阵,角度单位（弧度）
    /// @param fRotationAngle
    GsMatrixT(T fRotationAngle)
    {
        Elements(1, 0, 0, 1, 0, 0);
        Rotate(fRotationAngle);
    }

    /// @brief 缩放矩阵
    /// @param scalex
    /// @param scaley
    GsMatrixT(T scalex, T scaley)
    {
        m_m11 = scalex;
        m_m12 = 0;
        m_m21 = 0;
        m_m22 = scaley;
        m_dx = 0;
        m_dy = 0;
    }

    /// @brief 得到矩阵6元素
    /// @param m
    /// @return
    bool Elements(T *m) const
    {
        memcpy(m, m_m, sizeof(T) * 6);
        return true;
    }
    /// @brief 以模板得到矩阵6元素
    /// @param m
    /// @return
    template<class U>
    bool ElementsT(U *m) const
    {
        for (int i = 0; i < 6; i++)
        {
            m[i] = m_m[i];
        }
        return true;
    }

    /// @brief 以模板得到矩阵6元素
    /// @param m11
    /// @param m12
    /// @param m21
    /// @param m22
    /// @param dx
    /// @param dy
    /// @return
    template<class U>
    bool ElementsT(U *m11, U *m12, U *m21, U *m22, U *dx, U *dy) const
    {
        if (m11)
        {
            *m11 = m_m11;
        }
        if (m12)
        {
            *m12 = m_m12;
        }
        if (m21)
        {
            *m21 = m_m21;
        }
        if (m22)
        {
            *m22 = m_m22;
        }
        if (dx)
        {
            *dx = m_dx;
        }
        if (dy)
        {
            *dy = m_dy;
        }
        return true;
    }

    /// @brief 获取矩阵数据的指针
    /// @return
    const T *Ptr() const
    {
        return m_m;
    }

    /// @brief 获取矩阵数据的指针
    /// @return
    T *Ptr()
    {
        return m_m;
    }

    /// @brief 为矩阵6元素赋值
    /// @param m11
    /// @param m12
    /// @param m21
    /// @param m22
    /// @param dx
    /// @param dy
    /// @return
    GsMatrixT<T> &Elements(T m11, T m12, T m21, T m22, T dx, T dy)
    {
        m_m11 = m11;
        m_m12 = m12;
        m_m21 = m21;
        m_m22 = m22;
        m_dx = dx;
        m_dy = dy;
        return *this;
    }

    /// @brief 为矩阵6元素赋值
    /// @param m11
    /// @param m12
    /// @param m21
    /// @param m22
    /// @param dx
    /// @param dy
    /// @return
    template<class U>
    GsMatrixT<T> &ElementsT(U m11, U m12, U m21, U m22, U dx, U dy)
    {
        m_m11 = m11;
        m_m12 = m12;
        m_m21 = m21;
        m_m22 = m22;
        m_dx = dx;
        m_dy = dy;
        return *this;
    }

    /// @brief 为矩阵6元素赋值
    /// @param m
    /// @return
    template<class U>
    GsMatrixT<T> &ElementsT(const U *m)
    {
        for (int i = 0; i < 6; i++)
        {
            m_m[i] = m[i];
        }
        return *this;
    }

    /// @brief 矩阵X轴上偏移量
    /// @return
    T OffsetX() const
    {
        return m_dx;
    }

    /// @brief 矩阵Y轴上偏移量
    /// @return
    T OffsetY() const
    {
        return m_dy;
    }

    /// @brief 矩阵X轴上缩放量
    /// @return
    T ScaleX() const
    {
        return m_m11;
    }

    /// @brief 矩阵Y轴上缩放量
    /// @return
    T ScaleY() const
    {
        return m_m22;
    }

    /// @brief 矩阵旋转角度
    /// @return
    T RotationAngle() const
    {
        return asin(m_m12);
    }

    /// @brief 矩阵初始化，导入一个单位矩阵
    /// @return
    GsMatrixT<T> &Reset()
    {
        Elements(1, 0, 0, 1, 0, 0);
        return *this;
    }

    /// @brief 矩阵相乘(左乘）
    /// @param matrix
    /// @return
    GsMatrixT &LeftMultiply(const GsMatrixT &matrix)
    {
        GsMatrixT<T> mx(matrix);
        mx.Multiply(*this);
        *this = mx;
        return *this;
    }

    /// @brief 矩阵相乘(右乘）
    /// @param matrix
    /// @return
    GsMatrixT &Multiply(const GsMatrixT &matrix)
    {
        //当前矩阵乘以目标矩阵
        T m[6] = {m_m[0], m_m[1], m_m[2], m_m[3], m_m[4], m_m[5]};

        //相乘计算
        m_m11 = m[0] * matrix.m_m11 + m[1] * matrix.m_m21;
        m_m12 = m[0] * matrix.m_m12 + m[1] * matrix.m_m22;
        m_m21 = m[2] * matrix.m_m11 + m[3] * matrix.m_m21;
        m_m22 = m[2] * matrix.m_m12 + m[3] * matrix.m_m22;
        m_dx = m[4] * matrix.m_m11 + m[5] * matrix.m_m21 + matrix.m_dx;
        m_dy = m[4] * matrix.m_m12 + m[5] * matrix.m_m22 + matrix.m_dy;

        return *this;
    }

    /// @brief 矩阵乘法操作符
    /// @param matrix
    /// @return
    GsMatrixT operator*(const GsMatrixT &matrix) const
    {
        GsMatrixT out(*this);
        return out.Multiply(matrix);
    }

    /// @brief 仿射变换矩阵平移
    /// @param offsetX x轴上平移量
    /// @param offsetY y轴上平移量
    /// @return
    GsMatrixT<T> &Translate(T offsetX, T offsetY)
    {
        //计算平移
        m_dx += offsetX;
        m_dy += offsetY;

        return *this;
    }

    /// @brief 生成一个偏移的矩阵
    /// @param offsetX x轴上平移量
    /// @param offsetY y轴上平移量
    /// @return
    static GsMatrixT<T> DoTranslate(T offsetX, T offsetY)
    {
        GsMatrixT<T> mx;
        mx.Translate(offsetX, offsetY);
        return mx;
    }

    /// @brief 生成缩放矩阵
    /// @param scaleX x轴上缩放量
    /// @param scaleY y轴上缩放量
    /// @return
    static GsMatrixT<T> DoScale(T scaleX, T scaleY)
    {
        GsMatrixT<T> mx;
        mx.Scale(scaleX, scaleY);
        return mx;
    }

    /// @brief 生成一个旋转矩阵
    /// @param angle 矩阵旋转角度单位（弧度）
    /// @return
    static GsMatrixT<T> DoRotate(T angle)
    {
        GsMatrixT<T> mx;
        mx.Rotate(angle);
        return mx;
    }

    /// @brief 仿射变换矩阵旋转
    /// @param angle 矩阵旋转角度
    /// @param x 选中中心x坐标
    /// @param y 选中中心y坐标
    /// @return
    static GsMatrixT<T> DoRotate(T angle, T x, T y)
    {
        GsMatrixT<T> mx;
        mx.Rotate(angle, x, y);
        return mx;
    }
    /// @brief 仿射变换剪切变换（错切变换）
    /// @param shearX 矩阵横向剪切距离
    /// @param shearY 矩阵纵向剪切距离
    /// @return
    static GsMatrixT<T> DoShear(T shearX, T shearY)
    {
        GsMatrixT<T> mx;
        mx.Shear(shearX, shearY);
        return mx;
    }

    /// @brief 仿射变换矩阵缩放
    /// @param scaleX x轴上缩放量
    /// @param scaleY y轴上缩放量
    /// @return
    GsMatrixT<T> &Scale(T scaleX, T scaleY)
    {
        //计算缩放
        m_m11 *= scaleX;
        m_m21 *= scaleX;
        m_dx *= scaleX;
        m_m12 *= scaleY;
        m_m22 *= scaleY;
        m_dy *= scaleY;

        return *this;
    }

    /// @brief 仿射变换矩阵旋转
    /// @param angle 矩阵旋转角度单位（弧度）
    /// @return
    GsMatrixT<T> &Rotate(T angle)
    {
        Rotate(angle, 0, 0);
        return *this;
    }

    /// @brief 仿射变换矩阵旋转
    /// @param angle 矩阵旋转角度
    /// @param x 选中中心x坐标
    /// @param y 选中中心y坐标
    /// @return
    GsMatrixT<T> &Rotate(T angle, T x, T y)
    {
        //计算角度
        T ca = cos(angle);
        T sa = sin(angle);

        //得到6元素
        T m[6] = {m_m[0], m_m[1], m_m[2], m_m[3], m_m[4], m_m[5]};

        //计算旋转
        m_m11 = m[0] * ca - m[1] * sa;
        m_m12 = m[0] * sa + m[1] * ca;
        m_m21 = m[2] * ca - m[3] * sa;
        m_m22 = m[2] * sa + m[3] * ca;
        m_dx = m[4] * ca - m[5] * sa + x - x * ca + y * sa;
        m_dy = m[4] * sa + m[5] * ca + y - x * sa - y * ca;

        return *this;
    }

    /// @brief 仿射变换剪切变换（错切变换）
    /// @param shearX 矩阵横向剪切距离
    /// @param shearY 矩阵纵向剪切距离
    /// @return
    GsMatrixT<T> &Shear(T shearX, T shearY)
    {
        //得到6元素
        T m[6] = {m_m[0], m_m[1], m_m[2], m_m[3], m_m[4], m_m[5]};

        m_m11 = m[0] + m[1] * shearX;
        m_m12 = m[0] * shearY + m[1];
        m_m21 = m[2] + m[3] * shearX;
        m_m22 = m[2] * shearY + m[3];
        m_dx = m[4] + m[5] * shearX;
        m_dy = m[4] * shearY + m[5];

        return *this;
    }
    /// @brief 仿射变换镜像变换（镜像变换）
    /// @param mirrorX 矩阵横向对称轴
    /// @param mirrorY 矩阵纵向对称轴
    /// @return
    GsMatrixT<T> &Mirror(T mirrorX, T mirrorY)
    {
        //得到6元素
        T m[6] = {m_m[0], m_m[1], m_m[2], m_m[3], m_m[4], m_m[5]};

        m_m11 = -m[0];
        m_m22 = -m[3];
        m_dx = m[4] + 2 * mirrorX;
        m_dy = m[5] + 2 * mirrorY;

        return *this;
    }

    /// @brief 矩阵求逆
    /// @return
    GsMatrixT<T> &Invert()
    {
        //如果不可逆则返回错误
        if (!IsInvertible())
        {
            return *this;
        }

        //得到6元素
        T m[6] = {m_m[0], m_m[1], m_m[2], m_m[3], m_m[4], m_m[5]};

        //矩阵的行列式
        T D = m[0] * m[3] - m[1] * m[2];

        m_m11 = m[3] / D;
        m_m12 = -m[1] / D;
        m_m21 = -m[2] / D;
        m_m22 = m[0] / D;
        m_dx = (m[2] * m[5] - m[3] * m[4]) / D;
        m_dy = (m[1] * m[4] - m[0] * m[5]) / D;

        return *this;
    }

    /// @brief 点变换
    /// @param pts
    /// @param count
    /// @return
    template<class Q>
    bool TransformPointsT(Q *pts, int count) const
    {
        for (int i = 0; i < count; i++)
        {
            Q x = pts[2 * i];
            Q y = pts[2 * i + 1];
            pts[2 * i] = x * m_m11 + y * m_m21 + m_dx;
            pts[2 * i + 1] = x * m_m12 + y * m_m22 + m_dy;
        }
        return true;
    }

    /// @brief 变换
    /// @param pts
    /// @param count
    /// @return
    template<class Q>
    bool TransformVectorsT(Q *pts, int count) const
    {
        for (int i = 0; i < count; i++)
        {
            Q x = pts[2 * i];
            Q y = pts[2 * i + 1];
            pts[2 * i] = x * m_m11 + y * m_m21;
            pts[2 * i + 1] = x * m_m12 + y * m_m22;
        }
        return true;
    }

    /// @brief 判断矩阵是否可以求逆
    /// @return
    bool IsInvertible() const
    {
        //如果矩阵的行列式为0，则矩阵不可逆
        if (Utility::Math::IsEqual((m_m[0] * m_m[3] - m_m[1] * m_m[2]), 0))
        {
            return false;
        }
        return true;
    }

    /// @brief 判断矩阵是否是单位矩阵
    /// @return
    bool IsIdentity() const
    {
        return Utility::Math::IsEqual(m_m11, 1) &&
               Utility::Math::IsEqual(m_m12, 0) &&
               Utility::Math::IsEqual(m_m21, 0) &&
               Utility::Math::IsEqual(m_m22, 1) &&
               Utility::Math::IsEqual(m_dx, 0) &&
               Utility::Math::IsEqual(m_dy, 0);
    }

    /// @brief 判断矩阵是否相等
    /// @param rhs
    /// @return
    bool Equals(const GsMatrixT &rhs) const
    {
        return Utility::Math::IsEqual(m_m11, rhs.m_m11) &&
               Utility::Math::IsEqual(m_m12, rhs.m_m12) &&
               Utility::Math::IsEqual(m_m21, rhs.m_m21) &&
               Utility::Math::IsEqual(m_m22, rhs.m_m22) &&
               Utility::Math::IsEqual(m_dx, rhs.m_dx) &&
               Utility::Math::IsEqual(m_dy, rhs.m_dy);
    }

    /// @brief 矩阵等号操作符
    /// @param rhs
    /// @return
    GsMatrixT &operator=(const GsMatrixT &rhs)
    {
        memcpy(m_m, rhs.m_m, sizeof(T) * 6);
        return *this;
    }
};

/// @brief 单精度矩阵
typedef GsMatrixT<float> GsMatrix;
/// @brief 双精度矩阵
typedef GsMatrixT<double> GsMatrixD;

template<typename T = float>
class GsMatrix3DT
{
protected:
    union
    {
        T m_m[12];
        struct
        {
            T m_m11, m_m12, m_m13, m_m21, m_m22, m_m23, m_m31, m_m32, m_m33, m_dx, m_dy, m_dz;
        };
    };

public:
    GsMatrix3DT()
    {
        Elements(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0);
    }
    /// @brief 由矩阵构造矩阵
    /// @param rhs
    GsMatrix3DT(const GsMatrix3DT &rhs)
    {
        memcpy(m_m, rhs.m_m, 12 * sizeof(T));
    }

    /// @brief 构造矩阵12元素
    /// @param m11
    /// @param m12
    /// @param m13
    /// @param m21
    /// @param m22
    /// @param m23
    /// @param m31
    /// @param m32
    /// @param m33
    /// @param dx
    /// @param dy
    /// @param dz
    GsMatrix3DT(T m11, T m12, T m13, T m21, T m22, T m23, T m31, T m32, T m33, T dx, T dy, T dz)
    {
        m_m11 = m11;
        m_m12 = m12;
        m_m13 = m13;
        m_m21 = m21;
        m_m22 = m22;
        m_m23 = m23;
        m_m31 = m31;
        m_m32 = m32;
        m_m33 = m33;
        m_dx = dx;
        m_dy = dy;
        m_dz = dz;
    }

    /// @brief 平移矩阵
    /// @param offset
    GsMatrix3DT(T *offset)
    {
        Elements(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0);
        Translate(offset[0], offset[1], offset[2]);
    }

    /// @brief 求绕任意任意矢量(x,y,z)旋转angle的变换
    /// @brief 假定坐标轴为右手系,angle单位为弧度
    /// @param angle
    /// @param x
    /// @param y
    /// @param z
    GsMatrix3DT(T angle, T x, T y, T z)
    {
        Elements(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0);
        Rotate(angle, x, y, z);
    }
    /// @brief 缩放矩阵
    /// @param scalex
    /// @param scaley
    /// @param scalez
    GsMatrix3DT(T scalex, T scaley, T scalez)
    {
        m_m11 = scalex;
        m_m12 = 0;
        m_m13 = 0;
        m_m21 = 0;
        m_m22 = scaley;
        m_m23 = 0;
        m_m31 = 0;
        m_m32 = 0;
        m_m33 = scalez;
        m_dx = 0;
        m_dy = 0;
        m_dz = 0;
    }

    /// @brief 为矩阵12元素赋值
    /// @param m11
    /// @param m12
    /// @param m13
    /// @param m21
    /// @param m22
    /// @param m23
    /// @param m31
    /// @param m32
    /// @param m33
    /// @param dx
    /// @param dy
    /// @param dz
    /// @return
    GsMatrix3DT<T> &Elements(T m11, T m12, T m13, T m21, T m22, T m23, T m31, T m32, T m33, T dx, T dy, T dz)
    {
        m_m11 = m11;
        m_m12 = m12;
        m_m13 = m13;
        m_m21 = m21;
        m_m22 = m22;
        m_m23 = m23;
        m_m31 = m31;
        m_m32 = m32;
        m_m33 = m33;
        m_dx = dx;
        m_dy = dy;
        m_dz = dz;
        return *this;
    }
    /// @brief 为矩阵12元素赋值
    /// @param m11
    /// @param m12
    /// @param m13
    /// @param m21
    /// @param m22
    /// @param m23
    /// @param m31
    /// @param m32
    /// @param m33
    /// @param dx
    /// @param dy
    /// @param dz
    /// @return
    template<class U>
    GsMatrix3DT<T> &ElementsT(U *m11, U *m12, U *m13, U *m21, U *m22, U *m23, U *m31, U *m32, U *m33, U *dx, U *dy, U *dz)
    {
        m_m11 = m11;
        m_m12 = m12;
        m_m13 = m13;
        m_m21 = m21;
        m_m22 = m22;
        m_m23 = m23;
        m_m31 = m31;
        m_m32 = m32;
        m_m33 = m33;
        m_dx = dx;
        m_dy = dy;
        m_dz = dz;
        return *this;
    }
    /// @brief 为矩阵12元素赋值
    /// @param m
    /// @return
    template<class U>

    GsMatrix3DT<T> &ElementsT(const U *m)
    {
        for (int i = 0; i < 12; i++)
        {
            m_m[i] = m[i];
        }
        return *this;
    }


    /// @brief 得到矩阵12元素
    /// @param m
    /// @return
    bool Elements(T *m) const
    {
        memcpy(m, m_m, sizeof(T) * 12);
        return true;
    }

    /// @brief 以模板得到矩阵12元素
    /// @param m
    /// @return
    template<class U>
    bool ElementsT(U *m) const
    {
        for (int i = 0; i < 12; i++)
        {
            m[i] = m_m[i];
        }
        return true;
    }

    /// @brief 以模板得到矩阵12元素
    /// @param m11
    /// @param m12
    /// @param m13
    /// @param m21
    /// @param m22
    /// @param m23
    /// @param m31
    /// @param m32
    /// @param m33
    /// @param dx
    /// @param dy
    /// @param dz
    /// @return
    template<class U>
    bool ElementsT(U *m11, U *m12, U *m13, U *m21, U *m22, U *m23, U *m31, U *m32, U *m33, U *dx, U *dy, U *dz) const
    {
        if (m11)
        {
            *m11 = m_m11;
        }
        if (m12)
        {
            *m12 = m_m12;
        }
        if (m13)
        {
            *m13 = m_m13;
        }
        if (m21)
        {
            *m21 = m_m21;
        }
        if (m22)
        {
            *m22 = m_m22;
        }
        if (m23)
        {
            *m23 = m_m23;
        }
        if (m31)
        {
            *m31 = m_m31;
        }
        if (m32)
        {
            *m32 = m_m32;
        }
        if (m33)
        {
            *m33 = m_m33;
        }
        if (dx)
        {
            *dx = m_dx;
        }
        if (dy)
        {
            *dy = m_dy;
        }
        if (dz)
        {
            *dz = m_dz;
        }
        return true;
    }

    /// @brief 获取矩阵数据的指针
    /// @return
    const T *Ptr() const
    {
        return m_m;
    }

    /// @brief
    /// @param angle
    /// @return
    GsMatrix3DT<T> &Rotate(T angle)
    {
        Rotate(angle, 0, 0, 0);
        return *this;
    }
    /// @brief 三轴旋转angleX,angleY,angleZ为X,Y,Z轴的旋转角度，不旋转则设为0
    /// @param angleX
    /// @param angleY
    /// @param angleZ
    /// @return
    GsMatrix3DT<T> &Rotate(T angleX, T angleY, T angleZ)
    {
        //得到12元素
        T m[12] = {m_m[0], m_m[1], m_m[2], m_m[3], m_m[4], m_m[5], m_m[6], m_m[7], m_m[8], m_m[9], m_m[10], m_m[11]};

        double a1 = cos(angleY) * cos(angleZ);
        double a2 = -cos(angleY) * sin(angleZ);
        double a3 = sin(angleY);
        double b1 = sin(angleX) * sin(angleY) * cos(angleZ) + cos(angleX) * sin(angleZ);
        double b2 = -sin(angleX) * sin(angleY) * sin(angleZ) + cos(angleX) * cos(angleZ);
        double b3 = -sin(angleX) * cos(angleY);
        double c1 = -cos(angleX) * sin(angleY) * cos(angleZ) + sin(angleX) * sin(angleZ);
        double c2 = cos(angleX) * sin(angleY) * sin(angleZ) + sin(angleX) * cos(angleZ);
        double c3 = cos(angleX) * cos(angleY);

        m_m11 = m[0] * a1 + m[1] * a2 + m[2] * a3;
        m_m12 = m[0] * b1 + m[1] * b2 + m[2] * b3;
        m_m13 = m[0] * c1 + m[1] * c2 + m[2] * c3;
        m_m21 = m[3] * a1 + m[4] * a2 + m[5] * a3;
        m_m22 = m[3] * b1 + m[4] * b2 + m[5] * b3;
        m_m23 = m[3] * c1 + m[4] * c2 + m[5] * c3;
        m_m31 = m[6] * a1 + m[7] * a2 + m[8] * a3;
        m_m32 = m[6] * b1 + m[7] * b2 + m[8] * b3;
        m_m33 = m[6] * c1 + m[7] * c2 + m[8] * c3;
        m_dx = m[9] * a1 + m[10] * a2 + m[11] * a3;
        m_dy = m[9] * b1 + m[10] * b2 + m[11] * b3;
        m_dz = m[9] * c1 + m[10] * c2 + m[11] * c3;
        return *this;
    }
    /// @brief 求绕任意任意矢量(x,y,z)旋转angle的变换
    /// @param angle 旋转角度，单位弧度
    /// @param xyz 表示旋转轴位置的3维向量
    /// @return 变换矩阵
    GsMatrix3DT<T> &Rotate(T angle, T *xyz)
    {
        double x = xyz[0];
        double y = xyz[1];
        double z = xyz[2];
        //得到12元素
        T m[12] = {m_m[0], m_m[1], m_m[2], m_m[3], m_m[4], m_m[5], m_m[6], m_m[7], m_m[8], m_m[9], m_m[10], m_m[11]};
        double c = cos(angle);
        double s = sin(angle);
        ///旋转矩阵
        double a1 = x * x * (1 - c) + c, a2 = x * y * (1 - c) - z * s, a3 = x * z * (1 - c) + y * s;
        double b1 = y * x * (1 - c) + z * s, b2 = y * y * (1 - c) + c, b3 = y * z * (1 - c) - x * s;
        double c1 = x * z * (1 - c) - y * s, c2 = y * z * (1 - c) + x * s, c3 = z * z * (1 - c) + c;
        m_m11 = m[0] * a1 + m[1] * a2 + m[2] * a3;
        m_m12 = m[0] * b1 + m[1] * b2 + m[2] * b3;
        m_m13 = m[0] * c1 + m[1] * c2 + m[2] * c3;
        m_m21 = m[3] * a1 + m[4] * a2 + m[5] * a3;
        m_m22 = m[3] * b1 + m[4] * b2 + m[5] * b3;
        m_m23 = m[3] * c1 + m[4] * c2 + m[5] * c3;
        m_m31 = m[6] * a1 + m[7] * a2 + m[8] * a3;
        m_m32 = m[6] * b1 + m[7] * b2 + m[8] * b3;
        m_m33 = m[6] * c1 + m[7] * c2 + m[8] * c3;
        m_dx = m[9] * a1 + m[10] * a2 + m[11] * a3;
        m_dy = m[9] * b1 + m[10] * b2 + m[11] * b3;
        m_dz = m[9] * c1 + m[10] * c2 + m[11] * c3;
        return *this;
    }
    /// @brief
    /// @param offsetX
    /// @param offsetY
    /// @param offsetZ
    /// @return
    GsMatrix3DT<T> &Translate(T offsetX, T offsetY, T offsetZ)
    {
        //计算平移
        m_dx += offsetX;
        m_dy += offsetY;
        m_dz += offsetZ;

        return *this;
    }
    /// @brief 仿射变换矩阵缩放
    /// @param scaleX x轴上缩放量
    /// @param scaleY y轴上缩放量
    /// @param scaleZ
    /// @return
    GsMatrix3DT<T> &Scale(T scaleX, T scaleY, T scaleZ)
    {
        //计算缩放
        m_m11 *= scaleX;
        m_m21 *= scaleX;
        m_m31 *= scaleX;
        m_dx *= scaleX;
        m_m12 *= scaleY;
        m_m22 *= scaleY;
        m_m32 *= scaleY;
        m_dy *= scaleY;
        m_m13 *= scaleZ;
        m_m23 *= scaleZ;
        m_m33 *= scaleZ;
        m_dz *= scaleZ;

        return *this;
    }

    /// @brief
    /// @param offsetX
    /// @param offsetY
    /// @param offsetZ
    /// @return
    static GsMatrix3DT<T> DoTranslate(T offsetX, T offsetY, T offsetZ)
    {
        GsMatrix3DT<T> mx;
        mx.Translate(offsetX, offsetY, offsetZ);
        return mx;
    }

    /// @brief 生成缩放矩阵
    /// @param scaleX x轴上缩放量
    /// @param scaleY y轴上缩放量
    /// @param scaleZ
    /// @return
    static GsMatrix3DT<T> DoScale(T scaleX, T scaleY, T scaleZ)
    {
        GsMatrix3DT<T> mx;
        mx.Scale(scaleX, scaleY, scaleZ);
        return mx;
    }

    /// @brief 生成一个旋转矩阵
    /// @param angle 矩阵旋转角度单位（弧度）
    /// @param angleX
    /// @param angleY
    /// @param angleZ
    /// @return
    static GsMatrix3DT<T> DoRotate(T angleX, T angleY, T angleZ)
    {
        GsMatrix3DT<T> mx;
        mx.Rotate(angleX, angleY, angleZ);
        return mx;
    }
    /// @brief 生成一个旋转矩阵
    /// @param angle 矩阵旋转角度单位（弧度）
    /// @param xyz 表示旋转轴位置的3维向量
    /// @return 变换矩阵
    static GsMatrix3DT<T> DoRotate(T angle, T *xyz)
    {
        GsMatrix3DT<T> mx;
        mx.Rotate(angle, xyz);
        return mx;
    }

    /// @brief 矩阵初始化，导入一个单位矩阵
    /// @return
    GsMatrix3DT<T> &Reset()
    {
        Elements(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0);
        return *this;
    }

    /// @brief 矩阵相乘(左乘）
    /// @param matrix
    /// @return
    GsMatrix3DT &LeftMultiply(const GsMatrix3DT<T> &matrix)
    {
        GsMatrix3DT<T> mx(matrix);
        mx.Multiply(*this);
        *this = mx;
        return *this;
    }
    /// @brief 矩阵相乘(右乘）
    /// @param matrix
    /// @return
    GsMatrix3DT &Multiply(const GsMatrix3DT<T> &matrix)
    {
        //当前矩阵乘以目标矩阵
        T m[12] = {m_m[0], m_m[1], m_m[2], m_m[3], m_m[4], m_m[5], m_m[6], m_m[7], m_m[8], m_m[9], m_m[10], m_m[11]};

        //相乘计算
        m_m11 = m[0] * matrix.m_m11 + m[1] * matrix.m_m21 + m[2] * matrix.m_m31;
        m_m12 = m[0] * matrix.m_m12 + m[1] * matrix.m_m22 + m[2] * matrix.m_m32;
        m_m13 = m[0] * matrix.m_m13 + m[1] * matrix.m_m23 + m[2] * matrix.m_m33;
        m_m21 = m[3] * matrix.m_m11 + m[4] * matrix.m_m21 + m[5] * matrix.m_m31;
        m_m22 = m[3] * matrix.m_m12 + m[4] * matrix.m_m22 + m[5] * matrix.m_m32;
        m_m23 = m[3] * matrix.m_m13 + m[4] * matrix.m_m23 + m[5] * matrix.m_m33;
        m_m31 = m[6] * matrix.m_m11 + m[7] * matrix.m_m21 + m[8] * matrix.m_m31;
        m_m32 = m[6] * matrix.m_m12 + m[7] * matrix.m_m22 + m[8] * matrix.m_m32;
        m_m33 = m[6] * matrix.m_m13 + m[7] * matrix.m_m23 + m[8] * matrix.m_m33;

        m_dx = m[9] * matrix.m_m11 + m[10] * matrix.m_m21 + m[11] * matrix.m_m31 + matrix.m_dx;
        m_dy = m[9] * matrix.m_m12 + m[10] * matrix.m_m22 + m[11] * matrix.m_m32 + matrix.m_dy;
        m_dz = m[9] * matrix.m_m13 + m[10] * matrix.m_m23 + m[11] * matrix.m_m33 + matrix.m_dz;

        return *this;
    }

    /// @brief 矩阵乘法操作符
    /// @param matrix
    /// @return
    GsMatrix3DT operator*(const GsMatrix3DT &matrix) const
    {
        GsMatrix3DT out(*this);
        return out.Multiply(matrix);
    }

    /// @brief 点变换
    /// @param pts
    /// @param count
    /// @return
    template<class Q>
    bool TransformPointsT(Q *pts, int count) const
    {
        for (int i = 0; i < count; i++)
        {
            Q x = pts[3 * i];
            Q y = pts[3 * i + 1];
            Q z = pts[3 * i + 2];
            pts[3 * i] = x * m_m11 + y * m_m21 + z * m_m31 + m_dx;
            pts[3 * i + 1] = x * m_m12 + y * m_m22 + z * m_m32 + m_dy;
            pts[3 * i + 2] = x * m_m13 + y * m_m23 + z * m_m33 + m_dz;
        }
        return true;
    }

    //第y行第x列的代数余子式的行列式
    static double Det(const T *M, int x, int y)
    {
        int x0, x1, y0, y1;
        double m;
        y0 = (y + 1) % 3;
        y1 = (y + 2) % 3;
        x0 = (x + 1) % 3;
        x1 = (x + 2) % 3;
        y0 *= 3;
        y1 *= 3;
        m = (T) M[y0 + x0] * M[y1 + x1];
        m -= (T) M[y0 + x1] * M[y1 + x0];
        return m;
    }

    //行列式
    T Det() const
    {
        const T *M = (T *) m_m;
        return M[0] * Det(M, 0, 0) + M[1] * Det(M, 1, 0) + M[2] * Det(M, 2, 0);
    }

    //矩阵的逆
    GsMatrix3DT<T> Invert() const
    {
        T M[9], D[3], d, *p;
        int i;
        if (0 == (d = Det()))
        {
            return GsMatrix3DT<T>(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        }
        for (d = 1.0 / d, i = 0; i < 9; ++i)
        {
            M[i] = Det(m_m, i / 3, i % 3) * d;
        };
        for (i = 0; i < 3; ++i)
        {
            p = M + i;
            D[i] = p[0] * m_dx + p[3] * m_dy + p[6] * m_dz;
            D[i] = -D[i];
        }
        return GsMatrix3DT<T>(M[0], M[1], M[2], M[3], M[4], M[5], M[6], M[7], M[8], D[0], D[1], D[2]);
    }
};

/// @brief 单精度矩阵
typedef GsMatrix3DT<float> GsMatrix3D;
/// @brief 双精度矩阵
typedef GsMatrix3DT<double> GsMatrix3DD;


/// @brief 支持对象设置矩阵，对象析构时恢复。
/// @tparam O
/// @tparam M
template<typename O, typename M>
class TransformLayer
{
    O *m_TransObject;
    M m_MatrixOri;

    /// @brief 响应此事件向Display上绘制数据不会记录到Cache中
    GsDelegate<void(const M &)> OnSetTransform;

    /// @brief
    GsDelegate<M()> OnGetTransform;

public:
    /// @brief
    /// @param t
    /// @param mx
    TransformLayer(O *t, const M &mx)
    {
        m_TransObject = t;
        if (t)
        {
            m_MatrixOri = t->Transform();
            t->Transform(mx);
        }
    }

    /// @brief
    /// @param t
    TransformLayer(O *t)
    {
        m_TransObject = t;
        if (t)
        {
            m_MatrixOri = t->Transform();
        }
    }

    /// @brief 恢复矩阵
    void Restore()
    {
        if (!m_TransObject)
        {
            return;
        }
        m_TransObject->Transform(m_MatrixOri);
        m_TransObject = NULL;
    }

    ~TransformLayer()
    {
        Restore();
    }
};


}// namespace Utility
}// namespace Lite
