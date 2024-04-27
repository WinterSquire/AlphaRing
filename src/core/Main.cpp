#include <Windows.h>

#include "Log.h"
#include "ISystem.h"

#include "ExternalConsole.h"
#include "../hook/Hook.h"

extern void waitForDestory();

bool Prologue() {
    if (ExternalConsole()->initialize() != ISystem::SYS_OK) return false;
    if (Hook()->initialize() != ISystem::SYS_OK) return false;
    return true;
}

signed Main() {

    waitForDestory();

    return 0;
}

bool Epilogue() {
    LOG_INFO("Shutdown");

    Hook()->shutdown();

    ExternalConsole()->shutdown();

    return true;
}

void StartupThread(HANDLE hModule) {if (Prologue()) Main(); Epilogue();}

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