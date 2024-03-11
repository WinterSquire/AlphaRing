#include "Log.h"

void Log::Init() {
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
}

void Log::Shutdown() {
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    FreeConsole();
}
