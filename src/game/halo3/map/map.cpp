#include "map.h"

#include <mutex>
#include <cstring>

static std::mutex mutex;

class CMap : public ICMap {
public:
    void setMapInfo(Info *info) override;
    const LockedResource<Info> getMapInfo() override;

private:
    Info m_info;
};

static CMap map;
ICMap* g_pICMap = &map;

void CMap::setMapInfo(ICMap::Info *info) {
    std::lock_guard<std::mutex> lock(mutex);
    if (info == nullptr) memset(&m_info, 0, sizeof(Info));
    else memcpy(&m_info, info, sizeof(Info));
}

const LockedResource<ICMap::Info> CMap::getMapInfo() {
    return {mutex, m_info};
}
