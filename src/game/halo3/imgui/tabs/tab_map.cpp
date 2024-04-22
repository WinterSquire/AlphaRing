#include "../basic_widget.h"

#include "game/halo3/game/map.h"

class TabMap : public BasicWidget {
public:
    TabMap(const char* name) : BasicWidget(name) {}
    void render() override;

};

static TabMap s_instance("Map");
BasicWidget* tab_map = &s_instance;

void TabMap::render() {
    const char* map_types[4] = {"", "Campaign", "Multiplayer", "MainMenu"};
    char buffer[1024];

    auto map = Map()->getMap();

    if (map == nullptr) return;

    {
        auto map_name = strrchr(map->name, '\\');

        if (map_name == nullptr) map_name = map->name;

        sprintf(buffer, "Map: %s (%s)", map_name, map_types[map->game_type]);

        ImGui::Text(buffer);
    }
    {
        ImGui::Text("Skull");

        const int skull_count = sizeof(eSkullValue) / sizeof(int);

        for (int i = 0; i < skull_count; ++i) {
            const char *skull_name = eSkullName[i];
            int skull_value = eSkullValue[i];

            bool status = map->get_skull((eSkull) skull_value);

            if (i % 4 > 0) ImGui::SameLine();

            if (ImGui::Selectable(skull_name, status, 0, {200, 200}))
                map->set_skull((eSkull) skull_value, !status);
        }
    }
}
