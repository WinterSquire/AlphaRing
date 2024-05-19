#include "native.h"
#include "core/String.h"

#include <cstring>

CHalo4Native g_pCHalo4;

INDEX CHalo4Native::CNativeFunc::local_player_add(const wchar_t *name, const wchar_t *id) {
    typedef __int64 (__fastcall* func_init_t) (INDEX index, void* a2, bool a3);
    player_init_t new_player;
    int index = NativeHalo4()->Players()->PlayerManager()->m_size;

    if (index < 0 || index > 3) return NONE;

    memset(&new_player, 0, sizeof(player_init_t));

    new_player.v_true = true;
    new_player.user_input = new_player.input_map = index;

    auto p_action = NativeHalo4()->NativeInfo()->getEntryAddress(OFFSET_HALO4_V_ENTRY_PLAYERS_ACTION);

    new_player.respawn_flag = *(int*)(p_action + 16);
    new_player.respawn_flag2 = *(__int16*)(p_action + 20);

    if (name) {
        String::wstrcpy(new_player.name, name);
        String::wstrcpy(new_player.name2, name);
    }

    if (id) {
        String::wstrcpy(new_player.id, id);
    }

    return (func_init_t(NativeHalo4()->NativeInfo()->getModuleAddress() + OFFSET_HALO4_PF_ADD_LOCAL_PLAYER))(index, &new_player, false);
}
