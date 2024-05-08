#include "../basic_widget.h"

#include "game/halo3/native/native.h"

class TabPhysics : public BasicWidget {
public:
    TabPhysics(const char* name) : BasicWidget(name) {}
    void render() override;
    void update() override{}
};

static TabPhysics s_instance("Physics");
BasicWidget* tab_physics = &s_instance;

void TabPhysics::render() {
    auto p_physics = NativeHalo3()->Physics();

    if (p_physics == nullptr) return;

    ImGui::Checkbox("Enable Bump Possession", &p_physics->BumpPossessionSetting()->enable);

    auto p_physics_constant = p_physics->PhysicsConstant();
    if (p_physics_constant != nullptr) {
        ImGui::DragFloat("Gravity", &p_physics_constant->gravity, 0.1f);
        if (ImGui::Button("Reset Gravity")) {
            p_physics_constant->set_gravity(1.0f);
        }
    }

}
