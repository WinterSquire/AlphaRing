#include "Hook.h"

#include "MinHook.h"

const __int64 OFFSET_ENGINE_INIT = 0xB2A20;
const __int64 OFFSET_ENGINE_UNINIT = 0xB2EB6;
const __int64 OFFSET_MAP_INIT = 0x12E6CE;
const __int64 OFFSET_SCRIPT = 0xEF2BF;

bool Hook::Init() {
    auto result = MH_Initialize();
    return result == MH_OK;
}

void Hook::Shutdown() {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}
