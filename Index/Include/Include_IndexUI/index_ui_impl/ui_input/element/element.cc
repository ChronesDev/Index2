#pragma once

#include "../ui.cc"

#include "../context/icontext.cc"
#include "../descriptor/descriptor.cc"

namespace Index::UI
{
    template <class T> struct UIInputElement : virtual UIElement
    {
    protected:
        IUIInputContext<T>* IInputContext_ = nullptr;
        bool HasIInputContext_ = false;

    public:
        IUIInputContext<T>* GetIInputContext() const { return IInputContext_; }
        INDEX_Property(get = GetIInputContext) IUIInputContext<T>* IInputContext;

        bool GetHasIInputContext_() const { return HasIInputContext_; }
        INDEX_Property(get = GetHasIInputContext_) bool HasIInputContext;

    protected:
        void UIInputElement_OnAttachedToUIRoot_(IPtr<IUIRoot> root)
        {
            auto ptr = dynamic_cast<IUIInputContext<T>*>(root.Ptr);
            if (ptr)
            {
                IInputContext_ = ptr;
                HasIInputContext_ = true;
            }
        }
        void UIInputElement_OnDetachedFromUIRoot_()
        {
            IInputContext_ = nullptr;
            HasIInputContext_ = false;
        }

    protected:
        void OnAttachedToUIRoot_(IPtr<IUIRoot> root) override
        {
            UIInputElement_OnAttachedToUIRoot_();
            UIElement::OnAttachedToUIRoot_(root);
        }
        void OnDetachedFromUIRoot_() override
        {
            UIInputElement_OnDetachedFromUIRoot_();
            UIElement::OnDetachedFromUIRoot_();
        }

    protected:
        bool IsFocused_ = false;

    public:
        virtual bool GetIsFocusable() const { return false; }
        INDEX_Property(get = GetIsFocusable) bool IsFocusable;

        bool GetIsFocused() const { return IsFocused_; }
        INDEX_Property(get = GetIsFocused) bool IsFocused;

    public:
        virtual void TryFocus()
        {
            if (!HasIInputContext) return;
            if (!IsFocusable) return;
            if (IsFocused) return;

            IInputContext_->UIInputElement_Focus_(ISelf());

            IsFocused_ = true;
            OnFocused();
        }
        virtual void Focus()
        {
            if (!HasIInputContext) INDEX_THROW("Missing IInputContext.");
            if (!IsFocusable) INDEX_THROW("Element cannot be focused.");
            if (IsFocused) return;

            IInputContext_->UIInputElement_Focus_(ISelf());

            IsFocused_ = true;
            OnFocused();
        }
        virtual void Unfocus()
        {
            if (!IsFocused) return;

            if (IInputContext_->FocusedElement_ != ISelf()) INDEX_THROW("Element is not focused in IInputContext.");
            IInputContext_->UIInputElement_Unfocus_(ISelf());

            IsFocused_ = false;
            OnUnfocused();
        }

    protected:
        virtual void OnFocused() { }
        virtual void OnUnfocused() { }
    };
}