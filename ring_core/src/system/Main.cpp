#include <Windows.h>

#include "./Log.h"
#include "../hook/Hook.h"
#include "../interface/Interface.h"

void StartupThread(HANDLE hModule) {
    bool result;

    if (Log::Init() == false) {
        LOG_ERROR("Log Failed To Initialize!");
        return;
    }

    LOG_INFO("Log Initialized!");

    if (Hook::Init() == false) {
        LOG_ERROR("Game Hook Failed To Initialize!");
        return;
    }

    LOG_INFO("Game Hook Initialized!");

    if (sInterface.initialize() == false) {
        LOG_ERROR("Interface Failed To Initialize!");
        return;
    }

    LOG_INFO("Interface Initialized!");

    LOG_INFO("Initialize Success!");

    while (true) {

    }

    Hook::Shutdown();

    Log::Shutdown();

    sInterface.shutdown();
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