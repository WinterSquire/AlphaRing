#include "Input.h"

typedef DWORD (WINAPI* xinput_get_state_t)(_In_  DWORD dwUserIndex, _Out_ XINPUT_STATE* pState) WIN_NOEXCEPT;
static xinput_get_state_t g_pfnXInputGetState = nullptr;

namespace AlphaRing {
    namespace Input {
        bool Init() {
            auto hModule = GetModuleHandleA("XINPUT1_3.dll");
            if (hModule || (hModule = GetModuleHandleA("XINPUT1_4.dll")) || (hModule = GetModuleHandleA("XINPUT9_1_0.dll"))) {
                g_pfnXInputGetState = (xinput_get_state_t)GetProcAddress(hModule, "XInputGetState");
            }

            if (!g_pfnXInputGetState) {
                MessageBoxA(nullptr, "Failed to load XInputGetState", "AlphaRing", MB_OK | MB_ICONERROR);
                ExitProcess(0);
            }

            return true;
        }

        bool GetXInputGetState(DWORD dwUserIndex, XINPUT_STATE* pState) {
            if (!g_pfnXInputGetState || !pState) return false;
            return g_pfnXInputGetState(dwUserIndex, pState) == ERROR_SUCCESS;
        }
    };
}