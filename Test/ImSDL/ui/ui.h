#pragma once

#include "elements/all.h"
#include "ui_descriptor.h"
#include "util.h"

#include <index_macros>
#include <index_ui_macros>

namespace Index::UI::ImSDL
{
    Rect DrawArea = {};

    IPtr<ImRoot> IC;

    fun DoSetup()->void;
    fun DoRender()->void;
    fun GetUI()->ui_ref;

    global fun DoSetup()->void
    {
        IC = INew<ImRoot>();
        ui_ref ui = GetUI();
        IC->AttachRootElement(ui);
    }

    global fun DoRender()->void
    {
        IC->Compute(ImGui::GetFrameCount(), DrawArea);

        IC->DrawList_ = ImGui::GetBackgroundDrawList();
        IC->Render();
        IC->DrawList_ = nullptr;

        IC->Update();
    }

    global fun GetUI()->ui_ref
    {
        var mapper = ContainerMapper();

        // clang-format disable
        sub VStack mapn {
            m Width = 300;
            m Padding = { 6 };
            sub Rectangle mapn {
                m Name = "RECT";
                m Width = 100;
                m MinSize = { 100, 100 };
                m Margin = { 20, 20 };
            };
        };
        // clang-format enable

        return mapper.Make();
    }
}

#include <index_macros_end>
#include <index_ui_macros_end>
