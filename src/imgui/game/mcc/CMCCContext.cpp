#include "CMCCContext.h"

#include "core/String.h"
#include "hook/mcc/setting/setting.h"
#include "hook/mcc/module/Module.h"
#include "hook/d3d11/main_renderer.h"

static const char* tutorial_message = R"(TUTORIAL:

Press "F4" or "Start + Back" to toggle the menu.

To navigate using Controller use the "Right Stick" to move the mouse and "RB" to click.

Having this menu open will disable inputs or pause the game.
)";

static auto msg_about = R"(
        Alpha Ring
                Made by WinterSquire
)";

static bool show_tutorial = false;
static bool show_about = false;
static bool show_splitscreen = false;
static bool show_patch = false;
static bool show_network = false;

CMCCContext CMCCContext::instance;
ICContext* g_pMCCContext = &CMCCContext::instance;

void CMCCContext::render() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Alpha Ring")) {
            if (ImGui::BeginMenu("Options")) {
                ImGui::MenuItem("Disable Input On Menu", nullptr, &InputSetting()->disable_input_on_menu);
                bool tmp = MainRenderer()->GetShowMouse();
                if (ImGui::MenuItem("Hide Mouse On Menu", nullptr, &tmp))
                    MainRenderer()->SetShowMouse(tmp);

                ImGui::EndMenu();
            }

            ImGui::Separator();

            ImGui::MenuItem("Tutorial", nullptr, &show_tutorial);
            ImGui::MenuItem("About", nullptr, &show_about);
            if (ImGui::MenuItem("Close", nullptr)) {MainRenderer()->ToggleContext();}

            ImGui::Separator();

            ImGui::EndMenu();
        }

        ImGui::MenuItem("Patch", nullptr, &show_patch);
        ImGui::MenuItem("Splitscreen", nullptr, &show_splitscreen);
        ImGui::MenuItem("Network", nullptr, &show_network);

        ImGui::EndMainMenuBar();
    }

    if (show_patch) {
        ImGui::Begin("Patch", &show_patch, ImGuiWindowFlags_MenuBar);
        context_patch();
        ImGui::End();
    }

    if (show_splitscreen) {
        ImGui::Begin("Splitscreen", &show_splitscreen, ImGuiWindowFlags_MenuBar);
        context_splitscreen();
        ImGui::End();
    }

    if (show_network) {
        ImGui::Begin("Network", &show_network, ImGuiWindowFlags_MenuBar);
        context_network();
        ImGui::End();
    }

    if (show_tutorial) {
        ImGui::Begin("Tutorial", &show_tutorial);
        ImGui::Text(tutorial_message);
        ImGui::End();
    }

    if (show_about) {
        ImGui::Begin("About", &show_about);
        ImGui::Text(msg_about);
        ImGui::End();
    }
}

void CMCCContext::context_splitscreen() {
    char buffer[1024];
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    auto p_profile_setting = ProfileSetting();
    auto p_input_setting = InputSetting();

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

void CMCCContext::context_patch() {
    static int counter;
    auto p_print = [](Patch* patch) {
        bool enabled = patch->enabled();

        ImGui::PushID(counter++);
        if (ImGui::Checkbox(patch->name(), &enabled)) patch->setState(enabled);
        ImGui::PopID();

        if (ImGui::IsItemHovered() && patch->have_desc())
            ImGui::SetTooltip("%s", patch->desc());
    };

    if (ImGui::BeginMenuBar()) {
        if (ImGui::MenuItem("Reload Patch")) ModuleMCC()->reload_patch();

        ImGui::EndMenuBar();
    }

    if (!ImGui::BeginTabBar("patch")) return;

    counter = 0;

    for (int i = MODULE_HALO1; i < MODULE_MCC; ++i) {
        auto p_patches = ModuleMCC()
                ->get((eModule)i)
                ->patches();

        if (ImGui::BeginTabItem(cModuleName[i])) {
            ImGui::Text("Embed Patches");
            for (auto patch : p_patches->embed_patches())
                p_print(patch);

            ImGui::Text("Patches");
            for (auto patch : p_patches->patches())
                p_print(patch);

            ImGui::EndTabItem();
        }
    }

    ImGui::EndTabBar();
}

void CMCCContext::context_network() {
    static RequestInfo* current_info = nullptr;

    if (ImGui::BeginMenuBar()) {
        ImGui::MenuItem(NetworkSetting()->b_enable_capture ? "Disable Capture" : "Enable Capture",
                        nullptr, &NetworkSetting()->b_enable_capture);

        if (ImGui::MenuItem("Clear")) {
            current_info = nullptr;
            NetworkSetting()->clear();
        }

        ImGui::EndMenuBar();
    }

    NetworkSetting()->execute([](std::vector<RequestInfo*>& requests) {
        int index = 0;
        ImGui::BeginChild("Request List", {ImGui::GetWindowWidth() * 0.4f, 0});
        for (auto info : requests) {
            ImGui::PushID(index);
            if (ImGui::Selectable(info->url.c_str() + info->url_length, current_info == info))
                current_info = info;
            ImGui::PopID();
            ++index;
        }
        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::BeginChild("Requests Detail");
        if (current_info != nullptr) {
            ImGui::Text("Method: %s", current_info->method.c_str());
            ImGui::InputText("url", current_info->url.data(), current_info->url.size(), ImGuiInputTextFlags_ReadOnly);
            ImGui::InputTextMultiline("headers", current_info->headers.data(), current_info->headers.size(), ImVec2(0, 0), ImGuiInputTextFlags_ReadOnly);
            ImGui::InputTextMultiline("body", current_info->body.data(), current_info->body.size(), ImVec2(0, 0), ImGuiInputTextFlags_ReadOnly);
            ImGui::InputTextMultiline("response", current_info->response.data(), current_info->response.size(), ImVec2(0, 0), ImGuiInputTextFlags_ReadOnly);
        }
        ImGui::EndChild();
    });
}
