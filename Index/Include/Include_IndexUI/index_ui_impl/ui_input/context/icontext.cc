#pragma once

#include "../ui.cc"

namespace Index::UI
{
    template <class T> struct IUIInputContext : virtual UIRoot
    {
    protected:
        IPtr<UIElement> FocusedElement_;

    public:
        IPtr<UIElement> GetFocusedElement() const { return FocusedElement_; }
        INDEX_Property(get = GetFocusedElement) IPtr<UIElement> FocusedElement;

        // TODO: Finish that
    };
}