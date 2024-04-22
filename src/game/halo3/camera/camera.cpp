#include "camera.h"

#include "../native/native.h"

class CCamera : public ICCamera {
public:
    camera_t *getCamera(Index player_index) override;

};

static CCamera s_instance;
ICCamera* g_pICCamera = &s_instance;

camera_t *CCamera::getCamera(Index player_index) {
    if (player_index < 0 || player_index > 3) return nullptr;
    return (camera_t*)(NativeInfo()->getEntryAddress((int)eEntry::cameras) + player_index * 0x180i64);
}