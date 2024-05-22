#pragma once

#include <Windows.h>
#include <Xinput.h>

namespace AlphaRing {
    namespace Input {
        bool Init();
        bool GetXInputGetState(DWORD dwUserIndex, XINPUT_STATE* pState);
    };
}