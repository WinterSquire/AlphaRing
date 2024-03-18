#pragma once

class PhysicsConstant
{
    float gravity;
    float v0;
    float v1;
    float v2;
    float un;
    float v3;
    float v4;
    float v5;

    void reset();
    void set_gravity(float scale);
};

static PhysicsConstant *physicsConstant;

//   v0 = *(*(NtCurrentTeb()->ThreadLocalStoragePointer + TlsIndex) + 304i64);
//   *v0 = 0x40857AF5;                             // gravity
//   *(v0 + 4) = 0x3F800000;
//   *(v0 + 8) = 0x3A902DE0;
//   *(v0 + 24) = 0;
//   *(v0 + 12) = 0i64;
//   *(v0 + 20) = 0;
//   *(v0 + 28) = cosf(0.61086524);
