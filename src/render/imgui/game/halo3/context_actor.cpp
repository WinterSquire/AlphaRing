#include "CHalo3Context.h"

static bool show_context = false;

void CHalo3Context::context_actor() {
    if (ImGui::BeginMainMenuBar()) {
        ImGui::MenuItem("Actor", nullptr, &show_context);
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
