#ifndef CUSTOM_WIDGET_BASIC_WIDGET_H
#define CUSTOM_WIDGET_BASIC_WIDGET_H

#include "imgui.h"
#include "imgui_internal.h"

namespace ImGui::CustomWidget {
    class BasicWidget {
    public:
        virtual void render() = 0;
    };
}

#endif //CUSTOM_WIDGET_BASIC_WIDGET_H
