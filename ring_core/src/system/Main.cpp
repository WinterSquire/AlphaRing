#include <Windows.h>

#include "directx11_hook.h"
#include "mcc_hook.h"

#include "Log.h"
#include "../hook/Hook.h"
#include "../interface/Interface.h"

void ModuleLoad(ModuleInfo *info) {
    if (info->errorCode == 0) {
        LOG_INFO("Module {0}: Loaded At: {1:x}", info->title, info->hModule);
    } else {
        LOG_INFO("Module {0}: Loaded Error: {1}", info->title, info->errorCode);
    }
}

void ModuleUnload(ModuleInfo *info) {
    LOG_INFO("Module {0}: Is about to unload", info->title);
}

void StartupThread(HANDLE hModule) {
    bool result;

    Log::Init();

    result = MCCHook::Initialize(ModuleLoad, ModuleUnload);

    if (result) LOG_INFO("MCC Hook Initialized!");

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