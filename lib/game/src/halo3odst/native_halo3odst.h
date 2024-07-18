#pragma once

#include "base.h"
#include "../ICNative.h"

#include "offset_halo3odst.h"

DefNative(Halo3ODST) {
    namespace Function {
        // Main Thread
        // Don't use these functions directly in Render Thread!
        INDEX local_player_add(const wchar_t *name, const wchar_t *id);
    }

    DefEntryEntity(Players, OFFSET_HALO3ODST_V_ENTRY_PLAYERS) {
    };

}
