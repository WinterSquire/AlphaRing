#include "map.h"

#include <cstring>

class CMap : public ICMap {
public:
    void setMapInfo(Info *info) override;
    Info* getMapInfo() override;

private:
    Info m_info;

};

static CMap map;
ICMap* g_pICMap = &map;

void CMap::setMapInfo(ICMap::Info *info) {
    if (info == nullptr) memset(&m_info, 0, sizeof(Info));
    else memcpy(&m_info, info, sizeof(Info));
}

ICMap::Info* CMap::getMapInfo() {
    return &m_info;
}
