#include "Hook.h"
#include "../core/Log.h"

#include "MinHook.h"

#include "./d3d11/hook.h"
#include "./mcc/mcc.h"
#include "./halo3/halo3.h"

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
        LOG_ERROR("Directx11 Hook Fail To Initialize!");
        goto RET_ERROR;
    }

    LOG_INFO("MinHook Initialized!");

    if (Directx11Hook::Initialize() == false) {
        LOG_ERROR("Directx11 Hook Fail To Initialize!");
        goto RET_ERROR;
    }

    LOG_INFO("Directx11 Hook Initialized!");

    if (MCCHook::Initialize() == false) {
        LOG_ERROR("MCC Hook Fail To Initialize!");
        goto RET_ERROR;
    }

    LOG_INFO("MCC Hook Initialized!");

    if (Halo3Hook::Init() == false) {
        LOG_ERROR("Halo3 Hook Fail To Initialize!");
        goto RET_ERROR;
    }

    LOG_INFO("Halo3 Hook Initialized!");

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
