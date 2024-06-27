#include "mcc.h"

#include "common.h"
#include "./module/Module.h"
#include "offset_mcc.h"

#include <minhook/MinHook.h>

#include "core/String.h"
#include "input/Input.h"
#include "hook/mcc/module/patch/Patch.h"
#include "hook/d3d11/main_renderer.h"

#include "./setting/setting.h"

#define DefDetourFunction(return_type, call_type, name, ...) \
    static return_type (call_type *ppOriginal_##name)(__VA_ARGS__); \
    static return_type call_type name(__VA_ARGS__)

static float (__fastcall* deltaTime)(long long qpc);
static void (__fastcall* get_player0_input)(INPUT_t* self);

DefDetourFunction(void, __fastcall, module_load, module_info_t* info, int a2, __int64 a3) {
    ppOriginal_module_load(info, a2, a3);
    ModuleMCC()->get(info->title)->load_module(info);
}

DefDetourFunction(__int64, __fastcall, module_unload, module_info_t* info) {
    auto result = ppOriginal_module_unload(info);
    ModuleMCC()->get(info->title)->unload_module();
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

    auto p_input_setting = InputSetting();
    auto p_profile_setting = ProfileSetting();

    if (p_input_setting->disable_input_on_menu && MainRenderer()->ShowContext())
        return false;

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

DefDetourFunction(HINTERNET, __stdcall, dWinHttpConnect, HINTERNET hSession, LPCWSTR pswzServerName, INTERNET_PORT nServerPort, DWORD dwReserved) {
    HINTERNET result = ppOriginal_dWinHttpConnect(hSession, pswzServerName, nServerPort, dwReserved);

    NetworkSetting()->set_url(result, pswzServerName);

    return result;
}

DefDetourFunction(HINTERNET, __stdcall, dWinHttpOpenRequest, HINTERNET hConnect, LPCWSTR pwszVerb, LPCWSTR pwszObjectName, LPCWSTR pwszVersion, LPCWSTR pwszReferrer, LPCWSTR* ppwszAcceptTypes, DWORD dwFlags) {
    HINTERNET result = ppOriginal_dWinHttpOpenRequest(hConnect, pwszVerb, pwszObjectName, pwszVersion, pwszReferrer, ppwszAcceptTypes, dwFlags);

    NetworkSetting()->add(result, hConnect, pwszVerb, pwszObjectName);

    return result;
}

DefDetourFunction(BOOL, __stdcall, dWinHttpAddRequestHeaders, HINTERNET hRequest, LPCWSTR pwszHeaders, DWORD dwHeadersLength, DWORD dwModifiers) {
    NetworkSetting()->set_header(hRequest, pwszHeaders);

    return ppOriginal_dWinHttpAddRequestHeaders(hRequest, pwszHeaders, dwHeadersLength, dwModifiers);
}

static int count = 0;

DefDetourFunction(BOOL, __stdcall, dWinHttpWriteData, HINTERNET hRequest, LPCVOID lpBuffer, DWORD dwNumberOfBytesToWrite, LPDWORD lpdwNumberOfBytesWritten) {
    NetworkSetting()->set_body(hRequest, lpBuffer, dwNumberOfBytesToWrite);

    return ppOriginal_dWinHttpWriteData(hRequest, lpBuffer, dwNumberOfBytesToWrite, lpdwNumberOfBytesWritten);
}

DefDetourFunction(BOOL, __stdcall, dWinHttpReadData, HINTERNET hRequest, LPVOID lpBuffer, DWORD dwNumberOfBytesToRead, LPDWORD lpdwNumberOfBytesRead) {
    auto result = ppOriginal_dWinHttpReadData(hRequest, lpBuffer, dwNumberOfBytesToRead, lpdwNumberOfBytesRead);

    NetworkSetting()->set_response(hRequest, lpBuffer, dwNumberOfBytesToRead);

    return result;
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

    if (!ModuleMCC()->Init(hModule, isWS))
        return false;

    ModuleMCC()->version().toString(buffer, sizeof(buffer));

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

    Patch::apply(GetProcAddress(GetModuleHandleA("KERNEL32.DLL"), "IsDebuggerPresent"),
                 "\x31\xC0\xC3\x90\x90\x90\x90",
                 7);

    auto h_win_http = GetModuleHandleA("winhttp.dll");

    auto p_open_request = GetProcAddress(h_win_http, "WinHttpOpenRequest");

    auto p_set_header = GetProcAddress(h_win_http, "WinHttpAddRequestHeaders");

    auto p_write_data = GetProcAddress(h_win_http, "WinHttpWriteData");

    auto p_connect = GetProcAddress(h_win_http, "WinHttpConnect");

    auto p_read_data = GetProcAddress(h_win_http, "WinHttpReadData");

    if (MH_CreateHook(p_read_data, dWinHttpReadData, (void**)&ppOriginal_dWinHttpReadData) != MH_OK ||
        MH_EnableHook(p_read_data) != MH_OK)
        return false;

    if (MH_CreateHook(p_connect, dWinHttpConnect, (void**)&ppOriginal_dWinHttpConnect) != MH_OK ||
        MH_EnableHook(p_connect) != MH_OK)
        return false;

    if (MH_CreateHook(p_open_request, dWinHttpOpenRequest, (void**)&ppOriginal_dWinHttpOpenRequest) != MH_OK ||
        MH_EnableHook(p_open_request) != MH_OK)
        return false;

    if (MH_CreateHook(p_set_header, dWinHttpAddRequestHeaders, (void**)&ppOriginal_dWinHttpAddRequestHeaders) != MH_OK ||
        MH_EnableHook(p_set_header) != MH_OK)
        return false;

    if (MH_CreateHook(p_write_data, dWinHttpWriteData, (void**)&ppOriginal_dWinHttpWriteData) != MH_OK ||
        MH_EnableHook(p_write_data) != MH_OK)
        return false;



    return true;
}
