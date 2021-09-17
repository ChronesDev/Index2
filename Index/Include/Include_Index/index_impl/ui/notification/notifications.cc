#pragma once

#include "notification.cc"

// Bundled Notification
namespace Index::UI::Notifications
{
	struct BundledN : UINotification
	{

	};
}

// Keyboard Notifications
namespace Index::UI::Notifications
{
	struct KeyEventN : UINotification
	{
		// Key
	};

	struct KeyPressedN : UINotification
	{
		// Key
	};

	struct KeyReleasedN : UINotification
	{
		// Key
	};
}

// Mouse Notifications
namespace Index::UI::Notifications
{
	struct MouseMovedN : UINotification
	{
		// Delta Position
		// Mouse Position
	};

	struct MouseScrolledN : UINotification
	{
		// Scroll
	};
}