#pragma once

#include "../ui.cc"

// UIElement
namespace Index::UI
{
    struct UIElement;
}

// IUIAnimatable
namespace Index::UI
{
    struct IUIAnimatable
    {
        virtual void AnimationTick() = 0;
    };
}