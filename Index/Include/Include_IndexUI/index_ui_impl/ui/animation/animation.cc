#pragma once

#include "ianimation.cc"

namespace Index::UI
{
    template <class TTransition, class TElement, class TType, void (TElement::*TSetter)(TType),
        TType (TElement::*TGetter)()>
    struct UIAnimation : virtual IUIAnimation
    {
    protected:
        TElement* Element_ = nullptr;

    protected:
        TType CachedValue_ = {};

        void Tick() override
        {
            if (Element_ == nullptr) INDEX_THROW("Element_ was nullptr.");
            if (!IsPlaying) return;

            auto currentValue = TGetter(Element_);
            if (currentValue != CachedValue_)
            {
                Stop();
                return;
            }
        }

    protected:
        TTransition Transition_;
        TimeSpan Duration_;

        bool HasBegun_ = false;
        bool HasStopped_ = false;
        bool HasFinished_ = false;

        bool IsPlaying_ = false;
        bool IsPaused_ = false;

        float Progress_ = 0;

        TimePoint StartPoint_ = Time.Now;

    public:
        TTransition GetTransition() const { return Transition_; }
        void SetTransition(TTransition value) { Transition_ = value; }
        INDEX_Property(get = GetTransition, put = SetTransition) TTransition Transition;

        bool GetHasBegun() const override { return HasBegun_; }
        bool GetHasStopped() const override { return HasStopped_; }
        bool GetHasFinished() const override { return HasFinished_; }

        bool GetIsPlaying() const override { return IsPlaying_; }
        bool GetIsPaused() const override { return IsPaused_; }

        float GetProgress() const override { return Progress_; }
        float GetRealProgress() const override
        {
            if (!IsPlaying) return 0;
            if (Duration_.Sec == 0) return 1;
            return Clamp<float>((Time.Now - StartPoint_).Sec / Duration_.Sec, 0, 1);
        }

        void Play() override { }
        void Pause() override { }
        void Stop() override
        {
            HasBegun_ = false;
            HasStopped_ = true;
            HasFinished_ = false;
            IsPlaying_ = false;
        }
        void Replay() override
        {
            Stop();
            Play();
        }

    protected:
        void Reset_()
        {
            HasBegun_ = false;
            HasStopped_ = false;
            HasFinished_ = false;

            IsPlaying_ = false;
            IsPaused_ = false;

            Progress_ = 0;
        }

        void Play_()
        {
            if (IsPlaying) return;
            Reset_();

            HasBegun_ = true;
            IsPlaying_ = true;

            StartPoint_ = Time.Now;
        }
    };
}