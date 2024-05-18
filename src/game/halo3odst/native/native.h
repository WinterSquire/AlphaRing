#pragma once

#include "base.h"
#include "game/ICNative.h"

#include "offset_halo3odst.h"

#include "../game/players.h"

typedef unsigned int INDEX;

class CHalo3ODSTNative : public ICNative {
public:
    class ICNativeFunc {
    public:
        // Main Thread
        // Don't use these functions directly in Render Thread!
        INDEX local_player_add(const wchar_t *name, const wchar_t *id);

        CHalo3ODSTNative* m_native;
    };

    class ICPlayers {
    public:
        inline entity_manager_t<player_info_t>* PlayerManager() { return (entity_manager_t<player_info_t>*) m_native->NativeInfo()->getEntryAddress(OFFSET_HALO3ODST_V_ENTRY_PLAYERS); }

        CHalo3ODSTNative* m_native;
    };

    inline ICNativeFunc* NativeFunc() {return &m_nativeFunc;}
    inline CNativeInfo *NativeInfo() override {return &m_nativeInfo;};
    inline ICPlayers* Players() {return &m_players;}

private:
    CNativeInfo m_nativeInfo;
    ICNativeFunc m_nativeFunc {this};
    ICPlayers m_players {this};
};

extern CHalo3ODSTNative g_pCHalo3ODST;
inline CHalo3ODSTNative* NativeHalo3ODST() {return &g_pCHalo3ODST;}
