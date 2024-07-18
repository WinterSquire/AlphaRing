#pragma once

#include "mcc/module/patch/Patch.h"
#include "mcc/module/entry/entry.h"

#include <Windows.h>

#include "CGameEngine.h"

struct module_info_t {
    __int32 title;
    __int32 errorCode;
    __int64 hModule;

    void* create_data_access;
    void* un;
};

class CModule {
public:
    CModule(EntrySet* entrySet, std::initializer_list<CPatch> patches);

    void load_module(const module_info_t *p_info);

    void unload_module();

    inline module_info_t info() { return m_info;}
    inline CPatchSet* patches() {return &m_patches;}

private:
    module_info_t m_info;
    EntrySet* m_entries;
    CPatchSet m_patches;

    struct FunctionTable {
        __int64 (__fastcall* CreateDataAccess)(void *ppDataAccess); // todo: create class CDataAccess
        __int64 (__fastcall* CreateGameEngine)(CGameEngine** ppGameEngine);
        errno_t (__fastcall* SetLibrarySettings)(wchar_t *Source); // set language?
    };
    FunctionTable pTarget;
    FunctionTable ppOriginal;
};

namespace MCC::Module {
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

    CModule* GetSubModule(int module);
    CModule* GetSubModule(const char* module_name);
    inline CModule* GetSubModule(eModule module) {return GetSubModule((int)module);}
}