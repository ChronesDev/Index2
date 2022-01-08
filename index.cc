#include <index>
#include <index_ui>

#include <index_macros>
#include <index_ui_macros>

namespace Index::UI
{
    INDEX_UI_Declare(MyElement);

    struct MyElement : UIContainer
    {
        INDEX_UI_UseMapper(MyElementMapper);
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
                e.Attach(c->Make());
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

    while (true)
    {
        u->ComputeLayout(counter);
        u->ComputeLayoutPosition(screen);

        u->Render();
    }

    Console.ReadLine();

    return 0;
}

#include <index_macros_end>
#include <index_ui_macros_end>