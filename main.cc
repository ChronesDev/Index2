#include <iostream>
#include <chrono>
#include <any>
#include <index>

#include "src/Window.h"

#include <index_ui_macros>

#define n ::New
#define null Index::UI::NullF
#define name .Name =
#define size .Size = Index::Size
#define minsize .MinSize = Index::Size
#define maxsize .MaxSize = Index::Size
#define dyn [&]() -> float
#define selfdyn [&](UIDynamic* that, UIContext* u) -> float
#define color .Color =
#define colors .Color = Colors::
#define flex .Flex =
#define flags .Flags =
#define edges .Edges = Index::Vec4F
#define build .Build = [&](UIContext* u, Layout i) -> ui_ref
#define execute .Execute = [&](UIContext* u, Layout i)

using namespace Index;
using namespace Index::UI;

struct MyConstructor : ScopedElement<MyConstructor>
{
    ui_wref fillRect;
    int I = 0;

    ui_ref Construct() override
    {
        return UI::Stack n ({
            Executor n ({
                execute {
                    if (fillRect.IsNull) fillRect = u->Find("MyRect");
                    if (var s = fillRect.Lock)
                    {
                        I++;
                        s->Size = { 300 + (float)I, 300 + (float)I };
                        if (I >= 400) I = 0;
                    }
                }
            }),
            ImUI::FillRect n ({
                name "MyRect",
                colors White
            })
        });
    }
};

int main()
{
    UPtr<ImUI::ImUIContext> context = UNew<ImUI::ImUIContext>();

    IPtr<UIElement> ui = UI::Stack n ({
        MyConstructor n ()
    });

    context->SetRoot(ui);

    OnRender = [&]() {

        ImDrawList& db = *ImGui::GetBackgroundDrawList();
        db.AddRectFilled({0, 0}, ToImVec2(WindowSize),ToImColor(Colors::Black));

        context->Render(WindowSize, &db);
    };

    Entry();


    return 0;
}

#include <index_ui_macros_end>