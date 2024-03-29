#include "Hook.h"
#include "../core/Log.h"

#include "MinHook.h"

#include "./d3d11/hook.h"
#include "./mcc/mcc.h"
#include "./halo3/halo3.h"

#include "../game/halo3/native/native.h"

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
    Native::Init(p_h3_module);
}

void EngineUninit() {
    LOG_INFO("Engine Uninit");
}

void WorldInit() {

}

void WorldUninit() {

}

bool Hook::Init() {
    if (MH_Initialize() != MH_OK) {
        LOG_ERROR("Directx11 Hook Fail To Initialize!");
        return false;
    }

    LOG_INFO("MinHook Initialized!");

    if (Directx11Hook::Initialize() == false) {
        LOG_ERROR("Directx11 Hook Fail To Initialize!");
        return false;
    }

    LOG_INFO("Directx11 Hook Initialized!");

    if (MCCHook::Initialize(ModuleLoad, ModuleUnload) == false) {
        LOG_ERROR("MCC Hook Fail To Initialize!");
        return false;
    }

    LOG_INFO("MCC Hook Initialized!");

    if (Halo3Hook::Init() == false) {
        LOG_ERROR("Halo3 Hook Fail To Initialize!");
        return false;
    }

    LOG_INFO("Halo3 Hook Initialized!");

    Halo3Hook::Engine::setInitCallback(EngineInit);
    Halo3Hook::Engine::setUninitCallback(EngineUninit);



    return true;
}

void Hook::Shutdown() {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}
