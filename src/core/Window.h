#pragma once

#include <windows.h>
#include "./String.h"

#include "./Renderer.h"

class CWindow {
friend class CRenderer;

public:
    CWindow(int width, int height, const char* title, const char* className);

    CWindow() : m_title {'\0'}, m_className {'\0'}, m_wc() {
        m_registered = false;
        m_hWnd = nullptr;
        m_pWndProc = nullptr;
        m_old_pWndProc = nullptr;
    }

    ~CWindow() {
        if (m_hWnd)
            DestroyWindow(m_hWnd);
        if (m_registered)
            UnregisterClass(m_wc.lpszClassName, m_wc.hInstance);
    }

    void show() {
        ShowWindow(m_hWnd, SW_SHOW);
        UpdateWindow(m_hWnd);
    }

    inline WNDPROC set_wnd_proc(WNDPROC proc) {
        m_pWndProc = proc;
        m_old_pWndProc = (WNDPROC)SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)m_pWndProc);
        return m_old_pWndProc;
    };

    inline HWND get_hwnd() { return m_hWnd; }

    void set_renderer(CRenderer* renderer);

protected:
    WNDCLASS                m_wc;
    HWND                    m_hWnd;
    WNDPROC					m_pWndProc;
    WNDPROC                 m_old_pWndProc;

    CRenderer* m_renderer;
    bool m_registered;
    char m_title[256];
    char m_className[256];

};