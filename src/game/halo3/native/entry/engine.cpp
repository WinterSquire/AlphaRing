#include "../native.h"
#include "common.h"

#include <Windows.h>

// todo: Scheduler

namespace Halo3::Entry::Engine {
    void Prologue() {
        LOG_INFO("Engine Prologue");
        // open access to main thread resources
        // main thread resources will be copied to the render thread
        NativeHalo3()->NativeInfo()->update((__int64) GetModuleHandleA("halo3.dll"));
    }
    void Epilogue() {
        LOG_INFO("Engine Epilogue");
    }
}