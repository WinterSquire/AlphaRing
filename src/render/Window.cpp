#include "Window.h"

#include "Renderer.h"
#include "input/Input.h"

#include <mutex>
#include <condition_variable>
#include <windows.h>
#include "imgui/imgui.h"

static std::mutex cv_m;
static std::condition_variable cv;
static bool b_shouldDestory = false;

void Window::waitForDestroy() {
    std::unique_lock<std::mutex> lk(cv_m);
    cv.wait(lk, [] {return b_shouldDestory; });
}

void Window::signalDestroy() {
    std::lock_guard<std::mutex> lk(cv_m);
    b_shouldDestory = true;
    cv.notify_one();
}

inline bool GetControllerState(XINPUT_STATE& state, DWORD controllerIndex = 0) {
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    return AlphaRing::Input::GetXInputGetState(controllerIndex, &state);
}

LRESULT Window::Window_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    XINPUT_STATE state;

    if (GetControllerState(state)) {
        static bool b_toggled = false;
        static bool b_pressed = false;

        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START && state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) {
            if (!b_toggled) {
                Renderer()->ToggleContext();
                b_toggled = true;
                return false;
            }
        } else {
            b_toggled = false;
        }

        if (Renderer()->ShowContext()) {
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
    }

    //todo: WM_IME_COMPOSITION Support

    if (uMsg == WM_KEYDOWN && wParam == VK_F4) {
        Renderer()->ToggleContext();
        return false;
    }

    return false;
}
