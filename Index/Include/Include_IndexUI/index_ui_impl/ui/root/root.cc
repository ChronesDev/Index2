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

            if (!r.IsNull) r->AttachToUIRoot(ISelf());
            RootElement_ = r;
            OnAttachedRootElement_(r);
        }

        virtual void DetachRootElement()
        {
            if (RootElement_.IsNull) return;
            RootElement_->DetachFromUIRoot();
            RootElement_ = IPtr<UIElement>(nullptr);
        }

    protected:
        virtual void OnAttachedRootElement_(IPtr<UIElement> r) { }
        virtual void OnDetachedRootElement_() { }
    };
}