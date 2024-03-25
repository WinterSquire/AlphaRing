#include "halo3.h"

#include "MinHook.h"

#include "./entry/entry.h"

const __int64 OFFSET_MAP_INIT = 0x12E6CE;
const __int64 OFFSET_SCRIPT = 0xEF2BF;

bool Halo3Hook::Init() {return true;}

bool Halo3Hook::Update(__int64 hModule) { return Entry::update_all(hModule); }

void Halo3Hook::Shutdown() {}
