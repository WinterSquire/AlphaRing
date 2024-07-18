#ifndef CUSTOM_WIDGET_CURVE_H
#define CUSTOM_WIDGET_CURVE_H

#include "imgui.h"
#include "keyframe.h"

#include <set>

struct curve_t {
    static unsigned int id_count;

    const char* p_name;
    bool locked;
    bool enabled;
    bool visibility;
    ImU32 curve_selected_color;
    ImU32 curve_unselected_color;
    keyframe_t* p_head;
    keyframe_t* p_tail;

    keyframe_t* p_last;

    curve_t(const char* name, ImColor curve_color);

    keyframe_t* addKeyframe(ImVec2 keyframe);
    keyframe_t* addKeyframe(float x, float y);
    void moveKeyframe(keyframe_t* keyframe, float2 offset);
    void dropKeyframe(keyframe_t* keyframe);

    float getValue(float frame);
};


#endif //CUSTOM_WIDGET_CURVE_H
