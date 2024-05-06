#include "actors.h"

#include "../native/native.h"

class CActor : public ICActor {
public:
    actor_t *getActor() override;

};

static CActor s_instance;
ICActor* g_pHalo3ICActor = &s_instance;

actor_t *CActor::getActor() {
    return (actor_t*) NativeHalo3()->NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_LOOP_ACTORS);
}