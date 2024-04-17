#include "entry.h"

namespace Halo3::Entry::World {
    const __int64 OFFSET = 0xEEDD4;
    extern void Prologue();
    extern void Epilogue();
    void detour();

    ::Entry entry{OFFSET, (__int64)detour};
}

void Halo3::Entry::World::detour() {
    Prologue();
    entry.getPointerOriginal()();
    Epilogue();
}