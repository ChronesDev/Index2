#pragma once

#include "inc.h"

#include <index_macros>

namespace Index::UI::ImSDL
{
    global fun ToImColor(Color c)->ImColor { return ImColor(c.R, c.G, c.B, c.A); }
    global fun ToColor(ImColor c)->Color { return Color::Raw({ c.Value.x, c.Value.y, c.Value.z, c.Value.w }); }

    global fun ToImVec(Vec2F v)->ImVec2 { return { v.X, v.Y }; }
    //global fun ToImVec(Vec3F v)->ImVec3 { return { v.X, v.Y, v.Z }; }
    global fun ToImVec(Vec4F v)->ImVec4 { return { v.X, v.Y, v.Z, v.W }; }
    global fun ToImVec(Size s)->ImVec2 { return { s.Width, s.Height }; }
}

#include <index_macros_end>