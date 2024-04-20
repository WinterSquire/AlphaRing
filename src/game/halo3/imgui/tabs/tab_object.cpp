#include "tabs.h"

#include "game/halo3/objects/objects.h"

void Halo3::IMGUI::Tabs::tab_object() {
    char buffer[1024];
    int count = Objects()->getObjectCount();

    sprintf(buffer, "Total Object: %d", count);

    ImGui::Text(buffer);
}

