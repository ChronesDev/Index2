#pragma once

#include "../core/include.cc"
#include "../std/include.cc"
#include "../time/include.cc"

#include "transition.cc"

namespace Index
{
    template <class TTransition> class IAnimation : public TTransition
    {
        using TType = typename TTransition::T;

        using TTransition::TTransition;
        IAnimation() = default;
        IAnimation(TType from, TType to, TimeSpan duration) : TTransition(from, to), Duration(duration) { }

        TimeSpan Duration = TimeSpan::Zero();
    };


}