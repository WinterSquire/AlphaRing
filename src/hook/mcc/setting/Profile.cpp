#include "Profile.h"

#include <objbase.h>

profile_setting g_profile_setting;

profile_setting::profile_setting() {
    __int64 guid[2];
    b_override = false;
    b_override_player0 = false;
    player_count = 1;

    for (auto & profile : profiles) {
        CoCreateGuid((GUID*)guid);
        profile.id = guid[0] ^ guid[1];
        profile.name[0] = 0;
    }
}
