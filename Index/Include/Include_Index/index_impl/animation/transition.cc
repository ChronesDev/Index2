#pragma once

#include "../core/include.cc"
#include "../std/include.cc"

#include "../easing/easing.cc"

namespace Index
{
    template <class TType, class TEasing> struct ITransition : TEasing
    {
        ITransition() = default;
        ITransition(TType from, TType to)
            : From(from)
            , To(to)
        {
        }
        
        using T = TType;
        
        TType From;
        TType To;
        
        TType operator()(double v) const
        {
            Interpolate(v);
        }

    protected:
        virtual TType Interpolate(double v) const = 0;
    };
    
}