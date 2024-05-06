#include "common.h"

#include "../native/native.h"

#include "render/Renderer.h"

namespace Halo3::Entry::Draw { void Prologue(int type); void Epilogue(int type); }

void Halo3::Entry::Draw::Prologue(int type) {
    auto flag = NativeHalo3()->Render()->getWireframe();
    if ((flag->model && flag->structure) || (flag->model && type == 2) || (flag->structure && type == 1)) {
        Renderer()->SetStateWireframe();
    } else if (flag->model && !flag->structure && type == 1) {
        Renderer()->SetState(*(void**)(NativeHalo3()->NativeInfo()->getModuleAddress() + 0x46BA948));
    }
}

void Halo3::Entry::Draw::Epilogue(int type) {
}
