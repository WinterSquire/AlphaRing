#include "native.h"

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
    new_player.respawn_flag = 0x0000459D;

    if (name) {
        memcpy(new_player.name, name, sizeof(new_player.name));
        memcpy(new_player.name2, name, sizeof(new_player.name2));
    }

    if (id) {
        memcpy(new_player.id, id, sizeof(new_player.id));
    }

    return (func_init_t(m_native->NativeInfo()->getModuleAddress() + OFFSET_HALO3ODST_PF_ADD_LOCAL_PLAYER))(index, &new_player, false);
}
