#include "CGamepadMapping.h"

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

const std::array<const char *, 16>* CGamepadMapping::ButtonNames() {return &button_names;}

const std::array<const char *, 66>* CGamepadMapping::ActionNames() {return &action_names;}

#include <imgui.h>
#include <cstdio>

void CGamepadMapping::ImGuiContext() {
    char buffer[10];

    for (int i = 0; i < action_names.size(); ++i) {
        auto name = action_names.at(i);
        if (name == nullptr) {
            sprintf(buffer, "Button %d", i);
            name = buffer;
        }

        ImGui::PushItemWidth(200);
        int value = actions[i];
        if (ImGui::Combo(name, &value, button_names.data(), button_names.size()))
            actions[i] = static_cast<CGamepadMapping::eButton>(value);
        ImGui::PopItemWidth();
    }
}
