#pragma once

#include "../ui.cc"

// UIElement
namespace Index::UI
{
    struct UIElement;
}

// IUIProvider
namespace Index::UI
{
    struct IUIProvider
    {
        virtual ~IUIProvider() = 0;

        virtual bool IsConnectedTo(const IPtr<UIElement>& e) = 0;

        virtual void Connect(IPtr<UIElement> e) = 0;
        virtual void Disconnect(IPtr<UIElement> e) = 0;

    };
}