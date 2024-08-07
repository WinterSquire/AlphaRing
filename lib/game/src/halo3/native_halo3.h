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
    INDEX object_create(Datum datum, const Vector3& position);
    void object_change_color(INDEX object_index);
}

#include "./ai/actors.h"
#include "./camera/director.h"
#include "./camera/observer.h"
#include "./game/players.h"
#include "./game/game_globals.h"
#include "./game/game_time.h"
#include "./game/player_mapping.h"
#include "./interface/chud/chud.h"
#include "./interface/chud/chud_messaging.h"
#include "./objects/objects.h"
#include "./units/units.h"
#include "./physics/physics_constants.h"
#include "./rasterizer/rasterizer.h"
#include "./render/views/render_texture_camera_view.h"

#define DefH3Global(name) inline name##_definition* name() { return (name##_definition*)teb_data()->name; }

DefNative(Halo3) {
    inline halo3_teb_data_definition* teb_data() { return (halo3_teb_data_definition*)(*(s_nativeInfo.m_pTLS + s_nativeInfo.m_TlsIndex)); }

    DefH3Global(actor);
    DefH3Global(director_globals);
    DefH3Global(observer_globals);
    DefH3Global(players_globals);
    DefH3Global(game_globals);
    DefH3Global(game_time_globals);
    DefH3Global(player_mapping_globals);
    DefH3Global(chud_persistent_user_data1);
    DefH3Global(chud_persistent_user_data2);
    DefH3Global(physics_constants);
    DefH3Global(rasterizer_game_states);
    DefH3Global(render_texture_globals);

    inline entity_manager_t<players_definition>* players() { return (entity_manager_t<players_definition>*)teb_data()->players; }
    inline entity_manager_t<object_definition>* object() { return (entity_manager_t<object_definition>*)teb_data()->object; }

    DefPtr(Log, 0xA48170) {
        struct log_t {
            char title[0x100];
            char content[0x200];
        };

        log_t log[0x20];

        static_assert((sizeof(log_t) == 0x300));
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

    DefPtr(Input, OFFSET_HALO3_PV_ENABLE_INPUT) {
        bool enable;
    };

    DefPtr(VideoSetting, OFFSET_HALO3_PV_GLOBAL_VARIABLE) {
        char buffer1[0x8];
        char buffer2[0x6C];
        float fov_fp;
        float fov_3rd;
    };

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
}
