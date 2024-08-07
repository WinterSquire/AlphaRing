#include "native_halo3.h"

ThreadLocalStorage Halo3::Native::s_nativeInfo;

bool Halo3::Native::Function::player_push_message(Index player_index, const wchar_t *msg, int type) {
    if (player_index >= MAX_LOCAL_PLAYERS) return false;

    INVOKE<void>(OFFSET_HALO3_PF_PLAYER_PUSH_MESSAGE, &chud_persistent_user_data1()->player[player_index].msg, msg, type);

    return true;
}

__int64 Halo3::Native::Function::player_possess(INDEX player_index, INDEX target) {
    if ((__int16)player_index >= MAX_ONLINE_PLAYERS) return false;

    return INVOKE<__int64>(OFFSET_HALO3_PF_PLAYER_POSSESS, player_index, target);
}

INDEX Halo3::Native::Function::object_create(Datum datum, const Vector3 &position) {
    struct NewObjectData {
        Datum Datum;//0X0
        __int8 v0[0x8];
        __int32 VariantID;//0xC
        __int8 v1[0x8];
        __int8 flags;//0x18 (0x10)
        Vector3 position;//0x1c
        Vector3 forward;
        Vector3 up;
        Vector3 translational_velocity;
        Vector3 angular_velocity;
        float scale;
        __int8 v3[0x124];
    } newObjectData;//0x180

    INVOKE<void>(0x341158, &newObjectData, datum, (INDEX)NONE, (__int64)0);

    newObjectData.position = position;

    auto result = INVOKE<INDEX>(0x341738, &newObjectData);

    if (result == NONE) return result;

    INVOKE<bool>(0x1EA04, result);

    return result;
}

void Halo3::Native::Function::object_change_color(INDEX object_index) {
    INVOKE<void>(OFFSET_HALO3_PF_OBJECT_CHANGE_COLOR, object_index, true);
}
