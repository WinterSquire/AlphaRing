#include "mcc.h"

#include "MinHook.h"

extern void ModuleLoad(void* info);
extern void ModuleUnload(void* info);

static __int64 OFFSET_MODULE_SET = 0x3FFD590; // p_module_set

static __int64 OFFSET_MODULE_LOAD = 0x442394;
static void (__fastcall *ppOriginal_ModuleLoad)(void* a1, int a2, __int64 a3);
static void __fastcall MODULE_LOAD_DETOUR(void* a1, int a2, __int64 a3) {
    ppOriginal_ModuleLoad(a1, a2, a3);
    ModuleLoad(a1);
}

static __int64 OFFSET_MODULE_UNLOAD = 0x4426F8; // rbx = p_module_info
static __int64 (__fastcall *ppOriginal_ModuleUnload)(void* a1);
static __int64 __fastcall MODULE_UNLOAD_DETOUR(void* a1) {
    auto result = ppOriginal_ModuleUnload(a1);
    ModuleUnload(a1);
    return result;
}

bool MCCHook::Initialize() {
    auto hModule = (__int64)GetModuleHandleA("MCC-Win64-Shipping.exe");

    if (hModule == 0) return false;

    auto status = MH_Initialize();

    if (!(status == MH_OK || status == MH_ERROR_ALREADY_INITIALIZED)) return false;

    status = MH_CreateHook((LPVOID) (hModule + OFFSET_MODULE_LOAD),
                           MODULE_LOAD_DETOUR,
                           (void **) &ppOriginal_ModuleLoad
    );

    if (status != MH_OK) return false;

    status = MH_EnableHook((LPVOID)(hModule + OFFSET_MODULE_LOAD)); // !! essential

    if (status != MH_OK) return false;

    status = MH_CreateHook((LPVOID) (hModule + OFFSET_MODULE_UNLOAD),
                           MODULE_UNLOAD_DETOUR,
                           (void **) &ppOriginal_ModuleUnload
    );

    if (status != MH_OK) return false;

    status = MH_EnableHook((LPVOID)(hModule + OFFSET_MODULE_UNLOAD)); // !! essential

    if (status != MH_OK) return false;

    return true;
}

void MCCHook::Shutdown() {
    MH_DisableHook(MH_ALL_HOOKS);
}
