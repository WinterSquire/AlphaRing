#include "../native.h"
#include "common.h"


// todo: Scheduler
namespace Halo3ODST::Entry::Engine {
    void Prologue() {
        LOG_INFO("Engine Prologue");
        // open access to main thread resources
        // main thread resources will be copied to the render thread
        NativeHalo3ODST()->NativeInfo()->update((__int64) GetModuleHandleA("Halo3ODST.dll"));
    }
    void Epilogue() {
        LOG_INFO("Engine Epilogue");
    }
}