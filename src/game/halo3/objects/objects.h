#ifndef ALPHA_RING_OBJECTS_H
#define ALPHA_RING_OBJECTS_H

#include "../base/base.h"
#include "eObjectType.h"
#include "../game/eTeam.h"

struct ObjectInfo;

class ICObjects {
public:
    virtual entity_manager_t<ObjectInfo>* getObjectManager() = 0;

};

extern ICObjects* g_pICObjects;
inline ICObjects* Objects() {return g_pICObjects;}

struct objects_t {
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

    inline bool isUnit() { return (1 << type) & ((1 << OBJECTTYPE_BIPED) | (1 << OBJECTTYPE_GIANT) | (1 << OBJECTTYPE_VEHICLE)); }
    // damage flags
    inline bool CannotTakeDamage(){return damage_flags & 0x100u;}
    inline void CannotTakeDamage(bool b){if(b)damage_flags |= 0x100u;else damage_flags &= ~0x100u;}
    inline bool CannotDieFromDamage(){return damage_flags & 0x10000u;}
    inline void CannotDieFromDamage(bool b){if(b)damage_flags |= 0x10000u;else damage_flags &= ~0x10000u;}

    inline void kill() { damage_flags |= 0x40;}

    __int16 size();

};

struct units_t : objects_t {
    __int8 v9[0x54];
    INDEX actor_index;//0x168
    __int8 v10[0x4];
    __int32 unit_flags;
    eTeamAI team;//0x174
    t_Player player_index;//0x178
    __int8 v11[0xA0];//0x20C?
    INDEX aim_target;//0x21C
    __int8 v12[0x14C];//378 crouch程度 1.0max
    float camo_time;
    __int8 v13[0x12C];//378 crouch程度 1.0max
    INDEX bump_target;//0x49C bump target
    __int8 bump_close;

    inline bool FlashLight(){return unit_flags & 0x8000000u;}
    inline void FlashLight(bool b){if(b) unit_flags |= 0x8000000u;else damage_flags &= ~0x8000000u;}
    inline bool CanMove(){return unit_flags & 0x3u;}
    inline void CanMove(bool b){if(b) unit_flags |= 0x3u;else unit_flags &= ~0x3u;}
    inline void EnableCamo() { unit_flags |= 0x10u | 0x8u; }
    inline void SetCamo(float time) { EnableCamo(); camo_time = time; }
};

struct ObjectInfo {
    __int64 v0;
    __int64 v1;
    objects_t* address;

    inline bool isValid() {return address != nullptr;}
};

#endif //ALPHA_RING_OBJECTS_H
