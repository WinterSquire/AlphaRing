#include "../native.h"

#include "halo2.h"

namespace Halo2::Entry::Load {
    static bool bIsLoading;

    void Prologue() {
        bIsLoading = true;
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
