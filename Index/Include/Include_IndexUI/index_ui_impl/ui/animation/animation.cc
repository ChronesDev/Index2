#pragma once

#include "ianimation.cc"

namespace Index::UI
{
    template <
        class TAnimation,
        class TElement,
        class TType,
        void (TElement::*TSetter)(TType),
        TType (TElement::*TGetter)()>
    struct UIAnimation : virtual IUIAnimation
    {
    protected:
        TElement* Element_ = nullptr;

    protected:
        TType CachedValue_ = { };

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
        bool HasBegun_ = false;
        bool HasStopped_ = false;
        bool HasFinished_ = false;

        bool IsPlaying_ = false;
        bool IsPaused_ = false;

        float Progress_ = 0;

    public:
        bool GetHasBegun() const override { return HasBegun_; }
        bool GetHasStopped() const override { return HasStopped_; }
        bool GetHasFinished() const override { return HasFinished_; }

        bool GetIsPlaying() const override { return IsPlaying_; }
        bool GetIsPaused() const override { return IsPaused_; }

        float GetProgress() const override { return Progress_; }

        void Play() override { }
        void Pause() override { }
        void Stop() override { }
        void Replay() override { }
    };
}