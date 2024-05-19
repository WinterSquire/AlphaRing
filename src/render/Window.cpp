#include "Window.h"
#include "Renderer.h"
#include "String.h"

#include "windows.h"

#include <mutex>
#include <condition_variable>
#include <Xinput.h>
#include <chrono>
#include <thread>

#pragma comment(lib, "Xinput.lib")

static std::mutex cv_m;
static std::condition_variable cv;
static bool b_shouldDestory = false;

XINPUT_STATE GetControllerState(DWORD controllerIndex = 0) {
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    DWORD result = XInputGetState(controllerIndex, &state);

    if (result == ERROR_SUCCESS) {
        return state;
    }
    else {
        throw std::runtime_error("Controller is not connected.");
    }
}

void Window::waitForDestroy() {
    std::unique_lock<std::mutex> lk(cv_m);
    cv.wait(lk, [] {return b_shouldDestory; });
}

void Window::signalDestroy() {
    std::lock_guard<std::mutex> lk(cv_m);
    b_shouldDestory = true;
    cv.notify_one();
}

LRESULT Window_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    XINPUT_STATE state = GetControllerState(0);
    switch (uMsg) {
    case WM_KEYDOWN: {
        switch (wParam) {
        case VK_F4: {
            bool& b = Renderer()->ShowContext();
            b = !b;
            break;
        }
        }
        break;
    }
    case WM_KEYUP: {
        break;
    }
    default:
        break;
    }
    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
        bool& b = Renderer()->ShowContext();
        b = !b;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return false;
}
