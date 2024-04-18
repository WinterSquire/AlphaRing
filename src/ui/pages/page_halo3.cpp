#include "page_halo3.h"

#include "imgui.h"
#include "ui/Context.h"

void page_halo3_context() {
    ImGui::Text("Halo3!");
}

static Page page_halo3{900, "Halo3", page_halo3_context};