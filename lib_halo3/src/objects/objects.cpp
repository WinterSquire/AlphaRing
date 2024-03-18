#include "objects.h"

#include "../native/native.h"

bool Objects_t::IsUnit() {
    return type & (BIPED|GIANT|VEHICLE);
}

__int16 Objects_t::size() {
    return *(__int16*)(*(__int64*)(Native::gethModule() + 0x810D20 + type * 8) + 0x6);
}
