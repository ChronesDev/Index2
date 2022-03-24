#pragma once

#include "../ui.cc"

namespace Index::UI
{
    template <class T> struct UIInputElement;

    template <class T> struct IUIInputContext : virtual UIRoot
    {
        friend UIInputElement<T>;

    protected:
        IPtr<UIElement> FocusedElement_;

    public:
        IPtr<UIElement> GetFocusedElement() const { return FocusedElement_; }
        INDEX_Property(get = GetFocusedElement) IPtr<UIElement> FocusedElement;

        bool GetHasFocusedElement() const { return !FocusedElement_.IsNull; }
        INDEX_Property(get = GetHasFocusedElement) bool HasFocusedElement;

    protected:
        virtual void UIInputElement_Focus_(const IPtr<UIElement>& e) = 0;
        virtual void UIInputElement_Unfocus_() = 0;

    public:
        virtual bool FocusElement(const IPtr<UIElement>& e) = 0;
        virtual bool FocusElement(const IPtr<UIInputElement<T>>& e) = 0;
        virtual bool UnfocusElement() = 0;
    };
}