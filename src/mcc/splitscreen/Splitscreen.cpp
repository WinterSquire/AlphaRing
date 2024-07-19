#include "Splitscreen.h"

#include "common.h"

#include "global/Global.h"

#include <offset_mcc.h>

namespace MCC::Splitscreen {
    DefDetourFunction(__int64, __fastcall, get_index_by_xuid, void* a1, __int64 xuid) {
        auto p_setting = AlphaRing::Global::MCC::Profile();

        if (!p_setting->b_override)
            return ppOriginal_get_index_by_xuid(a1, xuid);

        if (xuid == p_setting->profiles[0].xuid)
            return 0;

        for (int i = 0; i < 4; ++i) {
            if (xuid == p_setting->profiles[i].id)
                return i;
        }

        return 0;
    }

    // todo:: let other players have the ability to pause the game

    bool Initialize() {
        bool result;

        // fix: changing team freeze the game
        result = AlphaRing::Hook::Detour({
            {0x2D01DC, 0, get_index_by_xuid, (void**)&ppOriginal_get_index_by_xuid},
        });

        assertm(result, "MCC:Splitscreen: failed to hook");

        return true;
    }
}

#include "imgui.h"

namespace MCC::Splitscreen {
    void RealContext(int index);

    void ImGuiContext() {
        char buffer[1024];
        static int editing_player = -1;
        static bool show_splitscreen;

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("Splitscreen")) {
                auto p_profile = AlphaRing::Global::MCC::Profile();

                ImGui::MenuItem(p_profile->b_override ? "Disable" : "Enable", nullptr, &p_profile->b_override);
                ImGui::PushItemWidth(200);ImGui::InputInt("Players", &p_profile->player_count);ImGui::PopItemWidth();

                ImGui::Separator();

                ImGui::MenuItem("Override player1's profile", nullptr, &p_profile->b_override_player0);
                ImGui::MenuItem("Use player1's profile", nullptr, &p_profile->b_use_player0_profile);
                ImGui::MenuItem("Enable K/M for player1", nullptr, &p_profile->b_player0_use_km);

                ImGui::Separator();

                for (int i = 0; i < p_profile->player_count; ++i) {
                    sprintf(buffer, "Player %d", i + 1);
                    if (ImGui::MenuItem(buffer, nullptr, editing_player == i)) {
                        editing_player = i;
                        show_splitscreen = true;
                    }
                }

                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if (show_splitscreen && editing_player != -1) {
            sprintf(buffer, "Player %d", editing_player);
            if (ImGui::Begin(buffer, &show_splitscreen, 0))
                RealContext(editing_player);
            ImGui::End();
        } else if (editing_player != -1) {
            editing_player = -1;
        }
    }

    const unsigned int offsets[] = {0x1C,0x1D,0x1F,0x21,0x23,0x24,0x27,0x2C,0x30,0x34,0x1AC,0x1B5,0x1B6,0x1B7,0x1B8,0x1BC,0x1C8,0x1CB,0x1CC,0x1CD,0x1CE,0x1CF,0x1D0,0x1D1,0x1D2,0x1D3,0x1D4,0x1D5,0x1D6,0x1D8,0x1DC};

    void RealContext(int index) {
        char buffer[1024];
        auto p_profile = AlphaRing::Global::MCC::Profile();
        auto p_data = &p_profile->profiles[index];
        const char* items[] = {"Controller 1", "Controller 2", "Controller 3", "Controller 4", "NONE"};

        ImGui::PushItemWidth(200);
        sprintf(buffer, "%ls", p_data->name);
        if (ImGui::InputText("Name", buffer, sizeof(buffer)))
            wsprintfW(p_data->name, L"%hs", buffer);
        ImGui::PopItemWidth();

        if (index || !p_profile->b_player0_use_km) {
            ImGui::PushItemWidth(200);
            ImGui::Combo("Input", &p_data->controller_index, items, IM_ARRAYSIZE(items));
            ImGui::PopItemWidth();
        }

        auto p_button_names = p_profile->get_button_names();
        auto p_action_names = p_profile->get_action_names();

        for (int i = 0; i < 66; ++i) {
            ImGui::PushItemWidth(200);
            auto p_action_name = p_action_names[i];
            if (p_action_name == nullptr) {
                sprintf(buffer, "Button %d", i);
                p_action_name = buffer;
            }
            int value = p_data->gamepad_mapping[i];
            if (ImGui::Combo(p_action_name, &value, p_button_names, 15))
                p_data->gamepad_mapping[i] = value;
            ImGui::PopItemWidth();
        }
    }
}