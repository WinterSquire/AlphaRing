#include "native_func.h"

#include "native_info.h"

class CNativeFunc : public ICNativeFunc {
public:
    bool pushMsg(int player_index, const char *msg, int type) override;
    __int64 draw(__int64 drawType, unsigned int count, void *data, unsigned int size) override;
};

static CNativeFunc native_func;
ICNativeFunc* g_pICNativeFunc = &native_func;

bool CNativeFunc::pushMsg(int player_index, const char *msg, int type) {
    typedef void (__fastcall* func_t)(__int64 a1, const char *a2, int a3);
    static const int OFFSET = 0x2D4884;

    if (!(player_index < 4)) return false;

    if (NativeInfo()->getModuleAddress() == 0) return false;

    if (NativeInfo()->getEntryAddress(30) == 0) return false;

    auto p1 = NativeInfo()->getEntryAddress(30) + 0x1F8Ci64 + 0x28C8i64 * player_index;

    ((func_t)(NativeInfo()->getModuleAddress() + OFFSET))(p1, msg, type);

    return true;
}

__int64 CNativeFunc::draw(__int64 drawType, unsigned int count, void *data, unsigned int size) {
    typedef __int64 (__fastcall* func_t)(__int64 drawType, unsigned int count, void *data, unsigned int size);
    static const int OFFSET = 0x2A2F04;

    if (NativeInfo()->getModuleAddress() == 0) return false;

    return ((func_t)(NativeInfo()->getModuleAddress() + OFFSET))(drawType, count, data, size);
}
