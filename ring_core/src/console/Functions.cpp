#include "Functions.h"

#include "Function.h"
#include "Common.h"


void CC_NoClip(const Arg& arg) {
    CPrint("NoClip On\n");
}

static Function fnNoClip(CC_NoClip, "noclip", "change player physics");
