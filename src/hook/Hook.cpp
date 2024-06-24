#include "Hook.h"

#include <minhook/MinHook.h>

#include "./d3d11/d3d11.h"
#include "./mcc/mcc.h"

bool AlphaRing::Hook::Init() {
    if (MH_Initialize() != MH_OK)
        return false;

    if (!Directx11Hook::Initialize())
        return false;

    if (!MCCHook::Initialize())
        return false;

    return true;
}

bool AlphaRing::Hook::Shutdown() {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();

    return true;
}
