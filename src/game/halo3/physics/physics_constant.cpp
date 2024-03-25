#include "physics_constant.h"

#include <cmath>

void PhysicsConstant::reset() {
    gravity = 4.1712594f;//0x40857AF5
    v0 = 1.0f;//0x3F800000
    v1 = 0.0011f;//0x3A902DE0
    v2 = 0;
    un = 0;
    v3 = 0;
    v4 = 0;
    v5 = cosf(0.61086524);
}

void PhysicsConstant::set_gravity(float scale) {
    gravity = scale * 4.1712594f;
}
