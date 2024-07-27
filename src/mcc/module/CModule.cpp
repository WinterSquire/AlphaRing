#include <unordered_map>
#include "CModule.h"

CModule::CModule(EntrySet *entrySet, std::initializer_list<CPatch> patches)
: m_entries(entrySet), m_patches(patches) {};

void CModule::load_module(const module_info_t *p_info) {
    if (p_info == nullptr) return;

    m_info = *p_info;

    if (m_info.hModule == 0 || m_info.errorCode != 0) return;

    m_patches.update(m_info.hModule);

    m_patches.apply();

    if (m_entries)
        m_entries->update(m_info.hModule);
}

void CModule::unload_module() {
    memset(&m_info, 0, sizeof(module_info_t));
}

#include "mcc/module/entry/halo1/halo1.h"
#include "offset_halo2.h"
#include "mcc/module/entry/halo3/halo3.h"
#include "mcc/module/entry/halo3odst/halo3odst.h"
#include "mcc/module/entry/haloreach/haloreach.h"
#include "mcc/module/entry/halo4/halo4.h"
#include "mcc/module/entry/groundhog/groundhog.h"

static struct {
    CModule halo1;
    CModule halo2;
    CModule halo3;
    CModule halo4;
    CModule groundhog;
    CModule halo3odst;
    CModule haloreach;
} modules {
    {nullptr, {
        {"splitscreen_patch1", "", OFFSET_HALO1_PF_4PLAYERS, "\xEB\x18", true},
        {"splitscreen_patch2", "", OFFSET_HALO1_PF_PAUSE, "\xEB", true},
        {"splitscreen_patch3", "", OFFSET_HALO1_PF_IDK, "\x90\x90\x90\x90\x90\x90", true}, // fix [issue](https://github.com/WinterSquire/AlphaRing/issues/19)
}}, {nullptr, {
        {"splitscreen_patch1", "", OFFSET_HALO2_PF_PLAYER_VALID, "\x31\xC0\xB0\x01\xC3\x90", true},
        {"splitscreen_patch2", "", OFFSET_HALO2_PF_PLAYER_COUNT1, "\x04", true},
        {"splitscreen_patch3", "", OFFSET_HALO2_PF_PLAYER_COUNT2, "\x04", true},
        {"splitscreen_patch4", "force making splitscreen works with more than 2 players", 0x5153E, "\x83\xF8\x01\x74\x04", true},
}}, {Halo3EntrySet(), {
        {"splitscreen_patch1", "", OFFSET_HALO3_PF_COOP_JOIN, "\x31\xC0\xC3\x90", true},
        {"Remove Black Bar1", "remove black bar", 0x8AD160, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x3F", true},
        {"Remove Black Bar2", "remove black bar", 0x8AD174, "\x00\x00\x00\x00\x00\x00\x00\x3F\x00\x00\x80\x3F", true},
        {"Remove Black Bar3", "remove black bar", 0x8AD1B0, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x3F", true},
}}, {nullptr, {
        {"splitscreen_patch1", "", OFFSET_HALO4_PF_COOP_JOIN, "\x31\xC0\xC3\x90", true},
        {"splitscreen_patch2", "", OFFSET_HALO4_PF_COOP_REJOIN, "\xEB", true},
        {"splitscreen_patch3", "", OFFSET_HALO4_PF_COOP_PLAYER_LIMIT, "\x90\x90\x90\x90\x90\x90", true},
        {"Remove Black Bar1", "remove black bar", 0xE84E40, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x3F\x00\x00\x00\x3F\x01", false},
        {"Remove Black Bar2", "remove black bar", 0xE84E54, "\x00\x00\x00\x00\x00\x00\x00\x3F\x00\x00\x80\x3F\x00\x00\x80\x3F\x01", false},
        {"Remove Black Bar3", "remove black bar", 0xE84E90, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x3F\x00\x00\x00\x3F\x01", false},
}}, {nullptr, {
        {"splitscreen_patch1", "", OFFSET_GROUNDHOG_PF_COOP_JOIN, "\x31\xC0\xC3\x90", true},
        {"splitscreen_patch2", "", OFFSET_GROUNDHOG_PF_REJOIN, "\xEB", true},
        {"Remove Black Bar1", "remove black bar", 0xE76560, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x3F\x00\x00\x00\x3F\x01", false},
        {"Remove Black Bar2", "remove black bar", 0xE76574, "\x00\x00\x00\x00\x00\x00\x00\x3F\x00\x00\x80\x3F\x00\x00\x80\x3F\x01", false},
        {"Remove Black Bar3", "remove black bar", 0xE765B0, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x3F\x00\x00\x00\x3F\x01", false},
}}, {nullptr, {
        {"splitscreen_patch1", "", OFFSET_HALO3ODST_PF_COOP_JOIN, "\x31\xC0\xC3\x90", true},
        {"Remove Black Bar1", "remove black bar", 0x8F1FC0, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x3F", true},
        {"Remove Black Bar2", "remove black bar", 0x8F1FD4, "\x00\x00\x00\x00\x00\x00\x00\x3F\x00\x00\x80\x3F", true},
        {"Remove Black Bar3", "remove black bar", 0x8F2010, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x3F", true},
}}, {nullptr, {
        {"splitscreen_patch1", "", OFFSET_HALOREACH_PF_COOP_JOIN, "\x31\xC0\xC3\x90", true},
        {"splitscreen_patch2", "", OFFSET_HALOREACH_PF_COOP_REJOIN, "\xEB", true},
        {"Remove Black Bar1", "remove black bar", 0xB43D10, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x3F\x00\x00\x00\x3F\x01", true},
        {"Remove Black Bar2", "remove black bar", 0xB43D24, "\x00\x00\x00\x00\x00\x00\x00\x3F\x00\x00\x80\x3F\x00\x00\x80\x3F\x01", true},
        {"Remove Black Bar3", "remove black bar", 0xB43D60, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x3F\x00\x00\x00\x3F\x01", true},
}}};

static std::unordered_map<std::string, CModule*> map_modules {
    {"halo1.dll", &modules.halo1 + 0},
    {"halo2.dll", &modules.halo1 + 1},
    {"halo3.dll", &modules.halo1 + 2},
    {"halo4.dll", &modules.halo1 + 3},
    {"groundhog.dll", &modules.halo1 + 4},
    {"halo3odst.dll", &modules.halo1 + 5},
    {"haloreach.dll", &modules.halo1 + 6},
};

namespace MCC::Module {
    CModule *GetSubModule(int module) {
        return &modules.halo1 + module;
    }

    CModule *GetSubModule(const char *module_name) {
        auto it = map_modules.find(module_name);
        if (it == map_modules.end())
            return nullptr;
        return it->second;
    }
}
