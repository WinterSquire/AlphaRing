#include "../native/native.h"
#include "common.h"

namespace Halo3::Entry::Map {void Prologue(void* map_info);void Epilogue(void* map_info);}

void Halo3::Entry::Map::Prologue(void* map_info) {
    LOG_INFO("Game Init");
}

void Halo3::Entry::Map::Epilogue(void* map_info) {
    auto p_coop = NativeHalo3()->Players()->getPlayerCoop();
    if (p_coop->enable) {
        for (int i = 1; i < p_coop->count; ++i) {
            NativeHalo3()
                    ->NativeFunc()
                    ->local_player_add(L"UWU", L"UWU");
        }
    }
}
