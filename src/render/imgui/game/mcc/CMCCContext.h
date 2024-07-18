#pragma once

#include "render/imgui/ICContext.h"

class CMCCContext : public ICContext {
public:
    void render() override;

    static CMCCContext instance;
};

extern ICContext* g_pMCCContext;
