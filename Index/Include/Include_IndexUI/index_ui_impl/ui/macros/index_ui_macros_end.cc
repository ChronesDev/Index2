#pragma once

#undef ui_ref Index::IPtr<Index::UI::UIElement>
#undef ui_ptr Index::UI::UIElement*

#undef sub parent.template Sub <

#undef map > () += [this](auto& parent, auto mapper)
#undef mapn > () += [](auto& parent, auto mapper)
#undef mapc(capture) > () += [capture](auto& parent, auto mapper)

#undef mapm > () += [this](auto& parent, auto mapper) {}
#undef mapmn > () += [](auto& parent, auto mapper) {}
#undef mapmc(capture) > () += [capture](auto& parent, auto mapper) {}

#undef set mapper.
#undef get mapper.