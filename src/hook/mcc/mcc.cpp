#include "mcc.h"

#include "common.h"
#include "module/Module.h"
#include "offset_mcc.h"

#include <minhook/MinHook.h>

#include "core/String.h"
#include "input/Input.h"
#include "patch/Patch.h"
#include "render/Renderer.h"

#include "./setting/setting.h"

#define DefDetourFunction(return_type, call_type, name, ...) \
    static return_type (call_type *ppOriginal_##name)(__VA_ARGS__); \
    static return_type call_type name(__VA_ARGS__)

static float (__fastcall* deltaTime)(long long qpc);
static void (__fastcall* get_player0_input)(INPUT_t* self);

DefDetourFunction(void, __fastcall, module_load, module_info_t* info, int a2, __int64 a3) {
    ppOriginal_module_load(info, a2, a3);
    Modules()->get((eModule)info->title)->load_module(info);
}

DefDetourFunction(__int64, __fastcall, module_unload, module_info_t* info) {
    auto result = ppOriginal_module_unload(info);
    Modules()->get((eModule)info->title)->unload_module();
    return result;
}

DefDetourFunction(char, __fastcall, get_xbox_user_id, void* pSelf, __int64* pId, wchar_t *pName, int size, int index) {
    auto p_setting = ProfileSetting();

    if (p_setting->profiles[0].xid == 0)
        ppOriginal_get_xbox_user_id(pSelf, &p_setting->profiles[0].xid, nullptr, 0, 0);

    if (!p_setting->b_override || (!p_setting->b_override_player0 && !index))
        return ppOriginal_get_xbox_user_id(pSelf,pId,pName,size,index);

    if (index >= p_setting->player_count)
        return false;

    if (pId)
        *pId = p_setting->profiles[index].id;

    if (pName)
        String::wstrcpy(pName, p_setting->profiles[index].name, size >> 1);

    return true;
}

DefDetourFunction(bool, __fastcall, input_get_status, INPUT_t* self, int index, input_data_t* pData, char a4) {
    bool result;
    LARGE_INTEGER qpc;
    float delta_time = 0;
    INPUT_t::InputDevice* p_device;

    if (Renderer()->ShowContext())
        return false;

    auto p_input_setting = InputSetting();
    auto p_profile_setting = ProfileSetting();

    if (!p_input_setting->override_input)
        return ppOriginal_input_get_status(self, index, pData, a4);

    if (index >= p_profile_setting->player_count)
        return false;

    if (p_input_setting->enable_km && !index) {
        p_device = self->p_input_device[4];
        get_player0_input(self);

        QueryPerformanceCounter(&qpc);
        auto v1 = qpc.QuadPart - self->qpc.QuadPart;
        auto v2 = self->qpc.QuadPart - qpc.QuadPart;
        delta_time = fminf(fmaxf(deltaTime(v1 >= v2 ? v2 : v1) * 1000.0,0.1), 1000.0);
        self->qpc = qpc;
    } else {
        auto choice = p_input_setting->controller_map[index];
        if (choice == 4 || (p_device = self->p_input_device[choice]) == nullptr)
            return true;

        memset(&p_device->state, 0, sizeof(XINPUT_STATE));
        AlphaRing::Input::GetXInputGetState(p_device->input_user, &p_device->state);
    }

    result = p_device
            ->p_method_table
            ->set_state(p_device, delta_time, pData);

    p_device->p_method_table->check(p_device);

    return result;
}

DefDetourFunction(__int64, __fastcall, get_player_profile, __int64 self, __int64 xid) {
    auto p_setting = ProfileSetting();
    if (p_setting->b_override && p_setting->b_use_player0_profile && p_setting->profiles[0].xid != 0)
        xid = p_setting->profiles[0].xid;
    return ppOriginal_get_player_profile(self, xid);
}

bool MCCHook::Initialize() {
    bool isWS;
    void* pTarget;
    __int64 hModule;
    char buffer[1024];

    struct {__int64 offset_steam; __int64 offset_ws; void* detour;void** ppOriginal; } hooks[] {
            {OFFSET_MCC_PF_MODULELOAD, OFFSET_MCC_WS_PF_MODULELOAD,  module_load, (void **)&ppOriginal_module_load},
            {OFFSET_MCC_PF_MODULEUNLOAD, OFFSET_MCC_WS_PF_MODULEUNLOAD, module_unload, (void **)&ppOriginal_module_unload},
            {OFFSET_MCC_PF_GAMEINPUT, OFFSET_MCC_WS_PF_GAMEINPUT, input_get_status, (void **)&ppOriginal_input_get_status},
            {OFFSET_MCC_PF_GET_USER_ID, OFFSET_MCC_WS_PF_GET_USER_ID, get_xbox_user_id, (void **)&ppOriginal_get_xbox_user_id},
            {OFFSET_MCC_PF_GET_PROFILE, OFFSET_MCC_WS_PF_GET_PROFILE, get_player_profile, (void **)&ppOriginal_get_player_profile},
    };

    struct {__int64 offset_steam; __int64 offset_ws; void** ppf;} funcs[] {
            {OFFSET_MCC_PF_GET_PLAYER0_INPUT, OFFSET_MCC_WS_PF_GET_PLAYER0_INPUT, (void**)&get_player0_input},
            {OFFSET_MCC_PF_DELTA_TIME, OFFSET_MCC_WS_PF_DELTA_TIME, (void**)&deltaTime},
    };

    if ((isWS = (hModule = (__int64)GetModuleHandleA("MCC-Win64-Shipping.exe")) == 0) &&
        (hModule = (__int64)GetModuleHandleA("MCCWinStore-Win64-Shipping.exe")) == 0)
        return false;

    auto p_mcc = Modules()->get(MCC);

    p_mcc->load_module({MCC,0, hModule});

    p_mcc->version().toString(buffer, sizeof(buffer));

    LOG_INFO("Game Version: {}({})", buffer, isWS ? "Windows Store" : "Steam");

    for (auto &func : funcs) {
        if (func.ppf == nullptr)
            return false;
        *func.ppf = (void*)(hModule + (isWS ? func.offset_ws : func.offset_steam));
    }

    for (auto &hook : hooks) {
        if ((pTarget = (LPVOID) (hModule + (isWS ? hook.offset_ws : hook.offset_steam))),
                MH_CreateHook(pTarget, hook.detour, hook.ppOriginal) != MH_OK ||
                MH_EnableHook(pTarget) != MH_OK)
            return false;
    }

    return true;
}
