#include "Interface.h"

#include "../hook/d3d11/imgui_impl.h"

#include "Context.h"

class CInterface : public ISystem {
public:
    eStatus initialize() override;
    eStatus shutdown() override;

    static CInterface s_instance;
};

CInterface CInterface::s_instance;
ISystem* g_pInterface = &CInterface::s_instance;

ISystem::eStatus CInterface::initialize() {

    ImmediateGUI::SetCallback(ContextEntry);

    LOG_INFO("Interface Initialized!");
    return SYS_OK;
}

ISystem::eStatus CInterface::shutdown() {
    return SYS_OK;
}

