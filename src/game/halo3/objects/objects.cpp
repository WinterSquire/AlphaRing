#include "objects.h"

#include "../native/native.h"

__int16 objects_t::size() {
    return 0;
//    return *(__int16*)(*(__int64*)(NativeInfo::getTLS().get_hModule() + 0x810D20 + type * 8) + 0x6);
}

class CObjects : public ICObjects {
public:
    entity_manager_t<ObjectInfo> *getObjectManager() override;
};

static CObjects objects;
ICObjects* g_pHalo3ICObjects = &objects;

entity_manager_t<ObjectInfo> *CObjects::getObjectManager() {
    return (entity_manager_t<ObjectInfo> *)(NativeHalo3()->NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_OBJECT));
}

