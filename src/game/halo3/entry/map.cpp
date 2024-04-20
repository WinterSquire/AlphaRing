#include "../map/map.h"

namespace Halo3::Entry::Map {void Prologue(void* map_info);void Epilogue(void* map_info);}

void Halo3::Entry::Map::Prologue(void* map_info) {
    auto p_mapInfo = (::ICMap::Info*)map_info;
    ::Map()->setMapInfo(p_mapInfo);
}

void Halo3::Entry::Map::Epilogue(void* map_info) {

}
