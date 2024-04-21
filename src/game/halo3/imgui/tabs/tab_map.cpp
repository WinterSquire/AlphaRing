#include "tabs.h"

#include "game/halo3/game/map.h"

void Halo3::IMGUI::Tabs::tab_map() {
    const char* map_types[4] = {"", "Campaign", "Multiplayer", "MainMenu"};
    char buffer[1024];

    auto map_info = Map()->getMapInfo();
    sprintf(buffer, "Map: %s(%-11s)", map_info->map_name, map_types[map_info->map_type]);
    ImGui::Text(buffer);
}
