#include "native.h"
#include "core/String.h"

#include <cstring>

CHalo3ODSTNative g_pCHalo3ODST;

INDEX CHalo3ODSTNative::ICNativeFunc::local_player_add(const wchar_t *name, const wchar_t *id) {
    typedef __int64 (__fastcall* func_init_t) (INDEX index, void* a2, bool a3);
    player_init_t new_player;

    int index = m_native->Players()->PlayerManager()->m_size;

    if (index < 0 || index > 3) return NONE;

    memset(&new_player, 0, sizeof(player_init_t));

    new_player.v_true = true;
    new_player.user_input = new_player.input_map = index;

    auto p_action = NativeHalo3ODST()->NativeInfo()->getEntryAddress(OFFSET_HALO3ODST_V_ENTRY_PLAYERS_ACTION);

    new_player.respawn_flag = *(int*)(p_action + 12);
    new_player.unun = *(__int16*)(p_action + 12 + 4);

    if (name) {
        String::wstrcpy(new_player.name, name);
        String::wstrcpy(new_player.name2, name);
    }

    if (id) {
        String::wstrcpy(new_player.id, id);
    }

    return (func_init_t(m_native->NativeInfo()->getModuleAddress() + OFFSET_HALO3ODST_PF_ADD_LOCAL_PLAYER))(index, &new_player, false);
}
