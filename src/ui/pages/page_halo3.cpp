#include "page_halo3.h"

#include <cstdio>
#include <cstring>
#include <cwchar>

#include "imgui.h"
#include "ui/Context.h"
#include "game/halo3/map/map.h"
#include "game/halo3/game/players.h"
#include "game/halo3/objects/objects.h"

// todo fix crash when loading other titles

namespace Halo3::Entry::Draw {extern bool getWireFrame();extern void setWireFrame(bool value);}
static void tab_render() {
    bool bWireFrame = Halo3::Entry::Draw::getWireFrame();
    if (ImGui::Checkbox("Wireframe", &bWireFrame))
        Halo3::Entry::Draw::setWireFrame(bWireFrame);
}

static void tab_map() {
    const char* map_types[4] = {"", "Campaign", "Multiplayer", "MainMenu"};
    char buffer[1024];

    auto map_info = Map()->getMapInfo();
    sprintf(buffer, "Map: %s Type: %-11s ", map_info.get().map_name, map_types[map_info.get().map_type]);
    ImGui::Text(buffer);
}

static void tab_object() {
    char buffer[1024];
    int count = Objects()->getObjectCount();

    sprintf(buffer, "Total Object: %d", count);

    ImGui::Text(buffer);
}

static void tab_player() {
    char buffer[1024];
    char player_name[256] {0};

    auto p_player = Players()->getPlayer(0);
    if (p_player != nullptr) {
        std::wcstombs(player_name, p_player->name, sizeof(buffer));
    }

    sprintf(buffer, "Player0 Name: %s", player_name);

    ImGui::Text(buffer);
}

const struct Tab {
    typedef void(*callback_t)();
    const char* name;
    callback_t callback;
} tabs[] {
        {"Map", tab_map},
        {"Render",  tab_render},
        {"Object", tab_object},
        {"Player", tab_player},
};

void page_halo3_context() {
    ImGui::BeginTabBar("halo3_tab");
    for (auto tab : tabs) {
        if (!ImGui::BeginTabItem(tab.name)) continue;
        tab.callback();
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
}

static Page page_halo3{900, "Halo3", page_halo3_context};