#include "../native.h"
#include "common.h"

#include "halo3.h"

namespace Halo3::Entry::Map {
    void Prologue(void* map_info) {
        LOG_INFO("Game Init");
    }

    void Epilogue(void* map_info) {

    }

    Halo3Entry(entry, OFFSET_HALO3_PF_MAP, bool, detour, void* map_info) {
        Prologue(map_info);
        auto result = ((detour_t )entry.m_pOriginal)(map_info);
        Epilogue(map_info);

        return result;
    }
}
