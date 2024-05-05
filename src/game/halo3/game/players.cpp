#include "players.h"

#include "../native/native.h"

class CPlayers : public ICPlayers {
public:
    player_action_t *getPlayerAction() override;

    entity_manager_t<player_info_t> *getPlayerManager() override;
};

static CPlayers players;
ICPlayers* g_pICPlayers = &players;

entity_manager_t<player_info_t> *CPlayers::getPlayerManager() {
    return (entity_manager_t<player_info_t>*)NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_PLAYERS);
}

player_action_t *CPlayers::getPlayerAction() {
    return (player_action_t*)NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_PLAYERS_ACTION);
}
