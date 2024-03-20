#include "Hook.h"

#include "./asm/asm.h"
#include "Entry.h"
#include "MinHook.h"
#include "../system/Log.h"

static const __int64 OFFSET_SCRIPT = 0xEF2BF;

void func() {
    LOG_INFO("script call!");
}

Entry entry_script(OFFSET_SCRIPT, func, asm_hook_script_init, asm_hook_script_entry);

bool Hook::Init() {
    auto result = MH_Initialize();
    return result == MH_OK;
}

void Hook::Shutdown() {
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}

bool Hook::Check(__int64 hModule) {
    if (hModule == 0) return false;

    Entry::sethModule(hModule);

    for (auto entry: Entry::getAllEntries()) {
        entry->check();
    }

    return true;
}
