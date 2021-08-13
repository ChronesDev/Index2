#include <iostream>
#include <chrono>
#include <any>
#include <index>

#include "src/Window.h"

#include <index_ui_macros>

#define n ::New
#define u .UIRef

using namespace Index;
using namespace Index::UI;

struct S : Index::UI::UIElement
{
    IPtr<UIElement> Content;
    struct Args
    {
        IPtr<UIElement> Content;
    };
    template<class T = UIElement>
    struct New : public IPtr<T>
    {
        explicit New(Args e) {
            if constexpr (!std::is_same<UIElement, T>::value) {
                static_cast<IPtr<T>&>(*this) = INew<S>(e).As<UIElement>();
            }
            if constexpr (std::is_same<S, T>::value) {
                static_cast<IPtr<T>&>(*this) = INew<S>(e);
            }
            else {
                static_cast<IPtr<T>&>(*this) = INew<S>(e).As<T>();
            }
        }
    };
    explicit S(Args e) {
        Content = std::move(e.Content);
    }
    virtual void Build(Layout i) override
    {

    }
    virtual void Notify(INotification *e) override
    {

    }
};

int main()
{
    ui_ref r = Wrap n {
        content Wrap n {
            content Holder n {
               content {
                   ImUI::Rectangle n{
                       .Fill = Color::RGBA(0, 0, 0, 255)
                   }u,
                   ImUI::Rectangle n{
                       .Fill = Color::RGBA(255, 255, 255, 127)
                   }u
               }
            }u
        }u,
    };

    ui_ref r2 = S n {{
        content S n {{
            content S n {{
                content S n {{
                    content S n {{
                        content S n {{
                            content S n {{
                                content S n {{

                                }}
                            }}
                        }}
                    }}
                }}
            }}
        }}
    }};

    /*
    UIContext::BeginBuild();

    struct MainApp : StatefulElement
    {
        void Construct() override
        {
            ui_list list;
            for (int i = 0; i < 255; i++) {
                list.Add(ImUI::Rectangle n {
                    .Size { 3, 10 },
                    .Fill = Color::RGB(i, i, i)
                });
            }
            add = StackH n {
                .Size { 100, 100 },
                .Alignment = Align::LeftBottom,
                content list
            };
        }
    };

    IPtr<UIElement> root = ImUI::WindowRoot n { content {
        INew<MainApp>(),
        Holder n {
            content {
                Holder n {

                }
            }
        }
    }};

    UIContext::Root = root.As<State>();

    UIContext::EndBuild();

    OnRender = []() {

        ImDrawList& db = *ImGui::GetBackgroundDrawList();
        UIContext::DrawList = ImGui::GetForegroundDrawList();

        // Background
        db.AddRectFilled({0, 0}, {WindowSize.X, WindowSize.Y}, ToImColor(Colors::Orange));

        UIContext::Render();

    };

    //Entry();

    */

    return 0;
}

#include <index_ui_macros_end>