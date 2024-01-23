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
** copy of this software and associated documentation files (the "Software"), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
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

#ifndef M2_RANDOM_H_
#define M2_RANDOM_H_

namespace m2 {

class Random
{
    unsigned short int m_Seed[7];

public:
    Random();
    Random(int seed);
    Random(unsigned short seed[7]);
    Random(const Random &rhs);
    Random(Random &&rhs) noexcept;
    Random &operator=(Random &&rhs) noexcept;
    Random &operator=(const Random &rhs);
    ~Random();

    void swap(Random &rhs);

    void xseed(unsigned short seed[3]);
    const unsigned short *seed() const;
    const unsigned short *xseed() const;

    int lRand48() noexcept;
    int nRand48(unsigned short xseed[3]) noexcept;

    int mRand48() noexcept;
    int jRand48(unsigned short xseed[3]) noexcept;

    double dRand48() noexcept;
    double eRand48(unsigned short xseed[3]) noexcept;

    int next();
    int next(int minValue, int maxValue);
    double next(double minValue, double maxValue);
    double nextDouble();
    void nextBytes(unsigned char *bytes, int nLen);
};

}// namespace m2

#endif//M2_RANDOM_H_