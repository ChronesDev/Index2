#pragma once

#include "../element/element.cc"
#include "iroot.cc"

namespace Index::UI
{
    struct UIRoot : IUIRoot
    {
    protected:
        IPtr<UIElement> RootElement_;

    public:
        IPtr<UIElement> GetRootElement() const { return RootElement_; }
        INDEX_Property(get = GetRootElement) IPtr<UIElement> RootElement;

        void SetRootElement(IPtr<UIElement> e) { RootElement_ = e; }
    };
}