#pragma once

#include "base.h"
#include "game/ICNative.h"

#include "offset_halo4.h"

#include "../game/players.h"

typedef unsigned int INDEX;

class CHalo4Native : public ICNative {
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

extern CHalo4Native g_pCHalo4;
inline CHalo4Native* NativeHalo4() {return &g_pCHalo4;}
