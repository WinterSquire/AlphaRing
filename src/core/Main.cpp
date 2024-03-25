#include <Windows.h>

#include "Log.h"

#include "ExternalConsole.h"
#include "../hook/Hook.h"
#include "../ui/Interface.h"

void StartupThread(HANDLE hModule) {
    bool result;

    if (ExternalConsole::Init() == false) {
        LOG_ERROR("ExternalConsole Failed To Initialize!");
        return;
    }

    LOG_INFO("ExternalConsole Initialized!");

    if (Hook::Init() == false) {
        LOG_ERROR("Game Hook Failed To Initialize!");
        return;
    }

    LOG_INFO("Game Hook Initialized!");

    if (sInterface.initialize() != System::SYS_OK) {
        LOG_ERROR("Interface Failed To Initialize!");
        return;
    }

    LOG_INFO("Interface Initialized!");

    LOG_INFO("Initialize Success!");

    while (true) {

    }

    Hook::Shutdown();

    ExternalConsole::Shutdown();

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