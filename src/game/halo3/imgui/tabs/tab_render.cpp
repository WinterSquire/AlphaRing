#include "tabs.h"

#include "imgui.h"
#include "../../render/render.h"

namespace Halo3::Entry::Draw {extern bool getWireFrame();extern void setWireFrame(bool value);}

void Halo3::IMGUI::Tabs::tab_render() {
    bool bWireFrame = Halo3::Entry::Draw::getWireFrame();
    if (ImGui::Checkbox("Wireframe", &bWireFrame))
        Halo3::Entry::Draw::setWireFrame(bWireFrame);

    auto p_flags = Render()->getRenderFlags();
    if (p_flags == nullptr) return;

    ImGui::Checkbox("show chud", &p_flags->show_chud);
    ImGui::Checkbox("show weapon", &p_flags->show_weapon);
    ImGui::Checkbox("show shield", &p_flags->show_shield);
    ImGui::Checkbox("show grenades", &p_flags->show_grenades);
    ImGui::Checkbox("show aim", &p_flags->show_aim);
    ImGui::Checkbox("show map", &p_flags->show_map);
    ImGui::Checkbox("show grenade3", &p_flags->show_grenade3);
    ImGui::Checkbox("show grenade4", &p_flags->show_grenade4);
}