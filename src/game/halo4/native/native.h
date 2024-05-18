#pragma once

#include "base.h"
#include "game/ICNative.h"

#include "offset_halo4.h"

#include "../game/players.h"

typedef unsigned int INDEX;

class CHalo4Native : public ICNative {
public:
    template<typename T>
    struct entity_manager_t {
        char un[0x48];
        __int64 m_size;     // 0x48
    };

    class CPlayers {
    public:
        inline entity_manager_t<player_info_t>* PlayerManager() {return (entity_manager_t<player_info_t>*) m_native->NativeInfo()->getEntryAddress(OFFSET_HALO4_V_ENTRY_PLAYERS);}
        CHalo4Native* m_native;
    };

    class CNativeFunc {
    public:
        // Main Thread
        // Don't use these functions directly in Render Thread!
        INDEX local_player_add(const wchar_t *name, const wchar_t *id);
    };

    inline CNativeFunc* NativeFunc() {return &m_nativeFunc;}
    inline CPlayers* Players() {return &m_players;}
    inline CNativeInfo* NativeInfo() override {return &m_nativeInfo;};

private:
    CNativeFunc m_nativeFunc;
    CNativeInfo m_nativeInfo;
    CPlayers m_players {this};

};

extern CHalo4Native g_pCHalo4;
inline CHalo4Native* NativeHalo4() {return &g_pCHalo4;}
