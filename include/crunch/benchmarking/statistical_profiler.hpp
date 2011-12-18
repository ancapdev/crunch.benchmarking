// Copyright (c) 2011, Christian Rorvik
// Distributed under the Simplified BSD License (See accompanying file LICENSE.txt)

#ifndef CRUNCH_BENCHMARKING_STATISTICAL_PROFILER_HPP
#define CRUNCH_BENCHMARKING_STATISTICAL_PROFILER_HPP

#include "crunch/benchmarking/api.hpp"

#include <vector>

namespace Crunch { namespace Benchmarking {

class StatisticalProfiler
{
public:
    CRUNCH_BENCHMARKING_API StatisticalProfiler(double targetNormStdDev, std::size_t minSamples, std::size_t maxSamples, std::size_t samplesPerCalculation = 1);

    CRUNCH_BENCHMARKING_API void AddSample(double sample);

    CRUNCH_BENCHMARKING_API void Reset();

    CRUNCH_BENCHMARKING_API bool IsDone() const;

    CRUNCH_BENCHMARKING_API std::size_t GetNumSamples() const;
    CRUNCH_BENCHMARKING_API double GetMin() const;
    CRUNCH_BENCHMARKING_API double GetMax() const;
    CRUNCH_BENCHMARKING_API double GetMean() const;
    CRUNCH_BENCHMARKING_API double GetMedian() const;
    CRUNCH_BENCHMARKING_API double GetStdDev() const;
    CRUNCH_BENCHMARKING_API double GetRawMin() const;
    CRUNCH_BENCHMARKING_API double GetRawMax() const;
    CRUNCH_BENCHMARKING_API double GetRawMean() const;
    CRUNCH_BENCHMARKING_API double GetRawStdDev() const;

private:
    void UpdateStatistics() const;

    double mTargetStdDev;
    std::size_t mMinSamples;
    std::size_t mMaxSamples;
    std::size_t mSamplesPerCalculation;
    mutable std::vector<double> mSamples;
    mutable std::size_t mLastCalculationSize;
    mutable double mRawMin;
    mutable double mRawMax;
    mutable double mRawMean;
    mutable double mRawStdDev;
    mutable double mMin;
    mutable double mMax;
    mutable double mMean;
    mutable double mMedian;
    mutable double mStdDev;
};

inline void StatisticalProfiler::AddSample(double sample)
{
    mSamples.push_back(sample);
}

inline std::size_t StatisticalProfiler::GetNumSamples() const
{
    return mSamples.size();
}

}}

#endif
