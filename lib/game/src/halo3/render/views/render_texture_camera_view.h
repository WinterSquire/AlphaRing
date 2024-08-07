#pragma once

#include "../../base/base.h"

struct render_texture_globals_definition {
    bool enable;
    char un0;
    bool bink;
    char un1;

    int render_mode; // 0x4

    INDEX object; // 0x1C
    int marker; // 0x20

    Vector3 position_world_offset; // 0x28

    float fov; // 0x58
    float aspect_ratio; // 0x5C
    Vector2 resolution; // 0x60

    // attaches the render texture camera to a given object marker
    void attach_to_object(INDEX target, int marker = 0) {
        *(int *) (this + 0x8) = 0;
        *(int *) (this + 0x1C) = target;
        *(int *) (this + 0x20) = marker;
        *(Vector3 * )(this + 0x28) = 0;
    }

    // targets the render texture camera to view a given object marker
    void target_object(INDEX target, int marker = 0) {
        *(int *) (this + 0xC) = 0;
        *(int *) (this + 0x34) = target;
        *(int *) (this + 0x38) = marker;
    }
};