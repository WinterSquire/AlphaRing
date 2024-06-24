#include "CHalo3Context.h"

#include "common.h"

static bool show_context = false;
static bool bFilter[14];
static int selected_object = -1;
static void print_object(int index);

void CHalo3Context::context_object() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Object")) {
            if (ImGui::MenuItem("Show Object Context", nullptr, &show_context)) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (!show_context) return;

    char buffer[1024];
    auto mng = Halo3::Native::Objects();
    if (mng == nullptr) return;

    if (ImGui::Begin("Object", &show_context, ImGuiWindowFlags_MenuBar)) {
        // MenuBar
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Filter")) {
                for (int i = 0; i < sizeof(bFilter); ++i)
                    if (ImGui::MenuItem(eObjectTypeName[i], NULL, bFilter[i]))
                        bFilter[i] = !bFilter[i];
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // body
        {
            const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();

            ImGui::BeginChild("Object Memory View", {0, -footer_height_to_reserve});
            {
                ImGui::BeginChild("Object List", {ImGui::GetWindowWidth() * 0.4f, 0});
                auto p_tag_names = Halo3::Native::TagName();
                for (Index i = 0; p_tag_names && i < mng->m_capacity; ++i) {
                    auto object = mng->get(i)->address;
                    if (object == nullptr || !bFilter[object->type]) continue;
                    auto tag_name = p_tag_names->get(object->datum);
                    if (tag_name == nullptr) continue;
                    tag_name = strrchr(tag_name, '\\');
                    if (tag_name == nullptr) continue;
                    sprintf(buffer, "%d %s", i, tag_name + 1);
                    if (ImGui::Selectable(buffer, i == selected_object))
                        selected_object = i;
                }
                ImGui::EndChild();
            }
            ImGui::SameLine();
            {
                ImGui::BeginChild("Object View");
                print_object(selected_object);
                ImGui::EndChild();
            }
            ImGui::EndChild();
        }

        ImGui::Separator();

        // foot
        sprintf(buffer, "Stats: Size(%d), Capacity(%d)", mng->m_size, mng->m_capacity);
        ImGui::Text(buffer);
    }
    ImGui::End();
}

static void print_object(int index) {
    const char* object_format = R"(
Object:
    Datum: %X
    Parent Object: %X
    Child Object: %X
    Position: %.2f %.2f %.2f
    Type: %s
)";
    const char* unit_format = R"(
Unit:
    Actor: %X
    Player: %X
    Aim Target: %X
    Bump Target: %X
    Bump Time: %hhd
)";
    bool b;
    char buffer[1024];

    auto mng = Halo3::Native::Objects();

    if (mng == nullptr || index < 0 || index > mng->m_capacity) return;

    auto p_object = mng->get(index)->address;
    Halo3::Native::Objects_t::units_t* p_unit = nullptr;

    if (p_object == nullptr) return;
    //============================== OBJECT ==============================

    if (ImGui::IsKeyPressed(ImGuiKey_F1, false)) {
        LOG_INFO("Object: {:x}", (__int64)p_object);
    }

    if (p_object->isUnit()) p_unit = (Halo3::Native::Objects_t::units_t*)p_object;

    sprintf(buffer, object_format,
            p_object->datum, p_object->parent_object_index, p_object->next_object_index,
            p_object->position.x, p_object->position.y, p_object->position.z,
            eObjectTypeName[p_object->type]
    );

    ImGui::Text(buffer);

    ImGui::SliderFloat("Scale", &p_object->scale, 0.001f, 10.0f);
    ImGui::SliderFloat("Health", &p_object->health, 0.001f, 100.0f);
    ImGui::SliderFloat("Shield", &p_object->shield, 0.0f, 100.0f);

    ImGui::Text("Damage Flags");
    {
        ImGui::Indent();
        b = p_object->CannotDieFromDamage();
        if (ImGui::Checkbox("CannotDieFromDamage", &b)) p_object->CannotDieFromDamage(b);
        b = p_object->CannotTakeDamage();
        if (ImGui::Checkbox("CannotTakeDamage", &b)) p_object->CannotTakeDamage(b);
        if (ImGui::Button("Kill")) p_object->kill();
        ImGui::Unindent();
    }

    // Color
    ImGui::Text("Change Colors");
    auto count = *(__int16*)((__int64)p_object + 0x146) / 12;
    auto offset = *(__int16*)((__int64)p_object + 0x148);
    for (int i = 0; i < count; ++i) {
        ImGui::PushID(i);
        if (ImGui::SliderFloat3("Color", (float*)((__int64)p_object + offset + 12 * i), 0.0f, 1.0f)) {
            int INDEX = mng->INDEX(index);
            setState([INDEX]{
                Halo3::Native::Function::object_change_color(INDEX);
            });
        }
        ImGui::PopID();
    }

    //============================== UNIT ==============================
    if (p_unit == nullptr) return;

    sprintf(buffer, unit_format,
            p_unit->actor_index, p_unit->player_index,
            p_unit->aim_target, p_unit->bump_target, p_unit->bump_close
    );

    ImGui::Text(buffer);

    if (ImGui::SliderFloat("Camo", &p_unit->camo_time, 0, 10.0f)) p_unit->EnableCamo();
    ImGui::Combo("Team", (int*)&p_unit->team, eTeamAIName, sizeof(eTeamAIName) / sizeof(const char *));
    b = p_unit->FlashLight(); if (ImGui::Checkbox("FlashLight", &b)) p_unit->FlashLight(b);
    b = p_unit->CanMove(); if (ImGui::Checkbox("CanMove", &b)) p_unit->CanMove(b);

    if (ImGui::Button("Possess")) {
        INDEX target = mng->INDEX(index);
        setState([target]{
            Halo3::Native::Function::player_possess(0, target);
        });
    }
}
