#pragma once

#include <d3d11.h>
#include "common.h"

#include "CGameGlobal.h"

struct CGameManager;

struct CGameEngine {
    enum eEventType {
        EventPause = 0,
        EventResume = 1,
        EventExit = 2,
        EventLoadCheckpoint = 3,
        EventRestart = 4,
        EventLoadSetting = 5,
        EventNewRound = 12,
        EventTeamChange = 18,
        EventReloadSetting = 23,
    };

    struct Item {
        struct Data {__int64 data[2];};
        struct _SLIST_ENTRY *Next;
        eEventType eventType;
        int one;
        Data data;
    };

    struct FunctionTable {
        void (__fastcall* free)(CGameEngine* self);
        __int64 (__fastcall* render_init)(CGameEngine* self, ID3D11Device* pDevice, ID3D11DeviceContext* pContext, IDXGISwapChain* pSwapchain, void* un);
        HANDLE (__fastcall* game_start)(CGameEngine* self, CGameManager* pGameManager, CGameGlobal::GameData *pGameData);
        PSLIST_ENTRY (__fastcall* set_event)(CGameEngine* self, int event_type, Item::Data *data);
        void* nop1[5];
        PSLIST_ENTRY (__fastcall* execute_command)(CGameEngine* self, const char *command);
        void* nop2;
    };

    FunctionTable* table;

    static bool Initialize(CGameEngine** ppGameEngine);

    inline void pause(bool value) {table->set_event(this, value ? EventPause : EventResume, nullptr);}
    inline void load_checkpoint() {table->set_event(this, EventLoadCheckpoint, nullptr);}
    inline void new_round() {table->set_event(this, EventNewRound, nullptr);}
    inline void restart() {table->set_event(this, EventRestart, nullptr);}
    inline void exit() {table->set_event(this, EventExit, nullptr);}
    inline void reload_setting() {table->set_event(this, EventReloadSetting, nullptr);}
    inline void load_setting() {table->set_event(this, EventLoadSetting, nullptr);}

    inline void change_team(__int64 xuid, int team) {
        Item::Data data = {xuid, team};
        table->set_event(this, EventTeamChange, &data);
    }

    inline void execute_command(const char* command, ...) {
        char buffer[1024 * 10];
        va_list args;
        va_start(args, command);
        vsprintf_s(buffer, command, args);
        va_end(args);
        table->execute_command(this, buffer);
    }
};

extern CGameEngine** g_ppGameEngine;
inline CGameEngine* GameEngine() {return *g_ppGameEngine;}

#define ExecuteScript(...) GameEngine()->execute_command("HS: " __VA_ARGS__)

#pragma region Halo3

struct CGameEngineH3 : CGameEngine {
    int count;
    float game_speed; // readonly?
    char buffer[0x10];
    Item items[31];
    SLIST_HEADER header[0x5]; // 0x400
    bool fine; // 0x450
    char padding[0x9];
};

static_assert((sizeof(CGameEngineH3) == 0x460));

#pragma endregion