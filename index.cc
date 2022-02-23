#include <index>
#include <index_ui>

#include <index_macros>
#include <index_ui_macros>

int main()
{
    using namespace Index;
    using namespace Index::UI;

    ContainerMapper mapper;
    sub Container mapn
    {
        sub Container mapn
        {
            // :)
            Debug.Log("My UI Stuff!");
        };

        sub Container mapmn;
    };

    mapper.Make();

    return 0;
}

#include <index_macros_end>
#include <index_ui_macros_end>