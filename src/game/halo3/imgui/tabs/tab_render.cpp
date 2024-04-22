#include "../basic_widget.h"

#include "game/halo3/render/render.h"

namespace Halo3::Entry::Draw {extern bool getWireFrame();extern void setWireFrame(bool value);}

class TabRender : public BasicWidget {
public:
    TabRender(const char* name) : BasicWidget(name) {}
    void render() override;

};

static TabRender s_instance("Render");
BasicWidget* tab_render = &s_instance;

void TabRender::render() {
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
    ImGui::Checkbox("show s_instance", &p_flags->show_map);
    ImGui::Checkbox("show grenade3", &p_flags->show_grenade3);
    ImGui::Checkbox("show grenade4", &p_flags->show_grenade4);
}
