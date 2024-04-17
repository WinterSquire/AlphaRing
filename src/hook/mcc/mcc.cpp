#include "mcc.h"
#include "asm/asm.h"

#include "MinHook.h"

using Callback_t = void(*)(void*);

struct ModuleInfo;
extern void ModuleLoad(ModuleInfo *info);
extern void ModuleUnload(ModuleInfo *info);

static __int64 OFFSET_MODULE_SET = 0x3FFD590; // p_module_set

static __int64 OFFSET_MODULE_LOAD = 0x4426AC; // r14 = p_module_info
static __int64 ppOriginal_ModuleLoad = 0;
static Callback_t s_load_callback = nullptr;

static __int64 OFFSET_MODULE_UNLOAD = 0x442728; // rbx = p_module_info
static __int64 ppOriginal_ModuleUnload = 0;
static Callback_t s_unload_callback = nullptr;

bool MCCHook::Initialize() {
    auto hModule = (__int64)GetModuleHandleA("MCC-Win64-Shipping.exe");

    if (hModule == 0) return false;

    auto status = MH_Initialize();

    if (!(status == MH_OK || status == MH_ERROR_ALREADY_INITIALIZED)) return false;

    asm_mcc_hook_load_init(ModuleLoad, &ppOriginal_ModuleLoad);

    status = MH_CreateHook((LPVOID) (hModule + OFFSET_MODULE_LOAD),
                           asm_mcc_hook_load_entry,
                           (void **) &ppOriginal_ModuleLoad
    );

    if (status != MH_OK) return false;

    status = MH_EnableHook((LPVOID)(hModule + OFFSET_MODULE_LOAD)); // !! essential

    if (status != MH_OK) return false;

    asm_mcc_hook_unload_init(ModuleUnload, &ppOriginal_ModuleUnload);

    status = MH_CreateHook((LPVOID) (hModule + OFFSET_MODULE_UNLOAD),
                           asm_mcc_hook_unload_entry,
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
