#include "module_watcher.h"

void ModuleLoad(ModuleInfo *info) {
    if (info->errorCode == 0) {
        LOG_INFO("Module {0}: Loaded At: {1:x}", ModuleInfo::cTitle[info->title], info->hModule);
        if (info->title == ModuleInfo::Halo3) {

        }
    } else {
        LOG_INFO("Module {0}: Loaded Error: {1}", ModuleInfo::cTitle[info->title], info->errorCode);
    }
}

void ModuleUnload(ModuleInfo *info) {
    LOG_INFO("Module {0}: Is about to unload", ModuleInfo::cTitle[info->title]);
}