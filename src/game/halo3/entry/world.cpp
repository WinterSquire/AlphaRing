#include "../native/native.h"

#include "common.h"

namespace Halo3::Entry::World { void Prologue(); void Epilogue(); }

static int tick = 0;

static bool bInit = false;

bool bemit = false;

void world_test() {
    bemit = true;
}

void Halo3::Entry::World::Prologue() {
    if (bemit) {
        NativeFunc()->player_push_message(0, L"Respawn");
        NativeFunc()->player_possess(0, NONE);
        bemit = false;
    }

    if (bInit) return;
    if (tick != 300) ++tick;
    else {
        NativeFunc()->player_push_message(0, L"Welcome");
        bInit = true;
        tick = 0;
    }
}

void Halo3::Entry::World::Epilogue() {

}

