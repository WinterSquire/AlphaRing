#include "native_haloreach.h"

#include <cstring>

CNativeInfo HaloReach::Native::s_nativeInfo;

INDEX HaloReach::Native::Function::player_add(const wchar_t *name, const wchar_t *id, bool isClient) {
    typedef __int64 (__fastcall* func_init_t) (INDEX index, void* a2, bool a3);
    // size: 0xA0
    struct player_init_t {
        bool v_true;
        bool b_isClient;
        char un0[0x6];
        int user_input; // 0x8
        int input_map; // 0xC
        int respawn_flag; // 0x10
        int respawn_flag2; // 0x14
        __int64 xid;
        wchar_t name[0x10]; // 0x20
        char un3[36];
        wchar_t id[0x4]; // 0x64
        char un4[12];
        wchar_t name2[0x10]; // 0x78
        char un5[0x8];
    } new_player;
    int index = Players()->m_size;

    memset(&new_player, 0, sizeof(player_init_t));

    new_player.v_true = true;
    new_player.xid = index;

    if ((new_player.b_isClient = isClient)) {
        new_player.input_map = new_player.user_input = -1;
    } else {
        new_player.input_map = new_player.user_input = index;
        memcpy(&new_player.respawn_flag,
               (void*)(s_nativeInfo.getEntryAddress(OFFSET_HALOREACH_V_ENTRY_PLAYERS_ACTION) + 8),
               6);
    }

    if (name) {
        String::wstrcpy(new_player.name, name);
        String::wstrcpy(new_player.name2, name);
    }

    if (id) {
        String::wstrcpy(new_player.id, id);
    }

    return (func_init_t(s_nativeInfo.getModuleAddress() + OFFSET_HALOREACH_PF_ADD_LOCAL_PLAYER))(index, &new_player, false);
}
