#include "CGameManager.h"

#include "common.h"

#include "mcc/splitscreen/settings.h"
#include "input/Input.h"
#include "mcc/splitscreen/Splitscreen.h"

CGameManager* pGameManager;
CGameManager::FunctionTable CGameManager::ppOriginal;

bool CGameManager::Initialize(CGameManager* mng) {
    pGameManager = mng;

    return AlphaRing::Hook::Detour({
        {pGameManager->table->get_player_profile, get_player_profile, (void**)&ppOriginal.get_player_profile},
        {pGameManager->table->get_key_state, get_key_state, (void**)&ppOriginal.get_key_state},
        {pGameManager->table->get_xbox_user_id, get_xbox_user_id, (void**)&ppOriginal.get_xbox_user_id},
        {pGameManager->table->set_vibration, set_vibration, (void**)&ppOriginal.set_vibration},
        {pGameManager->table->retrive_gamepad_mapping, retrive_gamepad_mapping, (void**)&ppOriginal.retrive_gamepad_mapping},
    });
}

void CGameManager::set_vibration(CGameManager *self, DWORD dwUserIndex, XINPUT_VIBRATION *pVibration) {
    CDeviceManager::InputDevice* p_device;
    auto p_input_setting = &Settings()->input_setting;
    auto device_manager = DeviceManager();

    if (!p_input_setting->override_input)
        return ppOriginal.set_vibration(self, dwUserIndex, pVibration);

    if (p_input_setting->enable_km && !dwUserIndex)
        return;

    auto choice = p_input_setting->controller_map[dwUserIndex];

    if (choice == 4 || !(p_device = device_manager->p_input_device[choice]))
        return;

    AlphaRing::Input::SetState(p_device->input_user, pVibration);
}

__int64 CGameManager::get_player_profile(CGameManager *self, __int64 xid)  {
    auto p_setting = &Settings()->profile_setting;
    if (p_setting->b_override && p_setting->b_use_player0_profile && p_setting->profiles[0].xuid != 0)
        xid = p_setting->profiles[0].xuid;
    return ppOriginal.get_player_profile(self, xid);
}

char CGameManager::get_xbox_user_id(CGameManager *self, __int64 *pId, wchar_t *pName, int size, int index) {
    auto p_setting = &Settings()->profile_setting;

    if (p_setting->profiles[0].xuid == 0)
        ppOriginal.get_xbox_user_id(self, &p_setting->profiles[0].xuid, nullptr, 0, 0);

    if (!p_setting->b_override || (!p_setting->b_override_player0 && !index))
        return ppOriginal.get_xbox_user_id(self, pId, pName, size, index);

    if (index >= p_setting->player_count)
        return false;

    if (pId)
        *pId = p_setting->profiles[index].id;

    if (pName)
        String::wstrcpy(pName, p_setting->profiles[index].name, size >> 1);

    return true;
}

bool CGameManager::get_key_state(CGameManager *self, DWORD index, input_data_t *p_input) {
    bool result;
    LARGE_INTEGER qpc;
    float delta_time = 0;
    CDeviceManager::InputDevice* p_device;

    auto p_input_setting = &Settings()->input_setting;
    auto p_profile_setting = &Settings()->profile_setting;
    auto device_manager = DeviceManager();
    auto p_global = AlphaRing::Global::Global();

    if (p_global->show_imgui) {
        if (p_global->pause_game_on_menu_shown)
            return false;
        else if (p_global->disable_input_on_menu_shown)
            return true;
    }

    if (!p_input_setting->override_input)
        return ppOriginal.get_key_state(self, index, p_input);

    if (index >= p_profile_setting->player_count)
        return false;

    if (p_input_setting->enable_km && !index) {
        p_device = device_manager->p_input_device[4];
        device_manager->table->update_state(device_manager, 0, 0, false);
        QueryPerformanceCounter(&qpc);
        auto v1 = qpc.QuadPart - device_manager->qpc.QuadPart;
        auto v2 = device_manager->qpc.QuadPart - qpc.QuadPart;
        delta_time = fminf(fmaxf(MCC::Splitscreen::DeltaTime(v1 >= v2 ? v2 : v1) * 1000.0,0.1), 1000.0);
        device_manager->qpc = qpc;
    } else {
        auto choice = p_input_setting->controller_map[index];
        if (choice == 4 || (p_device = device_manager->p_input_device[choice]) == nullptr)
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

__int64 CGameManager::retrive_gamepad_mapping(CGameManager *self, __int64 xid) {
    auto p_setting = &Settings()->profile_setting;
    if (p_setting->b_override && p_setting->b_use_player0_profile && p_setting->profiles[0].xuid != 0)
        xid = p_setting->profiles[0].xuid;
    return ppOriginal.retrive_gamepad_mapping(self, xid);
}
