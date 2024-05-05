#ifndef ALPHA_RING_MODULE_H
#define ALPHA_RING_MODULE_H

#include "../os/FileVersion.h"

enum eModule : __int32 {
    Halo1 = 0,
    Halo2 = 1,
    Halo3 = 2,
    Halo4 = 3,
    Groundhog = 4,
    Halo3ODST = 5,
    HaloReach = 6,
    MCC = 7,
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
};

class ICModules {
public:
    virtual ICModule* get(eModule module) = 0;

};

extern ICModules* g_pModules;
inline ICModules* Modules() {return g_pModules;};

#endif //ALPHA_RING_MODULE_H
