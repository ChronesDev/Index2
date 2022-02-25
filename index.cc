#include <index>
#include <index_ui>

#include <index_macros>
#include <index_ui_macros>

int main()
{
    using namespace Index;
    using namespace Index::UI;

    {
        IPtr<Container> u1 = INew<Container>();
        {
            IPtr<Container> u2 = INew<Container>();
            IPtr<Container> u3 = INew<Container>();
            IPtr<Container> u4 = INew<Container>();

            u1->Attach(u2);
            u2->Attach(u3);
            u3->Attach(u4);

            u1->Detach(u2);
        }
    }

    return 0;
}

#include <index_macros_end>
#include <index_ui_macros_end>