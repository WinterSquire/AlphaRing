#include "entry.h"

namespace Halo3::Entry::Render {
    const __int64 OFFSET = 0x1851EC;
    extern void Prologue();
    extern void Epilogue();
    void detour();

    ::Entry entry{OFFSET, (__int64)detour};
}

void Halo3::Entry::Render::detour() {
    Prologue();
    entry.getPointerOriginal()();
    Epilogue();
}
