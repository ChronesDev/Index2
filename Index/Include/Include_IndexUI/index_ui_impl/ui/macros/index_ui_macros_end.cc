#pragma once

#define ui_ref IPtr<UIElement>
#define ui_ptr UIElement*

#define sub parent.template Sub <

#define map > () += [this](auto& parent, auto mapper)
#define mapn > () += [](auto& parent, auto mapper)
#define mapc(capture) > () += [capture](auto& parent, auto mapper)

#define mapm > () += [this](auto& parent, auto mapper) {}
#define mapmn > () += [](auto& parent, auto mapper) {}
#define mapmc(capture) > () += [capture](auto& parent, auto mapper) {}

#define set mapper.
#define get mapper.