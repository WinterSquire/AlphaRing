#include "CHalo3Context.h"

static bool show_context = false;

void CHalo3Context::context_physics() {
    if (ImGui::BeginMainMenuBar()) {
        ImGui::MenuItem("Physics", nullptr, &show_context);
        ImGui::EndMainMenuBar();
    }

    if (!show_context) return;

    if (ImGui::Begin("Physics", &show_context)) {
        ImGui::Checkbox("Enable Bump Possession", &AlphaRing::Global::Halo3::Physics()->enable_bump_possession);

        auto p_physics_constant = Halo3::Native::PhysicsConstant();

        if (p_physics_constant != nullptr) {
            ImGui::DragFloat("Gravity", &p_physics_constant->gravity, 0.1f);
            if (ImGui::Button("Reset Gravity")) {
                p_physics_constant->set_gravity(1.0f);
            }
        }
    }
}
