#include "home_page.h"

#include "hook/mcc/setting/setting.h"
#include "core/String.h"

#define InputInt(name, value, v_min, v_max) int _input_int_##name##_tmp_value = *value; \
if (ImGui::InputInt(#name, &_input_int_##name##_tmp_value) && _input_int_##name##_tmp_value >= v_min && _input_int_##name##_tmp_value <= v_max) \
    *value = _input_int_##name##_tmp_value;

static struct Tab {
    const char* name;
    void (*render)();
} tabs[] = {
    { "Input", [] {
        auto p_setting = InputSetting();

        ImGui::Checkbox("Override Input", &p_setting->override_input);

        if (!p_setting->override_input) return;

        ImGui::SameLine();

        ImGui::Checkbox("Enable K/M For Player 1", &p_setting->enable_km);

        for (int i = 0; i < 4; ++i) {
            if (i || !p_setting->enable_km) {
                const char* items[] = { "Controller 1", "Controller 2", "Controller 3", "Controller 4", "NONE" };
                ImGui::Text("Player %d", i + 1);
                ImGui::PushID(i);
                ImGui::Combo("", &p_setting->controller_map[i], items, IM_ARRAYSIZE(items));
                ImGui::PopID();
            }
        }
    } },
    { "Coop", [] {
        const char* coop_warning_message = R"(WARNING:
    3 or 4 Players is not supported for Campaign in Halo CE, Halo 2, Halo 4 and Spartan Ops.
    Doing so will cause the map to not load or for the game to crash.
)";

        char buffer[MAX_NAME_LENGTH];
        auto p_setting = ProfileSetting();

        ImGui::Checkbox("Override Profile", &p_setting->b_override);

        if (!p_setting->b_override) return;

        ImGui::SameLine();

        ImGui::Checkbox("Override Player 1", &p_setting->b_override_player0);

        InputInt(PlayerCount, &p_setting->player_count, 1, 4);

        // Warning message for if Player Count is greater than 2 players.
        if (p_setting->player_count > 2) {
            ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), coop_warning_message);
            ImGui::PopTextWrapPos();
        }

        for (int i = !p_setting->b_override_player0; i < p_setting->player_count; ++i) {
            ImGui::Text("Player %d", i + 1);
            ImGui::PushID(i);
            String::strcpy(buffer, p_setting->profiles[i].name, MAX_NAME_LENGTH);
            if (ImGui::InputText("Name", buffer, MAX_NAME_LENGTH)) {
                String::wstrcpy(p_setting->profiles[i].name, buffer, MAX_NAME_LENGTH);
            }
            ImGui::PopID();
            
        }
    } },
};

void ImGui::CustomWidget::HomePage::render() {
    ImGui::BeginTabBar("mcc_tab");
    for (auto tab : tabs) {
        if (!ImGui::BeginTabItem(tab.name)) continue;
        tab.render();
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
}
