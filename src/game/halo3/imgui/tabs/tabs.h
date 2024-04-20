#ifndef ALPHA_RING_TABS_H
#define ALPHA_RING_TABS_H

#include "common.h"
#include "imgui.h"

struct Tab {
    typedef void(*callback_t)();
    const char* name;
    callback_t callback;
};

namespace Halo3::IMGUI::Tabs {
    void tab_map();
    void tab_object();
    void tab_player();
    void tab_render();
    void tab_time();
}

#endif //ALPHA_RING_TABS_H
