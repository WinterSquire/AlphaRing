#include "tabs.h"

#include <functional>

#include "../../base/base.h"
#include "../../native/native.h"
#include "../../game/players.h"
#include "../../objects/objects.h"

namespace Halo3::Entry::World {extern void AddTask(std::function<void()> func);}

static void print_player(int index) {
    char buffer[1024];
    char player_name[256];
    const char* format = R"(
Player %d
    Name: %s
    INDEX: %X
    Position: %.2f %.2f %.2f
    Team: %d
)";
    auto p_player = Players()->getPlayerManager()->get(index);
    if (p_player == nullptr) return;
    std::wcstombs(player_name, p_player->name, sizeof(player_name));
    sprintf_s(buffer, format,
            index, player_name, p_player->object_INDEX,
            p_player->position.x, p_player->position.y, p_player->position.z,
            p_player->team
        );
    ImGui::Text(buffer);
    if (ImGui::Button("Respawn")) {
        Halo3::Entry::World::AddTask([index] {
            NativeFunc()->player_possess(index, NONE);
        });
    }
}

void Halo3::IMGUI::Tabs::tab_player() {
    auto p_player = Players()->getPlayerManager();

    if (p_player == nullptr) return;

    for (int i = 0; i < p_player->m_capacity; ++i) print_player(i);

    auto p_action = Players()->getPlayerAction();
    if (p_action == nullptr) return;
    ImGui::Checkbox("Disable Action", &p_action->disable_input);
}

