#pragma once

#include "../core/include.cc"
#include "../std/include.cc"
#include "../time/include.cc"

#include "easing_functions/include.cc"

namespace Index
{
    template <class TClass, class TType> struct IAnimation
    {
        TType From;
        TType To;

        IAnimation(TType from, TType to)
            : From(from)
            , To(to)
        {
        }

        TType Interpolate(double v) const { return ((TClass*)this)->Lerp(From, To, v); }
        TType Interpolate(float v) const { return Interpolate((double)v); }
    };
}