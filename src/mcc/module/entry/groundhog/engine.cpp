#include "groundhog.h"

#include "common.h"

// todo: Scheduler
namespace GroundHog::Entry::Engine {
    void Prologue() {
        LOG_INFO("Engine Prologue");
        // open access to main thread resources
        // main thread resources will be copied to the render thread
        GroundHog::Native::s_nativeInfo.update("groundhog.dll");
    }

    void Epilogue() {
        LOG_INFO("Engine Epilogue");
    }

    GroundHogEntry(entry, OFFSET_GROUNDHOG_PF_ENGINE, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}