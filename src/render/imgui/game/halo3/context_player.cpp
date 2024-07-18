#include "CHalo3Context.h"
#include "common.h"

static bool show_context = false;

static const char* format = R"(
Player %d
    Name: %s
    INDEX: %X
    Position: %.2f %.2f %.2f
    Team: %d
)";

void CHalo3Context::context_player() {
    if (ImGui::BeginMainMenuBar()) {
        ImGui::MenuItem("Player", nullptr, &show_context);
        ImGui::EndMainMenuBar();
    }

    if (!show_context) return;

    char buffer[1024];
    char player_name[256];
    auto p_player = Halo3::Native::Players();
    auto p_action = Halo3::Native::PlayersAction();

    if (!p_player || !p_action) return;

    if (ImGui::Begin("Player", &show_context)) {
        if (ImGui::IsKeyPressed(ImGuiKey_F1, false)) {
            LOG_INFO("Player0: {:x}", (__int64)p_player->get(0));
        }

        ImGui::Checkbox("Disable Action", &p_action->disable_input);

        ImGui::SameLine();

        for (int i = 0; i < p_player->m_capacity; ++i) {
            auto p_player = Halo3::Native::Players()->get(i);

            if (p_player == nullptr) continue;

            std::wcstombs(player_name, p_player->name, sizeof(player_name));
            sprintf_s(buffer, format,
                      i, player_name, p_player->object_INDEX,
                      p_player->position.x, p_player->position.y, p_player->position.z,
                      p_player->team
            );

            ImGui::Text(buffer);

            if (ImGui::Button("Respawn")) {
                setState([i] {
                    Halo3::Native::Function::player_possess(i, NONE);
                });
            }
        }
    }
    ImGui::End();
}
