#include "entry.h"

namespace Halo3::Entry::Map {
    const __int64 OFFSET = 0x12E388;
    extern void Prologue(void*);
    extern void Epilogue(void*);
    bool detour(void* map_info);

    ::Entry entry{OFFSET, (__int64)detour};
}

bool Halo3::Entry::Map::detour(void* map_info) {
    typedef bool (__fastcall *func_t)(void* map_info);
    auto func = (func_t)entry.getPointerOriginal();
    Prologue(map_info);
    auto result = func(map_info);
    Epilogue(map_info);
    return result;
}
