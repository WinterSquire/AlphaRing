#include "Hook.h"
#include "../core/Log.h"

#include "MinHook.h"

#include "./d3d11/hook.h"
#include "./mcc/mcc.h"
#include "./halo3/halo3.h"

#include "../game/halo3/halo3.h"

__int64 p_h3_module = 0;

void ModuleLoad(ModuleInfo *info) {
    if (info->errorCode == 0) {
        LOG_INFO("Module {0}: Loaded At: {1:x}", ModuleInfo::cTitle[info->title], info->hModule);
        if (info->title == ModuleInfo::Halo3) {
            if (Halo3Hook::Update(info->hModule))
                LOG_INFO("Halo3 Hook Reload Success!");
            else
                LOG_ERROR("Halo3 Hook Reload Failed!");
            p_h3_module = info->hModule;
        }
    } else {
        LOG_INFO("Module {0}: Loaded Error: {1}", ModuleInfo::cTitle[info->title], info->errorCode);
    }
}

void ModuleUnload(ModuleInfo *info) {
    LOG_INFO("Module {0}: Is about to unload", ModuleInfo::cTitle[info->title]);
}


void EngineInit() {
    LOG_INFO("Engine Init");



}

void EngineUninit() {
    LOG_INFO("Engine Uninit");
}

void WorldInit() {
    static bool bfirst = true;

    LOG_INFO("World Init");

    if (bfirst) {
        Native::Init(p_h3_module);
        // 初始化有问题
        LOG_INFO("Object Root: {0:x}", object_manager.getRoot());
        // 不能正常获取开始地址
        LOG_INFO("Object Begin: {0:x}", object_manager.begin());

        bfirst = false;
    }
}

void WorldUninit() {

}

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

    if (MCCHook::Initialize(ModuleLoad, ModuleUnload) == false) {
        LOG_ERROR("MCC Hook Fail To Initialize!");
        goto RET_ERROR;
    }

    LOG_INFO("MCC Hook Initialized!");

    if (Halo3Hook::Init() == false) {
        LOG_ERROR("Halo3 Hook Fail To Initialize!");
        goto RET_ERROR;
    }

    LOG_INFO("Halo3 Hook Initialized!");

    Halo3Hook::Engine::setInitCallback(EngineInit);
    Halo3Hook::Engine::setUninitCallback(EngineUninit);
    Halo3Hook::World::setInitCallback(WorldInit);
    Halo3Hook::World::setUninitCallback(WorldUninit);

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
