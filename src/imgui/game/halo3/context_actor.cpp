#include "CHalo3Context.h"

static bool show_context = false;

void CHalo3Context::context_actor() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Actor")) {
            if (ImGui::MenuItem("Show Actor Context", nullptr, &show_context)) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (!show_context) return;

    if (ImGui::Begin("Actor", &show_context)) {
        auto p_actor = Halo3::Native::Actor();

        if (p_actor == nullptr) return;

        ImGui::Checkbox("Enable Ai", &p_actor->enable_ai);
    }
    ImGui::End();
}
