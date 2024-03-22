#include "halo3.h"

#include "MinHook.h"

#include "./asm/asm.h"

const __int64 OFFSET_ENGINE_INIT = 0xB2A20;
const __int64 OFFSET_ENGINE_UNINIT = 0xB2EB6;
const __int64 OFFSET_MAP_INIT = 0x12E6CE;
const __int64 OFFSET_SCRIPT = 0xEF2BF;

bool Halo3Hook::Init() {
    return true;
}

bool Halo3Hook::Update(__int64 hModule) {
    return true;
}

void Halo3Hook::Shutdown() {

}
