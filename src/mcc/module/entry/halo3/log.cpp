#include "halo3.h"

#include "common.h"

namespace Halo3::Entry::Log {
    Halo3Entry(entry, 0xB3C1C, char*, detour, char *header, char* format, __int64 data1, __int64 data2) {
        auto result = ((detour_t)entry.m_pOriginal)(header, format, data1, data2);
        if (format && result && strncmp(header, "game_tick", 9)) LOG_INFO("{}: {}", header, result);
        return result;
    }
}
