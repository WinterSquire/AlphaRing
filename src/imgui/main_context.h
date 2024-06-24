#pragma once

#include "imgui/imgui.h"

typedef void (*invoke_t)();

class ICMainContext {
public:
    enum {None, Halo1, Halo2, Halo3, Halo3ODST, HaloReach, Halo4,};

    virtual void render(int render_flag = None) = 0;

};

extern ICMainContext* g_pMainContext;
inline ICMainContext* MainContext() {return g_pMainContext;}

class ICContext {
public:
    virtual void render() = 0;
};


