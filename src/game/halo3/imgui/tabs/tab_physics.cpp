#include "../basic_widget.h"

#include "game/halo3/native_halo3.h"

class TabPhysics : public BasicWidget {
public:
    TabPhysics(const char* name) : BasicWidget(name) {}
    void render() override;
    void update() override{}
};

static TabPhysics s_instance("Physics");
BasicWidget* tab_physics = &s_instance;

void TabPhysics::render() {
    ImGui::Checkbox("Enable Bump Possession", &Halo3::Physics::BumpPossession()->enable);

    auto p_physics_constant = Halo3::Native::PhysicsConstant();

    if (p_physics_constant != nullptr) {
        ImGui::DragFloat("Gravity", &p_physics_constant->gravity, 0.1f);
        if (ImGui::Button("Reset Gravity")) {
            p_physics_constant->set_gravity(1.0f);
        }
    }

}
