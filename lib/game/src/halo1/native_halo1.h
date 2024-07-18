#pragma once

#include "base.h"
#include "../ICNative.h"

#include "halo1.h"

class CHalo1Native : public ICNative {
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

extern CHalo1Native g_pCHalo1;
inline CHalo1Native* NativeHalo1() {return &g_pCHalo1;}
