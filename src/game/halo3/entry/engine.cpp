#include "../native/native.h"
#include "common.h"

#include <windows.h>

// todo: Scheduler

namespace Halo3::Entry::Engine {
    void Prologue() {
        LOG_INFO("Engine Prologue");
        NativeHalo3()->NativeInfo()->update((__int64) GetModuleHandleA("halo3.dll"));
    }
    void Epilogue() {
        LOG_INFO("Engine Epilogue");
    }
}