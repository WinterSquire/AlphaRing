#include "native.h"

#include <cstring>
#include <windows.h>

CHalo2Native g_pCHalo2;

INDEX CHalo2Native::ICNativeFunc::local_player_add(const wchar_t *name, const wchar_t *id) {
    typedef __int64 (__fastcall* func_init_t) (INDEX index, void* a2);
    player_init_t new_player;

    auto hModule = (__int64)GetModuleHandleA("halo2.dll");

    int index = *(int*)(*(__int64*)(hModule + 0xE7FA28) + 0x40);

    if (index < 0 || index > 3) return NONE;

    memset(&new_player, 0, sizeof(player_init_t));

    new_player.v_true = true;
    new_player.user_input = new_player.input_map = index;
    new_player.respawn_flag = *(__int64*)(*(__int64*)(hModule + 0xE7FA20) + 0x30);

    if (name) {
        memcpy(new_player.name, name, sizeof(new_player.name));
    }

    if (id) {
        memcpy(new_player.id, id, sizeof(new_player.id));
    }

    *(int*)(*(__int64*)(hModule + 0xE7FA20) + 0x2C) |= 1 << index;

    return (func_init_t(hModule + OFFSET_HALO2_PF_ADD_LOCAL_PLAYER))(index, &new_player);
}
