#include "Log.h"

#include <cstdio>

#include "MinHook.h"
#include "hook/d3d11.h"
#include "hook/mcc.h"

#include "render/Window.h"

#include <filesystem>

bool Prologue() {
    const char* home_dir = "../../../alpha_ring";

    if (!std::filesystem::exists(home_dir)) {
        std::filesystem::create_directories(home_dir);
    }

    if (AllocConsole() == false)
        return false;

    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    LOG_INFO("Version: {}", GAME_VERSION);

    if (MH_Initialize() != MH_OK) {
        LOG_ERROR("MinHook Fail To Initialize!");
        return false;
    }

    if (!Directx11Hook::Initialize()) {
        LOG_ERROR("Directx11 Hook Fail To Initialize!");
        return false;
    }

    if (!MCCHook::Initialize()) {
        LOG_ERROR("MCC Hook Fail To Initialize!");
        return false;
    }

    return true;
}

signed Main() {
    Window::waitForDestroy();

    return 0;
}

bool Epilogue() {
    LOG_INFO("Shutdown");

    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();

    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    FreeConsole();

    return true;
}

void StartupThread(HANDLE hModule) {
    if (Prologue())
        Main();
    Epilogue();
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