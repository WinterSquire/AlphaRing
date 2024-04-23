#include "camera.h"

#include "../native/native.h"

class CCamera : public ICCamera {
public:
    camera_t *getCamera() override;
    camera_data_t *getCameraData(Index player_index) override;
};

static CCamera s_instance;
ICCamera* g_pICCamera = &s_instance;

camera_t *CCamera::getCamera() {
    return (camera_t*)NativeInfo()->getEntryAddress(eEntry::cameras);
}

camera_data_t *CCamera::getCameraData(Index player_index) {
    return (camera_data_t*)NativeInfo()->getEntryAddress(eEntry::cameras_data) + player_index;
}
