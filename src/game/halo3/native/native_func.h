#ifndef ALPHA_RING_NATIVE_FUNC_H
#define ALPHA_RING_NATIVE_FUNC_H

#include "../base/base.h"

class ICNativeFunc {
public:
    // Main Thread
    // Don't use these functions directly in Render Thread!
    virtual bool player_push_message(__int16 player_index, const wchar_t* msg, int type = 2) = 0;
    virtual __int64 player_possess(INDEX player_index, INDEX target) = 0;
};

extern ICNativeFunc* g_pICNativeFunc;
inline ICNativeFunc* NativeFunc() { return g_pICNativeFunc; }


#endif //ALPHA_RING_NATIVE_FUNC_H
