#include "common.h"

#include "../native/native.h"
#include "../render/render.h"

namespace ImmediateGUI {extern void SetStateWireframe(); extern void SetState(void *ptr);}
namespace Halo3::Entry::Draw { void Prologue(int type); void Epilogue(int type); }

void Halo3::Entry::Draw::Prologue(int type) {
    auto flag = Render()->getWireframe();
    if ((flag->model && flag->structure) || (flag->model && type == 2) || (flag->structure && type == 1)) {
        ImmediateGUI::SetStateWireframe();
    } else if (flag->model && !flag->structure && type == 1) {
        ImmediateGUI::SetState(*(void**)(NativeInfo()->getModuleAddress() + 0x46BA948));
    }
}

void Halo3::Entry::Draw::Epilogue(int type) {
}
