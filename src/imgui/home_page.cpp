#include "home_page.h"

#include "input/Input.h"

void ImGui::CustomWidget::HomePage::render() {
    auto p_setting = InputSetting();

    ImGui::Checkbox("Override Input", &p_setting->override_input);

    if (p_setting->override_input) {
        ImGui::Checkbox("Enable K/M", &p_setting->enable_km);
        const char* players[] = { "1 Player", "2 Players", "3 Players", "4 Players" };
        ImGui::Text("Player Count:");
        ImGui::Combo("", &p_setting->playercount, players, IM_ARRAYSIZE(players));
        for (int i = 0; i < p_setting->playercount + 1; ++i) {
            if (i || !p_setting->enable_km) {
                const char* items[] = { "Controller 0", "Controller 1", "Controller 2", "Controller 3", "NONE" };
                ImGui::Text("Player %d", i + 1);
                ImGui::PushID(i);
                ImGui::Combo("", &p_setting->controller_map[i], items, IM_ARRAYSIZE(items));
                ImGui::PopID();
            }
        }
    }
}
