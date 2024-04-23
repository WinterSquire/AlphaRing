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
        Vector3 rotation;
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

class ICCamera {
public:
    virtual camera_t* getCamera() = 0;
    virtual camera_data_t* getCameraData(Index player_index) = 0;
    virtual video_setting_t* getVideoSetting() = 0;
};

extern ICCamera* g_pICCamera;
inline ICCamera* Camera() {return g_pICCamera;}


#endif //ALPHA_RING_CAMERA_H
