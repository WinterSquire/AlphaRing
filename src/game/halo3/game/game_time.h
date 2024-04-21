#ifndef ALPHA_RING_GAME_TIME_H
#define ALPHA_RING_GAME_TIME_H

struct game_time_t {
    __int8 v0;
    __int8 un[3];
    __int16 tick_per_second;
    float second_per_tick;
    __int32 game_time;
    float speed;
};

class ICTime {
public:
    virtual game_time_t* getGameTime() = 0;
};

extern ICTime* g_pICTime;
inline ICTime* Time() {return g_pICTime;}

#endif //ALPHA_RING_GAME_TIME_H
