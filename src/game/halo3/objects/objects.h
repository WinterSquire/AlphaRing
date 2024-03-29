#ifndef ALPHA_RING_OBJECTS_H
#define ALPHA_RING_OBJECTS_H

#include "../base/type.h"

struct Objects_t {
    Datum datum;//0x0
    __int8 v0[8];
    INDEX next_object_index;//0xC
    INDEX parent_object_index;//0x10
    __int8 v1[0x3C];
    Vector3 position;//0x50
    Vector3 facing;//0x5C
    Vector3 up;//0x68
    __int8 b2[0x16];//0x74
    float scale;//0x8C
    __int8 v3[0x6];
    __int8 type;//0x96
    __int8 v4[0x11];
    unsigned int physics_flags;//0xA8
    __int8 v5[0xA];
    __int8 variant_index;//0xB6
    __int8 v6[0x15];
    unsigned int physics;//0xCC
    __int8 v7[0x24];
    float health;//0xF4
    float shield;//0xF8
    __int8 v8[0x14];
    unsigned int damage_flags;//1<<4 0x110

/*
    int flags;
    int simulation_flags;
    int gamestate_index;
    int havok_comonent_index;
    int next_recycling_group_member;
    int object_identifier;
    int scenario_datum_index;
    int change_colors;
    int attached_bounds_center;
    int parent_recycling_group;
    int parent_info;
 * */

    enum {
        BIPED,
        VEHICLE,
        WEAPON,
        EQUIPMENT,
        TERMINAL,
        PROJECTILE,
        SCENERY,
        MACHINE,
        CONTROL,
        SOUNDSCENERY,
        CRATE,
        CREATURE,
        GIANT,
        EFFECTSCENERY
    };

    bool IsUnit();
    __int16 size();
};


#endif //ALPHA_RING_OBJECTS_H
