#pragma once

#include <vector>
#include <Windows.h>
#include <initializer_list>

class ModuleDefinition {
public:
    ModuleDefinition(const char *moduleName, std::initializer_list<const char*> funcs);

    void* GetFunc(int index);
private:
    HMODULE m_hModule;
    std::vector<void*> m_funcs;

};
