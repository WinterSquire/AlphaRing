#include "native.h"

#include <cstring>

CHalo2Native g_pCHalo2;

INDEX CHalo2Native::ICNativeFunc::local_player_add(const wchar_t *name, const wchar_t *id) {
    typedef __int64 (__fastcall* func_init_t) (INDEX index, void* a2);
    // size: 0xD4
    struct player_init_t {
        bool v_true;
        bool un0;
        __int16 user_input; // 0x2
        int input_map; // 0x4
        __int64 respawn_flag; // 0x8
        char un2[0x8];
        wchar_t name[0x10]; // 0x18
        char un3[48];
        wchar_t id[0x4]; // 0x68
        char un4[0x64];
    } new_player;

    auto hModule = NativeHalo2()->m_nativeInfo.getModuleAddress();

    int index = *(int*)(*(__int64*)(hModule + OFFSET_HALO2_PV_PLAYERS) + 0x40);

    if (index < 0 || index > 3) return NONE;

    memset(&new_player, 0, sizeof(player_init_t));

    new_player.v_true = true;
    new_player.user_input = new_player.input_map = index;
    new_player.respawn_flag = *(__int64*)(*(__int64*)(hModule + OFFSET_HALO2_PV_RESPAWN) + 0x30);

    if (name) {
        memcpy(new_player.name, name, sizeof(new_player.name));
    }

    if (id) {
        memcpy(new_player.id, id, sizeof(new_player.id));
    }

    *(int*)(*(__int64*)(hModule + OFFSET_HALO2_PV_RESPAWN) + 0x2C) |= 1 << index;

    return (func_init_t(hModule + OFFSET_HALO2_PF_ADD_LOCAL_PLAYER))(index, &new_player);
}
