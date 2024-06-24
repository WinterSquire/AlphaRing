#pragma once

#include "./patch/Patch.h"
#include "core/FileVersion.h"

enum eModule : __int32 {
    MODULE_HALO1 = 0,
    MODULE_HALO2 = 1,
    MODULE_HALO3 = 2,
    MODULE_HALO4 = 3,
    MODULE_GROUNDHOG = 4,
    MODULE_HALO3ODST = 5,
    MODULE_HALOREACH = 6,
    MODULE_MCC = 7,
};

inline static const char* cModuleName[] {
        "halo1",
        "halo2",
        "halo3",
        "halo4",
        "groundhog",
        "halo3odst",
        "haloreach",
        "MCC-Win64-Shipping"
};

struct module_info_t {
    __int32 title;
    __int32 errorCode;
    __int64 hModule;
};

class ICModule {
public:
    virtual inline void load_module(const module_info_t& info) = 0;
    virtual inline void load_module(const module_info_t *p_info) = 0;
    virtual inline void unload_module() = 0;

    virtual inline module_info_t info() = 0;
    virtual inline FileVersion version() = 0;
    virtual inline PatchSet* patches() = 0;
};

class ICModuleMCC {
public:
    virtual bool Init(__int64 hModule, bool isWS) = 0;
    virtual ICModule* get(int module) = 0;
    virtual inline FileVersion version() = 0;
    virtual bool reload_patch(const char* xml_path = "./alpha_ring/patch.xml") = 0;
};

extern ICModuleMCC* g_pModuleMCC;
inline ICModuleMCC* ModuleMCC() {return g_pModuleMCC;};
