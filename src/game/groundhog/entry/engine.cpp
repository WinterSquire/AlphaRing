#include "game/groundhog/native.h"
#include "common.h"

#include "groundhog.h"

// todo: Scheduler
namespace GroundHog::Entry::Engine {
    void Prologue() {
        LOG_INFO("Engine Prologue");
        // open access to main thread resources
        // main thread resources will be copied to the render thread
        GroundHog::Native::s_nativeInfo.update((__int64) GetModuleHandleA("groundhog.dll"));
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