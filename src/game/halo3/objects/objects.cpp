#include "objects.h"

#include "../native/native.h"

bool Objects_t::IsUnit() {
    return type & (BIPED|GIANT|VEHICLE);
}

__int16 Objects_t::size() {
    return 0;
//    return *(__int16*)(*(__int64*)(NativeInfo::getTLS().get_hModule() + 0x810D20 + type * 8) + 0x6);
}
