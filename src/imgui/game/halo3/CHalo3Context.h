#pragma once

#include "imgui/main_context.h"
#include "game/halo3/native_halo3.h"

#include <functional>

namespace Halo3::Entry::World {extern void AddTask(const std::function<void()>& func);}

#define setState(...) Halo3::Entry::World::AddTask(__VA_ARGS__)

class CHalo3Context : public ICContext {
public:
    void render() override;

    void context_global();
    void context_actor();
    void context_camera();
    void context_object();
    void context_physics();
    void context_player();
    void context_render();

    static CHalo3Context instance;
};

extern ICContext* g_pHalo3Context;
