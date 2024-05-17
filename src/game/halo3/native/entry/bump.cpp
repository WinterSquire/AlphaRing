#include "../native.h"

namespace Halo3::Entry::Bump {
    void Prologue(unsigned int self, unsigned int target);
    void Epilogue(unsigned int self, unsigned int target);
}

static bool bSwap = false;
static INDEX vTarget = NONE;
static units_t* p_self = nullptr;
static units_t* p_target = nullptr;

void Halo3::Entry::Bump::Prologue(unsigned int self, unsigned int target) {
    bSwap = false;
    if (!NativeHalo3()->Physics()->BumpPossessionSetting()->enable || target == NONE || self == NONE) return;
    auto p_obj_s = NativeHalo3()->Objects()->getObjectManager()->get(self)->address;
    auto p_obj_t = NativeHalo3()->Objects()->getObjectManager()->get(target)->address;
    if (p_obj_s == nullptr || p_obj_t == nullptr) return;
    if (!p_obj_s->isUnit() || !p_obj_t->isUnit()) return;
    vTarget = target;
    p_self = (units_t*)p_obj_s; p_target = (units_t*)p_obj_t;
    if (p_self->bump_close >= 0) bSwap = true;
}

void Halo3::Entry::Bump::Epilogue(unsigned int self, unsigned int target) {
    if (!bSwap) return; bSwap = false;
    if (p_self->bump_close >= 0 || p_self->player_index == NONE || p_target->player_index != NONE) return;
    NativeHalo3()->NativeFunc()->player_possess(p_self->player_index, vTarget);
    if (p_target->type == OBJECTTYPE_BIPED)
        p_target->bump_close = p_self->bump_close;
}