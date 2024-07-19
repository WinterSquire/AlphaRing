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

static const char* button_name[] = {
        "Left Trigger","Right Trigger",
        "Dpad Up","Dpad Down","Dpad Left","Dpad Right",
        "Start","Back",
        "Left Thumb","Right Thumb",
        "Left Shoulder","Right Shoulder",
        "A","B","X","Y"
};

static const char* action_name[] = {
        "Jump",
        nullptr,
        "Action/Reload",
        nullptr,
        "Change Weapon",
        "Melee",
        nullptr,
        "Throw Grenade",
        "Use Right Weapon",
        "Crouch",
        "Player Zoom",
        nullptr,
        nullptr,
        "Swap Left Weapon",
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        "Multiplayer Scoreboard",
        nullptr,
        nullptr,
        "Use Equipment",
        nullptr,
        "Fly Up",
        "Fly Down",
        "Drop/Pickup",
        "Thrust",
        "Precision Mode",
        "Delete",
        "Object Options",
        "Tools",
        "Play/Edit",
        "Editor Zoom",
        "Rotate",
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        "Toggle Rotation Axes",
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
};

const char **AlphaRing::Global::MCC::Profile_t::get_button_names() {return button_name;}
const char **AlphaRing::Global::MCC::Profile_t::get_action_names() {return action_name;}
