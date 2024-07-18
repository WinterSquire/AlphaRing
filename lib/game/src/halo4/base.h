#pragma once

#define NONE -1
#define MAX_LOCAL_PLAYERS 4
#define MAX_ONLINE_PLAYERS 16

typedef unsigned short Index;
typedef unsigned int INDEX;
typedef unsigned int t_Player;
typedef unsigned int Datum;
typedef unsigned int StringID;

namespace Halo4 {
    template<typename T>
    struct entity_manager_t {
        char un[0x48];
        __int64 m_size;     // 0x48
    };
}