#pragma once

#include <chrono>

#include "../../helpers/include.cc"
#include "../timepoint/timepoint.cc"

namespace Index
{
    const inline struct TimeHelper
    {
    public:
        TimePoint GetNow() const { return TimePoint::Now(); }
        INDEX_Property(get = GetNow) TimePoint Now;
    }
    Time;
}