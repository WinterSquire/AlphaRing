#include "camera.h"

#include "../native/native.h"

class CCamera : public ICCamera {
public:
    camera_t *getCamera() override;
    camera_data_t *getCameraData(Index player_index) override;
    video_setting_t *getVideoSetting() override;
};

static CCamera s_instance;
ICCamera* g_pICCamera = &s_instance;

camera_t *CCamera::getCamera() {
    return (camera_t*)NativeInfo()->getEntryAddress(eEntry::cameras);
}

camera_data_t *CCamera::getCameraData(Index player_index) {
    return (camera_data_t*)NativeInfo()->getEntryAddress(eEntry::cameras_data) + player_index;
}

video_setting_t *CCamera::getVideoSetting() {
    return (video_setting_t*)(NativeInfo()->getModuleAddress() + 0x2D3DD70 + 0x8 + 0x6C);
}
