#include "./halo3.h"
#include "global/Global.h"

#include "render/Render.h"

namespace Halo3::Entry::Draw {
    Halo3Entry(entry_structure, OFFSET_HALO3_PF_DRAW_STRUCTURE, __int64, detour1, unsigned int a1, __int64 a2, __int64 a3, __int64 a4) {
        if (AlphaRing::Global::Halo3::Render()->structure) AlphaRing::Render::SetStateWireframe();
        return ((detour1_t)entry_structure.m_pOriginal)(a1, a2, a3, a4);
    }

    Halo3Entry(entry_model, OFFSET_HALO3_PF_DRAW_MODEL, __int64, detour2, __int64 p_render_model, __int64 a2) {
        if (AlphaRing::Global::Halo3::Render()->model) AlphaRing::Render::SetStateWireframe();
        return ((detour2_t)entry_model.m_pOriginal)(p_render_model, a2);
    }
}