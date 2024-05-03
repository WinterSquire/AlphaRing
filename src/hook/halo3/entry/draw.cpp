#include "entry.h"

namespace Halo3::Entry::Draw {
    const __int64 OFFSET1 = 0x27FDB4;
    const __int64 OFFSET2 = 0x2B51E0;
    extern void Prologue(int type);
    extern void Epilogue(int type);
    __int64 detour1(unsigned int a1, __int64 a2, __int64 a3, __int64 a4);
    __int64 detour2(__int64 p_render_model, __int64 a2);

    ::Entry entry_structure{OFFSET1, (__int64)detour1};
    ::Entry entry_model{OFFSET2, (__int64)detour2};
}


__int64 Halo3::Entry::Draw::detour1(unsigned int a1, __int64 a2, __int64 a3, __int64 a4) {
    typedef __int64 (__fastcall* func_t)(unsigned int a1, __int64 a2, __int64 a3, __int64 a4);
    auto func = (func_t)entry_structure.getPointerOriginal();
    Prologue(1);
    auto result = func(a1, a2, a3, a4);
    Epilogue(1);
    return result;
}

__int64 Halo3::Entry::Draw::detour2(__int64 p_render_model, __int64 a2) {
    typedef __int64 (__fastcall* func_t)(__int64 p_render_model, __int64 a2);
    auto func = (func_t)entry_model.getPointerOriginal();
    Prologue(2);
    auto result = func(p_render_model, a2);
    Epilogue(2);
    return result;
}