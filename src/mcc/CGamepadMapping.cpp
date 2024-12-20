#include "CGamepadMapping.h"
#include "CGameEngine.h"

static std::array<const char*, 16> button_names {
        "Left Trigger","Right Trigger",
        "Dpad Up","Dpad Down","Dpad Left","Dpad Right",
        "Start","Back",
        "Left Thumb","Right Thumb",
        "Left Shoulder","Right Shoulder",
        "A","B","X","Y"
};

static std::array<const char*, 66> action_names {
        "Jump",
        "Switch Grenades 1",
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
        "Sprint",
        "Banshee Bomb",
        "Player Move Forward", // H1A
        "Player Move Backward", // H1A
        "Player Move Left", // H1A
        "Player Move Right", // H1A
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
        "Duplicate",
        "Lock",
        "Reset",
        "Select Next Grenades 2",
        "Select Previous Grenades 2",
        "Special Action",
        "Open Loadouts Menu",
        "Toggle Display Waypoint Markers",
        "Toggle Display Waypoint Markers Alternative",
        "Push to Talk", // not sure
        "Vehicle Ascend",
        "Vehicle Descend",
        "Select Previous Grenades",
        "Select Next Grenades",
};

const std::array<const char *, 16>* CGamepadMapping::ButtonNames() {return &button_names;}

const std::array<const char *, 66>* CGamepadMapping::ActionNames() {return &action_names;}

#include <imgui.h>
#include <cstdio>

void CGamepadMapping::ImGuiContext() {
    char buffer[10];
    bool result = false;

    for (int i = 0; i < action_names.size(); ++i) {
        auto name = action_names.at(i);
        if (name == nullptr) {
            sprintf(buffer, "Button %d", i);
            name = buffer;
        }

        ImGui::PushItemWidth(200);
        int value = actions[i];
        if (ImGui::Combo(name, &value, button_names.data(), button_names.size())) {
            actions[i] = static_cast<CGamepadMapping::eButton>(value);
            result = true;
        }
        ImGui::PopItemWidth();
    }

    if (result) {
        auto p_engine = GameEngine();
        if (p_engine) p_engine->load_setting();
    }
}
