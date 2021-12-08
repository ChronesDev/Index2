#include <index>
#include <index_ui>

#include <index_ui_macros>

int main()
{
    using namespace Index;

    auto a = LinearAnimation { 0, 10, TimeSpan::FromSec(8) };

    ui_ref m;
    ui_ptr mptr = m.Ptr;
}

#include <index_ui_macros_end>