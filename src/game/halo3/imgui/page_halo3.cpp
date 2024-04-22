#include "page_halo3.h"

#include "imgui.h"

extern BasicWidget* tab_actor;
extern BasicWidget* tab_map;
extern BasicWidget* tab_time;
extern BasicWidget* tab_render;
extern BasicWidget* tab_object;
extern BasicWidget* tab_player;

BasicWidget* const tabs[] {
    tab_map,
    tab_time,
    tab_player,
    tab_object,
    tab_actor,
    tab_render,
};

void Halo3::IMGUI::page_halo3() {
    ImGui::BeginTabBar("halo3_tab");
    for (auto tab : tabs) {
        if (!ImGui::BeginTabItem(tab->name())) continue;
        tab->render();
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
}
