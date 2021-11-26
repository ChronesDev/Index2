#pragma once

#include <thread>

#include "../../helpers/include.cc"
#include "../timepoint/timepoint.cc"

namespace Index
{
    struct TimeI
    {
    public:
        TimePoint GetNow() const { return TimePoint::Now(); }
        INDEX_Property(get = GetNow) TimePoint Now;

    public:
        void Delay(TimeSpan duration) const { std::this_thread::sleep_for(duration.StdDuration); }
    };

    inline const TimeI Time = {};
}