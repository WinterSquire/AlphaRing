#pragma once

#include <Windows.h>
#include <Xinput.h>

namespace AlphaRing {
    namespace Input {
        bool Init();
        bool Shutdown();
        bool Update();
        bool GetXInputGetState(DWORD dwUserIndex, XINPUT_STATE* pState);
        void SetState(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration);
    };
}