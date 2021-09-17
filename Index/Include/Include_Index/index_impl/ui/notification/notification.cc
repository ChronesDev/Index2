#pragma once

#include <type_traits>

#include "../ui.cc"

namespace Index::UI
{
	struct ICancelable
	{
		bool Cancel = false;
	};
}