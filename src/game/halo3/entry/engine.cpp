#include "../native/native.h"
#include "common.h"

#include <windows.h>

namespace Halo3::Entry::Engine {
    void Prologue() {
        LOG_INFO("Engine Prologue");
        NativeInfo()->setModuleAddress((__int64)GetModuleHandleA("Halo3.dll"));
    }
    void Epilogue() {
        LOG_INFO("Engine Epilogue");
    }
}