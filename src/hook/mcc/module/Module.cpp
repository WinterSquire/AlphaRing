#include "Module.h"

#include <functional>
#include <utility>

#include <Windows.h>

#include "./entry/halo1/halo1.h"
#include "offset_halo2.h"
#include "./entry/halo3/halo3.h"
#include "./entry/halo3odst/halo3odst.h"
#include "./entry/haloreach/haloreach.h"
#include "./entry/halo4/halo4.h"
#include "./entry/groundhog/groundhog.h"

#include "tinyxml2/tinyxml2.h"

#include "common.h"

class CModule : public ICModule {
public:
    CModule(const char* module_name, EntrySet* entrySet, std::initializer_list<Patch> patches)
    : m_module_name(module_name), m_entries(entrySet), m_patches(patches) {};

    void load_module(const module_info_t &info) override {
        load_module(&info);
    }

    void load_module(const module_info_t *p_info) override {
        wchar_t buffer[MAX_PATH];

        if (p_info == nullptr) return;

        memcpy(&m_info, p_info, sizeof(module_info_t));

        if (m_info.hModule == 0 || m_info.errorCode != 0) return;

        m_patches.update(m_info.hModule);

        m_patches.apply();

        if (m_entries)
            m_entries->update(m_info.hModule);

        if (GetModuleFileNameW((HMODULE)m_info.hModule, buffer, MAX_PATH) <= 0) return;

        m_version = FileVersion(buffer);
    }

    void unload_module() override {
        memset(&m_info, 0, sizeof(module_info_t));
        m_version = 0;
    }

    FileVersion version() override {return m_version;}
    module_info_t info() override { return m_info;}
    PatchSet* patches() override {return &m_patches;}
    const char* name() const {return m_module_name.c_str();}

private:
    std::string m_module_name;
    FileVersion m_version;
    module_info_t m_info;
    EntrySet* m_entries;
    PatchSet m_patches;
};

static const char* module_name[] = {
        "halo1.dll",
        "halo2.dll",
        "halo3.dll",
        "halo4.dll",
        "groundhog.dll",
        "halo3odst.dll",
        "haloreach.dll"
};

class CModules : public ICModuleMCC {
public:
    CModules(std::initializer_list<CModule> modules) {
        for (auto& module : modules) {
            m_modules.insert({module.name(), module});
        }
    }

    bool Init(__int64 hModule, bool isWS) override {
        wchar_t buffer[MAX_PATH];

        m_hModule = hModule;
        m_isWS = isWS;

        if (GetModuleFileNameW((HMODULE)hModule, buffer, MAX_PATH) <= 0)
            return false;

        m_version = FileVersion(buffer);

        reload_patch("../../../alpha_ring/patch.xml");

        return true;
    }

    ICModule *get(int module) override {
        return get(std::string(module_name[module]));
    }

    ICModule *get(const std::string &module_name) {
        auto it = m_modules.find(module_name);

        if (it == m_modules.end()) return nullptr;

        return &it->second;
    }

    bool reload_patch(const char* xml_path) override {
        FILE* file;
        char buffer[MAX_PATH];
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
            get(i)->patches()->clear();
        }

        for (auto element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement()) {
            auto p_module_name = element->Attribute("name");
            auto p_module_version = element->Attribute("version");

            if (p_module_name == nullptr || p_module_version == nullptr) return false;

            auto p_module = get(p_module_name);

            if (p_module == nullptr) continue;

            version().toString(buffer, sizeof(buffer));

            if (strcmp(p_module_version, buffer) != 0) continue;

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
                    auto p_patch =
                            new Patch(p_patch_name,
                                      p_patch_desc,
                                      std::strtoull(p_patch_offset, nullptr, 16),
                                      p_converter(p_patch_data),
                                      patch_enable);

                    p_module->patches()->add(p_patch);
                } catch (std::exception& e) {
                    LOG_ERROR("Patch %s: %s", p_patch_name, e.what());
                    continue;
                }
            }
        }

        return true;
    }

    FileVersion version() override {return m_version;}

    static CModules m_instance;
private:
    bool m_isWS;
    __int64 m_hModule;
    FileVersion m_version;
    std::unordered_map<std::string, CModule> m_modules;
};

CModules CModules::m_instance {
        { "halo1.dll", nullptr, {
            {"splitscreen_patch1", "", OFFSET_HALO1_PF_4PLAYERS, "\xEB\x18", true},
            {"splitscreen_patch2", "", OFFSET_HALO1_PF_PAUSE, "\xEB", true},
            {"splitscreen_patch3", "", OFFSET_HALO1_PF_IDK, "\x90\x90\x90\x90\x90\x90", true},
        }},{ "halo2.dll",nullptr, {
            {"splitscreen_patch1", "", OFFSET_HALO2_PF_PLAYER_VALID, "\x31\xC0\xB0\x01\xC3\x90", true},
            {"splitscreen_patch2", "", OFFSET_HALO2_PF_PLAYER_COUNT1, "\x04", true},
            {"splitscreen_patch3", "", OFFSET_HALO2_PF_PLAYER_COUNT2, "\x04", true},
        }},{ "halo3.dll",Halo3EntrySet(), {
            {"splitscreen_patch1", "", OFFSET_HALO3_PF_COOP_JOIN, "\x31\xC0\xC3\x90", true},
        }}, { "halo4.dll",nullptr, {
            {"splitscreen_patch1", "", OFFSET_HALO4_PF_COOP_JOIN, "\x31\xC0\xC3\x90", true},
            {"splitscreen_patch2", "", OFFSET_HALO4_PF_COOP_REJOIN, "\xEB", true},
            {"splitscreen_patch3", "", OFFSET_HALO4_PF_COOP_PLAYER_LIMIT, "\x90\x90\x90\x90\x90\x90", true},
        }}, { "groundhog.dll",nullptr, {
            {"splitscreen_patch1", "", OFFSET_GROUNDHOG_PF_COOP_JOIN, "\x31\xC0\xC3\x90", true},
            {"splitscreen_patch2", "", OFFSET_GROUNDHOG_PF_REJOIN, "\xEB", true},
        }}, { "halo3odst.dll",nullptr, {
            {"splitscreen_patch1", "", OFFSET_HALO3ODST_PF_COOP_JOIN, "\x31\xC0\xC3\x90", true},
        }}, { "haloreach.dll",nullptr, {
            {"splitscreen_patch1", "", OFFSET_HALOREACH_PF_COOP_JOIN, "\x31\xC0\xC3\x90", true},
            {"splitscreen_patch2", "", OFFSET_HALOREACH_PF_COOP_REJOIN, "\xEB", true},
        }}
};

ICModuleMCC* g_pModuleMCC = &CModules::m_instance;