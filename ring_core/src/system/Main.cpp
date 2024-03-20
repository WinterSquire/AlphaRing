#include <iostream>
#include <Windows.h>

#include "directx11_hook.h"
#include "Log.h"
#include "../hook/Hook.h"

#include <Windows.h>

void StartupThread(HANDLE hModule) {
    bool result;

    Log::Init();

    result = Hook::Init();

    if (result) LOG_INFO("Game Hook Initialized!");

    result = Directx11Hook::Initialize();

    if (result) LOG_INFO("Directx11 Hook Initialized!");

    LOG_INFO("Initialize Success!");

    while (true) {
        Hook::Check(reinterpret_cast<long long int>(GetModuleHandleA("halo3.dll")));
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