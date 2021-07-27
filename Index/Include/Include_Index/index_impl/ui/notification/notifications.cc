#include "notification.cc"

// Keyboard Notifications
namespace Index::UI::Notifications
{
    struct KeyEventNotification : INotification
    {
        // Key
    };

    struct KeyPressedNotification : INotification
    {
        // Key
    };

    struct KeyReleasedNotification : INotification
    {
        // Key
    };
}

// Mouse Notifications
namespace Index::UI::Notifications
{
    struct MouseMovedNotification : INotification
    {
        // Delta Position
        // Mouse Position
    };

    struct MouseScrolledNotification : INotification
    {
        // Scroll
    };
}