#include "CGameEngine.h"

CGameEngine** g_ppGameEngine;

bool CGameEngine::Initialize(CGameEngine** ppGameEngine) {
    g_ppGameEngine = ppGameEngine;
    return true;
}
