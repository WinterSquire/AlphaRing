#pragma once

#include "imgui.h"
#include "imgui_internal.h"

namespace ImGui::CustomWidget {
    class BasicWidget {
    public:
        virtual void render() = 0;
    };
}