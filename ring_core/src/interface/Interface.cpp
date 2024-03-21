#include "Interface.h"

#include "directx11_hook.h"
#include "imgui.h"

void context() {
    ImGui::Begin("Alpha Ring");

    ImGui::End();
}

System::eStatus Interface::initialize() {
    ImmediateGUI::SetCallback(context);
    return SYS_OK;
}

System::eStatus Interface::shutdown() {
    return SYS_OK;
}
