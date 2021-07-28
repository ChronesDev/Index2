#include <algorithm>
#include <cmath>

namespace Index
{
    template<class T> constexpr T Min(T a, T b) {
        return a < b ? a : b;
    }

    template<class T> constexpr T Max(T a, T b) {
        return a > b ? a : b;
    }

    template<class T> constexpr T Clamp(T v, T a, T b) {
        std::clamp(v, a, b);
    }

    template<class T> constexpr T Lerp(T a, T b, T v) {
        std::lerp(a, b, v);
    }
}