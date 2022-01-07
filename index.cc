#include <index>
#include <index_ui>

#include <index_macros>
#include <index_ui_macros>

namespace Index::UI
{
    INDEX_UI_Declare(MyElement);

    struct MyElement : UIElement
    {
        INDEX_UI_UseMapper(MyElementMapper);
    };

    struct MyElementMapper : UIMapper
    {
        MyElementMapper() = default;

        ui_ref Make()
        {
            Debug.Log("Making :)");

            IPtr<MyElement> e_ref = INew<MyElement>();
            MyElement& e = e_ref.Value;

            e.Name = Name;
            e.Id = Id;
            e.Size = Size;
            e.MinSize = MinSize;

            return e_ref;
        }
    };
}

int main()
{
    using namespace Index;
    using namespace Index::UI;

    MyElementMapper parent;

    /**
     * Using Macros + Lambdas to create this UI abstraction style.
     */

    // Root
    sub MyElement mapn
    {
        // Properties
        set Size = { 10.f, 10.f };
        set Name = "MyElement :D";
        set Id = "8495678249568203458690";

        // Child
        sub MyElement mapn
        {
            // Property
            set Name = ":D";

            // Child
            sub MyElement mapmn;
        };
    };

    return 0;
}

#include <index_macros_end>
#include <index_ui_macros_end>