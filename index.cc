#include <index>
#include <index_ui>

#include <fmt/core.h>

#include <index_macros>
#include <index_ui_macros>

namespace Index::UI
{
    struct TestElement : UIElement
    {
        void AddChildren(IPtr<UIElement> e) { Children_Add_(e); }
        void RemoveChildren(IPtr<UIElement> e) { Children_Remove_(e); }

        void OnComputeLayout() override
        {
            UIElement::OnComputeLayout();
            Debug.Log("Computing layout: ", Name);
        }

        void OnComputeLayoutPosition(Rect i) override 
        { 
            Debug.Log("Computing layout position: ", Name);
            UIElement::OnComputeLayoutPosition(i);
        }

        void OnRender() override 
        { 
            var l = ComputedLayout;
            string s = fmt::format("Rect[{0:.2f},{1:.2f},{2:.2f},{3:.2f}]", l.X, l.Y, l.Width, l.Height);
            Debug.Log("Rendering: ", Name, " ", s);
        }
    };
}

int main()
{
    using namespace Index;
    using namespace Index::UI;

    ui_ref u1 = INew<TestElement>();
    u1->MinSize = Size { 11, 12 };
    u1->MaxSize = Size { 70, 70 };
    u1->Alignment = Align::LeftTop;
    u1->Name = "u1";

    IPtr<TestElement> u2 = INew<TestElement>();
    u2->AddChildren(u1);
    u2->Alignment = Align::Right;
    u2->Name = "u2";

    ui_ref u1_1 = INew<TestElement>();
    u1_1->MinSize = Size { 5, 5 };
    u1_1->Alignment = Align::Center;
    u1_1->Name = "u1_1";

    IPtr<TestElement> u2_1 = INew<TestElement>();
    u2_1->AddChildren(u1_1);
    u2_1->Padding = Vec4F(3);
    u2_1->Alignment = Align::BottomCenter;
    u2_1->Name = "u2_1";

    IPtr<TestElement> u3 = INew<TestElement>();
    u3->AddChildren(u2);
    u3->AddChildren(u2_1);
    u3->Name = "u3";

    ui_ref uroot = u3;

    UInt64 frame = 0;
    Rect canvas = { 0, 0, 200, 100 };

    int counter = 0;

    while (true)
    {
        frame = (frame % (Limits::MaxValueOf<UInt64>() - 1)) + 1;
        uroot->ComputeLayout(frame);
        uroot->ComputeLayoutPosition(canvas);

        Debug.WriteLine();
        uroot->Render();
        Debug.WriteLine();

        Time.Delay(TimeSpan::FromSec(2));
        
        counter = (counter + 1) % 10;
        switch (counter)
        {
        case 2:
            Debug.Log(counter);
            u1->MinSize = Size(11);
            break;
        case 4:
            Debug.Log(counter);
            u1->MinSize = AutoS;
            break;
        case 8:
            Debug.Log(counter);
            u2->MinSize = Size(20);
            break;
        case 9:
            Debug.Log(counter);
            u2->MinSize = AutoS;
            break;
        }
    }

    Console.ReadLine();
}

#include <index_macros_end>
#include <index_ui_macros_end>