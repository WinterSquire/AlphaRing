#include "native.h"

#include "../base/enum.h"
#include "../objects/object_manager.h"

static ThreadLocalStorage tls;

bool Native::Init(__int64 hModule) {
    tls.update(hModule);

    object_manager.setRoot((__int64)tls.ptr(TLS_OBJECT));

    return false;
}

void Native::Shutdown() {

}

const ThreadLocalStorage &Native::getTLS() { return tls; }
