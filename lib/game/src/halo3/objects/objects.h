#pragma once

#include "../base/base.h"

struct objects_definition {
    enum ePhysicsFlags : unsigned int {
        _object_is_early_mover_bit = 0x1,
        _object_has_proxy_bit =  0x4000,
        _object_connected_to_physics_bit = 0x80,
        _object_is_early_mover_child_bit = 0x10,
    };

    enum eObjectFlags : unsigned int {
        _object_hidden_bit = 0x1,
        _object_in_limbo_bit = 0x80,
        _object_connected_to_map_bit = 0x100,
        _object_has_attached_looping_sounds_bit = 0x20,
        _object_has_attached_lights_bit = 0x10,
        _object_has_unattached_lights_bit = 0x40,
        _object_has_override_bit = 0x2000000,
    };

    INDEX tag_index; // 0x0
    eObjectFlags object_flags; //0x4
    int v0;
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
    ePhysicsFlags physics_flags;//0xA8
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
        int simulation_flags; 0xD2
        int gamestate_index;
        int havok_comonent_index; 0x9C
        int next_recycling_group_member;
        int object_identifier;
        int scenario_datum_index;
        int change_colors;
        int attached_bounds_center;
        int parent_recycling_group;
        int parent_info;
     * */

    inline bool isUnit() { return (1 << type) & ((1 << OBJECTTYPE_BIPED) | (1 << OBJECTTYPE_GIANT) | (1 << OBJECTTYPE_VEHICLE)); }
    // damage flags
    inline bool CannotTakeDamage(){return damage_flags & 0x100u;}
    inline void CannotTakeDamage(bool b){if(b)damage_flags |= 0x100u;else damage_flags &= ~0x100u;}
    inline bool CannotDieFromDamage(){return damage_flags & 0x10000u;}
    inline void CannotDieFromDamage(bool b){if(b)damage_flags |= 0x10000u;else damage_flags &= ~0x10000u;}

    inline void kill() { damage_flags |= 0x40;}
};

struct object_definition {
    unsigned __int16 id;
    __int32 unknown_1;
    __int32 unknown_2;
    __int32 size;
    objects_definition* address;
};