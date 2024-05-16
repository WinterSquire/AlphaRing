#ifndef ALPHA_RING_NATIVE_FUNC_H
#define ALPHA_RING_NATIVE_FUNC_H

#include "../base/base.h"

#include "../game/players.h"
#include "../game/game_time.h"
#include "../camera/camera.h"
#include "../objects/objects.h"

class ICNativeFunc {
public:
    // Main Thread
    // Don't use these functions directly in Render Thread!
    virtual bool player_push_message(Index player_index, const wchar_t* msg, int type = 2) = 0;
    virtual __int64 player_possess(INDEX player_index, INDEX target) = 0;
    virtual bool players_control_camera(bool custom_control) = 0;
    virtual bool player_set_camera(Index player_index, eCameraMode mode, float time = 0.0f) = 0;
    virtual INDEX local_player_add(const wchar_t *name, const wchar_t *id) = 0;

    virtual INDEX object_create(Datum datum, const Vector3& position) = 0;
};

#endif //ALPHA_RING_NATIVE_FUNC_H
