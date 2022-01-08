#pragma once

#include "../ui.cc"

namespace Index::UI
{
    INDEX_UI_Declare(UIContainer);

    struct UIContainer : virtual UIElement
    {
        virtual void Attach(const INDEX_UI_Ref& child) { AttachChild_(child); }
        virtual void Detach(const INDEX_UI_Ref& child) { DetachChild_(child); }
    };

    struct UIContainerMapper : virtual UIMapper
    {
    public:
        template <class T> auto Sub() { return Sub_<T>(); }

    protected:
        template<class T> void Impl_Children_(T& e)
        {
            for (auto& c : Children)
            {
                e.Attach(c->Make());
            }
        }
    };
}