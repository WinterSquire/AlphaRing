#include "../native.h"

#include "halo2.h"

#include <windows.h>

#include "patch/Patch.h"

namespace Halo2::Entry::Load {
    static bool bIsLoading;

    void Prologue() {
        bIsLoading = true;
        auto hModule = (__int64)GetModuleHandleA("halo2.dll");
        NativeHalo2()->NativeInfo()->update(hModule);
        // fix splitscreen respawn issue
        Patch::apply((void*)(hModule + 0x6A3B47), (void*)"\x90\x90", 2);
    }

    void Epilogue() {
        bIsLoading = false;
    }

    bool IsLoading() {
        return bIsLoading;
    }

    Halo2Entry(entry, OFFSET_HALO2_PF_LOAD, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
