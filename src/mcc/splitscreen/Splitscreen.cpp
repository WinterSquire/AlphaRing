#include "Splitscreen.h"

#include "input/Input.h"
#include "common.h"
#include "CGameManager.h"

#include "settings.h"

#include <offset_mcc.h>

static float (__fastcall* deltaTime)(long long qpc);

namespace MCC::Splitscreen {
    DefDetourFunction(__int64, __fastcall, get_index_by_xuid, void* a1, __int64 xuid) {
        auto p_setting = &Settings()->profile_setting;

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

    float DeltaTime(__int64 a1) {
        return deltaTime(a1);
    }

    // todo:: let other players have the ability to pause the game

    bool Initialize() {
        bool result;

        CGameManager* game_manager;
        CDeviceManager** device_manager;

        AlphaRing::Hook::Offset({
            {OFFSET_MCC_PF_DELTA_TIME, OFFSET_MCC_WS_PF_DELTA_TIME, (void**)&deltaTime},
            {0x3F76E50, 0, (void**)&game_manager},
            {0x3FFFFF8, 0, (void**)&device_manager},
        });

        assertm(game_manager != nullptr, "MCC:Splitscreen: failed to get GameManager");
        assertm(device_manager != nullptr, "MCC:Splitscreen: failed to get DeviceManager");

        result = CGameManager::Initialize(game_manager);

        assertm(result, "MCC:Splitscreen: failed to initialize GameManager");
        assertm(GameManager() != nullptr, "MCC:Splitscreen: GameManager is null"); // static instance

        result = CDeviceManager::Initialize(device_manager);

        assertm(result, "MCC:Splitscreen: failed to initialize DeviceManager");
//        assertm(DeviceManager() != nullptr, "MCC:Splitscreen: DeviceManager is null"); // heap memory

        result = AlphaRing::Hook::Detour({
            {0x2D01DC, 0, get_index_by_xuid, (void**)&ppOriginal_get_index_by_xuid},
        });

        assertm(result, "MCC:Splitscreen: failed to hook");

        return true;
    }
}

#include "imgui.h"

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

    void RealContext() {
        char buffer[1024];
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        auto p_profile_setting = &Settings()->profile_setting;
        auto p_input_setting = &Settings()->input_setting;

        if (ImGui::BeginMenuBar()) {
            if (ImGui::MenuItem(p_profile_setting->b_override ? "Disable Splitscreen" : "Enable Splitscreen",
                                nullptr, &p_profile_setting->b_override)) {
                p_input_setting->override_input = p_profile_setting->b_override;
            }

            if (!p_profile_setting->b_override) {
                ImGui::EndMenuBar();
                return;
            }

            ImGui::PushItemWidth(150);
            int tmp = p_profile_setting->player_count;
            if (ImGui::InputInt("Players", &tmp) && tmp >= 1 && tmp <= 4) {
                p_profile_setting->player_count = tmp;
            }
            ImGui::PopItemWidth();

            ImGui::MenuItem("Use Player1's Profile",nullptr, &p_profile_setting->b_use_player0_profile);

            ImGui::EndMenuBar();
        }

        for (int i = 0; i < p_profile_setting->player_count; ++i) {
            ImGui::Text("Player %d\n", i + 1);

            ImGui::Indent();

            if (i == 0) {
                ImGui::Checkbox("Enable K/M", &p_input_setting->enable_km);
                ImGui::SameLine();
                ImGui::Checkbox("Override Profile", &p_profile_setting->b_override_player0);
            }

            if (i || p_profile_setting->b_override_player0) {
                ImGui::Text("Name:");
                ImGui::SameLine();

                ImGui::PushID(i << 1 | 0);
                //todo: Wide Char Input Support
                String::strcpy(buffer, converter.to_bytes(p_profile_setting->profiles[i].name).c_str());
                ImGui::PushItemWidth(200);
                if (ImGui::InputText("", buffer, sizeof(buffer)))
                    String::wstrcpy(p_profile_setting->profiles[i].name, converter.from_bytes(buffer).c_str());
                ImGui::PopItemWidth();
                ImGui::PopID();
            }

            if (i || !p_input_setting->enable_km) {
                const char *items[] = {"Controller 1", "Controller 2", "Controller 3", "Controller 4", "NONE"};

                ImGui::Text("Input:");
                ImGui::SameLine();

                ImGui::PushID(i << 1 | 1);
                ImGui::PushItemWidth(200);
                ImGui::Combo("", &p_input_setting->controller_map[i], items, IM_ARRAYSIZE(items));
                ImGui::PopItemWidth();
                ImGui::PopID();
            }

            ImGui::Unindent();
        }
    }
}
