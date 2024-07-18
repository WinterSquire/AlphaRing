#pragma once

#include "CModule.h"
#include "./utils.h"

namespace MCC::Module {
    bool Initialize();

    bool IsWS();

    FileVersion Version();

    __int64 GetBaseAddress();

    bool ReloadPatch(const char *xml_path = "./alpha_ring/patch.xml");

    void ImGuiContext();
}
