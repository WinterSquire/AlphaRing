#include "native_groundhog.h"

#include <cstring>
#include "core/String.h"

CNativeInfo GroundHog::Native::s_nativeInfo;

INDEX GroundHog::Native::Function::local_player_add(const wchar_t *name, const wchar_t *id) {
    typedef __int64 (__fastcall* func_init_t) (INDEX index, void* a2, bool a3);
    // size: 0x148
    struct player_init_t {
        bool v_true;
        char un0[0x7];
        int user_input; // 0x8
        int input_map; // 0xC
        int respawn_flag; // 0x10
        int respawn_flag2; // 0x14
        char un2[0x8];
        wchar_t name[0x10]; // 0x20
        char un3[36];
        wchar_t id[0x4]; // 0x64
        char un4[180];
        wchar_t name2[0x10]; // 0x120
        char un5[0x8];
    } new_player;
    int index = Players()->m_size;

    if (index < 0 || index > 3) return NONE;

    memset(&new_player, 0, sizeof(player_init_t));

    new_player.v_true = true;
    new_player.user_input = new_player.input_map = index;

    auto p_action = s_nativeInfo.getEntryAddress(OFFSET_GROUNDHOG_V_ENTRY_PLAYERS_ACTION);

    new_player.respawn_flag = *(int*)(p_action + 16);
    new_player.respawn_flag2 = *(__int16*)(p_action + 20);

    if (name) {
        String::wstrcpy(new_player.name, name);
        String::wstrcpy(new_player.name2, name);
    }

    if (id) {
        String::wstrcpy(new_player.id, id);
    }

    return (func_init_t(s_nativeInfo.getModuleAddress() + OFFSET_GROUNDHOG_PF_ADD_LOCAL_PLAYER))(index, &new_player, false);
}
