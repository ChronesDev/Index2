#pragma once

#include "notification.cc"

// Keyboard Notifications
namespace Index::UI::Notifications
{
    struct KeyEventNotification : UINotification
    {
        // Key
    };

    struct KeyPressedNotification : UINotification
    {
        // Key
    };

    struct KeyReleasedNotification : UINotification
    {
        // Key
    };
}

// Mouse Notifications
namespace Index::UI::Notifications
{
    struct MouseMovedNotification : UINotification
    {
        // Delta Position
        // Mouse Position
    };

    struct MouseScrolledNotification : UINotification
    {
        // Scroll
    };
}