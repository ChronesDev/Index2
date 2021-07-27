#pragma once

#include <limits>

namespace Index::Limits
{
    template<class T> consteval T MaxValueOf() {
        return std::numeric_limits<T>::max();
    }

    template<class T> consteval T MinValueOf() {
        return std::numeric_limits<T>::min();
    }
}

// Standard Types
namespace Index::Limits
{
    constexpr float FloatMax = MaxValueOf<float>();
    constexpr float FloatMin = MinValueOf<float>();
    constexpr double DoubleMax = MaxValueOf<float>();
    constexpr double DoubleMin = MinValueOf<float>();
}