#pragma once

#include <mutex>
#include <condition_variable>
#include <windows.h>
#include <d3d11.h>

#include "./core/Window.h"

class CMainWindow : public CWindow {
public:
    CMainWindow() : CWindow(), m_exit(false), m_mutex(), m_cv() {}
    ~CMainWindow() {}

    void init(HWND hWnd, IDXGISwapChain* pSwapChain, ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
    static void waitForDestroy();
    static void signalDestroy();

private:
    static LRESULT dWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    static CMainWindow s_instance;

private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_exit;
};

inline CMainWindow* MainWindow() { return &CMainWindow::s_instance; }