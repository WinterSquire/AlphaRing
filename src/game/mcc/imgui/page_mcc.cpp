#include "page_mcc.h"

#include "imgui.h"

#include "../module_watcher/module_watcher.h"

void MCC::IMGUI::page_mcc() {
    ImVec4 color;
    char buffer[256];

    ImGui::Text("Module Info");

    ImGui::Indent();

    ImGui::BeginGroup();
    ImGui::Text("Name");
    for (int i = 0; i < 7; ++i) {
        sprintf_s(buffer, "%s", ModuleInfo::cTitle[i]);
        ImGui::Text(buffer);
    }
    ImGui::EndGroup();

    ImGui::SameLine();

    ImGui::BeginGroup();
    ImGui::Text("Address");
    for (int i = 0; i < 7; ++i) {
        {
            auto status = ModuleWatcher()->getModuleStatus((ModuleInfo::eTitle)i);
            sprintf_s(buffer, "%016llx", status.get().hModule);
        }
        ImGui::Text(buffer);
    }
    ImGui::EndGroup();

    ImGui::SameLine();

    ImGui::BeginGroup();
    ImGui::Text("Status");
    for (int i = 0; i < 7; ++i) {
        int code;
        {
            auto status = ModuleWatcher()->getModuleStatus((ModuleInfo::eTitle)i);
            code = (int)(status.get().hModule == 0) + (status.get().errorCode != 0);
        }
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
}