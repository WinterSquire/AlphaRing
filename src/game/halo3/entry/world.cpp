#include "../native/native.h"

#include "common.h"

namespace Halo3::Entry::World { void Prologue(); void Epilogue(); }

static int tick = 0;

static bool bInit = false;

void Halo3::Entry::World::Prologue() {
    if (bInit) return;
    if (tick != 300) ++tick;
    else {
        NativeFunc()->pushMsg(0, L"Welcome");
        bInit = true;
        tick = 0;
    }
}

void Halo3::Entry::World::Epilogue() {

}

