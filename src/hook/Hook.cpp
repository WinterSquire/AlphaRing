#include "Hook.h"
#include "common.h"

#include "MinHook.h"

#include "./d3d11/hook.h"
#include "module/Module.h"
#include "offset_mcc.h"

static void (__fastcall *ppOriginal_ModuleLoad)(module_info_t* info, int a2, __int64 a3);
static void __fastcall MODULE_LOAD_DETOUR(module_info_t* info, int a2, __int64 a3) {
    ppOriginal_ModuleLoad(info, a2, a3);
    Modules()->get((eModule)info->title)->load_module(info);
}

static __int64 (__fastcall *ppOriginal_ModuleUnload)(module_info_t* info);
static __int64 __fastcall MODULE_UNLOAD_DETOUR(module_info_t* info) {
    auto result = ppOriginal_ModuleUnload(info);
    Modules()->get((eModule)info->title)->unload_module();
    return result;
}

class CHook : public ISystem {
public:
    eStatus initialize() override;
    eStatus shutdown() override;

    static CHook s_instance;
};

CHook CHook::s_instance;
ISystem* g_pHook = &CHook::s_instance;

ISystem::eStatus CHook::initialize() {
    char buffer[1024];
    __int64 hModule;
    void* pTarget;

    if (MH_Initialize() != MH_OK) {
        LOG_ERROR("MinHook Fail To Initialize!");
        goto RET_ERROR;
    }

    if (Directx11Hook::Initialize() == false) {
        LOG_ERROR("Directx11 Hook Fail To Initialize!");
        goto RET_ERROR;
    }

    if ((hModule = (__int64)GetModuleHandleA("MCC-Win64-Shipping.exe")) == 0) goto RET_ERROR;

    auto p_mcc = Modules()->get(MCC);

    p_mcc->load_module({MCC,0, hModule});

    p_mcc->version().toString(buffer, sizeof(buffer));

    LOG_INFO("Game Version: {}", buffer);

    if ((pTarget = (LPVOID) (hModule + OFFSET_MCC_PF_MODULELOAD)),
            MH_CreateHook(pTarget, MODULE_LOAD_DETOUR,(void **) &ppOriginal_ModuleLoad) != MH_OK ||
            MH_EnableHook(pTarget) != MH_OK)
        goto RET_ERROR;

    if ((pTarget = (LPVOID) (hModule + OFFSET_MCC_PF_MODULEUNLOAD)),
            MH_CreateHook(pTarget,MODULE_UNLOAD_DETOUR,(void **) &ppOriginal_ModuleUnload) != MH_OK ||
            MH_EnableHook(pTarget) != MH_OK)
        goto RET_ERROR;

    LOG_INFO("Game Hook Initialized!");
    return SYS_OK;

    RET_ERROR:
    LOG_ERROR("Game Hook Failed To Initialize!");
    return SYS_ERROR;
}

ISystem::eStatus CHook::shutdown() {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    return SYS_OK;
}
