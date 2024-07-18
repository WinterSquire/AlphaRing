#include "CGameEngine.h"

CGameEngine** g_ppGameEngine;

void CGameEngine::Initialize(CGameEngine** ppGameEngine) {
    g_ppGameEngine = ppGameEngine;
}
