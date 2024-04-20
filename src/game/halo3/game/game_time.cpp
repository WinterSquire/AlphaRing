#include "game_time.h"

#include "../native/native.h"

class CTime : public ICTime {
public:
    Time_t *getGameTime() override;
};

static CTime time;
ICTime* g_pICTime = &time;

Time_t* CTime::getGameTime() {
    return (Time_t*)NativeInfo()->getEntryAddress((int)eEntry::time);
}
