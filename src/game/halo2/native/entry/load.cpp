#include "../native.h"

#include "halo2.h"

#include <windows.h>

namespace Halo2::Entry::Load {
    static bool bIsLoading;

    void Prologue() {
        bIsLoading = true;
        NativeHalo2()->NativeInfo()->update((__int64)GetModuleHandleA("halo2.dll"));
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
