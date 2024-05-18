#pragma once

#include "base.h"
#include "game/ICNative.h"

#include "offset_GroundHog.h"

#include "../game/players.h"

typedef unsigned int INDEX;

class CGroundHogNative : public ICNative {
public:
    template<typename T>
    struct entity_manager_t {
        char un[0x48];
        __int64 m_size;     // 0x48
    };

    class CPlayers {
    public:
        inline entity_manager_t<player_info_t>* PlayerManager() {return (entity_manager_t<player_info_t>*) m_native->NativeInfo()->getEntryAddress(OFFSET_GROUNDHOG_V_ENTRY_PLAYERS);}
        CGroundHogNative* m_native;
    };
    class ICNativeFunc {
    public:
        // Main Thread
        // Don't use these functions directly in Render Thread!
        INDEX local_player_add(const wchar_t *name, const wchar_t *id);
    };

    inline ICNativeFunc* NativeFunc() {return &m_nativeFunc;}
    inline CNativeInfo *NativeInfo() override {return &m_nativeInfo;};
    inline CPlayers* Players() {return &m_players;}

private:
    ICNativeFunc m_nativeFunc;
    CNativeInfo m_nativeInfo;
    CPlayers m_players {this};

};

extern CGroundHogNative g_pCGroundHog;
inline CGroundHogNative* NativeGroundHog() {return &g_pCGroundHog;}
