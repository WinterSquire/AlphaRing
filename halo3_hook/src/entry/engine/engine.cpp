#include "engine.h"

#include "../entry.h"

using namespace Halo3Hook::Engine;

const __int64 OFFSET_ENGINE = 0xB2A20;

void engine_detour();

Entry engine{OFFSET_ENGINE, (__int64) engine_detour};

static callback_t init_func = nullptr;
void Halo3Hook::Engine::setEngineInitCallback(callback_t func) {init_func = func;}

static callback_t uninit_func = nullptr;
void Halo3Hook::Engine::setEngineUninitCallback(callback_t func) {uninit_func = func;}

void engine_detour() {
    if (init_func) init_func();
    engine.getPointerOriginal()();
    if (uninit_func) uninit_func();
}
