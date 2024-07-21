#pragma once

#include "../ICNative.h"
#include "offset_halo3.h"

#include "base/base.h"

#include <cstddef>
#include <cmath>

namespace Halo3::Native::Function {
    // Main Thread
    // Don't use these functions directly in Render Thread!
    bool player_push_message(Index player_index, const wchar_t* msg, int type = 2);
    __int64 player_possess(INDEX player_index, INDEX target);
    bool players_control_camera(bool custom_control);
    bool player_set_camera(Index player_index, eCameraMode mode, float time = 0.0f);
    INDEX local_player_add(const wchar_t *name, const wchar_t *id);
    INDEX object_create(Datum datum, const Vector3& position);
    void object_change_color(INDEX object_index);
}

DefNative(Halo3) {
    // ================================ Actor ================================
    DefEntry(Actor, OFFSET_HALO3_V_ENTRY_LOOP_ACTORS) {
        bool enable_ai;
    };

    // ================================ Camera ================================
    DefEntry(Camera, OFFSET_HALO3_V_ENTRY_CAMERAS) {
        struct cam_t {
            void *pp_func1;
            void *pp_mode_func;
            INDEX target;
            __int8 un0[0xC];
            Vector3 position;
            Radian3 rotation;
            __int8 un[0x120];
            int index; // 0x158
            __int8 un1[0x180 - 0x15C];
        } camera[MAX_LOCAL_PLAYERS];

        static_assert((sizeof(cam_t) == 0x180));

        __int8 un0[0x604 - MAX_LOCAL_PLAYERS * sizeof(cam_t)];

        // 0x604
        struct mode_t {
            int un_mode;
            eCameraMode mode;
            int un1;
        } mode[MAX_LOCAL_PLAYERS];
    };

    DefEntry(CameraData, OFFSET_HALO3_V_ENTRY_CAMERAS_DATA) {
        struct raw_data_t {
            __int8 un0[0x11C];
            struct data_t {
                Vector3 position;
                float un;
                Vector3 velocity;
                Vector3 v_rotation;
                Vector3 components;
            } data;
            __int8 un1[0x280];
        } data[MAX_LOCAL_PLAYERS];
    };

    DefEntry(TextureCamera, OFFSET_HALO3_V_ENTRY_TEXTURE_CAMERA) {
        bool enable;
        char un0;
        bool bink;
        char un1;

        int render_mode; // 0x4

        INDEX object; // 0x1C
        int marker; // 0x20

        Vector3 position_world_offset; // 0x28

        float fov; // 0x58
        float aspect_ratio; // 0x5C
        Vector2 resolution; // 0x60

        // attaches the render texture camera to a given object marker
        void attach_to_object(INDEX target, int marker = 0) {
            *(int *) (this + 0x8) = 0;
            *(int *) (this + 0x1C) = target;
            *(int *) (this + 0x20) = marker;
            *(Vector3 * )(this + 0x28) = 0;
        }

        // targets the render texture camera to view a given object marker
        void target_object(INDEX target, int marker = 0) {
            *(int *) (this + 0xC) = 0;
            *(int *) (this + 0x34) = target;
            *(int *) (this + 0x38) = marker;
        }
    };

    DefEntry(SplitScreen, OFFSET_HALO3_V_ENTRY_SPLIT_SCREEN) {
        int un0;
        INDEX map_player[4]; // 0x4
        char un1[0x20];
        INDEX input_player[4]; // 0x34
        char un2[0x30];
        int index[4];// 0x74
        int un3[3 * 4];// 0x84
        int screen_count; // 0xB4
        INDEX player_INDEX[4]; // 0xB8
        INDEX object_INDEX[4]; // 0xC8
        __int8 players[4]; // 0xD8
    };

    // ================================ Chud ================================
    DefEntry(Chud, OFFSET_HALO3_V_ENTRY_CHUD) {
        char buffer[0x144];
        bool chud_show;
        bool weapon_stats;
        bool crosshair;
        bool shield;
        bool grenades;
        bool messages;
        bool motion_sensor;
        bool spike_grenades;
        bool fire_grenades;
    };

    DefEntry(ChudMessage, OFFSET_HALO3_V_ENTRY_MESSAGE) {
        struct player_chud_t {
            char un0[0x6c];
            bool chud_texture_cam; // offset: 0x6C
            char un1;
            bool cinematic_scripting_destroy_cortana_effect_cinematic; // offset: 0x6E
            char un2[0x1F8C - 0x6F];
            // offset: 0x1F8Ci64 size: ?
            struct msg_t {
                // offset: 0x90 size: 0xE8i64
                struct str_t {
                    wchar_t text[0x60]; // 0x0
                    int un0 = 0x100; // 0xC0
                    int game_time = 0x100; // 0xC4
                    int un1; // 0xC8
                    int un2 = 0; // 0xCC
                    int un4[5]; // 0xD0
                    int un3 = 2; // 0xE4
                } str[6];

                static_assert((sizeof(str_t) == 0xE8));
            } msg;
            char un3[0x28C8 - (0x1F8C + sizeof(msg_t))];
        } player[MAX_LOCAL_PLAYERS];

        static_assert((sizeof(player_chud_t) == 0x28C8));
    };


    // ================================ Global ================================
    DefEntry(PhysicsConstant, OFFSET_HALO3_V_ENTRY_PHYSICS_CONSTANTS) {
        float gravity;
        float v0;
        float v1;
        float v2;
        float un;
        float v3;
        float v4;
        float v5;

        const float GRAVITY = 4.1712594f;   // 0x40857AF5

        inline void reset() {
            gravity = GRAVITY;
            v0 = 1.0f;
            v1 = 0.0011f;           // 0x3A902DE0
            v2 = 0;
            un = 0;
            v3 = 0;
            v4 = 0;
            v5 = cosf(0.61086524);
        }

        inline void set_gravity(float scale) { gravity = scale * GRAVITY; }
    };

    DefEntry(Map, OFFSET_HALO3_V_ENTRY_MAP) {
        __int8 un[0x10];
        // size: 0xFB60
        struct map_info_t {
            __int8 game_type; // 1 campaign; 2 mp; 3 mainmenu
            __int8 un1[0x43];
            char name[0x104];
            char un0[0xA8];
            // size: 0xB8
            struct player_init_t {
                bool v_true;
                bool v_false;
                __int16 user_input;
                int input_map;
                int respawn_flag; // 0x8
                int unun;
                __int64 un_flag; // 0x10
                wchar_t name[0x10]; // 0x18
                char un1[0x1E];
                wchar_t id[0x3]; // 0x56
                char un2[0x34];
                wchar_t name2[0x10]; // 0x90
                char un3[0x8];
            } playerInit[16]; // 0x200
            __int8 un2[0xEE08];
            // 0xFB88 - 0xFB98
            __int8 skulls[0x10];
        } map_info;

        inline bool get_skull(eSkull skull) { return map_info.skulls[skull / 8] & (1 << (skull % 8)); }

        inline void set_skull(eSkull skull, bool enable) {
            if (enable) map_info.skulls[skull / 8] |= (1 << (skull % 8));
            else map_info.skulls[skull / 8] &= ~(1 << (skull % 8));
        }
    };

    // ================================ Objects ================================
    DefEntryEntity(Objects, OFFSET_HALO3_V_ENTRY_OBJECT) {
        enum ePhysicsFlags : unsigned int {
            _object_is_early_mover_bit = 0x1,
            _object_has_proxy_bit =  0x4000,
            _object_connected_to_physics_bit = 0x80,
            _object_is_early_mover_child_bit = 0x10,
        };

        __int64 v0;
        __int64 v1;
        struct objects_t {
            enum eObjectFlags : unsigned int {
                _object_hidden_bit = 0x1,
                _object_in_limbo_bit = 0x80,
                _object_connected_to_map_bit = 0x100,
                _object_has_attached_looping_sounds_bit = 0x20,
                _object_has_attached_lights_bit = 0x10,
                _object_has_unattached_lights_bit = 0x40,
                _object_has_override_bit = 0x2000000,
            };

            Datum datum;//0x0
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
        } *address;

        struct units_t : objects_t {
            enum eUnitFlags {
                _biped_setting_relaxation_pose_bit = 0x200,
            };

            __int8 v9[0x54];
            INDEX actor_index;//0x168
            __int8 v10[0x4];
            __int32 unit_flags;
            eTeamAI team; //0x174
            t_Player player_index; //0x178
            __int8 v11[0xA0]; //0x20C?
            INDEX aim_target; //0x21C
            __int8 v12[0x14C];
            float camo_time;
            __int64 un;
            float crouch_progress; // [0, 1.0]
            __int8 v13[0xE4];
            __int16 biped_flags;
            __int8 v14[0x42];
            INDEX bump_target; // 1188
            __int8 bump_close;

            // 0x460 __int16 biped.flags

            inline bool FlashLight(){return unit_flags & 0x8000000u;}
            inline void FlashLight(bool b){if(b) unit_flags |= 0x8000000u;else damage_flags &= ~0x8000000u;}
            inline bool CanMove(){return unit_flags & 0x3u;}
            inline void CanMove(bool b){if(b) unit_flags |= 0x3u;else unit_flags &= ~0x3u;}
            inline void EnableCamo() { unit_flags |= 0x10u | 0x8u; }
            inline void SetCamo(float time) { EnableCamo(); camo_time = time; }
        };

        inline bool isValid() { return address != nullptr; }
    };

    DefPtr(ObjectInfos, OFFSET_HALO3_PV_OBJECT_INFOS) {
        struct object_info_t {
            const char *full_name;
            char magic[4];
            __int16 size;
            __int16 un[9];
            void *func[0x25];
            void *parent[0x13];
        } *object_infos[14];

        object_info_t *get(eObjectType type) { return object_infos[type]; }
    };

    // ================================ Players ================================
    DefEntryEntity(Players, OFFSET_HALO3_V_ENTRY_PLAYERS) {
        int Index; // 0x0000EC71
        char flags_0; // (1 << 3) black screen
        char flags_1;
        __int8 v0[0x22];
        INDEX object_INDEX; // 0x28 can't modify directly
        INDEX restore_INDEX; // 0x2C
        __int8 v1[0x1C];
        Vector3 position;// 0x4C
        wchar_t name[0x10]; // 0x58
        bool pref_voice;//0x78
        __int8 primary_color;
        __int8 secondary_color;
        __int8 tertiary_color;
        bool pref_species; // 0x7C
        __int8 v3[0x19];
        wchar_t id[4]; // 0x96
        __int8 v4[0x50];
        unsigned int team; // 0xF0
        __int8 v5[0xAC];
        unsigned int respawn_time; // 0x1A0
        __int8 v6[0x33];// 0x1AC respawn_time_second
        __int8 coop_index;// 0x1D7
        __int8 v7[0x2];
        __int8 v8[0x22];// 0xBC
        __int8 player_shield;
        __int8 v9[0x3];
        __int8 v10[0xC];
        __int8 player_camo;
        __int8 v11[0x87];
        Vector3 position2;// 0x294
        INDEX object_INDEX2;
        INDEX restore_INDEX2;
        float uk0, uk1, uk2;
        __int8 v20[0x3C];
    };

    static_assert((sizeof(Players_t) == 0x2F0));

    DefEntry(PlayersAction, OFFSET_HALO3_V_ENTRY_PLAYERS_ACTION) {
        __int32 player_count;
        bool disable_input;
    };

    DefPtr(Input, OFFSET_HALO3_PV_ENABLE_INPUT) {
        bool enable;
    };

    // ================================ Render ================================

    DefEntry(RenderFlag, OFFSET_HALO3_V_ENTRY_RENDER) {
        bool motion_blur;
        bool atmosphere_fog;
        bool patchy_fog;
        bool render_weather;
        bool cinematic_motion_blur;
    };

    DefPtr(VideoSetting, OFFSET_HALO3_PV_GLOBAL_VARIABLE) {
        char buffer1[0x8];
        char buffer2[0x6C];
        float fov_fp;
        float fov_3rd;
    };

    // ================================ TagFiles ================================
    DefPPtr(TagName, OFFSET_HALO3_PV_TAG_NAMES, 0) {
        inline static const int MAX_TAGS = 0x8000;

        int offset[MAX_TAGS];
        const char buffer[0x800000];
        const char *ptr[MAX_TAGS];

        inline const char *get(Index index) {
            if (index < 0 || index >= MAX_TAGS) return nullptr;
            return ptr[index];
        }
    };

    // https://github.com/XboxChaos/Assembly/blob/a9650c010fc6bb8e7d0ea01afe3a024619e4db95/src/Blamite/Blam/ITagGroup.cs#L6
    DefPPtr(ITagGroup, 0x20AC058, 0x8) {
        CharConstant Magic;
        CharConstant ParentMagic;
        CharConstant GrandparentMagic;
        StringID Description;
    };

    DefPPtr(TagSalt, 0xA48018, 0x0) {
        __int16 tag_group_index;
        __int16 datum_index_salt;
        __int32 memory_address;
    };

    // ================================ Time ================================
    DefEntry(Time, OFFSET_HALO3_V_ENTRY_TIME) {
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
}
