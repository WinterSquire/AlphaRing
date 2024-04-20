#ifndef ALPHA_RING_MAP_H
#define ALPHA_RING_MAP_H

#include "core/LockedResource.h"

class ICMap {
public:
    struct Info {
        __int8 map_type; // 1 campaign; 2 mp; 3 mainmenu
        __int8 un[67];
        char map_name[0x104];
    };

    virtual void setMapInfo(Info* info) = 0;
    virtual Info* getMapInfo() = 0;
};

extern ICMap* g_pICMap;
inline ICMap* Map() {return g_pICMap;}

#endif //ALPHA_RING_MAP_H
