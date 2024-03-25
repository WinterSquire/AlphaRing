#include "module_definition.h"

#include <filesystem>

ModuleDefinition::ModuleDefinition(const char *moduleName, std::initializer_list<const char*> funcs) {
    // Get System Directory
    wchar_t systemPath[MAX_PATH];
    if (!GetSystemDirectoryW(systemPath, MAX_PATH)) {
        MessageBoxA(0, "Unable to load system directory", "Error", 0);

        ExitProcess(0);
    }

    // Load DLL
    std::filesystem::path path(systemPath);
    path.append(moduleName);
    if ((m_hModule = LoadLibraryW(path.c_str())) == nullptr) {
        MessageBoxA(0, (std::string("Unable to load dll: ") + moduleName).c_str(), "Error", 0);

        ExitProcess(0);
    }

    // Find Function
    void *func_ptr;
    for (auto func: funcs) {
        if ((func_ptr = GetProcAddress(m_hModule, func)) == nullptr) {
            MessageBoxA(0, (std::string("Unable to load function: ") + func).c_str(), "Error", 0);

            ExitProcess(0);
        }

        m_funcs.push_back(func_ptr);
    }
}

void *ModuleDefinition::GetFunc(int index) {
    if (index < 0 || index > m_funcs.size()) return nullptr;
    return m_funcs[index];
}
