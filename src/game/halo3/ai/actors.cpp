#include "actors.h"

#include "../native/native.h"

class CActor : public ICActor {
public:
    actor_t *getActor() override;

};

static CActor s_instance;
ICActor* g_pICActor = &s_instance;

actor_t *CActor::getActor() {
    return (actor_t*)NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_LOOP_ACTORS);
}