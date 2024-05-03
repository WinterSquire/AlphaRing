#include "halo3.h"

#include "./entry/entry.h"

bool Halo3Hook::Init(__int64 hModule) { return Entry::update_all(hModule); }

void Halo3Hook::Shutdown() {}
