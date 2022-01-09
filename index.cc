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

    struct MyElementMapper : UIContainerMapper
    {
        MyElementMapper() = default;

        ui_ref Make()
        {
            Debug.Log("Making :) ", Name);

            IPtr<MyElement> e_ref = INew<MyElement>();
            MyElement& e = e_ref.Value;

            Impl_(e);
            Impl_Children_(e);

            return e_ref;
        }
    };
}

int main()
{
    using namespace Index;
    using namespace Index::UI;

    UStackMapper mapper;

    sub VStack mapn
    {
        set Name = "";
        set Alignment = Align::RightBottom;
        sub HStack mapn { set Name = "S"; };
        set Id = "982409-566890-23458609";
    };

    ui_ref u = mapper.Make();

    var result = u->PerformHitTest({ 10, 10 });

    UIFrameCounter counter;
    Rect screen = { 0, 0, 1920, 1080 };

    /*while (true)
    {
        u->ComputeLayout(counter.Next());
        u->ComputeLayoutPosition(screen);

        u->Render();

        u->Update();
    }*/

    List<int> l;
    l.Add(10);
    l.Add(9);
    l.Add(10);
    l.Add(7);
    l.Add(10);

    auto printList = [&]
    {
        for (auto a : l) Console.Write(a, " ");
        Console.WriteLine();
    };

    //printList();
    //
    //Console.Write(l.Remove(10), " ");
    //printList();
    //
    //Console.Write(l.RemoveAll(10), " ");
    //printList();

    Console.WriteLine(Console.ReadLine());

    return 0;
}

#include <index_macros_end>
#include <index_ui_macros_end>