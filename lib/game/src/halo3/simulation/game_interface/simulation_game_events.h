#pragma once

struct c_game_event {
    int un;
    int type;
    char buffer[34];
};

static_assert(sizeof(c_game_event) == 44);