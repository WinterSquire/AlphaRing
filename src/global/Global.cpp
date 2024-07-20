#include "Global.h"

#include <cstdio>
#include <guiddef.h>
#include <combaseapi.h>

namespace AlphaRing::Global {
    ImplGlobal(Global);

    namespace Halo3 {
        ImplGlobal(Physics);
        ImplGlobal(Render);
    }

    namespace MCC {
        ImplGlobal(Profile);
    }
}

AlphaRing::Global::MCC::Profile_t::Profile_t() {
    __int64 guid[2];
    const int controller_map[4] {3, 0, 1, 2};
    memset(this, 0, sizeof(Profile_t));

    player_count = 1;
    b_player0_use_km = true;

    CoCreateGuid((GUID*)guid);
    auto id = guid[0] ^ guid[1];

    for (int i = 0; i < 4; i++) {
        profiles[i].controller_index = controller_map[i];
        profiles[i].xuid = 0;
        profiles[i].id = id + i;
        swprintf(profiles[i].name, L"Player %d", i + 1);
    }
}
