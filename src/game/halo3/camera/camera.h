#ifndef ALPHA_RING_CAMERA_H
#define ALPHA_RING_CAMERA_H

#include "../base/base.h"
#include "eCameraMode.h"

struct camera_t {
    struct cam_t {
        void* pp_func1;
        void* pp_mode_func;
        INDEX target;
        __int8 un0[12];
        Vector3 position;
        Radian3 rotation;
        __int8 un[0x144];
    } camera[4];
    __int32 un1;
    __int32 un2;
    eCameraMode mode;
};

struct camera_data_t {
    __int8 un0[0x11C];
    struct data_t {
        Vector3 position;
        float un;
        Vector3 velocity;
        Vector3 v_rotation;
        Vector3 components;
    } data;
    __int8 un1[0x280];
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

class ICCamera {
public:
    virtual camera_t* getCamera() = 0;
    virtual camera_data_t* getCameraData(Index player_index) = 0;
    virtual video_setting_t* getVideoSetting() = 0;
};


#endif //ALPHA_RING_CAMERA_H
