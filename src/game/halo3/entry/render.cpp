#include "common.h"

#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "hook/d3d11/imgui_impl.h"

#include "../native/native.h"
#include "game/halo3/map/map.h"
#include "game/halo3/game/players.h"
#include "game/halo3/game/game_time.h"
#include "game/halo3/objects/objects.h"

namespace Halo3::Entry::Render { void Prologue(); void Epilogue(); }

void Halo3::Entry::Render::Prologue() {

}

void page_halo3_context();

// swap_chain.present(...) switches from mcc.exe to halo3.dll
void Halo3::Entry::Render::Epilogue() {
    // NewFrame
    ImmediateGUI::setRender(true);
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (!ImmediateGUI::isVisible()) return;
    ImGui::Begin("Halo3");
    page_halo3_context();
    ImGui::End();
}

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

void tab_time() {
    char buffer[1024];
    auto p_time = Time()->getGameTime();
    __int16 tick_per_second = 0;
    __int32 game_time = 0;
    float speed = 0;

    if (p_time != nullptr) {
        tick_per_second = p_time->tick_per_second;
        game_time = p_time->game_time;
        speed = p_time->speed;
    }
    sprintf(buffer, "Game Time: %d\nTick Per Second: %hd\nSpeed: %.2f", game_time, tick_per_second, speed);
    ImGui::Text(buffer);
}

const struct Tab {
    typedef void(*callback_t)();
    const char* name;
    callback_t callback;
} tabs[] {
        {"Map", tab_map},
        {"Time", tab_time},
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
