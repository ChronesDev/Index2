#pragma once

#define ui_ref ::Index::IPtr<::Index::UI::UIElement>
#define ui_ptr ::Index::UI::UIElement*

#define ui_map_ref ::Index::IPtr<::Index::UI::UIMapper>
#define ui_map_ptr ::Index::UI::UIMapper*

#define ui_sync std::lock_guard<std::recursive_mutex>

#define sub mapper.template Sub <

#define map > () += [this](auto& parent, auto& mapper)
#define mapn > () += [](auto& parent, auto& mapper)
#define mapc(capture) > () += [capture](auto& parent, auto& mapper)

#define mapm > () += [this](auto& parent, auto& mapper) {}
#define mapmn > () += [](auto& parent, auto& mapper) {}
#define mapmc(capture) > () += [capture](auto& parent, auto& mapper) {}

#define m mapper.