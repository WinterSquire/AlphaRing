#include "ExternalConsole.h"

#include <cstdio>

class CExternalConsole : public ISystem {
public:
    eStatus initialize() override;
    eStatus shutdown() override;

    static CExternalConsole s_instance;
};

CExternalConsole CExternalConsole::s_instance;
ISystem* g_pExternalConsole = &CExternalConsole::s_instance;

ISystem::eStatus CExternalConsole::initialize() {
    if (AllocConsole() == false) {
        LOG_ERROR("ExternalConsole Failed To Initialize!");
        return SYS_ERROR;
    }

    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);


    LOG_INFO("Version: {}", GAME_VERSION);

    return SYS_OK;
}

ISystem::eStatus CExternalConsole::shutdown() {
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    FreeConsole();
    return SYS_OK;
}
