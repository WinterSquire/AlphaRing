#include "ExternalConsole.h"

#include <cstdio>
#include <Windows.h>

bool ExternalConsole::Init() {
    if (AllocConsole() == false) return false;

    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    return true;
}

void ExternalConsole::Shutdown() {
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    FreeConsole();
}
