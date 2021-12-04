#pragma once

#include "../core/include.cc"
#include "../std/include.cc"
#include "../time/include.cc"

#include "transition.cc"

#define INDEX_MakeEasingAnimation(animation, easing)                                                                  \
    struct easing##animation : animation<Index::easing##Easing>                                                       \
    {                                                                                                                 \
        using animation<Index::easing##Easing>::animation;                                                            \
    };

#define INDEX_MakeEasingAnimationInOut(transition, easing_name)                                                      \
    INDEX_MakeEasingAnimation(transition, easing_name##In);                                                          \
    INDEX_MakeEasingAnimation(transition, easing_name##Out);                                                         \
    INDEX_MakeEasingAnimation(transition, easing_name##InOut);

namespace Index
{
    template <class TTransition> struct IAnimation : public TTransition
    {
        using TType = typename TTransition::T;

        using TTransition::TTransition;
        IAnimation() = default;
        IAnimation(TType from, TType to)
            : TTransition(from, to)
        {
        }
        IAnimation(TType from, TType to, TimeSpan duration)
            : TTransition(from, to)
            , Duration(duration)
        {
        }

        TimeSpan Duration = TimeSpan::Zero();

    protected:
        Nullable<TimePoint> StartPoint_;
        bool HasFinished_ = false;

    public:
        bool GetIsPlaying() { return StartPoint_.HasValue && !GetHasFinished(); }
        INDEX_Property(get = GetIsPlaying) bool IsPlaying;

        TimePoint GetStartPoint() const { return StartPoint_.template ValueOr(Time.Now); }
        INDEX_Property(get = GetStartPoint) TimePoint StartPoint;

        TType GetValue()
        {
            auto now = Time.Now;
            if (HasFinished) return this->To;
            if (!IsPlaying) throw std::exception("Cannot get Value while Animation is not playing.");
            if (Duration.RawDuration == 0) return this->To;
            TTransition::operator()(Index::Clamp((now - StartPoint_.Value).RawDuration / Duration.RawDuration, 0.0, 1.0));
        }
        INDEX_Property(get = GetValue) TType Value;

        TType ValueOr(TType other)
        {
            auto now = Time.Now;
            if (!IsPlaying) return other;
            if (Duration.RawDuration == 0) return this->To;
            TTransition::operator()(Index::Clamp((now - StartPoint_.Value).RawDuration / Duration.RawDuration, 0.0, 1.0));
        }

        bool GetHasFinished()
        {
            auto now = Time.Now;
            if (HasFinished_) return true;
            if (!StartPoint_.HasValue) return false;
            if (now - StartPoint_.Value > Duration)
            {
                HasFinished_ = true;
                StartPoint_ = Null;
                return true;
            }
            return false;
        }
        INDEX_Property(get = GetHasFinished) bool HasFinished;

    public:
        void Start()
        {
            auto now = Time.Now;
            if (IsPlaying) throw std::exception("Animation is already playing.");
            HasFinished_ = false;
            StartPoint_ = now;
        }

        void Restart()
        {
            if (IsPlaying) Stop();
            Start();
        }

        void Stop()
        {
            if (IsPlaying)
            {
                StartPoint_ = Null;
                HasFinished_ = false;
            }
        }

        void Start(TimeSpan duration)
        {
            Duration = duration;
            Start();
        }

        void Start(TType from, TType to)
        {
            this->From = from;
            this->To = to;
        }

        void Start(TType from, TType to, TimeSpan duration)
        {
            this->From = from;
            this->To = to;
            Duration = duration;
            Start();
        }
    };

    template <class TEasing> struct Animation : IAnimation<Transition<TEasing>>
    {
        using IAnimation<Transition<TEasing>>::IAnimation;
    };

    template <class TEasing> struct AnimationF : IAnimation<TransitionF<TEasing>>
    {
        using IAnimation<TransitionF<TEasing>>::IAnimation;
    };

    template <class TEasing> struct ColorAnimation : IAnimation<ColorTransition<TEasing>>
    {
        using IAnimation<ColorTransition<TEasing>>::IAnimation;
    };

    INDEX_MakeEasingAnimation(Animation, Linear);
    INDEX_MakeEasingAnimationInOut(Animation, Sine);
    INDEX_MakeEasingAnimationInOut(Animation, Cubic);
    INDEX_MakeEasingAnimationInOut(Animation, Quint);
    INDEX_MakeEasingAnimationInOut(Animation, Circ);
    INDEX_MakeEasingAnimationInOut(Animation, Quad);
    INDEX_MakeEasingAnimationInOut(Animation, Quart);
    INDEX_MakeEasingAnimationInOut(Animation, Expo);

    INDEX_MakeEasingAnimation(AnimationF, Linear);
    INDEX_MakeEasingAnimationInOut(AnimationF, Sine);
    INDEX_MakeEasingAnimationInOut(AnimationF, Cubic);
    INDEX_MakeEasingAnimationInOut(AnimationF, Quint);
    INDEX_MakeEasingAnimationInOut(AnimationF, Circ);
    INDEX_MakeEasingAnimationInOut(AnimationF, Quad);
    INDEX_MakeEasingAnimationInOut(AnimationF, Quart);
    INDEX_MakeEasingAnimationInOut(AnimationF, Expo);

    INDEX_MakeEasingAnimation(ColorAnimation, Linear);
    INDEX_MakeEasingAnimationInOut(ColorAnimation, Sine);
    INDEX_MakeEasingAnimationInOut(ColorAnimation, Cubic);
    INDEX_MakeEasingAnimationInOut(ColorAnimation, Quint);
    INDEX_MakeEasingAnimationInOut(ColorAnimation, Circ);
    INDEX_MakeEasingAnimationInOut(ColorAnimation, Quad);
    INDEX_MakeEasingAnimationInOut(ColorAnimation, Quart);
    INDEX_MakeEasingAnimationInOut(ColorAnimation, Expo);
}