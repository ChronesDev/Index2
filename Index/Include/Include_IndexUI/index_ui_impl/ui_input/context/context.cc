#pragma once

#include "icontext.cc"

#include "../element/element.cc"

namespace Index::UI
{
    template <class T> struct UIInputContext : IUIInputContext<T>
    {
    protected:
        UIInputElement<T>* IInputElement_;

        void SetIInputElement_(UIElement* e)
        {
            if (e == nullptr) IInputElement_ = nullptr;
            if (auto ptr = dynamic_cast<UIInputElement<T>*>(e); ptr)
                IInputElement_ = ptr;
            else
                INDEX_THROW("Bad type.");
        }

    protected:
        void UIInputElement_Focus_(const IPtr<UIElement>& e) override
        {
            if (this->HasFocusedElement)
            {
                if (auto ptr = this->FocusedElement_.template DynamicAs<UIInputElement<T>>(); ptr) { ptr->Unfocus(); }
            }
            SetIInputElement_(e.Ptr);
            this->FocusedElement_ = e;
        }
        void UIInputElement_Unfocus_() override
        {
            if (this->HasFocusedElement)
            {
                if (auto ptr = this->FocusedElement_.template DynamicAs<UIInputElement<T>>(); ptr) { ptr->Unfocus(); }
            }
            SetIInputElement_(nullptr);
            this->FocusedElement_ = nullptr;
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
            if (dynamic_cast<UIInputContext<T>*>(e->IInputContext) != this) INDEX_THROW("Foreign IInputContext.");
            e->Focus();
        }
        void UnfocusElement() override
        {
            if (this->HasFocusedElement)
            {
                if (auto ptr = this->FocusedElement_.template DynamicAs<UIInputElement<T>>(); ptr) { ptr->Unfocus(); }
            }
        }

    public:
        virtual void EventKeyPress(typename T::TKey key)
        {
            if (IInputElement_) { IInputElement_->EventKeyPress(key); }
        }
        virtual void EventKeyRelease(typename T::TKey key)
        {
            if (IInputElement_) { IInputElement_->EventKeyRelease(key); }
        }

        virtual void EventPointerMove(Vec2F from, Vec2F to)
        {
            if (IInputElement_) { IInputElement_->EventPointerMove(from, to); }
        }
        virtual void EventPointerPress(typename T::TKey key)
        {
            if (IInputElement_) { IInputElement_->EventPointerPress(key); }
        }
        virtual void EventPointerRelease(typename T::TKey key)
        {
            if (IInputElement_) { IInputElement_->EventPointerRelease(key); }
        }

    public:
    };
}