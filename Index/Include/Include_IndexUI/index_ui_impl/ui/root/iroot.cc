#pragma once

#include "../../index.cc"

namespace Index::UI
{
    struct UIElement;

    struct IUIRoot : IObj<IUIRoot>
    {
    public:
        virtual ~IUIRoot() = default;

    public:
        virtual void Render() = 0;
        virtual void Update() = 0;

        virtual void Compute(UInt64 frame, Rect i) = 0;
        virtual void ComputeLayout(UInt64 frame) = 0;
        virtual void ComputeLayoutPosition(Rect i) = 0;
    };
}