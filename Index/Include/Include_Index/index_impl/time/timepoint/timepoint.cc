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

    public:
        TimePoint(StdChronoTimePoint timePoint) {}

    public:

    };
}