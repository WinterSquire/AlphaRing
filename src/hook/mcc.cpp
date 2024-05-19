#include "mcc.h"

#include "module/Module.h"
#include "offset_mcc.h"
#include "input/Input.h"

#include "common.h"

#include "MinHook.h"
#include <Xinput.h>

#include "render/Renderer.h"

static __int64 hModule;

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
static bool (__fastcall *ppOriginal_input_get_status)(INPUT_t* self, int player_index, input_data_t* p_data, char a4);
static bool __fastcall input_get_status(INPUT_t* self, int player_index, input_data_t* p_data, char a4) {
    bool result = false;
    InputDevice* p_device;

     if (Renderer()->ShowContext()) return false;

    auto p_setting = InputSetting();

    if (!p_setting->override_input) return ppOriginal_input_get_status(self, player_index, p_data, a4);

    if (!*(bool*)(hModule + OFFSET_MCC_PV_WINDOWFOCUSED)) return result;

    if (p_setting->enable_km && !player_index) {
        p_device = self->p_input_device[4];
        for (auto j = *(__int64**)(hModule + OFFSET_MCC_PV_KEYBEGIN); j != (__int64*)(hModule + OFFSET_MCC_PV_KEYEND); j = (__int64*)j[1] )
            ((void (__fastcall *)(__int64, __int64 *))(hModule + OFFSET_MCC_PF_KEYCHECK))(((__int64)p_device + 0x20), j);
        if ( *(bool*)((__int64)p_device + 0xF8) && GetKeyState(0xA0) >= 0 )
            *(bool*)((__int64)p_device + 0xF8) = false;
        if ( *(bool*)((__int64)p_device + 249) && (GetKeyState(0xA1) & 0x8000) == 0 )
            *(bool*)((__int64)p_device + 0xF9) = false;
    } else {
        auto choice = p_setting->controller_map[player_index];
        if (choice == 4 || (p_device = self->p_input_device[choice]) == nullptr) return result;
        memset(&p_device->state, 0, sizeof(XINPUT_STATE));
        xinput_get_state(p_device->input_user, &p_device->state);
        *(__int64 *)((__int64)p_data + 0x10C) = 0i64;
    }

    result = p_device->p_method_table->set_state(p_device, 0, p_data);
    p_device->p_method_table->check(p_device);

    return result;
}

bool MCCHook::Initialize() {
    char buffer[1024];
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

    if ((pTarget = (LPVOID) (hModule + OFFSET_MCC_PF_GAMEINPUT)),
            MH_CreateHook(pTarget,input_get_status,(void **) &ppOriginal_input_get_status) != MH_OK ||
            MH_EnableHook(pTarget) != MH_OK)
        return false;

    xinput_get_state = reinterpret_cast<decltype(xinput_get_state)>(GetProcAddress(GetModuleHandleA("XINPUT1_3.dll"), "XInputGetState"));

    return true;
}
