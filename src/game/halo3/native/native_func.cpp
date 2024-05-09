#include "native_func.h"

#include "native_halo3.h"

class CNativeFunc : public ICNativeFunc {
public:
    bool player_push_message(Index player_index, const wchar_t *msg, int type) override;
    __int64 player_possess(INDEX player_index, INDEX target) override;

    bool players_control_camera(bool custom_control) override;
    bool player_set_camera(Index player_index, eCameraMode mode, float time) override;

};

static CNativeFunc native_func;
ICNativeFunc* g_pICHalo3NativeFunc = &native_func;

bool CNativeFunc::player_push_message(Index player_index, const wchar_t *msg, int type) {
    typedef void (__fastcall* func_t)(chud_t::msg_t* a1, const wchar_t *a2, int a3);

    if (player_index > 3) return false;

    auto p_chud = NativeHalo3()->Render()->getChud();

    if (p_chud == nullptr) return false;

    ((func_t)(NativeHalo3()->NativeInfo()->getModuleAddress() + OFFSET_HALO3_PF_PLAYER_PUSH_MESSAGE))(&p_chud[player_index].msg, msg, type);

    return true;
}

__int64 CNativeFunc::player_possess(INDEX player_index, INDEX target) {
    typedef __int64 (__fastcall* func_t) (INDEX player_index, INDEX target);

    if ((__int16)player_index > 15) return false;

    return ((func_t)(NativeHalo3()->NativeInfo()->getModuleAddress() + OFFSET_HALO3_PF_PLAYER_POSSESS))(player_index, target);
}

bool CNativeFunc::player_set_camera(Index player_index, eCameraMode mode, float time) {
    typedef bool (__fastcall* func_t) (void* a1, unsigned int a2, float a3, char a4);

    auto p_camera = NativeHalo3()->Camera()->getCamera();

    if (p_camera == nullptr) return false;

    players_control_camera(true);

    if (mode == CAMERAMODE_FOLLOWING) {
        auto p_player = NativeHalo3()->Players()->getPlayerManager()->get(player_index);
        if (p_player == nullptr) return false;
        p_camera->camera[player_index].target = p_player->object_INDEX;
    }

    return ((func_t)(NativeHalo3()->NativeInfo()->getModuleAddress() + OFFSET_HALO3_PF_PLAYER_SET_CAMERA))(p_camera, mode, time, 0);
}

bool CNativeFunc::players_control_camera(bool custom_control) {
    typedef bool (__fastcall* func_t) (bool);
    return ((func_t)(NativeHalo3()->NativeInfo()->getModuleAddress() + OFFSET_HALO3_PF_PLAYERS_CONTROL_CAMERA))(custom_control);
}
