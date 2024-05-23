#include "Window.h"
#include "Renderer.h"
#include "String.h"

#include <mutex>
#include <condition_variable>

#include <windows.h>

#include "input/Input.h"
#include <imgui.h>

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

LRESULT Window_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    XINPUT_STATE state;

    if (GetControllerState(state)) {
        static bool b_controller = false;
        ImGuiIO& io = ImGui::GetIO();
        const int deadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
        SHORT sThumbRX = state.Gamepad.sThumbRX;
        SHORT sThumbRY = state.Gamepad.sThumbRY;

        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
            if (!b_controller) {
                Renderer()->ToggleContext();
                b_controller = true;
            }
        } else {
            b_controller = false;
        }

        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
        {
            io.MouseDown[0] = true;
        }
        else
        {
            io.MouseDown[0] = false;
        }

        //Mapping Gamepad for GUI
        
        float mouseX = io.MousePos.x;
        float mouseY = io.MousePos.y;
        const float speed = 5.0f; //Mouse movespeed for Gamepad

        float normalizedLX = (abs(sThumbRX) > deadZone) ? (sThumbRX / 32767.0f) : 0.0f;
        float normalizedLY = (abs(sThumbRY) > deadZone) ? (sThumbRY / 32767.0f) : 0.0f;

        mouseX += normalizedLX * speed;
        mouseY -= normalizedLY * speed;

        io.MousePos = ImVec2(mouseX, mouseY);

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
