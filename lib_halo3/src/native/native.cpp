#include "native.h"

static __int64 s_hModule;
static Module s_module;
static __int64 s_teb;

bool Native::sethModule(__int64 hModule) {
    s_hModule = hModule;
    return true;
}

__int64 Native::gethModule() {
    return s_hModule;
}

bool Native::setModule(Module &&module) {
    s_module = module;
    return true;
}

const Module &Native::getModule() {
    return s_module;
}

bool Native::setTEB(__int64 teb) {
    s_teb = teb;
    return true;
}

__int64 Native::getTEB() {
    return s_teb;
}
