#include "CHalo3Context.h"

static bool show_context = false;

void CHalo3Context::context_physics() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Physics")) {
            if (ImGui::MenuItem("Show Physics Context", nullptr, &show_context)) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (!show_context) return;

    if (ImGui::Begin("Physics", &show_context)) {
        ImGui::Checkbox("Enable Bump Possession", &Halo3::Physics::BumpPossession()->enable);

        auto p_physics_constant = Halo3::Native::PhysicsConstant();

        if (p_physics_constant != nullptr) {
            ImGui::DragFloat("Gravity", &p_physics_constant->gravity, 0.1f);
            if (ImGui::Button("Reset Gravity")) {
                p_physics_constant->set_gravity(1.0f);
            }
        }
    }
}
