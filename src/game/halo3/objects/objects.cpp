#include "objects.h"

#include "../native/native.h"

class CObjects : public ICObjects {
public:
    entity_manager_t<ObjectInfo> *getObjectManager() override;
    object_infos_t *getObjectInfos() override;

};

static CObjects objects;
ICObjects* g_pHalo3ICObjects = &objects;

entity_manager_t<ObjectInfo> *CObjects::getObjectManager() {
    return (entity_manager_t<ObjectInfo> *)(NativeHalo3()->NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_OBJECT));
}

object_infos_t *CObjects::getObjectInfos() {
    return (object_infos_t*)(NativeHalo3()->NativeInfo()->getModuleAddress() + OFFSET_HALO3_PV_OBJECT_INFOS);
}

