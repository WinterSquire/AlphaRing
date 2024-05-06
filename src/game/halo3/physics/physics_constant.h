#ifndef ALPHA_RING_HALO3_PHYSICSCONSTANT_H
#define ALPHA_RING_HALO3_PHYSICSCONSTANT_H

#include <cmath>

struct PhysicsConstant {
    float gravity;
    float v0;
    float v1;
    float v2;
    float un;
    float v3;
    float v4;
    float v5;

    const float GRAVITY = 4.1712594f;   // 0x40857AF5

    inline void reset() {
        gravity = GRAVITY;
        v0 = 1.0f;
        v1 = 0.0011f;           // 0x3A902DE0
        v2 = 0;
        un = 0;
        v3 = 0;
        v4 = 0;
        v5 = cosf(0.61086524);
    }

    inline void set_gravity(float scale) {
        gravity = scale * GRAVITY;
    }
};

#endif //ALPHA_RING_HALO3_PHYSICSCONSTANT_H
