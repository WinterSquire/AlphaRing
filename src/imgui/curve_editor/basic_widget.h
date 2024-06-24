#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

namespace ImGui::CustomWidget {
    class BasicWidget {
    public:
        virtual void render() = 0;
    };
}