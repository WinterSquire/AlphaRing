#include "tag_files.h"

#include "../native/native.h"

class CTagFiles : public ICTagFiles {
public:
    tag_names_t* getTagName() override;

    static CTagFiles s_instance;
};

CTagFiles CTagFiles::s_instance;
ICTagFiles* g_pHalo3ICTagFiles = &CTagFiles::s_instance;

tag_names_t* CTagFiles::getTagName() {
    return *(tag_names_t**)(NativeHalo3()->NativeInfo()->getModuleAddress() + OFFSET_HALO3_PV_TAG_NAMES);
}
