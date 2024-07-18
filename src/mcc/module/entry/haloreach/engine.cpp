#include "haloreach.h"

#include "common.h"

// todo: Scheduler
namespace HaloReach::Entry::Engine {
    void Prologue() {
        LOG_INFO("Engine Prologue");
        // open access to main thread resources
        // main thread resources will be copied to the render thread
        HaloReach::Native::s_nativeInfo.update("haloreach.dll");
    }
    void Epilogue() {
        LOG_INFO("Engine Epilogue");
    }

    HaloReachEntry(entry, OFFSET_HALOREACH_PF_ENGINE, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
