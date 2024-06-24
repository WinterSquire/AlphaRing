#include "Patch.h"

#include <Windows.h>

bool Patch::apply(void *dst, const void *src, size_t size, void *backup) {
    bool result = false;
    DWORD oldprotect;

    if (dst == nullptr || src == nullptr || size == 0)
        return result;

    if (VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect)) {
        if (backup != nullptr)
            memcpy(backup, dst, size);
        memcpy(dst, src, size);
        result = true;
    }
    VirtualProtect(dst, size, oldprotect, &oldprotect);

    return result;
}
