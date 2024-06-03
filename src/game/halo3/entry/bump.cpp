#include "../native_halo3.h"

#include "halo3.h"

namespace Halo3::Entry::Bump {
    using units_t = Halo3::Native::Objects_t::units_t;

    static bool bSwap = false;
    static INDEX vTarget = NONE;
    static units_t* p_self = nullptr;
    static units_t* p_target = nullptr;

    void Prologue(INDEX self, INDEX target) {
        bSwap = false;
        if (!Halo3::Physics::BumpPossession()->enable || target == NONE || self == NONE) return;
        auto p_obj_s = Halo3::Native::Objects()->get(self)->address;
        auto p_obj_t = Halo3::Native::Objects()->get(target)->address;
        if (p_obj_s == nullptr || p_obj_t == nullptr) return;
        if (!p_obj_s->isUnit() || !p_obj_t->isUnit()) return;
        vTarget = target;
        p_self = (units_t*)p_obj_s; p_target = (units_t*)p_obj_t;
        if (p_self->bump_close >= 0) bSwap = true;
    }

    void Epilogue(INDEX self, INDEX target) {
        if (!bSwap) return; bSwap = false;
        if (p_self->bump_close >= 0 || p_self->player_index == NONE || p_target->player_index != NONE) return;
        Halo3::Native::Function::player_possess(p_self->player_index, vTarget);
        if (p_target->type == OBJECTTYPE_BIPED)
            p_target->bump_close = p_self->bump_close;
    }

    Halo3Entry(entry, OFFSET_HALO3_PF_BUMP, bool, detour, INDEX self, INDEX target) {
        Prologue(self, target);
        auto result = ((detour_t)entry.m_pOriginal)(self, target);
        Epilogue(self, target);
        return result;
    }
}
