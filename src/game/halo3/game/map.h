#ifndef ALPHA_RING_MAP_H
#define ALPHA_RING_MAP_H

#include "eSkull.h"
#include "players.h"

struct map_t {
    __int8 un[0x10];
    // size: 0xFB60
    struct map_info_t {
        __int8 game_type; // 1 campaign; 2 mp; 3 mainmenu
        __int8 un1[0x43];
        char name[0x104];
        char un0[0xA8];
        player_init_t playerInit[16]; // 0x200
        __int8 un2[0xEE08];
        // 0xFB88 - 0xFB98
        __int8 skulls[0x10];
    } map_info;

    inline bool get_skull(eSkull skull) { return map_info.skulls[skull / 8] & (1 << (skull % 8));}
    inline void set_skull(eSkull skull, bool enable) {
        if (enable) map_info.skulls[skull / 8] |= (1 << (skull % 8));
        else map_info.skulls[skull / 8] &= ~(1 << (skull % 8));
    }
};

class ICMap {
public:
    virtual map_t* getMap() = 0;
};


#endif //ALPHA_RING_MAP_H
