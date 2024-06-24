#include "Input.h"

#include "imgui/imgui.h"
#include "hook/d3d11/main_renderer.h"

static HMODULE hModule;
static DWORD (WINAPI* g_pXInputGetState)(_In_  DWORD dwUserIndex, _Out_ XINPUT_STATE* pState) WIN_NOEXCEPT;

namespace AlphaRing::Input {
    bool Init() {
        if ((hModule = GetModuleHandleA("XINPUT1_3.dll")) ||
            (hModule = GetModuleHandleA("XINPUT1_4.dll")) ||
            (hModule = GetModuleHandleA("XINPUT9_1_0.dll"))) {
            g_pXInputGetState = (decltype(g_pXInputGetState))GetProcAddress(hModule, "XInputGetState");
        }
        else {
            MessageBoxA(nullptr, "Failed to load XInputGetState", "AlphaRing", MB_OK | MB_ICONERROR);
            ExitProcess(0);
        }

        return true;
    }

    bool Shutdown() {
        return true;
    }

    bool GetXInputGetState(DWORD dwUserIndex, XINPUT_STATE* pState) {
        if (!g_pXInputGetState || !pState) return false;
        memset(pState, 0, sizeof(XINPUT_STATE));
        return g_pXInputGetState(dwUserIndex, pState) == ERROR_SUCCESS;
    }

    bool Update() {
        static bool b_toggled = false;
        static bool b_pressed = false;
        XINPUT_STATE state;

        if (!GetXInputGetState(0, &state))
            return false;

        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START && state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) {
            if (!b_toggled) {
                MainRenderer()->ToggleContext();
                b_toggled = true;
                return false;
            }
        } else {
            b_toggled = false;
        }

        if (MainRenderer()->ShowContext()) {
            const auto f_speed = [](SHORT x, SHORT y) -> ImVec2 {
                // Mouse Move Speed for Gamepad
                const auto speed = 5.0f;
                // Normalize Move Speed
                const auto f_normalize = [](SHORT sThumb) -> float {
                    const auto deadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
                    return (abs(sThumb) > deadZone) ? (sThumb / 32767.0f) : 0.0f;
                };
                // Get Final Move Speed
                return {f_normalize(x) * speed, -f_normalize(y) * speed};
            };

            ImGuiIO& io = ImGui::GetIO();

            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
                if (!b_pressed) {
                    io.MouseDown[0] = true;
                    b_pressed = true;
                }
            } else if (b_pressed) {
                io.MouseDown[0] = false;
                b_pressed = false;
            }

            io.MousePos += f_speed(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY);
        }

        return true;
    }
}