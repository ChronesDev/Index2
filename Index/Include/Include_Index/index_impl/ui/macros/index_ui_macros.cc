#include "../../macros/index_macros.cc"

#define build(func) Index::UI::Builder::New( \
    []() -> Index::UI::UIElement* \
    func \
)

#define content(value) Content = value