#include <iostream>
#include <windows.h>

#include "hook.h"

void StartupThread(HANDLE hModule) {
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    std::cout << Directx11Hook::Initialize();


    while (true) {

    }

    Directx11Hook::Shutdown();

    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    FreeConsole();
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