#include "map.h"

#include "../native/native.h"

#include <cstring>

class CMap : public ICMap {
public:
    map_t *getMap() override;

};

static CMap s_instance;
ICMap* g_pICMap = &s_instance;

map_t *CMap::getMap() {
    return (map_t*)NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_MAP);
}
