#include "Profile.h"

#include <objbase.h>
#include <string>

profile_setting g_profile_setting;

profile_setting::profile_setting() {
    __int64 guid[2];
    b_override = false;
    b_override_player0 = false;
    player_count = 1;

    CoCreateGuid((GUID*)guid);
    auto id =guid[0] ^ guid[1];

    for (int i = 0; i < 4; i++) {
        profiles[i].id = id + i;
        wprintf(profiles[i].name, L"Player %d", i + 1);
    }
}
