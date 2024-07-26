#include "mcc.h"

#include <offset_mcc.h>

#include "mcc/CGameManager.h"

#include "mcc/module/Module.h"
#include "mcc/network/Network.h"
#include "mcc/splitscreen/Splitscreen.h"

namespace MCC {
    static float (__fastcall* deltaTime)(long long qpc);

    float DeltaTime(__int64 a1) {
        return deltaTime(a1);
    }

    bool Initialize() {
        bool result;
        CGameEngine** ppGameEngine;
        CGameManager* game_manager;
        CDeviceManager** device_manager;

        AlphaRing::Hook::Offset({
            {0x3FFCAA8, 0x3E4B048, (void**)&ppGameEngine},
            {0x3F76E50, 0x3DC54D0, (void**)&game_manager},
            {0x3FFFFF8, 0x3E4E590, (void**)&device_manager},
            {OFFSET_MCC_PF_DELTA_TIME, OFFSET_MCC_WS_PF_DELTA_TIME, (void**)&deltaTime},
        });

        assertm(ppGameEngine != nullptr, "MCC: failed to get ppGameEngine");
        assertm(game_manager != nullptr, "MCC: failed to get pGameManager");
        assertm(device_manager != nullptr, "MCC: failed to get ppDeviceManager");

        result = CGameEngine::Initialize(ppGameEngine);

        assertm(result, "MCC: failed to initialize GameEngine");

        result = CGameManager::Initialize(game_manager);

        assertm(result, "MCC: failed to initialize GameManager");
        assertm(GameManager() != nullptr, "MCC:Splitscreen: GameManager is null"); // static instance

        result = CDeviceManager::Initialize(device_manager);

        assertm(result, "MCC: failed to initialize DeviceManager");

        if (!Module::Initialize())
            return false;

        if (!Splitscreen::Initialize())
            return false;

        if (!Network::Initialize())
            return false;

        return true;
    }
}
