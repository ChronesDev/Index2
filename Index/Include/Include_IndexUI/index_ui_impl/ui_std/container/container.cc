#pragma once

#include "../ui.cc"

namespace Index::UI
{
	struct UIContainer : virtual UIElement
	{
		virtual void Attach(const IPtr<>& child) { AttachChild_(child); }
		virtual void Detach(const IPtr<>& child) { DetachChild_(child); }
	};
}