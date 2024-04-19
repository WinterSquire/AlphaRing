#include "page_halo3.h"

#include "imgui.h"
#include "ui/Context.h"

namespace Halo3::Entry::Draw {
    extern bool getWireFrame();
    extern void setWireFrame(bool value);
}

void page_halo3_context() {
    bool bWireFrame = Halo3::Entry::Draw::getWireFrame();
    if (ImGui::Checkbox("Wireframe", &bWireFrame)) {
        Halo3::Entry::Draw::setWireFrame(bWireFrame);
    }
}

static Page page_halo3{900, "Halo3", page_halo3_context};