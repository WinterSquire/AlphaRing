#include "native_func.h"

#include "native_info.h"

class CNativeFunc : public ICNativeFunc {
public:
    bool player_push_message(__int16 player_index, const wchar_t *msg, int type) override;
    __int64 player_possess(INDEX player_index, INDEX target) override;
};

static CNativeFunc native_func;
ICNativeFunc* g_pICNativeFunc = &native_func;

bool CNativeFunc::player_push_message(__int16 player_index, const wchar_t *msg, int type) {
    typedef void (__fastcall* func_t)(__int64 a1, const wchar_t *a2, int a3);
    static const int OFFSET = 0x2D4884;

    if (player_index < 0 || player_index > 3) return false;
    if (NativeInfo()->getModuleAddress() == 0) return false;
    if (NativeInfo()->getEntryAddress(30) == 0) return false;

    auto p1 = NativeInfo()->getEntryAddress(30) + 0x1F8Ci64 + 0x28C8i64 * player_index;

    ((func_t)(NativeInfo()->getModuleAddress() + OFFSET))(p1, msg, type);

    return true;
}

__int64 CNativeFunc::player_possess(INDEX player_index, INDEX target) {
    typedef __int64 (__fastcall* func_t) (INDEX player_index, INDEX target);
    static const int OFFSET = 0xE33FC;

    if (player_index < 0) return false;
    if (NativeInfo()->getModuleAddress() == 0) return false;

    return ((func_t)(NativeInfo()->getModuleAddress() + OFFSET))(player_index, target);
}
