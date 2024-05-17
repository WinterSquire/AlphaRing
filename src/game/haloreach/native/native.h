#pragma once

#include "base.h"
#include "game/ICNative.h"

#include "offset_haloreach.h"

#include "../game/players.h"
#include "../camera/camera.h"

typedef unsigned int INDEX;

class CHaloReachNative : public ICNative {
public:
    class ICNativeFunc {
    public:
        // Main Thread
        // Don't use these functions directly in Render Thread!
        INDEX local_player_add(const wchar_t *name, const wchar_t *id);
    };

    inline ICNativeFunc* NativeFunc() {return &m_nativeFunc;}
    inline CNativeInfo *NativeInfo() override {return &m_nativeInfo;};

private:
    ICNativeFunc m_nativeFunc;
    CNativeInfo m_nativeInfo;

};

extern CHaloReachNative g_pCHaloReach;
inline CHaloReachNative* NativeHaloReach() {return &g_pCHaloReach;}
