#pragma once

#include "base.h"
#include "game/ICNative.h"

#include "offset_groundhog.h"

DefNative(GroundHog) {
    namespace Function {
        // Main Thread
        // Don't use these functions directly in Render Thread!
        INDEX local_player_add(const wchar_t *name, const wchar_t *id);
    }

    DefEntryEntity(Players, OFFSET_GROUNDHOG_V_ENTRY_PLAYERS) {
    };
}
