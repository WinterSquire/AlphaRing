#include "CGameEngine.h"

#include "common.h"

CGameEngine** g_ppGameEngine;

bool CGameEngine::Initialize(CGameEngine** ppGameEngine) {
    g_ppGameEngine = ppGameEngine;
    return true;
}
