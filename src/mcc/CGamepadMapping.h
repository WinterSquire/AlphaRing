#pragma once

#include <array>

struct CGamepadMapping {
    enum eButton : __int8 {
        LeftTrigger, RightTrigger,
        DpadUp, DpadDown, DpadLeft, DpadRight,
        Start, Back,
        LeftThumb, RightThumb,
        LeftShoulder, RightShoulder,
        A, B, X, Y
    };

    eButton actions[66];

    void ImGuiContext();

    static const std::array<const char*, 16>* ButtonNames();
    static const std::array<const char*, 66>* ActionNames();
};