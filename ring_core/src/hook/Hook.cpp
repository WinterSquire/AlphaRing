#include "Hook.h"

#include "MinHook.h"

bool Hook::Init() {
    auto result = MH_Initialize();
    return result == MH_OK;
}

void Hook::Shutdown() {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}
