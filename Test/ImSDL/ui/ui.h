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
            m Padding = { 6 };
            sub HStack mapn {
                m Height = 30;
            };
            sub Switcher mapn {
                m Name = "Switcher";
                m MinWidth = 600;
                m Height = 350;
                m Padding = { 0, 80, 0, 0 };
                m Index = 0;

                sub Container, 0 mapn {
                    sub Rectangle mapn {
                        m Name = "BREAK!";
                        m MaxSize = { 20, 20 };
                        m Fill = Colors::Red;
                    };
                };
                sub Container, 1 mapn {
                    sub Rectangle mapn {
                        m Name = "BREAK!";
                        m MaxSize = { 20, 20 };
                        m Fill = Colors::Lime;
                    };
                };
                sub Container, 2 mapmn;
            };
        };
        // clang-format enable

        return mapper.Make();
    }
}

#include <index_macros_end>
#include <index_ui_macros_end>
