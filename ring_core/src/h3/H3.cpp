#include "H3.h"

#include "lib_halo3.h"

#include <windows.h>

void H3::update() {
    Native::sethModule((long long int)GetModuleHandleA("halo3.dll"));
}