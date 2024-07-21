#include "CGameManager.h"

#include "common.h"

#include <cstdio>
#include <guiddef.h>
#include <combaseapi.h>

static struct ProfileContainer_t {CGameManager::Profile_t profiles[4]; ProfileContainer_t();} container;

inline CGameManager::Profile_t* CGameManager::get_profile(int index) {return container.profiles + index;}

ProfileContainer_t::ProfileContainer_t() {
    __int64 guid[2];
    const int controller_map[4] {3, 0, 1, 2};
    memset(this, 0, sizeof(ProfileContainer_t));

    CoCreateGuid((GUID*)guid);
    auto id = guid[0] ^ guid[1];

    for (int i = 0; i < 4; i++) {
        profiles[i].controller_index = controller_map[i];
        profiles[i].id = id + i;
        swprintf(profiles[i].name, L"Player %d", i + 1);
    }
}

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

// b_override = true;

__int64 CGameManager::get_xuid(int index) {
    __int64 result;
    auto setting = AlphaRing::Global::MCC::Splitscreen();

    if (index || setting->b_override_profile)
        return container.profiles[index].id;
    else
        return pGameManager->ppOriginal.get_xbox_user_id(pGameManager, &result, nullptr, 0, index) ? result : 0;
}

CInputDevice *CGameManager::get_controller(int index) {
    auto mng = DeviceManager();
    auto setting = AlphaRing::Global::MCC::Splitscreen();
    auto profile = get_profile(index);

    if ((!index && setting->b_player0_use_km) || profile->controller_index == 4)
        return nullptr;
    else
        return mng->p_input_device[get_profile(index)->controller_index];
}

int CGameManager::get_index(__int64 xuid) {
    for (int i = 1; i < 4; ++i)
        if (container.profiles[i].id == xuid)
            return i;
    return 0;
}