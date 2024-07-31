#include "CGameManager.h"

#include "common.h"

#include "./mcc.h"
#include "global/Global.h"
#include "input/Input.h"

void CGameManager::set_vibration(CGameManager *self, DWORD dwUserIndex, XINPUT_VIBRATION *pVibration) {
    CInputDevice* p_device;
    auto p_setting = AlphaRing::Global::MCC::Splitscreen();

    if (!p_setting->b_override) {
        ppOriginal.set_vibration(self, dwUserIndex, pVibration);
        return;
    }

    if (dwUserIndex >= p_setting->player_count)
        return;

    if (pVibration == nullptr || (p_device = get_controller(dwUserIndex)) == nullptr)
        return;

    AlphaRing::Input::SetState(p_device->input_user, pVibration);
}

bool CGameManager::get_xbox_user_id(CGameManager *self, __int64 *pId, wchar_t *pName, int size, int index) {
    auto p_setting = AlphaRing::Global::MCC::Splitscreen();
    auto p_profile = get_profile(index);

    if (!p_setting->b_override || !index)
        return ppOriginal.get_xbox_user_id(self, pId, pName, size, index);

    if (index >= p_setting->player_count)
        return false;

    if (pId)
        *pId = p_profile->id;

    if (pName)
        String::wstrcpy(pName, p_profile->name, size >> 1);

    return true;
}

bool CGameManager::get_key_state(CGameManager *self, DWORD index, input_data_t *p_input) {
    bool result;
    LARGE_INTEGER qpc;
    float delta_time = 0;
    CInputDevice* p_device;

    auto p_profile = AlphaRing::Global::MCC::Splitscreen();
    auto device_manager = DeviceManager();
    auto p_global = AlphaRing::Global::Global();

    memset(p_input, 0, sizeof(input_data_t));

    if (p_global->show_imgui) {
        if (p_global->pause_game_on_menu_shown)
            return false;
        else if (p_global->disable_input_on_menu_shown)
            return true;
    }

    if (!p_profile->b_override)
        return ppOriginal.get_key_state(self, index, p_input);

    if (index >= p_profile->player_count)
        return false;

    if (p_profile->b_player0_use_km && !index) {
        p_device = device_manager->p_input_device[4];
        device_manager->table->update_state(device_manager, 0, 0, false);
        QueryPerformanceCounter(&qpc);
        auto v1 = qpc.QuadPart - device_manager->qpc.QuadPart;
        auto v2 = device_manager->qpc.QuadPart - qpc.QuadPart;
        delta_time = fminf(fmaxf(MCC::DeltaTime(v1 >= v2 ? v2 : v1) * 1000.0,0.1), 1000.0);
        device_manager->qpc = qpc;
    } else {
        if ((p_device = get_controller(index)) == nullptr)
            return true;

        AlphaRing::Input::GetXInputGetState(p_device->input_user, &p_device->state);
    }

    result = p_device
            ->p_method_table
            ->set_state(p_device, delta_time, p_input);

    p_device
            ->p_method_table
            ->check(p_device);

    return result;
}

CUserProfile* CGameManager::get_player_profile(CGameManager *self, __int64 xid)  {
    auto index = get_index(xid);
    auto p_setting = AlphaRing::Global::MCC::Splitscreen();

    if (!p_setting->b_override)
        return ppOriginal.get_player_profile(self, xid);

    if (!p_setting->b_override_profile && ((!index) || (index && p_setting->b_use_player0_profile)))
        return ppOriginal.get_player_profile(self, get_xuid(0));

    if (p_setting->b_use_player0_profile)
        return &get_profile(0)->profile;

    return &get_profile(get_index(xid))->profile;
}

CGamepadMapping* CGameManager::retrive_gamepad_mapping(CGameManager *self, __int64 xid) {
    auto index = get_index(xid);
    auto p_setting = AlphaRing::Global::MCC::Splitscreen();

    if (!p_setting->b_override)
        return ppOriginal.retrive_gamepad_mapping(self, xid);

    if (!p_setting->b_override_profile && ((!index) || (index && p_setting->b_use_player0_profile)))
        return ppOriginal.retrive_gamepad_mapping(self, get_xuid(0));

    if (p_setting->b_use_player0_profile)
        return &get_profile(0)->mapping;

    return &get_profile(get_index(xid))->mapping;
}
