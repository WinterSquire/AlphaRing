#include "Functions.h"

#include "Function.h"
#include "../common/Common.h"

void CC_NoClip(const Arg& arg) {
    Print("NoClip On\n");
}

static Function fnNoClip(CC_NoClip, "noclip", "change player physics");
