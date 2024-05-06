#include "./halo3.h"

namespace Halo3::Entry::Draw {
    extern void Prologue(int type); extern void Epilogue(int type);
    __int64 detour1(unsigned int a1, __int64 a2, __int64 a3, __int64 a4);
    __int64 detour2(__int64 p_render_model, __int64 a2);

    Halo3Entry(entry_structure, OFFSET_HALO3_PF_DRAW_STRUCTURE, detour1);
    Halo3Entry(entry_model, OFFSET_HALO3_PF_DRAW_MODEL, detour2);
}

__int64 Halo3::Entry::Draw::detour1(unsigned int a1, __int64 a2, __int64 a3, __int64 a4) {
    typedef __int64 (__fastcall* func_t)(unsigned int a1, __int64 a2, __int64 a3, __int64 a4);
    auto func = (func_t) entry_structure.m_pOriginal;
    Prologue(1);
    auto result = func(a1, a2, a3, a4);
    Epilogue(1);
    return result;
}

__int64 Halo3::Entry::Draw::detour2(__int64 p_render_model, __int64 a2) {
    typedef __int64 (__fastcall* func_t)(__int64 p_render_model, __int64 a2);
    auto func = (func_t) entry_model.m_pOriginal;
    Prologue(2);
    auto result = func(p_render_model, a2);
    Epilogue(2);
    return result;
}