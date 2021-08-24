#include <iostream>
#include <chrono>
#include <any>
#include <index>

#include "src/Window.h"

#include <index_ui_macros>

#define n ::New
#define null Index::UI::NullF
#define size .Size = Index::Size
#define minsize .MinSize = Index::Size
#define maxsize .MaxSize = Index::Size
#define dyn [&]() -> float
#define selfdyn [&](UIDynamic* that, UIContext* u) -> float
#define color .Color =
#define colors .Color = Colors::
#define flags .Flags =
#define edges .Edges = Index::Vec4F
#define build .Build = [&](UIContext* u, Layout i) -> ui_ref
#define execute .Execute = [&](UIContext* u, Layout i)

using namespace Index;
using namespace Index::UI;

struct MyConstructor : Constructor<MyConstructor>
{
    ui_ref Construct() override {
        return ImUI::FillRect n ({
            size(300, 300),
            color Colors::Green
        });
    }
};

int main()
{
    UPtr<ImUI::ImUIContext> context = UNew<ImUI::ImUIContext>();

    IPtr<UIElement> ui = UI::Stack n ({
        ImUI::FillRect n ({
            color Colors::White
        }),
        SplitH n ({
            content {
                ImUI::FillRect n ({
                    size(300, null),
                    colors RawGreen
                }),
                Expand<10> n ({
                    ImUI::FillRect n ({
                        colors RawRed
                    }),
                })
            }
        })
    });

    context->SetRoot(ui);

    OnRender = [&]() {

        ImDrawList& db = *ImGui::GetBackgroundDrawList();
        db.AddRectFilled({0, 0}, ToImVec2(WindowSize),ToImColor(Colors::White));

        context->Render(WindowSize, &db);
    };

    Entry();


    return 0;
}

#include <index_ui_macros_end>