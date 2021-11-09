#pragma once

#include <chrono>

#include "../../helpers/include.cc"
#include "../timespan/timespan.cc"

namespace Index
{
    struct TimePoint
    {
    protected:
        using StdChronoClock = std::chrono::high_resolution_clock;
        using StdChronoTimePoint = std::chrono::time_point<StdChronoClock>;
        using StdChronoDuration = std::chrono::duration<double>;

    private:
        TimePoint() = default;

    public:
        explicit TimePoint(StdChronoTimePoint timePoint)
            : StdTimePoint(timePoint)
        {
        }

    public:
        StdChronoTimePoint StdTimePoint;

    public:
        TimeSpan operator-(const TimePoint& other) const { return TimeSpan(StdTimePoint - other.StdTimePoint); }
        bool operator==(const TimePoint& other) const { return StdTimePoint == other.StdTimePoint; }
        bool operator!=(const TimePoint& other) const { return StdTimePoint != other.StdTimePoint; }
        bool operator<(const TimePoint& other) const { return StdTimePoint < other.StdTimePoint; }
        bool operator>(const TimePoint& other) const { return StdTimePoint > other.StdTimePoint; }
        bool operator<=(const TimePoint& other) const { return StdTimePoint <= other.StdTimePoint; }
        bool operator>=(const TimePoint& other) const { return StdTimePoint >= other.StdTimePoint; }

        TimeSpan operator^(const TimePoint& other) const
        {
            auto duration = StdTimePoint - other.StdTimePoint;
            return duration.count() >= 0 ? TimeSpan(duration) : TimeSpan(-duration);
        }

    public:
        inline static TimePoint Now() { return TimePoint(StdChronoClock::now()); }
    };
}