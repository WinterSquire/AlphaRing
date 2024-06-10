#include "Window.h"

#include "./core/String.h"
#include "Renderer.h"
#include "input/Input.h"

#include "imgui/imgui.h"

CMainWindow CMainWindow::s_instance;

CWindow::CWindow(int width, int height, const char* title, const char* className)
        : m_title {'\0'}, m_className {'\0'}, m_wc {
        CS_HREDRAW | CS_VREDRAW,
        DefWindowProc,
        0,
        0,
        GetModuleHandle(nullptr),
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        m_className
} {
    String::strcpy(m_title, title);
    String::strcpy(m_className, className);

    if (!(m_registered = RegisterClass(&m_wc))) return;

    m_hWnd = CreateWindow(className, title, WS_OVERLAPPEDWINDOW,
                          0, 0, width, height, nullptr, nullptr, m_wc.hInstance, nullptr);
}

void CMainWindow::init(HWND hWnd, IDXGISwapChain* pSwapChain, ID3D11Device* pDevice, ID3D11DeviceContext* pContext) {
    m_hWnd = hWnd;
    m_pSwapChain = pSwapChain;
    m_pDevice = pDevice;
    m_pContext = pContext;
    setWndProc(dWndProc);
}

LRESULT CMainWindow::dWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam) ||
        WndProc(hWnd, uMsg, wParam, lParam))
        return true;

    if ((uMsg == WM_QUIT || uMsg == WM_DESTROY || uMsg == WM_CLOSE) && hWnd == s_instance.m_hWnd)
        CMainWindow::signalDestroy();

    return CallWindowProc(s_instance.m_old_pWndProc, hWnd, uMsg, wParam, lParam);
}

LRESULT CMainWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    XINPUT_STATE state;

    if (AlphaRing::Input::GetXInputGetState(0, &state)) {
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

void CMainWindow::waitForDestroy() {
    std::unique_lock<std::mutex> lk(CMainWindow::s_instance.m_mutex);
    CMainWindow::s_instance.m_cv.wait(lk, [] {return CMainWindow::s_instance.m_exit;});
}

void CMainWindow::signalDestroy() {
    std::lock_guard<std::mutex> lk(CMainWindow::s_instance.m_mutex);
    CMainWindow::s_instance.m_exit = true;
    CMainWindow::s_instance.m_cv.notify_one();
}
