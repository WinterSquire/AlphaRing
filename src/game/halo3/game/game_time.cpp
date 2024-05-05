#include "game_time.h"

#include "../native/native.h"

class CTime : public ICTime {
public:
    game_time_t *getGameTime() override;
};

static CTime time;
ICTime* g_pICTime = &time;

game_time_t* CTime::getGameTime() {
    return (game_time_t*)NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_TIME);
}
