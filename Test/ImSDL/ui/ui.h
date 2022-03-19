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
            m Name = "Stack1";
            m Alignment = Align::LeftTop;
            m Margin = { 20, 20 };
            m Width = 100;

            sub Rectangle mapn {
                m Height = 40;
                m Fill = Color::RGB(97, 255, 69);
            };
            sub HStack mapn {
                sub Rectangle mapn {
                    m Width = 50;
                    m MinHeight = 50;
                    m Fill = Colors::Yellow;
                    m Padding = { 10 };
                };
                sub Rectangle mapn {
                    m Width = 50;
                    m MinHeight = 50;
                    m Fill = Colors::Blue;
                };
            };
            sub Rectangle mapn {
                m Height = 30;
                m Fill = Colors::Red;
            };
            sub Rectangle mapn {
                m Name = "X";
                m MaxSize = { AutoF, 50 };
                m Margin = { 5, 5 };
                m Padding = { 10, 0 };
                m Fill = Colors::Aqua;
            };
        };
        // clang-format enable

        return mapper.Make();
    }
}

#include <index_macros_end>
#include <index_ui_macros_end>
