#include "../native.h"
#include "common.h"


// todo: Scheduler
namespace GroundHog::Entry::Engine {
    void Prologue() {
        LOG_INFO("Engine Prologue");
        // open access to main thread resources
        // main thread resources will be copied to the render thread
        NativeGroundHog()->NativeInfo()->update((__int64) GetModuleHandleA("groundhog.dll"));
    }
    void Epilogue() {
        LOG_INFO("Engine Epilogue");
    }
}