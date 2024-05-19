#include "../native.h"
#include "common.h"

#include "halo3.h"

namespace Halo3::Entry::Map {
    struct map_info_t {
        char buffer[0x10];
        struct t1_t {
            char buffer[0xA8];
            struct t2_t {
#pragma pack(push, 1)
                char buffer_1[0x126C];
                int player_count0; // 0x126C
                int un;
                struct init_info {
                    __int64 unun; // 0x0
                    int player_index; // 0x8
                    __int16 user_input; // 0xC
                    char buffer[10];
                    int input_map; // 0x18
                    char buffer1[12];
                    // offset: 0x28
                    wchar_t name[0x10];
                    char un1[0x1E];
                    wchar_t id[0x3];
                    char un2[0x34];
                    wchar_t name2[0x10];
                    char un3[8];
                } initInfo[16];
#pragma pack(pop)
            } *t2;
        } *t1;
    };

    struct engine_t {

    };

    void Prologue(map_info_t* map_info, map_info_t::t1_t::t2_t* p_t2) {
        LOG_INFO("Game Init");
//        const wchar_t *name = L"UWU";
//        const wchar_t *id = L"UWU";
//
//        for (int index = 1; index <= 1; ++index) {
//            p_t2->player_count0 |= (1 << index);
//            auto &new_player = p_t2 ->initInfo[index];
//            memset(&new_player, 0, sizeof(new_player));
//
//            new_player.unun = index;
//            new_player.player_index = index;
//            new_player.user_input = index;
//            new_player.input_map = index;
//
//            if (name) {
//                wcscpy_s(new_player.name, name);
//                wcscpy_s(new_player.name2, name);
//            }
//
//            if (id) {
//                wcscpy_s(new_player.id, id);
//            }
//        }
    }

    void Epilogue(map_info_t* map_info, map_info_t::t1_t::t2_t* p_t2) {

    }

    Halo3Entry(entry, OFFSET_HALO3_PF_MAP, bool, detour, map_info_t * map_info, map_info_t::t1_t::t2_t* p_t2) {
        Prologue(map_info, p_t2);
        auto result = ((detour_t )entry.m_pOriginal)(map_info, p_t2);
        Epilogue(map_info, p_t2);
        return result;
    }
}
