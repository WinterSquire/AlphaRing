#include "home_page.h"

#include "../module/Module.h"
#include "../game/halo3/native/native.h"
bool coop;

void ImGui::CustomWidget::HomePage::render() {
    const int MODULE_COUNT = 8;
    ImVec4 color;
    char buffer[256];
    struct Module {
        module_info_t info;
        FileVersion version;
    } modules[MODULE_COUNT];

    ImGui::Text("Module Info");

    ImGui::Indent();

    ImGui::BeginGroup();
    ImGui::Text("Name");
    for (int i = 0; i < MODULE_COUNT; ++i) {
        auto p_module = Modules()->get((eModule)i);
        modules[i] = {p_module->info(), p_module->version()};
        sprintf_s(buffer, "%s", cModuleName[i]);
        ImGui::Text(buffer);
    }
    ImGui::EndGroup();

    ImGui::SameLine();

    ImGui::BeginGroup();
    ImGui::Text("Version");
    for (int i = 0; i < MODULE_COUNT; ++i) {
        modules[i].version.toString(buffer, sizeof(buffer));
        ImGui::Text(buffer);
    }
    ImGui::EndGroup();

    ImGui::SameLine();

    ImGui::BeginGroup();
    ImGui::Text("Address");
    for (int i = 0; i < MODULE_COUNT; ++i) {
        sprintf_s(buffer, "%016llx", modules[i].info.hModule);
        ImGui::Text(buffer);
    }
    ImGui::EndGroup();

    ImGui::SameLine();

    ImGui::BeginGroup();
    ImGui::Text("Status");
    for (int i = 0; i < MODULE_COUNT; ++i) {
        int code = (int)(modules[i].info.hModule == 0) + (modules[i].info.errorCode != 0);
        switch (code) {
            case 0:
                color = {0.0f, 1.0f, 0.0f, 1.0f};
                break;
            case 1:
                color = {0.235f, 0.235f, 0.235f, 1.0f};
                break;
            case 2:
                color = {1.0f, 0.0f, 0.0f, 1.0f};
                break;
        }
        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::Text("*");
        ImGui::PopStyleColor(1);
    }
    ImGui::EndGroup();

    ImGui::Unindent();

    auto p_coop = NativeHalo3()->Players()->getPlayerCoop();

    if (ImGui::Checkbox("Coop", &coop)) {
        p_coop->enable = coop;
    }

    if (coop) {
        auto count = p_coop->count;
        if (ImGui::InputInt("Coop Count", &count) && count >= 1 && count <= 4) {
            p_coop->count = count;
        }
    }
}
