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
#define flex .Flex =
#define flags .Flags =
#define edges .Edges = Index::Vec4F
#define build .Build = [&](UIContext* u, Layout i) -> ui_ref
#define execute .Execute = [&](UIContext* u, Layout i)

using namespace Index;
using namespace Index::UI;

struct MyConstructor : Element<MyConstructor>
{
    ui_ref Construct() override
    {
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
            color Colors::Black
        }),
        Padding n ({
            edges(270, 0, 30, 0),
            content {
                Container n ({
                    minsize(null, 40),
                    alignment StretchCenter,
                    content {
                        ImUI::OutRect n ({
                            colors White,
                            .Thickness = 2
                        }),
                        Padding n ({
                            edges(2),
                            content {
                                Builder n ({
                                    build {
                                        static bool leftExpanded = false;
                                        static int leftFlex = 1;
                                        static bool middleExpanded = false;
                                        static int middleFlex = 1;
                                        static bool rightExpanded = false;
                                        static int rightFlex = 1;

                                        using namespace ImGui;
                                        Begin("Tools");
                                        Text("This is a Demo.");
                                        // Left
                                        Separator();
                                        Text("Left");
                                        Checkbox("Left: Enable Expanded", &leftExpanded);
                                        SliderInt("Left: Flex", &leftFlex, 1, 50);
                                        // Middle
                                        Separator();
                                        Text("Middle");
                                        Checkbox("Middle: Enable Expanded", &middleExpanded);
                                        SliderInt("Middle: Flex", &middleFlex, 1, 50);
                                        // Right
                                        Separator();
                                        Text("Right");
                                        Checkbox("Right: Enable Expanded", &rightExpanded);
                                        SliderInt("Right: Flex", &rightFlex, 1, 50);
                                        End();

                                        return ColumnC n ({
                                            content {
                                                leftExpanded ? Expanded n ({
                                                    flex leftFlex,
                                                    content {
                                                        ImUI::FillRect n ({
                                                            colors Yellow
                                                        })
                                                    }
                                                }) : IPtr<UIElement>::Null(),
                                                ImUI::FillRect n ({
                                                    size(40, null),
                                                    colors Blue
                                                }),
                                                middleExpanded ? Expanded n ({
                                                    flex middleFlex,
                                                    content {
                                                        ImUI::FillRect n ({
                                                            colors Green
                                                        })
                                                    }
                                                }) : IPtr<UIElement>::Null(),
                                                ImUI::FillRect n ({
                                                    size(40, null),
                                                    colors Aqua
                                                }),
                                                rightExpanded ? Expanded n ({
                                                    flex rightFlex,
                                                    content {
                                                        ImUI::FillRect n ({
                                                            colors Red
                                                        })
                                                    }
                                                }) : IPtr<UIElement>::Null(),
                                            }
                                        });
                                    }
                                })
                            }
                        })
                    }
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