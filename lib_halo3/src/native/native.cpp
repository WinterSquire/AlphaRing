#include "native.h"

static Module module;

bool Native::updateData(Module &&data) {
    module = data;
    return true;
}

const Module &Native::getModuleData() {
    return module;
}

__int64 Native::GetModuleHandle() {
    return 0;
}
