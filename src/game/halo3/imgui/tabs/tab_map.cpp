#include "tabs.h"

#include "game/halo3/game/map.h"

void Halo3::IMGUI::Tabs::tab_map() {
    const char* map_types[4] = {"", "Campaign", "Multiplayer", "MainMenu"};
    char buffer[1024];

    auto map = Map()->getMap();
    if (map == nullptr) return;
    sprintf(buffer, "Map: %s(%s)", map->name, map_types[map->game_type]);
    ImGui::Text(buffer);

    const int skull_count = sizeof(eSkullValue) / sizeof(int);
    for (int i = 0; i < skull_count; ++i) {
        const char* skull_name = eSkullName[i];
        int skull_value = eSkullValue[i];

        bool status = map->get_skull((eSkull)skull_value);

        if (i > 0) ImGui::SameLine();

        if (ImGui::Selectable(skull_name, status, 0, {50,50}))
            map->set_skull((eSkull)skull_value, !status);
    }
}
