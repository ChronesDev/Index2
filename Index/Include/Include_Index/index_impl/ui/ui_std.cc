#pragma once

#include "ui.cc"

#pragma region Macros

#define INDEX_UI_DefaultMembers                             \
Index::Size MinSize { 0, 0 };                               \
Index::Size MaxSize { Index::UI::NullF, Index::UI::NullF }; \
Index::Size Size { Index::UI::NullF, Index::UI::NullF };    \
Index::Align Alignment = Index::Align::Stretch;

#define INDEX_UI_Args \
struct Args

#define INDEX_UI_New(class_name)                                                    \
template<class T = Index::UI::UIElement> static Index::IPtr<T> New(Args&& args) {   \
return Index::INew<class_name>(std::forward<Args>(args));                           \
}

#define INDEX_UI_NewArgs(class_name, args_name)                                        \
template<class T = Index::UI::UIElement> static Index::IPtr<T> New(args_name args) {   \
return Index::INew<class_name>(std::forward<args_name>(args));                         \
}

#define INDEX_UI_NewEmpty(class_name)                                                  \
template<class T = Index::UI::UIElement> static Index::IPtr<T> New() {                 \
return Index::INew<class_name>();                                                      \
}

#define INDEX_UI_Constructor(class_name) \
explicit class_name(Args e)

#define INDEX_UI_ConstructorArgs(class_name, args_name) \
explicit class_name(args_name e)

#define INDEX_UI_ConstructorEmpty(class_name) \
explicit class_name()

#pragma endregion

