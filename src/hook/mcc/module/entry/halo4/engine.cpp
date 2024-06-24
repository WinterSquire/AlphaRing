#include "halo4.h"

#include "common.h"

// todo: Scheduler
namespace Halo4::Entry::Engine {
    void Prologue() {
        LOG_INFO("Engine Prologue");
        // open access to main thread resources
        // main thread resources will be copied to the render thread
        Halo4::Native::s_nativeInfo.update("halo4.dll");
    }

    void Epilogue() {
        LOG_INFO("Engine Epilogue");
    }

    Halo4Entry(entry, OFFSET_HALO4_PF_ENGINE, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}