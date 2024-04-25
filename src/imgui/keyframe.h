#ifndef CUSTOM_WIDGET_KEYFRAME_H
#define CUSTOM_WIDGET_KEYFRAME_H

#include <cmath>

struct float2 {
    float x,y;

    inline float distance(const float2& other) const {float dx = x - other.x;float dy = y - other.y;return std::sqrt(dx * dx + dy * dy);}
    inline float2 normalize() const {float length = std::sqrt(x * x + y * y);return {x / length, y / length};}

    inline float2 operator* (const float value) const {return {x * value, y * value};}
    inline float2 operator- (const float2& other) const {return {x - other.x, y - other.y};}
    inline float2 operator+ (const float2& other) const {return {x + other.x, y + other.y};}
    inline void operator+= (const float2& other) { x += other.x; y += other.y;}
};

struct keyframe_t {
    unsigned int id;
    float2 left_handle;
    float2 keyframe;
    float2 right_handle;

    keyframe_t* next;
    keyframe_t* prev;

    // https://github.com/blender/blender/blob/main/source/blender/blenkernel/intern/curve_bezier.cc#L86
    inline float2 calculate_aligned_handle(const float2 &handle, const float2 &other_handle) const {return keyframe - (handle - keyframe).normalize() * other_handle.distance(keyframe);}
    inline void set_left_handle_position(float2 new_position) { if (new_position.x >= keyframe.x) return; left_handle = new_position; right_handle = calculate_aligned_handle(left_handle, right_handle);}
    inline void set_right_handle_position(float2 new_position) { if (new_position.x <= keyframe.x) return; right_handle = new_position; left_handle = calculate_aligned_handle(right_handle, left_handle);}
    inline void addValue(float offset) {keyframe.y += offset; left_handle.y += offset; right_handle.y += offset;}
    inline void setValue(float value) { addValue(keyframe.y - value);}
    inline void drop() {if (prev) prev->next = next; if (next) next->prev = prev;}
    inline void relocate() {
        keyframe_t *tmp;
        while (prev != nullptr && prev->keyframe.x > keyframe.x) {
            tmp = prev;
            if (next) next->prev = prev;
            prev->next = next;
            // move to prev
            next = prev;
            prev = prev->prev;
            if (tmp->prev) tmp->prev->next = this;
            tmp->prev = this;
        }
        while (next != nullptr && next->keyframe.x < keyframe.x) {
            tmp = next;
            if (prev) prev->next = next;
            next->prev = prev;
            // move to next
            prev = next;
            next = next->next;
            if (tmp->next) tmp->next->prev = this;
            tmp->next = this;
        }
    }
};


#endif //CUSTOM_WIDGET_KEYFRAME_H
