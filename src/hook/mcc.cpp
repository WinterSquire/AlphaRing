#include "mcc.h"

#include "module/Module.h"
#include "offset_mcc.h"

#include "common.h"

#include "MinHook.h"
#include <Xinput.h>

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

struct InputDevice {
    struct method_table_t {
        char un[0x38];
        __int64 (__fastcall *set_state)(InputDevice*, float, void*);
        void (__fastcall *check)(InputDevice*);
    } *p_method_table;
    char un0[0x800];
    int input_user;// 0x808
    char un1[0x110];
    XINPUT_STATE state; // 0x91C
};
struct INPUT_t {
    void** pp_method_table;
    InputDevice* p_input_device[5];
};

static DWORD (WINAPI* xinput_get_state)(_In_  DWORD dwUserIndex, _Out_ XINPUT_STATE* pState) WIN_NOEXCEPT;
static bool (__fastcall *ppOriginal_input_get_status)(INPUT_t* self, int player_index, void* p_input_device, char a4);
static bool __fastcall input_get_status(INPUT_t* self, int player_index, void* p_input_device, char a4) {
    bool result = false;
    if (player_index < 0 || player_index > 3) return false;
    auto p_device = self->p_input_device[player_index];
    if (p_device == nullptr) return result;
    *(__int64 *)((__int64)p_input_device + 0x10C) = 0i64;
    memset(&p_device->state, 0, sizeof(XINPUT_STATE));
    xinput_get_state(p_device->input_user, &p_device->state);
    result = p_device->p_method_table->set_state(p_device, 0, p_input_device);
    p_device->p_method_table->check(p_device);
    return result;
}

bool MCCHook::Initialize() {
    char buffer[1024];
    __int64 hModule;
    void* pTarget;

    if ((hModule = (__int64)GetModuleHandleA("MCC-Win64-Shipping.exe")) == 0) return false;

    auto p_mcc = Modules()->get(MCC);

    p_mcc->load_module({MCC,0, hModule});

    p_mcc->version().toString(buffer, sizeof(buffer));

    LOG_INFO("Game Version: {}", buffer);

    if ((pTarget = (LPVOID) (hModule + OFFSET_MCC_PF_MODULELOAD)),
            MH_CreateHook(pTarget, MODULE_LOAD_DETOUR,(void **) &ppOriginal_ModuleLoad) != MH_OK ||
            MH_EnableHook(pTarget) != MH_OK)
        return false;

    if ((pTarget = (LPVOID) (hModule + OFFSET_MCC_PF_MODULEUNLOAD)),
            MH_CreateHook(pTarget,MODULE_UNLOAD_DETOUR,(void **) &ppOriginal_ModuleUnload) != MH_OK ||
            MH_EnableHook(pTarget) != MH_OK)
        return false;

    if ((pTarget = (LPVOID) (hModule + 0x87AB80)),
            MH_CreateHook(pTarget,input_get_status,(void **) &ppOriginal_input_get_status) != MH_OK ||
            MH_EnableHook(pTarget) != MH_OK)
        return false;



    xinput_get_state = reinterpret_cast<decltype(xinput_get_state)>(GetProcAddress(GetModuleHandleA("XINPUT1_3.dll"), "XInputGetState"));

    return true;
}
