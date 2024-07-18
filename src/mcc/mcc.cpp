#include "mcc.h"

#include "mcc/module/Module.h"
#include "mcc/network/Network.h"
#include "mcc/splitscreen/Splitscreen.h"

struct TModule {
    char buffer[0x2BFE0];
    HMODULE hModule;
    int last_index;
    int current_index;
};

 void __fastcall sub_1401EB674(TModule* module, int index);

namespace MCC {
    bool Initialize() {
        if (!Module::Initialize())
            return false;

        if (!Splitscreen::Initialize())
            return false;

        if (!Network::Initialize())
            return false;

        return true;
    }
}
