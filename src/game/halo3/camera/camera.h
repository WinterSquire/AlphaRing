#ifndef ALPHA_RING_CAMERA_H
#define ALPHA_RING_CAMERA_H

#include "../base/base.h"
#include "eCameraMode.h"

struct camera_t {
    void* pp_func1;
    void* pp_mode_func;
    INDEX target;
};

class ICCamera {
public:
    virtual camera_t* getCamera(Index player_index) = 0;
};

extern ICCamera* g_pICCamera;
inline ICCamera* Camera() {return g_pICCamera;}


#endif //ALPHA_RING_CAMERA_H
