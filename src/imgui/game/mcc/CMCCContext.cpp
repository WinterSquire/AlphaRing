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

CMCCContext CMCCContext::instance;
ICContext* g_pMCCContext = &CMCCContext::instance;

void CMCCContext::render() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Alpha Ring")) {
            if (ImGui::MenuItem("Disable Input On Menu", nullptr, &InputSetting()->disable_input_on_menu)) {}
            if (ImGui::MenuItem("Patch", nullptr, &show_patch)) {}
            if (ImGui::MenuItem("Splitscreen", nullptr, &show_splitscreen)) {}
            if (ImGui::MenuItem("Tutorial", nullptr, &show_tutorial)) {}
            if (ImGui::MenuItem("About", nullptr, &show_about)) {}
            if (ImGui::MenuItem("Close", nullptr)) {MainRenderer()->ToggleContext();}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (show_patch) {
        ImGui::Begin("Patch", &show_patch);
        context_patch();
        ImGui::End();
    }

    if (show_splitscreen) {
        ImGui::Begin("Splitscreen", &show_splitscreen);
        context_splitscreen();
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

    if (ImGui::Checkbox("Split Screen", &p_profile_setting->b_override))
        p_input_setting->override_input = p_profile_setting->b_override;

    if (!p_profile_setting->b_override)
        return;

    ImGui::SameLine();

    ImGui::PushItemWidth(150);

    int tmp = p_profile_setting->player_count;
    if (ImGui::InputInt("Players", &tmp) && tmp >= 1 && tmp <= 4) {
        p_profile_setting->player_count = tmp;
    }

    ImGui::PopItemWidth();

    ImGui::Checkbox("Use Player1's Profile", &p_profile_setting->b_use_player0_profile);

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

static int counter = 0;

static void print_patch(Patch* patch) {
    bool enabled = patch->enabled();

    ImGui::PushID(counter++);
    if (ImGui::Checkbox(patch->name(), &enabled)) patch->setState(enabled);
    ImGui::PopID();

    if (ImGui::IsItemHovered() && patch->have_desc())
        ImGui::SetTooltip("%s", patch->desc());
}

void CMCCContext::context_patch() {
    if (ImGui::Button("Reload Patch")) {
        ModuleMCC()->reload_patch();
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
                print_patch(patch);

            ImGui::Text("Patches");
            for (auto patch : p_patches->patches())
                print_patch(patch);

            ImGui::EndTabItem();
        }
    }

    ImGui::EndTabBar();
}
