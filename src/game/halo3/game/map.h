#ifndef ALPHA_RING_MAP_H
#define ALPHA_RING_MAP_H

#include "eSkull.h"

struct map_t {
    __int8 un[0x10];
    __int8 game_type; // 1 campaign; 2 mp; 3 mainmenu
    __int8 un1[0x43];
    char name[0x104];

//    // offset: 0x200 size: 0xB8
//    struct player_init_info_t {
//        bool valid;
//        bool un;
//    } player_init_info[4];

    __int8 un2[0xFA30];
    // 0xFB88 - 0xFB98
    __int8 skulls[0x10];

    inline bool get_skull(eSkull skull) { return skulls[skull / 8] & (1 << (skull % 8));}
    inline void set_skull(eSkull skull, bool enable) {
        if (enable) skulls[skull / 8] |= (1 << (skull % 8));
        else skulls[skull / 8] &= ~(1 << (skull % 8));
    }
};

class ICMap {
public:
    virtual map_t* getMap() = 0;
};


#endif //ALPHA_RING_MAP_H
