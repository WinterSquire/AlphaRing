#include "Hook.h"
#include "common.h"

#include "MinHook.h"

#include "./d3d11/hook.h"
#include "./mcc/mcc.h"

class CHook : public ISystem {
public:
    eStatus initialize() override;
    eStatus shutdown() override;

    static CHook s_instance;
};

CHook CHook::s_instance;
ISystem* g_pHook = &CHook::s_instance;

ISystem::eStatus CHook::initialize() {
    if (MH_Initialize() != MH_OK) {
        LOG_ERROR("MinHook Fail To Initialize!");
        goto RET_ERROR;
    }

    if (Directx11Hook::Initialize() == false) {
        LOG_ERROR("Directx11 Hook Fail To Initialize!");
        goto RET_ERROR;
    }

    if (MCCHook::Initialize() == false) {
        LOG_ERROR("MCC Hook Fail To Initialize!");
        goto RET_ERROR;
    }

    LOG_INFO("Game Hook Initialized!");
    return SYS_OK;

    RET_ERROR:
    LOG_ERROR("Game Hook Failed To Initialize!");
    return SYS_ERROR;
}

ISystem::eStatus CHook::shutdown() {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    return SYS_OK;
}
