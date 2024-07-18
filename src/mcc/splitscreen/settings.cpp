#include "settings.h"

#include <cstdio>
#include <guiddef.h>
#include <combaseapi.h>

TSettings g_settings;

TSettings::profile_setting::profile_setting()  {
    __int64 guid[2];
    b_override = false;
    b_override_player0 = false;
    b_use_player0_profile = false;
    player_count = 1;

    CoCreateGuid((GUID*)guid);
    auto id =guid[0] ^ guid[1];

    for (int i = 0; i < 4; i++) {
        profiles[i].xuid = 0;
        profiles[i].id = id + i;
        swprintf(profiles[i].name, L"Player %d", i + 1);
    }
}
