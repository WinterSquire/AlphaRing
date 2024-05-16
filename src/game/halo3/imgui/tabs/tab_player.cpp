#include "../basic_widget.h"

#include <functional>

#include "../../native/native.h"

class TabPlayer : public BasicWidget {
public:
    TabPlayer(const char* name) : BasicWidget(name) {}
    void render() override;
    void update() override{}

    void print_player(int index);
};

static TabPlayer s_instance("Player");
BasicWidget* tab_player = &s_instance;

void TabPlayer::render() {
    auto p_player = NativeHalo3()->Players()->getPlayerManager();
    auto p_action = NativeHalo3()->Players()->getPlayerAction();

    if (!p_player || !p_action) return;

    ImGui::Checkbox("Disable Action", &p_action->disable_input);

    ImGui::SameLine();

    if (ImGui::Button("Add Player")) {
        setState([] {
            auto index = NativeHalo3()
                    ->NativeFunc()
                    ->local_player_add(L"UWU", L"UWU");

            if (index == NONE) return;

            index = (__int16)index;

            auto p_new_player = NativeHalo3()
                    ->Players()
                    ->getPlayerManager()
                    ->get(index);

            p_new_player->primary_color = index * 2 + 0;
            p_new_player->secondary_color = index * 2 + 1;
            p_new_player->pref_species = index % 2;
        });
    }

    for (int i = 0; i < p_player->m_capacity; ++i) print_player(i);
}

void TabPlayer::print_player(int index) {
    char buffer[1024];
    char player_name[256];
    const char* format = R"(
Player %d
    Name: %s
    INDEX: %X
    Position: %.2f %.2f %.2f
    Team: %d
)";
    auto p_player = NativeHalo3()
            ->Players()
            ->getPlayerManager()
            ->get(index);

    if (p_player == nullptr) return;

    std::wcstombs(player_name, p_player->name, sizeof(player_name));
    sprintf_s(buffer, format,
              index, player_name, p_player->object_INDEX,
              p_player->position.x, p_player->position.y, p_player->position.z,
              p_player->team
    );

    ImGui::Text(buffer);

    if (ImGui::Button("Respawn")) {
        setState([index] {
            NativeHalo3()->NativeFunc()->player_possess(index, NONE);
        });
    }
}
