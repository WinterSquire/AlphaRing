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