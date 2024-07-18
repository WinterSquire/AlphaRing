#include "native_halo3odst.h"
#include "String.h"

#include <cstring>

CNativeInfo Halo3ODST::Native::s_nativeInfo;

INDEX Halo3ODST::Native::Function::local_player_add(const wchar_t *name, const wchar_t *id) {
    typedef __int64 (__fastcall* func_init_t) (INDEX index, void* a2, bool a3);
    // size: 0x98
    struct player_init_t {
        bool v_true;
        bool v_false;
        __int16 user_input;
        int input_map;
        int respawn_flag; // 0x8
        int unun;
        __int64 un_flag; // 0x10
        wchar_t name[0x10]; // 0x18
        char un1[22];
        wchar_t id[0x3]; // 0x4E
        char un2[28];
        wchar_t name2[0x10]; // 0x70
        char un3[0x8];
    } new_player;

    int index = Players()->m_size;

    if (index < 0 || index > 3) return NONE;

    memset(&new_player, 0, sizeof(player_init_t));

    new_player.v_true = true;
    new_player.user_input = new_player.input_map = index;

    auto p_action = s_nativeInfo.getEntryAddress(OFFSET_HALO3ODST_V_ENTRY_PLAYERS_ACTION);

    new_player.respawn_flag = *(int*)(p_action + 12);
    new_player.unun = *(__int16*)(p_action + 12 + 4);

    if (name) {
        String::wstrcpy(new_player.name, name);
        String::wstrcpy(new_player.name2, name);
    }

    if (id) {
        String::wstrcpy(new_player.id, id);
    }

    return (func_init_t(s_nativeInfo.getModuleAddress() + OFFSET_HALO3ODST_PF_ADD_LOCAL_PLAYER))(index, &new_player, false);
}
