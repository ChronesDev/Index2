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
    UIContext::BeginBuild();

    struct MainApp : StatefulElement
    {
        void Construct() override
        {
            ui_list list;
            list.Add(Container n {})
        }
    };

    IPtr<UIElement> root = ImUI::WindowRoot n { content {
        INew<MainApp>()
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

    Entry();


    return 0;
}

#include <index_ui_macros_end>