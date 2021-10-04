#include "../../macros/index_macros.cc"

#define n ::New
#define size .Size = Index::Size
#define minsize .MinSize = Index::Size
#define maxsize .MaxSize = Index::Size
#define color .Color =
#define colors .Color = Index::Colors::
#define align .Alignment = Index::Align::
#define content .Content =
#define edges .Edges = Index::Vec4F

#define ui_list Index::List<Index::IPtr<Index::UI::UIElement>>
#define ui_static_ret(content)                                                                                        \
    static Index::IPtr<UIElement> _ret = content;                                                                     \
    return _ret.Ptr;
#define ui_self_init static auto& self = *this;
#define ui_func []() -> void
#define ui_ref Index::IPtr<Index::UI::UIElement>
#define ui_wref Index::WPtr<Index::UI::UIElement>
#define ui_state (+Index::UI::UIContext::CurrentStates)

#define ui_builder(func)                                                                                              \
    Index::UI::Builder::New(.Build                                                                                    \
        = [this](Index::UI::UIContext * u, Index::UI::Layout i) -> Index::Func<Index::IPtr<Index::UI::UIElement>>     \func)
#define ui_executor(func)                                                                                             \
    Index::UI::Executor::New(.Execute = [this](Index::UI::UIContext * u, Index::UI::Layout i) -> void func)