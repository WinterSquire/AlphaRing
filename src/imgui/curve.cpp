#include "curve.h"

unsigned int curve_t::id_count = 0;

curve_t::curve_t(const char* name, ImColor curve_color) {
    float hsv[3];
    curve_selected_color = curve_color;
    ImGui::ColorConvertRGBtoHSV(curve_color.Value.x, curve_color.Value.y, curve_color.Value.z, hsv[0], hsv[1], hsv[2]);
    curve_color.SetHSV(hsv[0], hsv[1], hsv[2] / 2);
    curve_unselected_color = curve_color;

    locked = false;
    enabled = true;
    visibility = true;
    p_name = name;
    p_head = p_tail = p_last = nullptr;
}

keyframe_t * curve_t::addKeyframe(ImVec2 keyframe) {
    return addKeyframe(keyframe.x, keyframe.y);
}

keyframe_t* curve_t::addKeyframe(float x, float y) {
    auto node = p_head;
    auto new_node = new keyframe_t{id_count++, x - 60, y, x, y, x + 60, y, nullptr, nullptr};
    if (node == nullptr) return p_head = p_tail = new_node;
    while (node != nullptr) {
        if (x <= node->keyframe.x) {
            new_node->prev = node->prev;
            new_node->next = node;
            if (node->prev) node->prev->next = new_node;
            return node->prev = new_node;
        }
        node = node->next;
    }
    p_tail->next = new_node;
    new_node->prev = p_tail;
    return p_tail = new_node;
}

float curve_t::getValue(float frame) {
    if (!enabled || p_head == nullptr || p_tail == nullptr) return 0;

    if (p_last == nullptr) {
        auto node = p_head;
        while (node != nullptr) {
            if (node->keyframe.x <= frame) p_last = node;
            else break;
            node = node->next;
        }
    } else {
        while (p_last->next != nullptr && p_last->next->keyframe.x <= frame) {
            p_last = p_last->next;
        }
        while (p_last != nullptr && p_last->keyframe.x > frame) {
            p_last = p_last->prev;
        }
    }

    if (p_last == nullptr) return p_head->keyframe.y;
    else if (p_last->next == nullptr) return p_tail->keyframe.y;

    auto t = (frame - p_last->keyframe.x) / (p_last->next->keyframe.x - p_last->keyframe.x);
    float u = 1.0f - t;
    float w1 = u * u * u;
    float w2 = 3 * u * u * t;
    float w3 = 3 * u * t * t;
    float w4 = t * t * t;
    return w1 * p_last->keyframe.y + w2 * p_last->right_handle.y + w3 * p_last->next->left_handle.y + w4 * p_last->next->keyframe.y;
}

void curve_t::dropKeyframe(keyframe_t *keyframe) {
    if (keyframe == nullptr) return;
    if (keyframe == p_head) p_head = keyframe->next;
    if (keyframe == p_tail) p_tail = keyframe->prev;
    keyframe->drop();
    delete keyframe;
}

void curve_t::moveKeyframe(keyframe_t *keyframe, float2 offset) {
    if (keyframe == nullptr) return;
    keyframe->keyframe += offset;
    keyframe->left_handle += offset;
    keyframe->right_handle += offset;
    keyframe->relocate();
    if (p_head->prev != nullptr) p_head = p_head->prev;
    if (p_tail->next != nullptr) p_tail = p_tail->next;
}
