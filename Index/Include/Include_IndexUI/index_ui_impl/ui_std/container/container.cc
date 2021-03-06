#pragma once

#include "../ui.cc"

// UIContainer
namespace Index::UI
{
    INDEX_UI_Declare(UIContainer);

    struct UIContainer : virtual UIElement
    {
        virtual void Attach(const INDEX_UI_Ref& child) { AttachChild_(child); }
        virtual void Attach(const INDEX_UI_Ref&& child) { AttachChild_(child); }
        virtual void Detach(const INDEX_UI_Ref& child) { DetachChild_(child); }
        virtual void Detach(const INDEX_UI_Ref&& child) { DetachChild_(child); }
    };

    struct UIContainerMapper : virtual UIElementMapper
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

// Container
namespace Index::UI
{
    INDEX_UI_Declare(Container);

    struct Container : virtual UIContainer
    {
        INDEX_UI_UseMapper(ContainerMapper);
    };

    struct ContainerMapper : virtual UIContainerMapper
    {
        INDEX_UI_Ref Make() override
        {
            IPtr<Container> e_ref = INew<Container>();
            Container& e = e_ref.Value;

            Impl_(e);
            Impl_Children_(e);

            return e_ref.DynamicAs<UIElement>();
        }
    };
}