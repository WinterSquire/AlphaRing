#include "../native/native.h"
#include "common.h"

namespace Halo3::Entry::Map {void Prologue(void* map_info);void Epilogue(void* map_info);}

void Halo3::Entry::Map::Prologue(void* map_info) {
    LOG_INFO("Game Init");
}

void Halo3::Entry::Map::Epilogue(void* map_info) {

}
