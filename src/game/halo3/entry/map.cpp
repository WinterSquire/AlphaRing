#include "../native/native.h"
#include "../game/map.h"
#include "common.h"

namespace Halo3::Entry::Map {void Prologue(void* map_info);void Epilogue(void* map_info);}

void Halo3::Entry::Map::Prologue(void* map_info) {
    auto p_mapInfo = (::ICMap::Info*)map_info;
    ::Map()->setMapInfo(p_mapInfo);
}

void Halo3::Entry::Map::Epilogue(void* map_info) {
//    char buffer[1024];
//    for (int i = 0; i <= 256; ++i) {
//        unsigned long long entry = NativeInfo()->getEntryAddress(i);
//        if (entry < 0x7FF000000000 || entry > 0x800000000000) continue;
//        auto name = *(const char**)entry;
//        char c = *name;
//        if (!(c >= 'a' && c <= 'z')) continue;
//        sprintf(buffer, "%.20s = %d", name, i);
//        LOG_INFO(buffer);
//    }
}
