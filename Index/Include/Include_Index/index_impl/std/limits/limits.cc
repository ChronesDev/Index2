#pragma once

#include <limits>

namespace Index::Limits
{
    template<class T> consteval T MaxValueOf() {
        return std::numeric_limits<T>::max();
    }

    template<class T> consteval T MinValueOf() {
        return std::numeric_limits<T>::max();
    }
}