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

        virtual void Conntect(UIElement* e) = 0;
        virtual void Disconnect(UIElement* e) = 0;
        virtual void DisconnectAll() = 0;

        virtual bool IsConnectedTo(UIElement* e) = 0;
    };
}