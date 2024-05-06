#include "map.h"

#include "../native/native.h"

#include <cstring>

class CMap : public ICMap {
public:
    map_t *getMap() override;

};

static CMap s_instance;
ICMap* g_pHalo3ICMap = &s_instance;

map_t *CMap::getMap() {
    return (map_t*)NativeHalo3()->NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_MAP);
}
