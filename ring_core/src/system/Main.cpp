#include <Windows.h>

#include "directx11_hook.h"
#include "halo3_hook.h"
#include "mcc_hook.h"

#include "Log.h"
#include "../hook/Hook.h"
#include "../interface/Interface.h"

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

#include "Common.h"

void EngineInit() {
    auto tls = ThreadLocalStorage(p_h3_module);

    LOG_INFO("Engine Init");
    LOG_INFO("MapEntry: {0:x}", (__int64)tls.ptr(9));
}

void EngineUninit() {
    LOG_INFO("Engine Uninit");
}


void StartupThread(HANDLE hModule) {
    bool result;

    Log::Init();

    result = MCCHook::Initialize(ModuleLoad, ModuleUnload);

    if (result) LOG_INFO("MCC Hook Initialized!");

    {
        result = Halo3Hook::Init();

        if (result) LOG_INFO("Halo3 Hook Initialized!");

        Halo3Hook::Engine::setEngineInitCallback(EngineInit);
        Halo3Hook::Engine::setEngineUninitCallback(EngineUninit);
    }

    result = Hook::Init();

    if (result) LOG_INFO("Game Hook Initialized!");

    result = Directx11Hook::Initialize();

    if (result) LOG_INFO("Directx11 Hook Initialized!");

    result = sInterface.initialize();

    LOG_INFO("Initialize Success!");

    while (true) {

    }

    Directx11Hook::Shutdown();

    Log::Shutdown();
}

BOOL APIENTRY DllMain(HANDLE handle, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(
                nullptr,
                0,
                (LPTHREAD_START_ROUTINE) StartupThread,
                handle,
                0,
                nullptr
                );
    }

    return true;
}