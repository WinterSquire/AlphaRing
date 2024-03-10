#ifndef ALPHA_RING_MODULE_DEFINITION_H
#define ALPHA_RING_MODULE_DEFINITION_H

#include <vector>
#include <windows.h>
#include <initializer_list>

class ModuleDefinition {
public:
    ModuleDefinition(const char *moduleName, std::initializer_list<const char*> funcs);

    void* GetFunc(int index);
private:
    HMODULE m_hModule;
    std::vector<void*> m_funcs;

};

#endif //ALPHA_RING_MODULE_DEFINITION_H
