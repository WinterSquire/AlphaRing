#include "halo3odst.h"

#include "common.h"

// todo: Scheduler

namespace Halo3ODST::Entry::Engine {
    void Prologue() {
        LOG_INFO("Engine Prologue");
        // open access to main thread resources
        // main thread resources will be copied to the render thread
        Halo3ODST::Native::s_nativeInfo.update("halo3odst.dll");
    }

    void Epilogue() {
        LOG_INFO("Engine Epilogue");
    }

    Halo3ODSTEntry(entry, OFFSET_HALO3ODST_PF_ENGINE, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
