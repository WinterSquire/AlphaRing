#include "players.h"

#include "../native/native.h"

class CPlayers : public ICPlayers {
public:
    PlayerInfo *getPlayer(int index) override;
};

static CPlayers players;
ICPlayers* g_pICPlayers = &players;

ICPlayers::PlayerInfo *CPlayers::getPlayer(int index) {
    auto entry = NativeInfo()->getEntryAddress((int)eEntry::players);
    if (entry == 0) return nullptr;
    return *(PlayerInfo**)(entry + 0x48) + index;
}
