#ifndef ALPHA_RING_GAME_TIME_H
#define ALPHA_RING_GAME_TIME_H

struct game_time_t {
    __int8 v0;
    __int8 v1;
    __int8 time_flag;
    __int8 v2;
    __int16 tick_per_second;
    float second_per_tick;
    __int32 game_time;
    float speed;

    void pause(bool value) {
        if (value) time_flag |= (1 << 3);
        else time_flag &= ~(1 << 3);
    }
};

class ICTime {
public:
    virtual game_time_t* getGameTime() = 0;
};

extern ICTime* g_pICTime;
inline ICTime* Time() {return g_pICTime;}

#endif //ALPHA_RING_GAME_TIME_H
