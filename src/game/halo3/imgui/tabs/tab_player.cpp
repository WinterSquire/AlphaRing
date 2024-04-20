#include "tabs.h"

#include "../../base/base.h"

#include "game/halo3/game/players.h"

static void print_player(int index) {
    char buffer[1024];
    char player_name[256];
    const char* format = R"(
Player %d(%X): %s
    Position: %.2f %.2f %.2f
    Team: %d
)";
    auto p_player = Players()->getPlayer(index);
    if (p_player == nullptr) return;
    std::wcstombs(player_name, p_player->name, sizeof(player_name));
    sprintf_s(buffer, format,
            index, p_player->object_INDEX, player_name,
            p_player->position.x, p_player->position.y, p_player->position.z,
            p_player->team
        );
    ImGui::Text(buffer);
}

void Halo3::IMGUI::Tabs::tab_player() {
    print_player(0);
}

