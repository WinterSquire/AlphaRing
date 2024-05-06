#include "Module.h"

#include <functional>

#include <windows.h>

class CModule : public ICModule {
public:
    CModule(std::function<void (__int64)> fInit = nullptr) : m_fInit(fInit) {};

    void load_module(const module_info_t &info) override {
        load_module(&info);
    }

    void load_module(const module_info_t *p_info) override {
        wchar_t buffer[MAX_PATH];

        if (p_info == nullptr) return;

        memcpy(&m_info, p_info, sizeof(module_info_t));

        if (m_info.hModule == 0 || m_info.errorCode != 0) return;

        if (m_fInit) m_fInit(m_info.hModule);

        if (GetModuleFileNameW((HMODULE)m_info.hModule, buffer, MAX_PATH) <= 0) return;

        m_version = FileVersion(buffer);
    }

    void unload_module() override {
        memset(&m_info, 0, sizeof(module_info_t));
        m_version = 0;
    }

    FileVersion version() override {return m_version;}
    module_info_t info() override { return m_info;}

private:
    FileVersion m_version;
    module_info_t m_info;
    std::function<void (__int64)> m_fInit;

};

#include "./entry/halo3/halo3.h"

class CModules : public ICModules {
public:
    ICModule *get(eModule module) override {return m_modules + module;}

    CModule m_modules[8] {
            {nullptr},
            {nullptr},
            {[] (__int64 hModule) {Halo3EntrySet()->update(hModule);}},
    };

    static CModules m_instance;
};

CModules CModules::m_instance;
ICModules* g_pModules = &CModules::m_instance;