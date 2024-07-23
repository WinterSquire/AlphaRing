#include "halo3.h"

namespace Halo3::Entry::Engine {
    Halo3Entry(entry, OFFSET_HALO3_PF_ENGINE, void, detour) {
        // open access to main thread resources
        // main thread resources will be copied to the render thread
        Halo3::Native::s_nativeInfo.update("halo3.dll");
        ((detour_t)entry.m_pOriginal)();
    }
}