#include "../basic_widget.h"

#include "game/halo3/render/render.h"

class TabRender : public BasicWidget {
public:
    TabRender(const char* name) : BasicWidget(name) {}
    void render() override;
    void update() override{}

};

static TabRender s_instance("Render");
BasicWidget* tab_render = &s_instance;

void TabRender::render() {
    ImGui::Text("Wireframe");
    auto p_wireframe = Render()->getWireframe();
    if (p_wireframe != nullptr)
    {
        ImGui::Indent();
        ImGui::Checkbox("model", &p_wireframe->model);
        ImGui::SameLine();
        ImGui::Checkbox("structure", &p_wireframe->structure);
        ImGui::Unindent();
    }

    ImGui::Text("Render");
    auto p_render = Render()->getRender();
    if (p_render != nullptr) {
        ImGui::Indent();
        ImGui::Checkbox("motion_blur", &p_render->motion_blur);
        ImGui::SameLine();
        ImGui::Checkbox("atmosphere_fog", &p_render->atmosphere_fog);

        ImGui::Checkbox("patchy_fog", &p_render->patchy_fog);
        ImGui::SameLine();
        ImGui::Checkbox("render_weather", &p_render->render_weather);

        ImGui::Checkbox("cinematic_motion_blur", &p_render->cinematic_motion_blur);
        ImGui::Unindent();
    }

    ImGui::Text("Chud");
    auto p_chud = Render()->getChud();
    if (p_chud != nullptr) {
        ImGui::Indent();
        ImGui::Checkbox("all", &p_chud->chud_show);

        ImGui::Text("Status");
        {
            ImGui::Indent();
            ImGui::Checkbox("shield", &p_chud->shield);
            ImGui::SameLine();
            ImGui::Checkbox("messages", &p_chud->messages);
            ImGui::SameLine();
            ImGui::Checkbox("motion_sensor", &p_chud->motion_sensor);
            ImGui::Unindent();
        }

        ImGui::Text("Weapon");
        {
            ImGui::Indent();
            ImGui::Checkbox("stats", &p_chud->weapon_stats);
            ImGui::SameLine();
            ImGui::Checkbox("crosshair", &p_chud->crosshair);
            ImGui::Unindent();
        }

        ImGui::Text("Grenade");
        {
            ImGui::Indent();
            ImGui::Checkbox("grenades", &p_chud->grenades);
            ImGui::SameLine();
            ImGui::Checkbox("spike", &p_chud->spike_grenades);
            ImGui::SameLine();
            ImGui::Checkbox("fire", &p_chud->fire_grenades);
            ImGui::Unindent();
        }

        ImGui::Unindent();
    }
}
