#include "hook.h"

#include "detour_function.h"
#include "MinHook.h"
#include "function_table.h"

bool Bind(void* target, void* function, void** original) {
    if (!target || !original || !function) return false;

    return MH_CreateHook(target, function, original) != MH_OK || MH_EnableHook(target) != MH_OK;
}

bool Directx11Hook::Initialize() {
    functionTable.Initialize();
    MH_Initialize();

    //[8]   Present
    Bind((void*)functionTable.functions[8], Detour::Present, (void**)&functionTable.Present);

    //[13]  ResizeBuffers
    Bind((void*)functionTable.functions[13], Detour::ResizeBuffers, (void**)&functionTable.ResizeBuffers);

    return true;
}

bool Directx11Hook::Shutdown() {
    MH_DisableHook((void*)functionTable.functions[8]);

    MH_DisableHook((void*)functionTable.functions[13]);

    return true;
}
