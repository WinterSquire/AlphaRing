#include "entry.h"

namespace Halo3::Entry::Engine {
    const __int64 OFFSET = 0xB2A20;
    extern void Prologue();
    extern void Epilogue();
    void detour();

    ::Entry engine{OFFSET, (__int64)detour};
}

void Halo3::Entry::Engine::detour() {
    Prologue();
    engine.getPointerOriginal()();
    Epilogue();
}
