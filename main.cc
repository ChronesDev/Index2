#include <iostream>
#include <chrono>
#include <any>
#include <index>
#include <index_impl/ui/ImUI/include.cc>

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

    WPtr<ImUI::FillRect> fillRect1;
    WPtr<ImUI::FillRect> fillRect2;
    int I = 0;

    ui_ref Construct() override
    {
        return UI::Stack n ({
            Executor n ({
                execute {
                    if (fillRect1.IsNull) fillRect1 = u->Find<ImUI::FillRect>("-1 MyRect");
                    if (fillRect2.IsNull) fillRect2 = u->Find<ImUI::FillRect>("-2 MyRect");

                    if (auto r = fillRect1.Lock)
                    {
                        r->Color = Colors::Blue;
                    }

                    if (auto r = fillRect2.Lock)
                    {
                        r->Color = Colors::Orange;
                    }
                }
            }),
            ScopedContainer n ({
                name "-1",
                content {
                    ImUI::FillRect n ({
                        name "MyRect",
                        size(50, 50),
                        alignment LeftTop,
                        colors Green
                    })
                }
            }),
            ScopedContainer n ({
                name "-2",
                content {
                    ImUI::FillRect n ({
                        name "MyRect",
                        size(50, 50),
                        alignment LeftBottom,
                        colors Red
                    })
                }
            }),
            Container n ({
            	size(null, 40),
            	content {
            		Column n ({
            			content {
            				ImUI::FillRect n ({
            					minsize(100, 0),
            					colors Green
            				}),
            				ImUI::FillRect n ({
            					minsize(0, 0),
            					colors Red
            				}),
            				ImUI::FillRect n ({
            					minsize(10, 0),
            					colors Blue
            				}),
            			}
            		})
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
        })
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