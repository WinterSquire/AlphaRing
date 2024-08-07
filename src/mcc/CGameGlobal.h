#pragma once

#include <windows.h>

struct CGameGlobal {
    enum eGame : int {
        Halo1 = 0,
        Halo2 = 1,
        Halo3 = 2,
        Halo4 = 3,
        GroundHog = 4,
        Halo3ODST = 5,
        HaloReach = 6,
    };

    enum eGameEvent : int {
        CreateGameEngine = 3,
        InitializeGraphics = 9,
        GameStart = 11,
        InGame = 12,
    };

    // 3F62910
    enum eGameState : int {
        GameExit = 1,
        EventExecute = 4,
    };

    char buffer[0xA8];
    struct GameData {
        char buffer[0x2BF30];
    } game_data;
    eGameState current_state;
    eGameState last_state;
    void* hModule;
    eGame current_game;
    eGame last_game; // 0x2BFEC

    eGameEvent* game_sate() {return (eGameEvent*)(this + 0x2C038);}
    LARGE_INTEGER* PerformanceCounter() {return (LARGE_INTEGER*)(this + 0x2C040);}
    bool is_paused() {return *(bool*)(this + 0x2C064);}
};

static_assert((sizeof(CGameGlobal::GameData) == 0x2BF30));

extern CGameGlobal** g_ppGameGlobal;
inline CGameGlobal* GameGlobal() {return *g_ppGameGlobal;}