#include "../native.h"
#include "common.h"


// todo: Scheduler
namespace HaloReach::Entry::Engine {
    void Prologue() {
        LOG_INFO("Engine Prologue");
        // open access to main thread resources
        // main thread resources will be copied to the render thread
        NativeHaloReach()->NativeInfo()->update((__int64) GetModuleHandleA("haloreach.dll"));
    }
    void Epilogue() {
        LOG_INFO("Engine Epilogue");
    }
}