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
    auto object = mng->get(index)->address;
    if (object == nullptr) return;

    sprintf(buffer, format,
            object->datum, object->parent_object_index, object->next_object_index,
            object->position.x, object->position.y, object->position.z,
            eObjectTypeName[object->type]
        );

    ImGui::Text(buffer);
    ImGui::SliderFloat("Scale", &object->scale, 0.001f, 100.0f);
    ImGui::SliderFloat("Health", &object->health, 0.001f, 100.0f);
    ImGui::SliderFloat("Shield", &object->shield, 0.0f, 100.0f);
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

