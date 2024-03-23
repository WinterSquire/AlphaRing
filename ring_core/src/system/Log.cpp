#include "Log.h"

bool Log::Init() {
    if (AllocConsole() == false) return false;

    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    return true;
}

void Log::Shutdown() {
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    FreeConsole();
}
