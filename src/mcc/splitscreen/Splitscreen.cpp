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

#include "../CGameEngine.h"

#include "imgui.h"

#include <string>

namespace MCC::Splitscreen {
    void RealContext();

    void ImGuiContext() {
        static bool show_splitscreen;

        if (ImGui::BeginMainMenuBar()) {
            ImGui::MenuItem("Splitscreen", nullptr, &show_splitscreen);
            ImGui::EndMainMenuBar();
        }

        if (show_splitscreen) {
            if (ImGui::Begin("Splitscreen", &show_splitscreen, ImGuiWindowFlags_MenuBar))
                RealContext();
            ImGui::End();
        }
    }

    void ProfileContext(int index) {
        char buffer[1024];
        auto p_profile = AlphaRing::Global::MCC::Profile();
        auto p_data = &p_profile->profiles[index];
        const char* items[] = {"Controller 1", "Controller 2", "Controller 3", "Controller 4", "NONE"};

        if (ImGui::Button("Load Profile")) {
            __int64 xuid;
            auto p_mng = GameManager();
            auto p_engine = GameEngine();
            if (p_mng) {
                CGameManager::get_xbox_user_id(p_mng, &xuid, nullptr, 0, 0);
                memcpy(&p_data->profile, p_mng->ppOriginal.get_player_profile(p_mng, xuid), sizeof(CUserProfile));
                memcpy(&p_data->mapping, p_mng->ppOriginal.retrive_gamepad_mapping(p_mng, xuid), sizeof(CGamepadMapping));
                if (p_engine)
                    p_engine->load_setting();
            }
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Use this in game!!! Or the game will crash!!!");

        ImGui::PushItemWidth(200);
        String::convert(buffer, p_data->name, 1024);
        if (ImGui::InputText("Name", buffer, sizeof(buffer)))
            String::convert(p_data->name, buffer, 1024);
        ImGui::PopItemWidth();

        ImGui::BeginDisabled(!index && p_profile->b_player0_use_km);
        ImGui::PushItemWidth(200);ImGui::Combo("Input", &p_data->controller_index, items, IM_ARRAYSIZE(items));ImGui::PopItemWidth();
        ImGui::EndDisabled();

        ImGui::BeginDisabled(!index && !p_profile->b_override_player0);

        if (ImGui::CollapsingHeader("Gamepad Mapping")) {
            ImGui::Indent();
            p_data->mapping.ImGuiContext();
            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Profile")) {
            ImGui::Indent();
            p_data->profile.ImGuiContext();
            ImGui::Unindent();
        }

        ImGui::EndDisabled();
    }

    void RealContext() {
        char buffer[10];
        auto p_profile = AlphaRing::Global::MCC::Profile();

        if (ImGui::BeginMenuBar()) {
            ImGui::MenuItem(p_profile->b_override ? "Disable" : "Enable", nullptr, &p_profile->b_override);
            if (ImGui::BeginMenu("Options")) {
                ImGui::MenuItem("Override player1's profile", nullptr, &p_profile->b_override_player0);
                ImGui::MenuItem("Use player1's profile", nullptr, &p_profile->b_use_player0_profile);
                ImGui::MenuItem("Enable K/M for player1", nullptr, &p_profile->b_player0_use_km);
                ImGui::EndMenu();
            }
            ImGui::PushItemWidth(200);ImGui::InputInt("Players", &p_profile->player_count);ImGui::PopItemWidth();
            ImGui::EndMenuBar();
        }

        if (ImGui::BeginTabBar("Players")) {
            for (int i = 0; i < p_profile->player_count; ++i) {
                sprintf(buffer, "Player %d", i + 1);
                if (ImGui::BeginTabItem(buffer)) {
                    ProfileContext(i);
                    ImGui::EndTabItem();
                }
            }
            ImGui::EndTabBar();
        }
    }
}