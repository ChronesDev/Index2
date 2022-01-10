#pragma once

#include "../ui.cc"

namespace Index::UI
{
    struct IUIAnimation
    {
        virtual bool GetHasBegun() const = 0;
        INDEX_Property(get = GetHasBegun) bool HasBegun;

        virtual bool GetHasStopped() const = 0;
        INDEX_Property(get = GetHasStopped) bool HasStopped;

        virtual bool GetHasFinished() const = 0;
        INDEX_Property(get = GetHasFinished) bool HasFinished;

        virtual bool GetIsPlaying() const = 0;
        INDEX_Property(get = GetIsPlaying) bool IsPlaying;

        virtual bool GetIsPaused() const = 0;
        INDEX_Property(get = GetIsPaused) bool IsPaused;

        virtual float GetProgress() const = 0;
        INDEX_Property(get = GetProgress) float Progress;

        virtual void Play() = 0;
        virtual void Pause() = 0;
        virtual void Stop() = 0;
        virtual void Replay() = 0;

        virtual void Tick() = 0;
    };
}