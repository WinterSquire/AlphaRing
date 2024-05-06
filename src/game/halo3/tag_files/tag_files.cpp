#include "tag_files.h"

#include "../native/native.h"

class CTagFiles : public ICTagFiles {
public:
    const char *getTagName(__int16 index) override;

    static CTagFiles s_instance;
};

CTagFiles CTagFiles::s_instance;
ICTagFiles* g_pHalo3ICTagFiles = &CTagFiles::s_instance;

const char *CTagFiles::getTagName(__int16 index) {
    if (index < 0 || index > 0x8000) return nullptr;
    return *((const char**)(*(__int64*)(NativeHalo3()->NativeInfo()->getModuleAddress() + 0xA48148) + 0x820000) + (__int16)index);
}
