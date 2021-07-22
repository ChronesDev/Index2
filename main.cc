#include <iostream>
#include <chrono>
#include <index>

#include <index_ui_macros>

global int i;

class A { };
class B : open A { };

int main()
{
    using namespace Index;
    using namespace Index::UI;

    var b = build({
        return nullptr;
    });

    var b2 = Builder::New([]() -> UIElement* {
        static var r = build({
            static var r = build({
                return nullptr;
            });
            return r.Ptr;
        });
        return r.Ptr;
    });

    List<int> i2 = { 10, 11, 10, 12, 13, 14, 15 };
    i2.Remove(10);
    i2.Reserve(1000);

    std::cout << i2.Capacity << std::endl;

    for (var v : i2) {
        std::cout << v << " ";
    }

    var i = INew<int>(100);
    return 0;
}

#include <index_ui_macros_end>