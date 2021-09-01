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
    Color Color;
    INDEX_UI_Args {
        INDEX_UI_DefaultMembers
        Index::Color Color;
    };
    INDEX_UI_New(MyConstructor)
    INDEX_UI_Constructor(MyConstructor) {
        INDEX_UI_SetDefaultMembers
        Color = e.Color;
    }

    ui_wref fillRect;
    int I = 0;

    ui_ref Construct() override
    {
        return UI::Stack n ({
            ImUI::FillRect n ({
                name "MyRect",
                color Color
            })
        });
    }
};

struct MyConstructor2 : ScopedElement<MyConstructor>
{
    Color Color;
    INDEX_UI_Args {
        INDEX_UI_DefaultMembers
        Index::Color Color;
    };
    INDEX_UI_New(MyConstructor2)
    INDEX_UI_Constructor(MyConstructor2) {
        INDEX_UI_SetDefaultMembers
        Color = e.Color;
    }

    ui_wref fillRect;
    int I = 0;

    ui_ref Construct() override
    {
        return UI::Stack n ({
            Executor n ({
                execute {
                    if (fillRect.IsNull) fillRect = u->Find("^", "HelloWorld", "MyRect");
                    if (var s = fillRect.Lock)
                    {
                        I++;
                        s->Size = { 300 + (float)I, 300 + (float)I };
                        if (I >= 400) I = 0;
                    }
                }
            })
        });
    }
};

int main()
{
    UPtr<ImUI::ImUIContext> context = UNew<ImUI::ImUIContext>();

    IPtr<UIElement> ui = UI::ScopedStack n ({
        MyConstructor n ({
            name "HelloWorld",
            colors Green
        }),
        MyConstructor2 n ({ })
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