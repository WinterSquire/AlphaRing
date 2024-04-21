#include "tabs.h"

#include "game/halo3/objects/objects.h"
#include "game/halo3/tag_files/tag_files.h"

void print_object(__int16 index) {
    char buffer[1024];
    const char* format = R"(
    Datum: %X
    Parent Object: %X
    Child Object: %X
    Position: %.2f %.2f %.2f
    Type: %s
)";
    auto mng = Objects()->getObjectManager();
    if (mng == 0 || index < 0 || index > mng->m_capacity) return;
    auto p_object = mng->get(index)->address;
    if (p_object == nullptr) return;

    sprintf(buffer, format,
            p_object->datum, p_object->parent_object_index, p_object->next_object_index,
            p_object->position.x, p_object->position.y, p_object->position.z,
            eObjectTypeName[p_object->type]
        );

    ImGui::Text(buffer);
    ImGui::SliderFloat("Scale", &p_object->scale, 0.001f, 10.0f);
    ImGui::SliderFloat("Health", &p_object->health, 0.001f, 100.0f);
    ImGui::SliderFloat("Shield", &p_object->shield, 0.0f, 100.0f);
    if (ImGui::Button("Kill")) p_object->kill();
}

int selected_object = -1;

void Halo3::IMGUI::Tabs::tab_object() {
    char buffer[1024];
    auto mng = Objects()->getObjectManager();
    if (mng == nullptr) return;

    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();

    ImGui::BeginChild("Object Memory View", {0, -footer_height_to_reserve});
    {
        ImGui::BeginChild("Object List", {ImGui::GetWindowWidth() * 0.4f, 0});
        for (int i = 0; i < mng->m_capacity; ++i) {
            auto object = mng->get(i)->address;
            if (object == nullptr) continue;
            auto tag_name = TagFiles()->getTagName(object->datum);
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

    ImGui::Separator();
    sprintf(buffer, "Capacity: %d\tSize: %d", mng->m_capacity, mng->m_size);
    ImGui::Text(buffer);
}

