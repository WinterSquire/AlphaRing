#include "Splitscreen.h"

#include "common.h"

#include "global/Global.h"

#include <offset_mcc.h>

#include "../CGameManager.h"

namespace MCC::Splitscreen {
    DefDetourFunction(__int64, __fastcall, get_index_by_xuid, void* a1, __int64 xuid) {
        auto p_setting = AlphaRing::Global::MCC::Splitscreen();

        if (!p_setting->b_override)
            return ppOriginal_get_index_by_xuid(a1, xuid);

        return CGameManager::get_index(xuid);
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
        auto p_setting = AlphaRing::Global::MCC::Splitscreen();
        auto p_profile = CGameManager::get_profile(index);
        const char* items[] = {"Controller 1", "Controller 2", "Controller 3", "Controller 4", "NONE"};

        if (ImGui::Button("Load Profile")) {
            __int64 xuid;
            auto p_mng = GameManager();
            auto p_engine = GameEngine();
            if (p_mng && (xuid = CGameManager::get_xuid(0))) {
                memcpy(&p_profile->profile, p_mng->ppOriginal.get_player_profile(p_mng, xuid), sizeof(CUserProfile));
                memcpy(&p_profile->mapping, p_mng->ppOriginal.retrive_gamepad_mapping(p_mng, xuid), sizeof(CGamepadMapping));
                if (p_engine)
                    p_engine->load_setting();
            }
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Use this in game!!! Or the game will crash!!!");

        ImGui::PushItemWidth(200);
        String::convert(buffer, p_profile->name, 1024);
        if (ImGui::InputText("Name", buffer, sizeof(buffer)))
            String::convert(p_profile->name, buffer, 1024);
        ImGui::PopItemWidth();

        ImGui::BeginDisabled(!index && p_setting->b_player0_use_km);
        ImGui::PushItemWidth(200);ImGui::Combo("Input", &p_profile->controller_index, items, IM_ARRAYSIZE(items));ImGui::PopItemWidth();
        ImGui::EndDisabled();

        bool is_disabled = (!index && !p_setting->b_override_profile) || (index && p_setting->b_use_player0_profile);

        if (ImGui::CollapsingHeader("Gamepad Mapping")) {
            ImGui::Indent();
            ImGui::BeginDisabled(is_disabled);
            p_profile->mapping.ImGuiContext();
            ImGui::EndDisabled();
            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Profile")) {
            ImGui::Indent();
            ImGui::BeginDisabled(is_disabled);
            p_profile->profile.ImGuiContext();
            ImGui::EndDisabled();
            ImGui::Unindent();
        }
    }

    void RealContext() {
        char buffer[10];
        auto p_setting = AlphaRing::Global::MCC::Splitscreen();

        if (ImGui::BeginMenuBar()) {
            ImGui::MenuItem(p_setting->b_override ? "Disable" : "Enable", nullptr, &p_setting->b_override);
            if (ImGui::BeginMenu("Options")) {
                ImGui::MenuItem("Use player1's profile", nullptr, &p_setting->b_use_player0_profile);
                ImGui::MenuItem("Enable K/M for player1", nullptr, &p_setting->b_player0_use_km);
                ImGui::MenuItem("Override profile", nullptr, &p_setting->b_override_profile);
                ImGui::EndMenu();
            }
#pragma region player count
            ImGui::PushItemWidth(200);
            int count = p_setting->player_count;
            if (ImGui::InputInt("Players", &count) && count >= 1 && count <=4) {
                p_setting->player_count = count;
            }
            ImGui::PopItemWidth();
            ImGui::EndMenuBar();
#pragma endregion
        }

        if (ImGui::BeginTabBar("Players")) {
            for (int i = 0; i < p_setting->player_count; ++i) {
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