#include "../native.h"
#include "common.h"


// todo: Scheduler
namespace Halo4::Entry::Engine {
    void Prologue() {
        LOG_INFO("Engine Prologue");
        // open access to main thread resources
        // main thread resources will be copied to the render thread
        NativeHalo4()->NativeInfo()->update((__int64) GetModuleHandleA("halo4.dll"));
    }
    void Epilogue() {
        LOG_INFO("Engine Epilogue");
    }
}