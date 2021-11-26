#pragma once

#include "../core/include.cc"
#include "../std/include.cc"

#include "../easing/easing.cc"

#define INDEX_MakeEasingTransition(transition, easing)                                                                \
    struct easing##transition : transition<Index::easing##Easing>                                                     \
    {                                                                                                                 \
        using transition<Index::easing##Easing>::transition;                                                          \
    };

#define INDEX_MakeEasingTransitionInOut(transition, easing_name)                                                      \
    INDEX_MakeEasingTransition(transition, easing_name##In);                                                          \
    INDEX_MakeEasingTransition(transition, easing_name##Out);                                                         \
    INDEX_MakeEasingTransition(transition, easing_name##InOut);

namespace Index
{
    template <class TType, class TEasing> struct ITransition
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
        TEasing Easing = { };

        TType operator()(double v) const { return RawInterpolate(Easing.operator()(v)); }

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

    template <class TEasing> struct ColorTransition : ITransition<Color, TEasing>
    {
        using ITransition<Color, TEasing>::ITransition;

    protected:
        [[nodiscard]] Color RawInterpolate(double v) const override
        {
            Color from = this->From;
            Color to = this->To;
            return Color::Raw(Vec4F { (to.R - from.R) * (float)v + from.R, (to.G - from.G) * (float)v + from.G,
                (to.B - from.B) * (float)v + from.B, (to.A - from.A) * (float)v + from.A });
        }
    };

    INDEX_MakeEasingTransition(Transition, Linear);
    INDEX_MakeEasingTransitionInOut(Transition, Sine);
    INDEX_MakeEasingTransitionInOut(Transition, Cubic);
    INDEX_MakeEasingTransitionInOut(Transition, Quint);
    INDEX_MakeEasingTransitionInOut(Transition, Circ);
    INDEX_MakeEasingTransitionInOut(Transition, Quad);
    INDEX_MakeEasingTransitionInOut(Transition, Quart);
    INDEX_MakeEasingTransitionInOut(Transition, Expo);

    INDEX_MakeEasingTransition(TransitionF, Linear);
    INDEX_MakeEasingTransitionInOut(TransitionF, Sine);
    INDEX_MakeEasingTransitionInOut(TransitionF, Cubic);
    INDEX_MakeEasingTransitionInOut(TransitionF, Quint);
    INDEX_MakeEasingTransitionInOut(TransitionF, Circ);
    INDEX_MakeEasingTransitionInOut(TransitionF, Quad);
    INDEX_MakeEasingTransitionInOut(TransitionF, Quart);
    INDEX_MakeEasingTransitionInOut(TransitionF, Expo);

    INDEX_MakeEasingTransition(ColorTransition, Linear);
    INDEX_MakeEasingTransitionInOut(ColorTransition, Sine);
    INDEX_MakeEasingTransitionInOut(ColorTransition, Cubic);
    INDEX_MakeEasingTransitionInOut(ColorTransition, Quint);
    INDEX_MakeEasingTransitionInOut(ColorTransition, Circ);
    INDEX_MakeEasingTransitionInOut(ColorTransition, Quad);
    INDEX_MakeEasingTransitionInOut(ColorTransition, Quart);
    INDEX_MakeEasingTransitionInOut(ColorTransition, Expo);
}