#include "module_watcher.h"

#include <mutex>

namespace Halo3Hook { extern bool Init(__int64 hModule); }

static ModuleInfo modules[7];
static std::mutex mutex;

class CModuleWatcher : public ICModuleWatcher {
public:
    eStatus initialize() override {return SYS_OK;}
    eStatus shutdown() override {return SYS_OK;}
    ModuleInfo getModuleStatus(eTitle title) const override {std::lock_guard<std::mutex> lock(mutex); return modules[title];}
};

static CModuleWatcher moduleWatcher;
ICModuleWatcher* g_pModuleWatcher = &moduleWatcher;

void ModuleLoad(void* info) {
    wchar_t buffer[MAX_PATH];
    std::lock_guard<std::mutex> lock(mutex);
    auto module_info = (module_info_t*) info;
    auto& module = modules[module_info->title];
    memcpy(&module.info, module_info, sizeof(module_info_t));

    if (module_info->errorCode == 0) {
        if (GetModuleFileNameW((HMODULE)module_info->hModule, buffer, MAX_PATH) > 0) {
            module.version = FileVersion(buffer);
        }
        LOG_DEBUG("CModule {0}: Loaded At: {1:x}", module.info.title, module.info.hModule);

        if (module.info.title == Halo3) {
            Halo3Hook::Init(module.info.hModule);
        }
    } else {
        LOG_DEBUG("CModule {0}: Loaded Error: {1}", module.info.title, module.info.errorCode);
    }
}

void ModuleUnload(void* info) {
    std::lock_guard<std::mutex> lock(mutex);
    auto module_info = (module_info_t*) info;
    auto& module = modules[module_info->title];
    memcpy(&module.info, module_info, sizeof(module_info_t));

    LOG_DEBUG("CModule {0}: Is about to unload", cTitle[module.info.title]);
}

