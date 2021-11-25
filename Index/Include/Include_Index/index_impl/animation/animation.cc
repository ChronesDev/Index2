#pragma once

#include "../core/include.cc"
#include "../std/include.cc"
#include "../time/include.cc"

#include "transition.cc"

namespace Index
{
    template <class TTransition> struct IAnimation : TTransition
    {
        using TType = typename TTransition::T;

    };


}