#include <iostream>
#include <Windows.h>

#include "hook.h"
#include "Log.h"

void StartupThread(HANDLE hModule) {
    Log::Init();

    auto result = Directx11Hook::Initialize();

    if (result) LOG_INFO("Directx11 Hook Initialized!");

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