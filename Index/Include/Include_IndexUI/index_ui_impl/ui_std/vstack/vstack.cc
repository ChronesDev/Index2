#pragma once

#include "../ui.cc"
#include "../container/container.cc"

namespace Index::UI
{
	struct VStack : virtual UIContainer
	{
		void OnComputeLayoutPosition(Rect i) override
		{
			Rect r = GetSubrect_(i);

			PolishComputedLayoutPosition();
		}
	};
}