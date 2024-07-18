#include "CPatch.h"
#include "CPatchSet.h"
#include <Windows.h>

bool CPatch::apply(void *dst, const void *src, size_t size, void *backup)  {
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

bool CPatch::setState(bool state) {
    if (m_enabled == state) return false;
    m_enabled = state;
    return apply();
}

bool CPatch::apply()  {
    auto dst = (void*)(m_parent->moduleAddress() + m_offset);
    if (m_enabled)
        return apply(dst, m_data.data(), m_data.size(), m_backup.data());
    else
        return apply(dst, m_backup.data(), m_backup.size());
}
