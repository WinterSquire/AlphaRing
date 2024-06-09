#include "Log.h"

#include <cstdio>

#include <minhook/MinHook.h>
#include "hook/d3d11.h"
#include "hook/mcc/mcc.h"

#include "render/Window.h"
#include "input/Input.h"

#include <filesystem>

//todo: filesystem

#define INIT_ERROR(error_message) { \
    LOG_ERROR(error_message); \
    MessageBoxA(0, "Alpha Ring: " error_message, "Error", 0); \
    return false; \
}

bool Prologue() {
    const char* home_dir = "../../../alpha_ring";

    if (!std::filesystem::exists(home_dir)) {
        std::filesystem::create_directories(home_dir);
    }

    if (AllocConsole() == false) INIT_ERROR("Console Fail To Allocate!");

    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    LOG_INFO("Version: {}", GAME_VERSION);

    if (!AlphaRing::Input::Init()) INIT_ERROR("Input Fail To Initialize!");

    if (MH_Initialize() != MH_OK) INIT_ERROR("MinHook Fail To Initialize!");

    if (!Directx11Hook::Initialize()) INIT_ERROR("DirectX11 Hook Fail To Initialize!");

    if (!MCCHook::Initialize()) INIT_ERROR("MCC Hook Fail To Initialize!");

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