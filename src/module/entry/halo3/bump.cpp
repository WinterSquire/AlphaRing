#include "./halo3.h"

namespace Halo3::Entry::Bump {
    extern void Prologue(unsigned int self, unsigned int target);
    extern void Epilogue(unsigned int self, unsigned int target);

    bool detour(unsigned int self, unsigned int target);

    Halo3Entry(entry, OFFSET_HALO3_PF_BUMP, detour);
}

bool Halo3::Entry::Bump::detour(unsigned int self, unsigned int target) {
    typedef bool (__fastcall* func_t)(unsigned int self, unsigned int target);
    auto func = (func_t)entry.m_pOriginal;

    Prologue(self, target);
    auto result = func(self, target);
    Epilogue(self, target);

    return result;
}
