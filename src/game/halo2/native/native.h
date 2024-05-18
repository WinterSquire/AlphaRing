#pragma once

#include "base.h"
#include "game/ICNative.h"

#include "offset_Halo2.h"

class CHalo2Native : public ICNative {
public:
    class ICNativeFunc {
    public:
        INDEX local_player_add(const wchar_t *name, const wchar_t *id);
    };

    inline ICNativeFunc* NativeFunc() {return &m_nativeFunc;}
    inline CNativeInfo *NativeInfo() override {return &m_nativeInfo;};

private:
    ICNativeFunc m_nativeFunc;
    CNativeInfo m_nativeInfo;

};

extern CHalo2Native g_pCHalo2;
inline CHalo2Native* NativeHalo2() {return &g_pCHalo2;}
