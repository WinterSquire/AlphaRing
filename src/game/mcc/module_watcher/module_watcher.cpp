#include "module_watcher.h"

namespace Halo3Hook { extern bool Init(__int64 hModule); }

void ModuleLoad(ModuleInfo *info) {
    if (info->errorCode == 0) {
        LOG_DEBUG("Module {0}: Loaded At: {1:x}", ModuleInfo::cTitle[info->title], info->hModule);
        if (info->title == ModuleInfo::Halo3) {
            Halo3Hook::Init(info->hModule);
        }
    } else {
        LOG_DEBUG("Module {0}: Loaded Error: {1}", ModuleInfo::cTitle[info->title], info->errorCode);
    }
}

void ModuleUnload(ModuleInfo *info) {
    LOG_DEBUG("Module {0}: Is about to unload", ModuleInfo::cTitle[info->title]);
}