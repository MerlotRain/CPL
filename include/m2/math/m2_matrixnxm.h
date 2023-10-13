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

#ifndef M2_MATRIXNXM_H_
#define M2_MATRIXNXM_H_

namespace m2 {

template<int N, int M, typename T>
class MatrixNxM
{
public:
    MatrixNxM();
    explicit MatrixNxM(const T *values);

    const T &operator()(int row, int column) const;
    T &operator()(int row, int column);

    bool isIdentity() const;
    void setToIdentity();

    void fill(T value);

    [[nodiscard]] MatrixNxM<M, N, T> transposed() const;

    MatrixNxM<N, M, T> &operator+=(const MatrixNxM<N, M, T> &other);
    MatrixNxM<N, M, T> &operator-=(const MatrixNxM<N, M, T> &other);
    MatrixNxM<N, M, T> &operator*=(T factor);
    MatrixNxM<N, M, T> &operator/=(T divisor);
    bool operator==(const MatrixNxM<N, M, T> &other) const;
    bool operator!=(const MatrixNxM<N, M, T> &other) const;

    void copyTo(T *values) const;

    T *data() { return *m; }
    const T *data() const { return *m; }
    const T *constData() const { return *m; }

    template<int NN, int MM, typename TT>
    friend MatrixNxM<NN, MM, TT> operator+(const MatrixNxM<NN, MM, TT> &m1,
                                           const MatrixNxM<NN, MM, TT> &m2);
    template<int NN, int MM, typename TT>
    friend MatrixNxM<NN, MM, TT> operator-(const MatrixNxM<NN, MM, TT> &m1,
                                           const MatrixNxM<NN, MM, TT> &m2);
    template<int NN, int M1, int M2, typename TT>
    friend MatrixNxM<M1, M2, TT> operator*(const MatrixNxM<NN, M2, TT> &m1,
                                           const MatrixNxM<M1, NN, TT> &m2);
    template<int NN, int MM, typename TT>
    friend MatrixNxM<NN, MM, TT> operator-(const MatrixNxM<NN, MM, TT> &matrix);
    template<int NN, int MM, typename TT>
    friend MatrixNxM<NN, MM, TT> operator*(TT factor,
                                           const MatrixNxM<NN, MM, TT> &matrix);
    template<int NN, int MM, typename TT>
    friend MatrixNxM<NN, MM, TT> operator*(const MatrixNxM<NN, MM, TT> &matrix,
                                           TT factor);
    template<int NN, int MM, typename TT>
    friend MatrixNxM<NN, MM, TT> operator/(const MatrixNxM<NN, MM, TT> &matrix,
                                           TT divisor);

private:
    T m[N][M];

    template<int NN, int MM, typename TT>
    friend class MatrixNxM;
};

template<int N, int M, typename T>
inline MatrixNxM<N, M, T>::MatrixNxM()
{
    setToIdentity();
}

template<int N, int M, typename T>
inline MatrixNxM<N, M, T>::MatrixNxM(const T *values)
{
    for (int col = 0; col < N; ++col)
        for (int row = 0; row < M; ++row) m[col][row] = values[row * N + col];
}

template<int N, int M, typename T>
inline const T &MatrixNxM<N, M, T>::operator()(int row, int column) const
{
    assert(row >= 0 && row < M && column >= 0 && column < N);
    return m[column][row];
}

template<int N, int M, typename T>
inline T &MatrixNxM<N, M, T>::operator()(int row, int column)
{
    assert(row >= 0 && row < M && column >= 0 && column < N);
    return m[column][row];
}

template<int N, int M, typename T>
inline bool MatrixNxM<N, M, T>::isIdentity() const
{
    for (int col = 0; col < N; ++col)
    {
        for (int row = 0; row < M; ++row)
        {
            if (row == col)
            {
                if (m[col][row] != 1.0f) return false;
            }
            else
            {
                if (m[col][row] != 0.0f) return false;
            }
        }
    }
    return true;
}

template<int N, int M, typename T>
inline void MatrixNxM<N, M, T>::setToIdentity()
{
    for (int col = 0; col < N; ++col)
    {
        for (int row = 0; row < M; ++row)
        {
            if (row == col) m[col][row] = 1.0f;
            else
                m[col][row] = 0.0f;
        }
    }
}

template<int N, int M, typename T>
inline void MatrixNxM<N, M, T>::fill(T value)
{
    for (int col = 0; col < N; ++col)
        for (int row = 0; row < M; ++row) m[col][row] = value;
}

template<int N, int M, typename T>
inline MatrixNxM<M, N, T> MatrixNxM<N, M, T>::transposed() const
{
    MatrixNxM<M, N, T> result(Qt::Uninitialized);
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col) result.m[row][col] = m[col][row];
    return result;
}

