#include "camera.h"

#include "../native/native.h"

class CCamera : public ICCamera {
public:
    camera_t *getCamera() override;
    camera_data_t *getCameraData() override;
    video_setting_t *getVideoSetting() override;
    split_screen_t *getSplitScreen() override;
};

static CCamera s_instance;
ICCamera* g_pHalo3ICCamera = &s_instance;

camera_t *CCamera::getCamera() {
    return (camera_t*) NativeHalo3()->NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_CAMERAS);
}

camera_data_t *CCamera::getCameraData() {
    return (camera_data_t*) NativeHalo3()->NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_CAMERAS_DATA);
}

video_setting_t *CCamera::getVideoSetting() {
    return (video_setting_t*)(NativeHalo3()->NativeInfo()->getModuleAddress() + OFFSET_HALO3_PV_GLOBAL_VARIABLE + 0x8 + 0x6C);
}

split_screen_t *CCamera::getSplitScreen() {
    return (split_screen_t*)NativeHalo3()->NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_SPLIT_SCREEN);
}
