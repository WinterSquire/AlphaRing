#pragma once

#include "imgui/main_context.h"

class CMCCContext : public ICContext {
public:
    void render() override;

    void context_patch();
    void context_splitscreen();
    void context_network();

    static CMCCContext instance;
};

extern ICContext* g_pMCCContext;
