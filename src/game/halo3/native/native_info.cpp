#include "native_info.h"

#include "os/ThreadLocalStorage.h"

static ThreadLocalStorage tls;

class CNativeInfo : public ICNativeInfo {
public:
    bool setModuleAddress(__int64 hModule) override;
    __int64 getModuleAddress() override;
    __int64 getEntryAddress(int index) override;

private:
    ThreadLocalStorage m_tls;

};

static CNativeInfo native_info;
ICNativeInfo* g_pICNativeInfo = &native_info;

bool CNativeInfo::setModuleAddress(__int64 hModule) {
    m_tls.update(hModule);

    return true;
}

__int64 CNativeInfo::getModuleAddress() {
    return m_tls.get_hModule();
}

__int64 CNativeInfo::getEntryAddress(int index) {
    return m_tls[index];
}
