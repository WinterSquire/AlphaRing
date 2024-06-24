#include "main_window.h"

#include "./core/String.h"
#include "./main_renderer.h"
#include "input/Input.h"

#include "imgui/imgui.h"

CMainWindow CMainWindow::s_instance;

void CMainWindow::init(HWND hWnd, IDXGISwapChain* pSwapChain, ID3D11Device* pDevice, ID3D11DeviceContext* pContext) {
    m_hWnd = hWnd;
    set_wnd_proc(dWndProc);
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

#include "filesystem/Filesystem.h"

//todo: WM_IME_COMPOSITION Support
LRESULT CMainWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    wchar_t path[MAX_PATH];
    AlphaRing::Input::Update();

    switch (uMsg) {
        case WM_KEYDOWN: {
            switch (wParam) {
                case VK_F1:
                    AlphaRing::Filesystem::GetResource("patch.xml", path);
                    wprintf(L"\n%s\n", path);
                    break;
                case VK_F4:
                    MainRenderer()->ToggleContext();
                    break;
            }
            break;
        }
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