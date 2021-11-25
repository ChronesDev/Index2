#pragma once

#include "../core/include.cc"
#include "../helpers/include.cc"
#include "../std/include.cc"

#include "easings.cc"

#define INDEX_MakeEasingInlineClass(function)                                                                         \
    struct function##Easing : IEasing                                                                                 \
    {                                                                                                                 \
        [[nodiscard]] double operator()(double v, double from, double to) const override                              \
        {                                                                                                             \
            return (to - from) * Index::Easings::function(v) + from;                                                  \
        }                                                                                                             \
    };                                                                                                                \
    namespace Easing                                                                                                  \
    {                                                                                                                 \
        [[nodiscard]] inline double function(double v, double from, double to)                                        \
        {                                                                                                             \
            return (to - from) * Index::Easings::function(v) + from;                                                  \
        }                                                                                                             \
        template <class T> [[nodiscard]] inline T function##T(double v, T from, T to)                                 \
        {                                                                                                             \
            (to - from) * Index::Easings::function(v) + from;                                                         \
        }                                                                                                             \
    }

#define INDEX_MakeEasingInlineClassInOut(function_name)                                                               \
    INDEX_MakeEasingInlineClass(function_name##In);                                                                   \
    INDEX_MakeEasingInlineClass(function_name##Out);                                                                  \
    INDEX_MakeEasingInlineClass(function_name##InOut);

namespace Index
{
    struct IEasing
    {
        [[nodiscard]] virtual double operator()(double v, double from, double to) const = 0;
    };

    INDEX_MakeEasingInlineClassInOut(Sine);
    INDEX_MakeEasingInlineClassInOut(Cubic);
    INDEX_MakeEasingInlineClassInOut(Quint);
    INDEX_MakeEasingInlineClassInOut(Circ);
    INDEX_MakeEasingInlineClassInOut(Quad);
    INDEX_MakeEasingInlineClassInOut(Quart);
    INDEX_MakeEasingInlineClassInOut(Expo);

}