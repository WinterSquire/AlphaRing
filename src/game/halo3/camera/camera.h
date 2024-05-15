#ifndef ALPHA_RING_CAMERA_H
#define ALPHA_RING_CAMERA_H

#include "../base/base.h"
#include "eCameraMode.h"

struct camera_t {
    // 0x180
    struct cam_t {
        void* pp_func1;
        void* pp_mode_func;
        INDEX target;
        __int8 un0[0xC];
        Vector3 position;
        Radian3 rotation;
        __int8 un[0x120];
        int index; // 0x158
        __int8 un1[0x180 - 0x15C];
    } camera[MAX_LOCAL_PLAYERS];

    __int8 un0[0x604 - MAX_LOCAL_PLAYERS * sizeof(cam_t)];

    // 0x604
    struct mode_t {
        int un_mode;
        eCameraMode mode;
        int un1;
    } mode[MAX_LOCAL_PLAYERS];
};

struct camera_data_t {
    struct raw_data_t {
        __int8 un0[0x11C];
        struct data_t {
            Vector3 position;
            float un;
            Vector3 velocity;
            Vector3 v_rotation;
            Vector3 components;
        } data;
        __int8 un1[0x280];
    } data[MAX_LOCAL_PLAYERS];
};

struct video_setting_t {
    float fov_fp;
    float fov_3rd;
};

struct texture_camera_t {
    bool enable;
    char un0;
    bool bink;
    char un1;

    int render_mode; // 0x4

    INDEX object; // 0x1C
    int marker; // 0x20

    Vector3 position_world_offset; // 0x28

    float fov; // 0x58
    float aspect_ratio; // 0x5C
    Vector2 resolution; // 0x60

    // attaches the render texture camera to a given object marker
    void attach_to_object(INDEX target, int marker = 0) {
        *(int*)(this + 0x8) = 0;
        *(int*)(this + 0x1C) = target;
        *(int*)(this + 0x20) = marker;
        *(Vector3*)(this + 0x28) = 0;
    }

    // targets the render texture camera to view a given object marker
    void target_object(INDEX target, int marker = 0) {
        *(int*)(this + 0xC) = 0;
        *(int*)(this + 0x34) = target;
        *(int*)(this + 0x38) = marker;
    }
};

struct split_screen_t {
    int un0;
    INDEX map_player[4];
    char un[0x60];
    int index[4];// 0x74
    int un1[3 * 4];// 0x84
    int screen_count; // 0xB4
    INDEX player_INDEX[4]; // 0xB8
    INDEX object_INDEX[4]; // 0xC8
    __int8 players[4]; // 0xD8

    bool set_player(Index index, INDEX player) {
        if (index < 0 || index > 3) return false;
        player_INDEX[index] = player;
        return true;
    }
};

class ICCamera {
public:
    virtual camera_t* getCamera() = 0;
    virtual camera_data_t* getCameraData() = 0;
    virtual video_setting_t* getVideoSetting() = 0;
    virtual inline split_screen_t* getSplitScreen() = 0;

};


#endif //ALPHA_RING_CAMERA_H
