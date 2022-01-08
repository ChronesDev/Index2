#include <index>
#include <index_ui>

#include <index_macros>
#include <index_ui_macros>

namespace Index::UI
{
    INDEX_UI_Declare(MyElement);

    struct MyElement : virtual UIElement
    {
        INDEX_UI_UseMapper(MyElementMapper);

        void AttachChild(const ui_ref& child) { AttachChild_(child); }
        void DetachChild(const ui_ref& child) { DetachChild_(child); }
    };

    struct MyElementMapper : virtual UIMapper
    {
        MyElementMapper() = default;

        ui_ref Make()
        {
            Debug.Log("Making :) ", Name);

            IPtr<MyElement> e_ref = INew<MyElement>();
            MyElement& e = e_ref.Value;

            e.Name = Name;
            e.Id = Id;
            e.Size = Size;
            e.MinSize = MinSize;

            for (auto& c : Children)
            {
                e.AttachChild(c->Make());
            }

            return e_ref;
        }
    };
}

int main()
{
    using namespace Index;
    using namespace Index::UI;

    MyElementMapper mapper;

    /**
     * Using Macros + Lambdas to create this UI abstraction style.
     */

    // Root
    sub MyElement mapn
    {
        Debug.Log("Executed 1");

        // Properties
        set Size = { 10.f, 10.f };
        set Name = "1";
        set Id = "8495678249568203458690";

        // Child
        sub MyElement mapn
        {
            Debug.Log("Executed 2");

            set Name = "2";
            set Alignment = Align::LeftTop;
            set Margin = { 10, 13, 3, 0 };

            sub MyElement mapn
            {
                Debug.Log("Executed 3");

                set Name = "3";
                sub MyElement mapmn;
            };
        };
    };

    ui_ref u = mapper.Make();

    UIFrameCounter counter;
    Rect screen = { 0, 0, 1920, 1080 };

    std::thread t([=] {
        u->Update();
        Time.Delay(TimeSpan::FromSec(0.2));
    });
    t.detach();

    while (true)
    {
        u->ComputeLayout(counter);
        u->ComputeLayoutPosition(screen);

        u->Render();
    }

    return 0;
}

#include <index_macros_end>
#include <index_ui_macros_end>