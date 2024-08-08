#pragma once

struct game_time_globals_definition {
    __int8 v0;
    __int8 v1;
    __int8 time_flag;
    __int8 v2;
    __int16 tick_per_second;
    float second_per_tick;
    __int32 game_time;
    float speed;
    float game_ticks_leftover; // [-1.0, 2.0]

    void pause(bool value) {
        if (value) time_flag |= (1 << 3);
        else time_flag &= ~(1 << 3);
    }
};