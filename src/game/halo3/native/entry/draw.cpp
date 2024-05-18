#include "../native.h"

#include "render/Renderer.h"

#include "halo3.h"

namespace Halo3::Entry::Draw {
    void Prologue(int type){
        auto flag = NativeHalo3()->Render()->getWireframe();
        if ((flag->model && flag->structure) || (flag->model && type == 2) || (flag->structure && type == 1)) {
            Renderer()->SetStateWireframe();
        } else if (flag->model && !flag->structure && type == 1) {
            Renderer()->SetState(*(void**)(NativeHalo3()->NativeInfo()->getModuleAddress() + 0x46BA948));
        }
    }

    void Epilogue(int type) {

    }

    Halo3Entry(entry_structure, OFFSET_HALO3_PF_DRAW_STRUCTURE, __int64, detour1, unsigned int a1, __int64 a2, __int64 a3, __int64 a4) {
        Prologue(1);
        auto result = ((detour1_t)entry_structure.m_pOriginal)(a1, a2, a3, a4);
        Epilogue(1);
        return result;
    }

    Halo3Entry(entry_model, OFFSET_HALO3_PF_DRAW_MODEL, __int64, detour2, __int64 p_render_model, __int64 a2) {
        Prologue(2);
        auto result = ((detour2_t)entry_model.m_pOriginal)(p_render_model, a2);
        Epilogue(2);
        return result;
    }
}
