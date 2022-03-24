#pragma once

#include "icontext.cc"

#include "../element/element.cc"

namespace Index::UI
{
    template <class T> struct UIInputContext : IUIInputContext<T>
    {
    protected:
        void UIInputElement_Focus_(const IPtr<UIElement>& e) override
        {
            if (this->HasFocusedElement)
            {
                if (auto ptr = this->FocusedElement_.template DynamicAs<UIInputElement<T>>(); ptr)
                {
                    ptr->Unfocus();
                }
            }
            this->FocusedElement_ = e;
        }
        void UIInputElement_Unfocus_() override
        {
            if (this->HasFocusedElement)
            {
                if (auto ptr = this->FocusedElement_.template DynamicAs<UIInputElement<T>>(); ptr)
                {
                    ptr->Unfocus();
                }
            }
        }

    public:
        void FocusElement(const IPtr<UIElement>& e) override
        {
            IPtr<UIInputElement<T>> ue = e.template DynamicAs<UIInputElement<T>>();
            if (ue.IsNull) INDEX_THROW("Bad type.");
            FocusElement(ue);
        }
        void FocusElement(const IPtr<UIInputElement<T>>& e) override
        {
            if (dynamic_cast<UIInputContext<T>>(e->IInputContext_) != this) INDEX_THROW("Foreign IInputContext.");
            e->Focus();
        }
        void UnfocusElement() override
        {
            if (this->HasFocusedElement)
            {
                if (auto ptr = this->FocusedElement_.template DynamicAs<UIInputElement<T>>(); ptr)
                {
                    ptr->Unfocus();
                }
            }
        }

    public:
        virtual void EventKeyPress(typename T::TKey key) { }
        virtual void EventKeyRelease(typename T::TKey key) { }

        virtual void EventPointerMove(Vec2F from, Vec2F to) { }
        virtual void EventPointerPress(typename T::TKey key) { }
        virtual void EventPointerRelease(typename T::TKey key) { }

    public:

    };
}