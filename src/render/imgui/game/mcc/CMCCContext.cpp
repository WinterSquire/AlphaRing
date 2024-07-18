#include "CMCCContext.h"

#include "global/Global.h"

#include "mcc/network/Network.h"
#include "mcc/splitscreen/Splitscreen.h"
#include "mcc/module/Module.h"

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

CMCCContext CMCCContext::instance;
ICContext* g_pMCCContext = &CMCCContext::instance;

void CMCCContext::render() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Alpha Ring")) {
            if (ImGui::BeginMenu("Options")) {
                {ImGui::MenuItem("On Menu", nullptr, false, false);
                    ImGui::MenuItem("Pause Game", nullptr, &AlphaRing::Global::Global()->pause_game_on_menu_shown);
                    ImGui::MenuItem("Disable Input", nullptr, &AlphaRing::Global::Global()->disable_input_on_menu_shown);
                    ImGui::MenuItem("Show Mouse", nullptr, &AlphaRing::Global::Global()->show_imgui_mouse);
                }
                {ImGui::MenuItem("Render", nullptr, false, false);
                    ImGui::MenuItem("Wireframe", nullptr, &AlphaRing::Global::Global()->wireframe);
                }
                ImGui::EndMenu();
            }

            ImGui::MenuItem("Tutorial", nullptr, &show_tutorial);
            ImGui::MenuItem("About", nullptr, &show_about);
            if (ImGui::MenuItem("Close", nullptr)) AlphaRing::Global::Global()->show_imgui = false;
//            if (ImGui::MenuItem("Exit", nullptr)) ExitProcess(1);
            ImGui::EndMenu();
        }

        ImGui::Separator();

        ImGui::EndMainMenuBar();
    }

    MCC::Module::ImGuiContext();

    MCC::Splitscreen::ImGuiContext();

    MCC::Network::ImGuiContext();

    if (ImGui::BeginMainMenuBar()) {
        ImGui::Separator();
        ImGui::EndMainMenuBar();
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
