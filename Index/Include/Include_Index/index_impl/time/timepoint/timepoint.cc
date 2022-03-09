#pragma once

#include <chrono>
#include <iomanip>

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
        TimePoint operator+(const TimeSpan& other) const
        {
            return TimePoint(StdTimePoint + std::chrono::nanoseconds((long long)other.Nano));
        }
        TimePoint& operator+=(const TimeSpan& other)
        {
            StdTimePoint += std::chrono::nanoseconds((long long)other.Nano);
            return *this;
        }
        TimePoint operator-(const TimeSpan& other) const
        {
            return TimePoint(StdTimePoint - std::chrono::nanoseconds((long long)other.Nano));
        }
        TimePoint& operator-=(const TimeSpan& other)
        {
            StdTimePoint -= std::chrono::nanoseconds((long long)other.Nano);
            return *this;
        }
        TimeSpan operator-(const TimePoint& other) const { return { StdTimePoint - other.StdTimePoint }; }
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

        inline static TimePoint Lerp(double v, TimePoint from, TimePoint to) { return from + (to - from).Lerp(v); }
    };

    inline std::ostream& operator<<(std::ostream& os, const TimePoint& timePoint)
    {
#if defined(INDEX_MSVC)
        os << "TimePoint {" << timePoint.StdTimePoint.time_since_epoch() << "}";
#elif defined(INDEX_Clang)
        os << "[Clang unsupported]";
#else
        auto t = std::chrono::high_resolution_clock::to_time_t(timePoint.StdTimePoint);
        os << "TimePoint {" << std::put_time(std::localtime(&t), "%F %T") << "}";
#endif
        return os;
    }
}