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

#ifndef M2_STATISTICS_H_
#define M2_STATISTICS_H_

#include <m2_flags.h>
#include <preconfig.h>

namespace m2 {

class LIBM2_EXPORT StatisticalSummary
{
public:
    enum Statistic
    {
        Count = 1 << 0,
        CountMissing = 1 << 15,
        Sum = 1 << 1,
        Mean = 1 << 2,
        Median = 1 << 3,
        StDev = 1 << 4,
        StDevSample = 1 << 5,
        Min = 1 << 6,
        Max = 1 << 7,
        Range = 1 << 8,
        Minority = 1 << 9,
        Majority = 1 << 10,
        Variety = 1 << 11,
        FirstQuartile = 1 << 12,
        ThirdQuartile = 1 << 13,
        InterQuartileRange = 1 << 14,
        First = 1 << 16,
        Last = 1 << 17,
        All = Count | CountMissing | Sum | Mean | Median | StDev | Max | Min |
              Range | Minority | Majority | Variety | FirstQuartile |
              ThirdQuartile | InterQuartileRange | First | Last
    };
    M2_DECLARE_FLAGS(Statistics, Statistic)

    StatisticalSummary(
            StatisticalSummary::Statistics stats = StatisticalSummary::All);
    virtual ~StatisticalSummary() = default;

    Statistics statistics() const;
    void setStatistics(StatisticalSummary::Statistics stats);

    void reset();

    void calculate(const std::list<double> &values);
    void addValue(double value);

    void finalize();

    double statistic(StatisticalSummary::Statistic stat) const;

    int count() const noexcept;

    int countMissing() const noexcept;

    double sum() const noexcept;
    double mean() const noexcept;
    double median() const noexcept;

    double min() const noexcept;
    double max() const noexcept;
    double range() const;

    double first() const noexcept;
    double last() const noexcept;
    double stDev() const noexcept;

    double sampleStDev() const noexcept;
    int variety() const noexcept;

    double minority() const noexcept;
    double majority() const noexcept;

    double firstQuartile() const noexcept;
    double thirdQuartile() const noexcept;

    double interQuartileRange() const;

private:
    Statistics mStatistics;
    int mCount;
    int mMissing;
    double mSum;
    double mMean;
    double mMedian;
    double mMin;
    double mMax;
    double mStdev;
    double mSampleStdev;
    double mMinority;
    double mMajority;
    double mFirstQuartile;
    double mThirdQuartile;
    double mFirst;
    double mLast;
    std::map<double, int> mValueCount;
    std::vector<double> mValues;
    bool mRequiresAllValueStorage = false;
    bool mRequiresHisto = false;
};

}// namespace m2

#endif//M2_STATISTICS_H_