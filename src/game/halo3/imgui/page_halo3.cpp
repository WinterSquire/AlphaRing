#include "page_halo3.h"

#include "imgui.h"

#include "tabs/tabs.h"

const Tab tabs[] {
        {"Map", Halo3::IMGUI::Tabs::tab_map},
        {"Time", Halo3::IMGUI::Tabs::tab_time},
        {"Render",  Halo3::IMGUI::Tabs::tab_render},
        {"Object", Halo3::IMGUI::Tabs::tab_object},
        {"Player", Halo3::IMGUI::Tabs::tab_player},
};

void Halo3::IMGUI::page_halo3() {
    ImGui::BeginTabBar("halo3_tab");
    for (auto tab : tabs) {
        if (!ImGui::BeginTabItem(tab.name)) continue;
        tab.callback();
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
}
