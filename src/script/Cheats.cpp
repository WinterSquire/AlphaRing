#include "Cheats.h"

#include "Function.h"

#include "../core/Log.h"

void CC_NoClip(const Arg& arg) {
    LOG_INFO("NoClip On\n");
}

static Function fnNoClip(CC_NoClip, "noclip", "change player physics");
