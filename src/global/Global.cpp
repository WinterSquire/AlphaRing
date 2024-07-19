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
        "Switch Grenades",
        "Action",
        "Reload Right Weapon",
        "Change Weapon",
        "Melee",
        "Toggle Flashlight",
        "Throw Grenade",
        "Use Right Weapon",
        "Crouch",
        "Player Zoom",
        nullptr,
        nullptr,
        "Swap/Reload Left Weapon",
        nullptr,
        "Banshee Bomb",
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        "Multiplayer Scoreboard",
        "Vehicle Function 2",
        "Vehicle Function 3",
        "Use Equipment",
        "Vehicle Function 1",
        "Editor Ascend",
        "Editor Descend",
        "Drop/Pickup",
        "Thrust",
        "Precision Mode",
        "Delete",
        "Object Options",
        "Tools",
        "Play/Edit",
        "Editor Zoom",
        "Rotate",
        "TOGGLE PANEL",
        "TOGGLE INTERFACE",
        "TOGGLE FIRST/THIRD PERSON",
        "CAMERA RESET",
        "JUMP FORWARD",
        "JUMP BACK",
        "PAUSE/RESUME PLAYBACK",
        "FAST FORWARD",
        "TOGGLE FREECAM",
        "BOOST",
        "THEATER PANNING",
        "THEATER ASCEND",
        "THEATER DESCEND",
        "Use Left Weapon",
        "Theater Zoom",
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
        "Vehicle Ascend",
        "Vehicle Descend",
        "Select Previous Grenades",
        "Select Next Grenades",
};

const char **AlphaRing::Global::MCC::Profile_t::get_button_names() {return button_name;}
const char **AlphaRing::Global::MCC::Profile_t::get_action_names() {return action_name;}
