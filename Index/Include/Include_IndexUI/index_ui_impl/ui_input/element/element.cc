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
        bool GetIsFocused() const { return IsFocused_; }
        INDEX_Property(get = GetIsFocused) bool IsFocused;

    public:
        // TODO: Finish that
        virtual void ForceFocus() { }
        virtual void TryFocus() { }
        virtual void Focus() {
            if (!HasIInputContext) INDEX_THROW("Missing IInputContext.");
            if (IsFocused) return;
        }
        virtual void Unfocus() { }
    };
}