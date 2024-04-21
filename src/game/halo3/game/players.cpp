#include "players.h"

#include "../native/native.h"

class CPlayers : public ICPlayers {
public:
    player_info_t *getPlayerInfo(int index) override;
    player_action_t *getPlayerAction() override;
};

static CPlayers players;
ICPlayers* g_pICPlayers = &players;

player_info_t* CPlayers::getPlayerInfo(int index) {
    auto entry = NativeInfo()->getEntryAddress((int)eEntry::players);
    if (entry == 0) return nullptr;
    return *(player_info_t**)(entry + 0x48) + index;
}

player_action_t *CPlayers::getPlayerAction() {
    return (player_action_t*)NativeInfo()->getEntryAddress((int)eEntry::players_action);
}
