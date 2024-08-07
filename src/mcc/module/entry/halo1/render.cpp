#include "halo1.h"

#include <Windows.h>

namespace Halo1::Entry::Render {
    void Prologue() {
//        NativeHalo1()->NativeInfo()->update((__int64) GetModuleHandleA("halo1.dll"));
    }

    void Epilogue() {

    }

    Halo1Entry(entry, OFFSET_HALO1_PF_RENDER, void, detour, void* a1, int a2) {
        Prologue();
        ((detour_t)entry.m_pOriginal)(a1, a2);
        Epilogue();
    }
}
