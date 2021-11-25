#pragma once

#include "../core/include.cc"
#include "../std/include.cc"

#include "../easing/easing.cc"

#define INDEX_MakeEasingTransition(easing)                                                                            \
    struct easing##Transition : Transition<Index::easing##Easing>                                                     \
    {                                                                                                                 \
        using Transition<Index::easing##Easing>::Transition;                                                          \
    };

#define INDEX_MakeEasingTransitionInOut(easing_name)                                                                  \
    INDEX_MakeEasingTransition(easing_name##In);                                                                      \
    INDEX_MakeEasingTransition(easing_name##Out);                                                                     \
    INDEX_MakeEasingTransition(easing_name##InOut);

namespace Index
{
    template <class TType, class TEasing> struct ITransition : TEasing
    {
        using TEasing::TEasing;
        ITransition() = default;
        ITransition(TType from, TType to)
            : From(from)
            , To(to)
        {
        }

        using T = TType;

        TType From;
        TType To;

        TType operator()(double v) const { return RawInterpolate(TEasing::operator()(v)); }

    protected:
        [[nodiscard]] virtual TType RawInterpolate(double v) const = 0;
    };

    template <class TEasing> struct Transition : ITransition<double, TEasing>
    {
        using ITransition<double, TEasing>::ITransition;

    protected:
        [[nodiscard]] double RawInterpolate(double v) const override
        {
            return (this->To - this->From) * v + this->From;
        }
    };

    template <class TEasing> struct TransitionF : ITransition<float, TEasing>
    {
        using ITransition<float, TEasing>::ITransition;

    protected:
        [[nodiscard]] float RawInterpolate(double v) const override
        {
            return (this->To - this->From) * (float)v + this->From;
        }
    };

    INDEX_MakeEasingTransitionInOut(Sine);
    INDEX_MakeEasingTransitionInOut(Cubic);
    INDEX_MakeEasingTransitionInOut(Quint);
    INDEX_MakeEasingTransitionInOut(Circ);
    INDEX_MakeEasingTransitionInOut(Quad);
    INDEX_MakeEasingTransitionInOut(Quart);
    INDEX_MakeEasingTransitionInOut(Expo);
}