template<int N, int M, typename T>
inline MatrixNxM<N, M, T> &
MatrixNxM<N, M, T>::operator+=(const MatrixNxM<N, M, T> &other)
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col) m[col][row] += other.m[col][row];
    return *this;
}

template<int N, int M, typename T>
inline MatrixNxM<N, M, T> &
MatrixNxM<N, M, T>::operator-=(const MatrixNxM<N, M, T> &other)
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col) m[col][row] -= other.m[col][row];
    return *this;
}

template<int N, int M, typename T>
inline MatrixNxM<N, M, T> &MatrixNxM<N, M, T>::operator*=(T factor)
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col) m[col][row] *= factor;
    return *this;
}

template<int N, int M, typename T>
inline bool
MatrixNxM<N, M, T>::operator==(const MatrixNxM<N, M, T> &other) const
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
        {
            if (m[col][row] != other.m[col][row]) return false;
        }
    return true;
}

template<int N, int M, typename T>
inline bool
MatrixNxM<N, M, T>::operator!=(const MatrixNxM<N, M, T> &other) const
{
    return !(*this == other);
}

template<int N, int M, typename T>
inline MatrixNxM<N, M, T> &MatrixNxM<N, M, T>::operator/=(T divisor)
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col) m[col][row] /= divisor;
    return *this;
}

template<int N, int M, typename T>
inline MatrixNxM<N, M, T> operator+(const MatrixNxM<N, M, T> &m1,
                                    const MatrixNxM<N, M, T> &m2)
{
    MatrixNxM<N, M, T> result(Qt::Uninitialized);
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            result.m[col][row] = m1.m[col][row] + m2.m[col][row];
    return result;
}

template<int N, int M, typename T>
inline MatrixNxM<N, M, T> operator-(const MatrixNxM<N, M, T> &m1,
                                    const MatrixNxM<N, M, T> &m2)
{
    MatrixNxM<N, M, T> result(Qt::Uninitialized);
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            result.m[col][row] = m1.m[col][row] - m2.m[col][row];
    return result;
}

template<int N, int M1, int M2, typename T>
inline MatrixNxM<M1, M2, T> operator*(const MatrixNxM<N, M2, T> &m1,
                                      const MatrixNxM<M1, N, T> &m2)
{
    MatrixNxM<M1, M2, T> result(Qt::Uninitialized);
    for (int row = 0; row < M2; ++row)
    {
        for (int col = 0; col < M1; ++col)
        {
            T sum(0.0f);
            for (int j = 0; j < N; ++j) sum += m1.m[j][row] * m2.m[col][j];
            result.m[col][row] = sum;
        }
    }
    return result;
}

template<int N, int M, typename T>
inline MatrixNxM<N, M, T> operator-(const MatrixNxM<N, M, T> &matrix)
{
    MatrixNxM<N, M, T> result(Qt::Uninitialized);
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            result.m[col][row] = -matrix.m[col][row];
    return result;
}

template<int N, int M, typename T>
inline MatrixNxM<N, M, T> operator*(T factor, const MatrixNxM<N, M, T> &matrix)
{
    MatrixNxM<N, M, T> result(Qt::Uninitialized);
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            result.m[col][row] = matrix.m[col][row] * factor;
    return result;
}

template<int N, int M, typename T>
inline MatrixNxM<N, M, T> operator*(const MatrixNxM<N, M, T> &matrix, T factor)
{
    MatrixNxM<N, M, T> result(Qt::Uninitialized);
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            result.m[col][row] = matrix.m[col][row] * factor;
    return result;
}

template<int N, int M, typename T>
inline MatrixNxM<N, M, T> operator/(const MatrixNxM<N, M, T> &matrix, T divisor)
{
    MatrixNxM<N, M, T> result(Qt::Uninitialized);
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            result.m[col][row] = matrix.m[col][row] / divisor;
    return result;
}

template<int N, int M, typename T>
inline void MatrixNxM<N, M, T>::copyTo(T *values) const
{
    for (int col = 0; col < N; ++col)
        for (int row = 0; row < M; ++row)
            values[row * N + col] = T(m[col][row]);
}

typedef MatrixNxM<2, 2, double> Matrix2x2;
typedef MatrixNxM<2, 3, double> Matrix2x3;
typedef MatrixNxM<2, 4, double> Matrix2x4;
typedef MatrixNxM<3, 2, double> Matrix3x2;
typedef MatrixNxM<3, 3, double> Matrix3x3;
typedef MatrixNxM<3, 4, double> Matrix3x4;
typedef MatrixNxM<4, 2, double> Matrix4x2;
typedef MatrixNxM<4, 3, double> Matrix4x3;


}// namespace m2

#endif//M2_MATRIXNXM_H_