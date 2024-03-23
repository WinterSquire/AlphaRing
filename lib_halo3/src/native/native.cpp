#include "native.h"

static ThreadLocalStorage tls;

bool Native::Init(__int64 hModule) {
    tls.update(hModule);


    return false;
}

void Native::Shutdown() {

}

const ThreadLocalStorage &Native::getTLS() { return tls; }
