#include "../../macros/index_macros.cc"

#define build(func) Index::UI::Builder::New( \
    []() -> Index::UI::UIElement* \
    func \
)

#define build_func []() -> Index::UI::UIElement*

#define content(value) Content = value

#define ui_list Index::List<Index::IPtr<Index::UI::UIElement>>

#define ui_static_ret(content) static Index::IPtr<UIElement> _ret = content; \
return _ret.Ptr;