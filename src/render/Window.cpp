#include "Window.h"
#include "Renderer.h"
#include "String.h"

#include <mutex>
#include <condition_variable>

#include <windows.h>
#include <Xinput.h>

static std::mutex cv_m;
static std::condition_variable cv;
static bool b_shouldDestory = false;
static DWORD (WINAPI* xinput_get_state)(_In_  DWORD dwUserIndex, _Out_ XINPUT_STATE* pState) WIN_NOEXCEPT;

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
    return xinput_get_state(controllerIndex, &state) == ERROR_SUCCESS;
}

LRESULT Window_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    XINPUT_STATE state;

    if (!xinput_get_state)
        xinput_get_state = reinterpret_cast<decltype(xinput_get_state)>(GetProcAddress(GetModuleHandleA("XINPUT1_3.dll"), "XInputGetState"));
    else if (GetControllerState(state)) {
        static bool b_controller = false;

        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
            if (!b_controller) {
                Renderer()->ToggleContext();
                b_controller = true;
            }
        } else {
            b_controller = false;
        }
    }

    switch (uMsg) {
    case WM_KEYDOWN: {
        switch (wParam) {
        case VK_F4:
            Renderer()->ToggleContext();
            break;
        }
        break;
    }
    case WM_KEYUP: {
        break;
    }
    default:
        break;
    }

    return false;
}
