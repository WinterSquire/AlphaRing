#pragma once

#include "base.h"
#include "game/ICNative.h"

#include "offset_GroundHog.h"

#include "../game/players.h"

typedef unsigned int INDEX;

class CGroundHogNative : public ICNative {
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

extern CGroundHogNative g_pCGroundHog;
inline CGroundHogNative* NativeGroundHog() {return &g_pCGroundHog;}
