#ifndef ALPHA_RING_ECAMERAMODE_H
#define ALPHA_RING_ECAMERAMODE_H

enum eCameraMode : unsigned int
{
    CAMERAMODE_FOLLOWING,
    CAMERAMODE_ORBITING,
    CAMERAMODE_FLYING,
    CAMERAMODE_FP,
    CAMERAMODE_DEAD,
    CAMERAMODE_STATIC,
    CAMERAMODE_SCRIPTED,
    CAMERAMODE_AUTHORED,
    CAMERAMODE_SANDBOX
};

static const char* eCameraModeName[] = {
        "FOLLOWING",
        "ORBITING",
        "FLYING",
        "FP",
        "DEAD",
        "STATIC",
        "SCRIPTED",
        "AUTHORED",
        "SANDBOX"
};

#endif //ALPHA_RING_ECAMERAMODE_H
