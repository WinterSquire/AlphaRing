#include "world.h"

#include "../entry.h"

using namespace Halo3Hook::World;

const __int64 OFFSET_WORLD = 0xEEDD4;

static void detour();

Entry world{OFFSET_WORLD, (__int64) detour};

static callback_t init_func = nullptr;
void Halo3Hook::World::setInitCallback(callback_t func) {init_func = func;}

static callback_t uninit_func = nullptr;
void Halo3Hook::World::setUninitCallback(callback_t func) {uninit_func = func;}

static bool bFirst = false;

static void detour() {
    if (!bFirst) {
        bFirst = true;

    }

    if (init_func) init_func();
    world.getPointerOriginal()();
    if (uninit_func) uninit_func();
}
