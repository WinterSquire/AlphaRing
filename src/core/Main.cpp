#include "log/Log.h"
#include "hook/Hook.h"
#include "input/Input.h"
#include "filesystem/Filesystem.h"
#include "hook/d3d11/main_window.h"

#define INIT_ERROR(error_message) { \
    MessageBoxA(0, "Alpha Ring: " error_message, "Error", 0); \
    return false; \
}

bool Prologue() {
    if (!AlphaRing::Log::Init())
        INIT_ERROR("Info Fail To Initialize!");

    LOG_INFO("Version: {}", GAME_VERSION);

    if (!AlphaRing::Hook::Init())
        INIT_ERROR("Hook Fail To Initialize!");

    if (!AlphaRing::Input::Init())
        INIT_ERROR("Input Fail To Initialize!");

    if (!AlphaRing::Filesystem::Init())
        INIT_ERROR("Filesystem Fail To Initialize!");

    return true;
}

signed Main() {
    MainWindow()->waitForDestroy();

    return 0;
}

bool Epilogue() {
    LOG_INFO("Shutdown");

    AlphaRing::Filesystem::Shutdown();
    AlphaRing::Input::Shutdown();
    AlphaRing::Hook::Shutdown();
    AlphaRing::Log::Shutdown();

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