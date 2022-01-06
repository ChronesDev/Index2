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
            Debug.Log("Computing layout");
        }

        void OnComputeLayoutPosition(Rect i) override 
        { 
            UIElement::OnComputeLayoutPosition(i);
            Debug.Log("Computing layout position");
        }

        void OnRender() override 
        { 
            var l = ComputedLayout;
            string s = fmt::format("Rect[{0:.2f},{1:.2f},{2:.2f},{3:.2f}]", l.X, l.Y, l.Width, l.Height);
            Debug.Log("Rendering: ", s);
        }
    };
}

int main()
{
    using namespace Index;
    using namespace Index::UI;

    ui_ref u1 = INew<TestElement>();
    u1->MinSize = Size { 11, 12 };
    u1->Alignment = Align::LeftTop;

    IPtr<TestElement> u2 = INew<TestElement>();
    u2->AddChildren(u1);
    u2->Alignment = Align::Right;

    IPtr<TestElement> u3 = INew<TestElement>();
    u3->AddChildren(u2);

    ui_ref uroot = u3;

    UInt64 frame = 0;
    Rect canvas = { 0, 0, 200, 100 };
    while (true)
    {
        frame = (frame % (Limits::MaxValueOf<UInt64>() - 1)) + 1;
        uroot->ComputeLayout(frame);
        uroot->ComputeLayoutPosition(canvas);

        Debug.WriteLine();
        uroot->Render();
        Debug.WriteLine();

        Time.Delay(TimeSpan::FromSec(3));
        break;
    }

    Console.ReadLine();
}

#include <index_macros_end>
#include <index_ui_macros_end>