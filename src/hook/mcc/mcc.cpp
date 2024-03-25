#include "mcc.h"
#include "asm/asm.h"

#include "MinHook.h"

#include <Windows.h>

const char* module_name = "MCC-Win64-Shipping.exe";

static __int64 OFFSET_MODULE_SET = 0x3FFD590; // p_module_set

static __int64 OFFSET_MODULE_LOAD = 0x4426AC; // r14 = p_module_info
static __int64 ppOriginal_ModuleLoad = 0;
static MCCHook::Callback_t s_load_callback = nullptr;
static void ModuleLoad(ModuleInfo* info) { if (s_load_callback) s_load_callback(info); }

static __int64 OFFSET_MODULE_UNLOAD = 0x442728; // rbx = p_module_info
static __int64 ppOriginal_ModuleUnload = 0;
static MCCHook::Callback_t s_unload_callback = nullptr;
static void ModuleUnload(ModuleInfo* info) { if (s_unload_callback) s_unload_callback(info); }

bool MCCHook::Initialize(Callback_t load_callback, Callback_t unload_callback) {
    s_load_callback = load_callback;
    s_unload_callback = unload_callback;

    __int64 hModule = (__int64)GetModuleHandleA(module_name);

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
