#include "home_page.h"

#include "hook/mcc/setting/setting.h"
#include "core/String.h"

#include <locale>
#include <codecvt>

#define InputInt(name, value, v_min, v_max) int _input_int_##name##_tmp_value = *value; \
if (ImGui::InputInt(#name, &_input_int_##name##_tmp_value) && _input_int_##name##_tmp_value >= v_min && _input_int_##name##_tmp_value <= v_max) \
    *value = _input_int_##name##_tmp_value;

void ImGui::CustomWidget::HomePage::render() {
    const char* tutorial_message = R"(TUTORIAL:

Press "F4" or "Start + Back" to toggle the menu.

To navigate using Controller use the "Right Stick" to move the mouse and "RB" to click.

Having this menu open will disable inputs or pause the game.
)";
    char buffer[1024];
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    auto p_profile_setting = ProfileSetting();
    auto p_input_setting = InputSetting();

    if (ImGui::Checkbox("Split Screen", &p_profile_setting->b_override)) {
        p_input_setting->override_input = p_profile_setting->b_override;
    }

    if (!p_profile_setting->b_override) {
        ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), tutorial_message);
        ImGui::PopTextWrapPos();
        return;
    }

    ImGui::SameLine();

    ImGui::PushItemWidth(150);
    InputInt(Players, &p_profile_setting->player_count, 1, 4);
    ImGui::PopItemWidth();

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
            const char* items[] = { "Controller 1", "Controller 2", "Controller 3", "Controller 4", "NONE" };

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
