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
            auto p_split = NativeHalo3()
                    ->Camera()
                    ->getSplitScreen();

            auto p_player_mng = NativeHalo3()
                    ->Players()
                    ->getPlayerManager();

            if (p_player_mng == nullptr) return;

            auto p_player0 = p_player_mng->get(0);

            auto p_obj = NativeHalo3()
                    ->Objects()
                    ->getObjectManager()
                    ->get(p_player0->object_INDEX)
                    ->address;

            if (p_obj == nullptr) return;

            INDEX object = NativeHalo3()
                    ->NativeFunc()
                    ->object_create(p_obj->datum, p_obj->position);

            if (object == NONE) return;

            int index = p_player_mng->m_size;
            auto player = NativeHalo3()->NativeFunc()->player_add(index);
            auto p_new_player = p_player_mng->get(index);

            p_new_player->name[0] = 'A' + index;
            p_new_player->pref_species = p_player0->pref_species;

            if (index >= 0 && index <= 3) {
                p_split->index[index] = index;
                p_split->player_INDEX[index] = player;
                p_split->players[index] = (1 << index);
            }

            NativeHalo3()
                ->NativeFunc()
                ->player_possess(player, object);
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
