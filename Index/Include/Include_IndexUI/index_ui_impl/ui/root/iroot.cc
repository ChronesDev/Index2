#pragma once

#include "../../index.cc"

#include "../touchelement/touchelement.cc"

namespace Index::UI
{
    struct UIElement;

    struct IUIRoot : IObj<IUIRoot>
    {
    public:
        virtual ~IUIRoot() = default;

    public:
        virtual IPtr<UIElement> GetRootElement() const = 0;
        INDEX_Property(get = GetRootElement) IPtr<UIElement> RootElement;

    public:
        virtual void Render() = 0;
        virtual void Update() = 0;

        virtual void Compute(UInt64 frame, Rect i) = 0;
        virtual void ComputeLayout(UInt64 frame) = 0;
        virtual void ComputeLayoutPosition(Rect i) = 0;

        virtual IPtr<UIElement> ElementHitTest(Vec2F p) = 0;
        virtual HitTestResult HitTest(Vec2F p) = 0;

    public:
        virtual IPtr<UIElement> Search(UIPath path) = 0;
        virtual IPtr<UIElement> TrySearch(UIPath path) = 0;
    };
}