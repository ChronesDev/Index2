#include <iostream>
#include <chrono>
#include <index>

#include "src/Window.h"

#include <index_ui_macros>

#define n ::New

int main()
{
    using namespace Index;
    using namespace Index::UI;

    Mem.PatchChars(nullptr, "\x00\x00");
    Mem.PatchBytes(nullptr, { 0x00, 0x00 });
    Mem.Patch(nullptr, { 0x0, 0x0 });
    Mem.Write<int>(nullptr, 10);

    return 0;

    OnRender = []() {

        ui_ref u = Rectangle n {

        };

        IPtr<UI::Rectangle> r = Rectangle n {

        };

        Mem.ReadStatic<int>(10);
        // Input Hook
        Mem.FindSignature("Minecraft.Windows", "48 89 5C 24 ?? 57 48 83 EC ?? 8B 05 ?? ?? ?? ?? 8B DA 89 54 24 ??");

    };

    Entry();

    return 0;
}

#include <index_ui_macros_end>