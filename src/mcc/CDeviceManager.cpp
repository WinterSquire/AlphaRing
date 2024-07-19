#include "CDeviceManager.h"

CDeviceManager** g_ppDeviceManager;

bool CDeviceManager::Initialize(CDeviceManager** mng) {
    g_ppDeviceManager = mng;
    return true;
}
