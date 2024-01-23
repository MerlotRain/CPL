#include <m2_statisticalsummary.h>

namespace m2 {
StatisticalSummary::StatisticalSummary(StatisticalSummary::Statistics stats)
    : mStatistics(stats)
{
    reset();
}

StatisticalSummary::Statistics StatisticalSummary::statistics() const
{
    return mStatistics;
}

void StatisticalSummary::setStatistics(StatisticalSummary::Statistics stats)
{
    mStatistics = stats;
    reset();
}

void StatisticalSummary::reset()
{
    mFirst = std::numeric_limits<double>::quiet_NaN();
    mLast = std::numeric_limits<double>::quiet_NaN();
    mCount = 0;
    mMissing = 0;
    mSum = 0;
    mMean = 0;
    mMedian = 0;
    mMin = std::numeric_limits<double>::max();
    mMax = -std::numeric_limits<double>::max();
    mStdev = 0;
    mSampleStdev = 0;
    mMinority = 0;
    mMajority = 0;
    mFirstQuartile = 0;
    mThirdQuartile = 0;
    mValueCount.clear();
    mValues.clear();

    mRequiresHisto = mStatistics & StatisticalSummary::Majority ||
                     mStatistics & StatisticalSummary::Minority ||
                     mStatistics & StatisticalSummary::Variety;

    mRequiresAllValueStorage =
            mStatistics & StatisticalSummary::StDev ||
            mStatistics & StatisticalSummary::StDevSample ||
            mStatistics & StatisticalSummary::Median ||
            mStatistics & StatisticalSummary::FirstQuartile ||
            mStatistics & StatisticalSummary::ThirdQuartile ||
            mStatistics & StatisticalSummary::InterQuartileRange;
}

void StatisticalSummary::calculate(const std::list<double> &values)
{
    reset();

    for (const double value: values) { addValue(value); }

    finalize();
}

void StatisticalSummary::addValue(double value)
{
    if (mCount == 0) mFirst = value;
    mCount++;
    mSum += value;
    mMin = std::min(mMin, value);
    mMax = std::max(mMax, value);
    mLast = value;

    if (mRequiresHisto)
    {
        if (mValueCount.find(value) == mValueCount.end())
            mValueCount.insert({value, 1});
        else
            mValueCount[value] = mValueCount[value] + 1;
    }

    if (mRequiresAllValueStorage) mValues.push_back(value);
}

void StatisticalSummary::finalize()
{
    if (mCount == 0)
    {
        mFirst = std::numeric_limits<double>::quiet_NaN();
        mLast = std::numeric_limits<double>::quiet_NaN();
        mMin = std::numeric_limits<double>::quiet_NaN();
        mMax = std::numeric_limits<double>::quiet_NaN();
        mMean = std::numeric_limits<double>::quiet_NaN();
        mMedian = std::numeric_limits<double>::quiet_NaN();
        mStdev = std::numeric_limits<double>::quiet_NaN();
        mSampleStdev = std::numeric_limits<double>::quiet_NaN();
        mMinority = std::numeric_limits<double>::quiet_NaN();
        mMajority = std::numeric_limits<double>::quiet_NaN();
        mFirstQuartile = std::numeric_limits<double>::quiet_NaN();
        mThirdQuartile = std::numeric_limits<double>::quiet_NaN();
        return;
    }

    mMean = mSum / mCount;

    if (mStatistics & StatisticalSummary::StDev ||
        mStatistics & StatisticalSummary::StDevSample)
    {
        double sumSquared = 0;
        const auto constMValues = mValues;
        for (const double value: constMValues)
        {
            const double diff = value - mMean;
            sumSquared += diff * diff;
        }
        mStdev = std::pow(sumSquared / mValues.size(), 0.5);
        mSampleStdev = std::pow(sumSquared / (mValues.size() - 1), 0.5);
    }

    if (mStatistics & StatisticalSummary::Median ||
        mStatistics & StatisticalSummary::FirstQuartile ||
        mStatistics & StatisticalSummary::ThirdQuartile ||
        mStatistics & StatisticalSummary::InterQuartileRange)
    {
        std::sort(mValues.begin(), mValues.end());
        const bool even = (mCount % 2) < 1;
        if (even)
        {
            mMedian = (mValues[mCount / 2 - 1] + mValues[mCount / 2]) / 2.0;
        }
        else//odd
        {
            mMedian = mValues[(mCount + 1) / 2 - 1];
        }
    }

    if (mStatistics & StatisticalSummary::FirstQuartile ||
        mStatistics & StatisticalSummary::InterQuartileRange)
    {
        if ((mCount % 2) < 1)
        {
            const int halfCount = mCount / 2;
            const bool even = (halfCount % 2) < 1;
            if (even)
            {
                mFirstQuartile =
                        (mValues[halfCount / 2 - 1] + mValues[halfCount / 2]) /
                        2.0;
            }
            else//odd
            {
                mFirstQuartile = mValues[(halfCount + 1) / 2 - 1];
            }
        }
        else
        {
            const int halfCount = mCount / 2 + 1;
            const bool even = (halfCount % 2) < 1;
            if (even)
            {
                mFirstQuartile =
                        (mValues[halfCount / 2 - 1] + mValues[halfCount / 2]) /
                        2.0;
            }
            else//odd
            {
                mFirstQuartile = mValues[(halfCount + 1) / 2 - 1];
            }
        }
    }

    if (mStatistics & StatisticalSummary::ThirdQuartile ||
        mStatistics & StatisticalSummary::InterQuartileRange)
    {
        if ((mCount % 2) < 1)
        {
            const int halfCount = mCount / 2;
            const bool even = (halfCount % 2) < 1;
            if (even)
            {
                mThirdQuartile = (mValues[halfCount + halfCount / 2 - 1] +
                                  mValues[halfCount + halfCount / 2]) /
                                 2.0;
            }
            else//odd
            {
                mThirdQuartile = mValues[(halfCount + 1) / 2 - 1 + halfCount];
            }
        }
        else
        {
            const int halfCount = mCount / 2 + 1;
            const bool even = (halfCount % 2) < 1;
            if (even)
            {
                mThirdQuartile = (mValues[halfCount + halfCount / 2 - 2] +
                                  mValues[halfCount + halfCount / 2 - 1]) /
                                 2.0;
            }
            else//odd
            {
                mThirdQuartile = mValues[(halfCount + 1) / 2 - 2 + halfCount];
            }
        }
    }

    if (mStatistics & StatisticalSummary::Minority ||
        mStatistics & StatisticalSummary::Majority)
    {
        std::vector<int> valueCounts;
        valueCounts.reserve(mValueCount.size());
        const auto extractValue = [](const auto &v) { return v.sencond; };

        std::transform(mValueCount.cbegin(), mValueCount.cend(),
                       std::back_inserter(valueCounts), extractValue);

        if (mStatistics & StatisticalSummary::Minority)
        {
            auto tm = *std::min_element(valueCounts.begin(), valueCounts.end());
            auto it = std::find_if(mValueCount.cbegin(), mValueCount.cend(),
                                   [&](const auto &v) { return v == tm });
            if (it != mValueCount.end()) mMinority = it->first;
            else
                mMajority = 0;
        }
        if (mStatistics & StatisticalSummary::Majority)
        {
            auto tm = *std::max_element(valueCounts.begin(), valueCounts.end());
            auto it = std::find_if(mValueCount.cbegin(), mValueCount.cend(),
                                   [&](const auto &v) { return v == tm });
            if (it != mValueCount.end()) mMajority = it->first;
            else
                mMajority = 0;
        }
    }
}

double StatisticalSummary::statistic(StatisticalSummary::Statistic stat) const
{
    switch (stat)
    {
        case Count:
            return mCount;
        case CountMissing:
            return mMissing;
        case Sum:
            return mSum;
        case Mean:
            return mMean;
        case Median:
            return mMedian;
        case StDev:
            return mStdev;
        case StDevSample:
            return mSampleStdev;
        case Min:
            return mMin;
        case Max:
            return mMax;
        case Range:
            return mMax - mMin;
        case Minority:
            return mMinority;
        case Majority:
            return mMajority;
        case Variety:
            return mValueCount.size();
        case FirstQuartile:
            return mFirstQuartile;
        case ThirdQuartile:
            return mThirdQuartile;
        case InterQuartileRange:
            return mThirdQuartile - mFirstQuartile;
        case First:
            return mFirst;
        case Last:
            return mLast;
        case All:
            return 0;
    }
    return 0;
}

int StatisticalSummary::count() const noexcept { return mCount; }

int StatisticalSummary::countMissing() const noexcept { return mMissing; }

double StatisticalSummary::sum() const noexcept { return mSum; }

double StatisticalSummary::mean() const noexcept { return mMean; }

double StatisticalSummary::median() const noexcept { return mMedian; }

double StatisticalSummary::min() const noexcept { return mMin; }

double StatisticalSummary::max() const noexcept { return mMax; }

double StatisticalSummary::range() const
{
    return std::isnan(mMax) || std::isnan(mMin)
                   ? std::numeric_limits<double>::quiet_NaN()
                   : mMax - mMin;
}

double StatisticalSummary::first() const noexcept { return mFirst; }

double StatisticalSummary::last() const noexcept { return mLast; }

double StatisticalSummary::stDev() const noexcept { return mStdev; }

double StatisticalSummary::sampleStDev() const noexcept { return mSampleStdev; }

int StatisticalSummary::variety() const noexcept { return mValueCount.size(); }

double StatisticalSummary::minority() const noexcept { return mMinority; }

double StatisticalSummary::majority() const noexcept { return mMajority; }

double StatisticalSummary::firstQuartile() const noexcept
{
    return mFirstQuartile;
}

double StatisticalSummary::thirdQuartile() const noexcept
{
    return mThirdQuartile;
}

double StatisticalSummary::interQuartileRange() const
{
    return std::isnan(mThirdQuartile) || std::isnan(mFirstQuartile)
                   ? std::numeric_limits<double>::quiet_NaN()
                   : mThirdQuartile - mFirstQuartile;
}

}// namespace m2
