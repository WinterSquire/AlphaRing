#include "entry.h"

namespace Halo3::Entry::Map {
    extern void Prologue(void*);
    extern void Epilogue(void*);
    bool detour(void* map_info);

    ::Entry entry{OFFSET_HALO3_PF_MAP, detour};
}

bool Halo3::Entry::Map::detour(void* map_info) {
    typedef bool (__fastcall *func_t)(void* map_info);
    auto func = (func_t)entry.pOriginal();

    Prologue(map_info);
    auto result = func(map_info);
    Epilogue(map_info);

    return result;
}
