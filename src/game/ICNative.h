#ifndef ALPHA_RING_ICNATIVE_H
#define ALPHA_RING_ICNATIVE_H

#include "os/ThreadLocalStorage.h"

class CNativeInfo {
public:
    bool update(__int64 hModule) {return m_tls.update(hModule);}
    __int64 getModuleAddress() {return m_tls.m_hModule;}
    __int64 getEntryAddress(int index) {return m_tls[index];}

private:
    ThreadLocalStorage m_tls;

};

class ICNative {
public:
    virtual CNativeInfo* NativeInfo() = 0;

};



#endif //ALPHA_RING_ICNATIVE_H
