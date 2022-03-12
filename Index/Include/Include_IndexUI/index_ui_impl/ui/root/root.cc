#pragma once

#include "../element/element.cc"
#include "iroot.cc"

namespace Index::UI
{
    struct UIRoot : virtual IUIRoot
    {
    public:
        ~UIRoot() override { DetachRootElement(); };

    protected:
        IPtr<UIElement> RootElement_;

    public:
        IPtr<UIElement> GetRootElement() const { return RootElement_; }
        INDEX_Property(get = GetRootElement) IPtr<UIElement> RootElement;

    public:
        virtual void AttachRootElement(IPtr<UIElement> r)
        {
            if (r.Ptr != RootElement_.Ptr) DetachRootElement();

            if (!r.IsNull) r->AttachToUIRootUpdate_(ISelf());
            RootElement_ = r;
            if (!r.IsNull) OnAttachedRootElement_(r);
        }
        virtual void DetachRootElement()
        {
            if (RootElement_.IsNull) return;
            RootElement_->DetachFromUIRootUpdate_();
            RootElement_ = IPtr<UIElement>(nullptr);
        }

    protected:
        virtual void OnAttachedRootElement_(IPtr<UIElement> r) { }
        virtual void OnDetachedRootElement_() { }

    public:
        void Render() override
        {
            if (RootElement_.IsNull) return;
            RootElement_->Render();
        }
        void Update() override
        {
            if (RootElement_.IsNull) return;
            RootElement_->Update();
        }

        void Compute(UInt64 frame, Rect i) override
        {
            if (RootElement_.IsNull) return;
            RootElement_->ComputeLayout(frame);
            RootElement_->ComputeLayoutPosition(i);
        }
        void ComputeLayout(UInt64 frame) override
        {
            if (RootElement_.IsNull) return;
            RootElement_->ComputeLayout(frame);
        }
        void ComputeLayoutPosition(Rect i) override
        {
            if (RootElement_.IsNull) return;
            RootElement_->ComputeLayoutPosition(i);
        }

        IPtr<UIElement> ElementHitTest(Vec2F p) override
        {
            if (RootElement_.IsNull) return IPtr<UIElement>(nullptr);
            return RootElement_->PerformElementHitTest(p);
        }

        HitTestResult HitTest(Vec2F p) override
        {
            if (RootElement_.IsNull) return HitTestResult();
            return RootElement_->PerformHitTest(p);
        }

        IPtr<UIElement> Search(UIPath path) override
        {
            if (RootElement_.IsNull) INDEX_THROW("RootElement was null.");
            return RootElement_->Search(path);
        }
        IPtr<UIElement> TrySearch(UIPath path) override
        {
            if (RootElement_.IsNull) return IPtr<UIElement>(nullptr);
            return RootElement_->TrySearch(path);
        }
    };
}