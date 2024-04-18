#include "native_func.h"

#include "native_info.h"

class CNativeFunc : public ICNativeFunc {
public:
    bool pushMsg(int player_index, const wchar_t *msg, int type) override;
    __int64 draw(__int64 drawType, unsigned int count, void *data, unsigned int size) override;

    __int64 draw_line(void *data, unsigned int line_count, unsigned int vertex_size) override;
};

static CNativeFunc native_func;
ICNativeFunc* g_pICNativeFunc = &native_func;

bool CNativeFunc::pushMsg(int player_index, const wchar_t *msg, int type) {
    typedef void (__fastcall* func_t)(__int64 a1, const wchar_t *a2, int a3);
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

__int64 CNativeFunc::draw_line(void *data, unsigned int line_count, unsigned int vertex_size) {
    typedef __int64 (__fastcall* preInit_t)(unsigned int a1, __int64 a2, unsigned int a3);
    typedef char (__fastcall* setType_t)(int a1);
    typedef char (*check_t)();
    __int64 result = -1;
    float v17[4] {1.0f, 1.0f, 1.0f, 1.0f};

    auto v1 = (unsigned int*)(NativeInfo()->getModuleAddress() + 0x967DB0);
    auto v2 = (unsigned int*)(NativeInfo()->getModuleAddress() + 0x8AB580);

    if (NativeInfo()->getModuleAddress() == 0) return false;

    if (((check_t)(NativeInfo()->getModuleAddress() + 0x28D734))() == false) return result;

    if ( (*v1 & 0xFFFFFFF3 | 4) != *v1 )
    {
        *v2 |= 1u;
        *v1 = *v1 & 0xFFFFFFF3 | 4;
    }

    ((setType_t)(NativeInfo()->getModuleAddress() + 0x277BE0))(2);

    ((preInit_t)(NativeInfo()->getModuleAddress() + 0x2AF0C8))(0x120000u, (__int64)v17, 0x10u);

    result = draw(1, line_count, data, vertex_size);

    if ( (*v1 & 0xFFFFFFF3 | 8) != *v1 )
    {
        *v2 |= 1u;
        *v1 = *v1 & 0xFFFFFFF3 | 8;
    }

    return result;
}
