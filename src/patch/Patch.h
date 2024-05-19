#ifndef ALPHA_RING_PATCH_H
#define ALPHA_RING_PATCH_H


#include <Windows.h>

class Patch {
public:
    inline static bool apply(void *dst, void *src, size_t size) {
        bool _flag = false;
        DWORD oldprotect;

        if (dst == nullptr || src == nullptr || size == 0) return _flag;

        if (VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect))
            memcpy(dst, src, size);
        VirtualProtect(dst, size, oldprotect, &oldprotect);
        return _flag;
    }
};


#endif //ALPHA_RING_PATCH_H
