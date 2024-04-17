#ifndef MCC_MODULE_WATCHER_H
#define MCC_MODULE_WATCHER_H

#include "module_definition.h"
#include "../../../core/ISystem.h"

class ICModuleWatcher : public ISystem {
public:
    typedef void(*invoke_t)();

    void setModuleEventInvoke(ModuleInfo::eTitle title, invoke_t func);
};

extern ICModuleWatcher* g_pModuleWatcher;

inline ICModuleWatcher* ModuleWatcher() {return g_pModuleWatcher;}

#endif //MCC_MODULE_WATCHER_H
