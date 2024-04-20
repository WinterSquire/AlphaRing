#include "tabs.h"

#include "imgui.h"

namespace Halo3::Entry::Draw {extern bool getWireFrame();extern void setWireFrame(bool value);}

void Halo3::IMGUI::Tabs::tab_render() {
    bool bWireFrame = Halo3::Entry::Draw::getWireFrame();
    if (ImGui::Checkbox("Wireframe", &bWireFrame))
        Halo3::Entry::Draw::setWireFrame(bWireFrame);
}