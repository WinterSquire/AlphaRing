#include "Module.h"

#include <functional>
#include <Windows.h>

#include "tinyxml2.h"

#include "common.h"
#include "offset_mcc.h"

namespace MCC::Module {
    DefDetourFunction(void, __fastcall, module_load, module_info_t* info, int a2, __int64 a3) {
        ppOriginal_module_load(info, a2, a3);
        GetSubModule(info->title)->load_module(info);
    }

    DefDetourFunction(__int64, __fastcall, module_unload, module_info_t* info) {
        GetSubModule(info->title)->unload_module();
        return ppOriginal_module_unload(info);
    }

    bool Initialize() {
        bool result;

        result = AlphaRing::Hook::Detour({
            {OFFSET_MCC_PF_MODULELOAD, OFFSET_MCC_WS_PF_MODULELOAD,  module_load, (void **)&ppOriginal_module_load},
            {OFFSET_MCC_PF_MODULEUNLOAD, OFFSET_MCC_WS_PF_MODULEUNLOAD, module_unload, (void **)&ppOriginal_module_unload},
        });

        assertm(result, "MCC:Module: failed to create hook");

        result = AlphaRing::Hook::Patch("KERNEL32.DLL", {
            {"IsDebuggerPresent", "\x31\xC0\xC3\x90\x90\x90\x90", 7}
        });

        assertm(result, "MCC:Module: failed to patch module \"kernel32.dll\"");

        CGameEngine** ppGameEngine = nullptr;

        AlphaRing::Hook::Offset({
            {0x3FFCAA8, 0, (void**)&ppGameEngine},
        });

        CGameEngine::Initialize(ppGameEngine);

        return true;
    }
}

bool MCC::Module::ReloadPatch(const char *xml_path) {
    FILE* file;
    wchar_t wbuffer[MAX_PATH];

    auto p_converter = [](const std::string& hex) {
        std::vector<__int8> bytes;

        for (unsigned int i = 0; i < hex.length(); i += 3) {
            std::string byteString = hex.substr(i, 2);
            auto byte = static_cast<__int8>(std::stoi(byteString, nullptr, 16));
            bytes.push_back(byte);
        }

        return bytes;
    };

    AlphaRing::Filesystem::GetDir(xml_path, wbuffer);

    if (_wfopen_s(&file, wbuffer, L"rb") != 0) return false;

    tinyxml2::XMLDocument doc;

    doc.LoadFile(file);

    auto root = doc.FirstChildElement();

    if (root == nullptr) return false;

    for (int i = MODULE_HALO1; i < MODULE_MCC; ++i) {
        GetSubModule(i)->patches()->clear();
    }

    for (auto element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement()) {
        auto p_module_name = element->Attribute("name");
        auto p_module_version = element->Attribute("version");

        if (p_module_name == nullptr || p_module_version == nullptr) return false;

        auto p_module = GetSubModule(p_module_name);

        if (p_module == nullptr) continue;

        if (strcmp(p_module_version, GAME_VERSION) != 0) continue;

        for (auto patch = element->FirstChildElement(); patch != nullptr; patch = patch->NextSiblingElement()) {
            auto p_patch_name = patch->Attribute("name");
            auto p_patch_desc = patch->Attribute("desc");
            auto p_patch_offset = patch->Attribute("offset");
            auto p_patch_data = patch->Attribute("aob");
            auto p_patch_enable = patch->Attribute("default");

            if (p_patch_name == nullptr || p_patch_offset == nullptr || p_patch_data == nullptr) continue;

            if (p_patch_desc == nullptr) p_patch_desc = "";

            auto patch_enable = false;

            if (p_patch_enable != nullptr && strcmp(p_patch_enable, "true") == 0)
                patch_enable = true;

            try {
                p_module->patches()->add(p_patch_name, p_patch_desc,
                          std::strtoull(p_patch_offset, nullptr, 16),
                          p_converter(p_patch_data),patch_enable);
            } catch (std::exception& e) {
                LOG_ERROR("Patch %s: %s", p_patch_name, e.what());
                continue;
            }
        }
    }

    return true;
}

#include "imgui.h"

namespace MCC::Module {
    void ContextPatch();
    void ContextEngine();

    void ImGuiContext() {
        static bool show_patch;
        static bool show_engine;

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("Game")) {
                ImGui::MenuItem("Engine", nullptr, &show_engine);
                ImGui::MenuItem("Patch", nullptr, &show_patch);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if (show_patch) {
            if (ImGui::Begin("Patch", &show_patch, ImGuiWindowFlags_MenuBar))
                ContextPatch();
            ImGui::End();
        }

        if (show_engine) {
            if (ImGui::Begin("Engine", &show_engine, 0))
                ContextEngine();
            ImGui::End();
        }
    }

    void ContextEngine() {
        auto p_engine = GameEngine();

        if (p_engine == nullptr) {
            ImGui::Text("Engine not created");
            return;
        }

        ImGui::Text(R"(Summary:
    - Command Count: %d
    - Game Speed: %.2f
)", p_engine->count, p_engine->game_speed);

        if (ImGui::Button("Load Checkpoint")) p_engine->load_checkpoint();
        if (ImGui::Button("New Round")) p_engine->new_round();
        if (ImGui::Button("Pause Game")) p_engine->pause(true);
        if (ImGui::Button("Resume Game")) p_engine->pause(false);
        if (ImGui::Button("Restart Game")) p_engine->restart();
        if (ImGui::Button("Exit Game")) p_engine->exit();
    }

    void ContextPatch() {
        static int counter;
        auto p_print = [](CPatch* patch) {
            bool enabled = patch->enabled();

            ImGui::PushID(counter++);
            if (ImGui::Checkbox(patch->name(), &enabled)) patch->setState(enabled);
            ImGui::PopID();

            if (ImGui::IsItemHovered() && patch->have_desc())
                ImGui::SetTooltip("%s", patch->desc());
        };

        if (ImGui::BeginMenuBar()) {
            if (ImGui::MenuItem("Reload Patch")) ReloadPatch();

            ImGui::EndMenuBar();
        }

        if (!ImGui::BeginTabBar("patch")) return;

        counter = 0;

        for (int i = MODULE_HALO1; i < MODULE_MCC; ++i) {
            auto p_patches = GetSubModule((eModule)i)->patches();

            if (ImGui::BeginTabItem(cModuleName[i])) {
                ImGui::Text("Embed Patches");
                for (auto patch : p_patches->embed_patches())
                    p_print(patch);

                ImGui::Text("Patches");
                for (auto patch : p_patches->patches())
                    p_print(patch);

                ImGui::EndTabItem();
            }
        }

        ImGui::EndTabBar();
    }
}
