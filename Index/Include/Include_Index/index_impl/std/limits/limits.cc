#pragma once

#include <limits>
#include "../../helpers/include.cc"

namespace Index::Limits
{
    template <class T> INDEX_Consteval T MaxValueOf() { return std::numeric_limits<T>::max(); }

    template <class T> INDEX_Consteval T MinValueOf() { return std::numeric_limits<T>::min(); }
}

// Standard Types
namespace Index::Limits
{
    constexpr float FloatMax = MaxValueOf<float>();
    constexpr float FloatMin = MinValueOf<float>();
    constexpr double DoubleMax = MaxValueOf<double>();
    constexpr double DoubleMin = MinValueOf<double>();
}