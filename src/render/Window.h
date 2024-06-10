#ifndef ALPHA_RING_WINDOW_H
#define ALPHA_RING_WINDOW_H

#include <mutex>
#include <condition_variable>
#include <windows.h>
#include <d3d11.h>

class CWindow {
public:
    CWindow(int width, int height, const char* title, const char* className);

    CWindow() : m_title {'\0'}, m_className {'\0'}, m_wc() {
        m_registered = false;
        m_hWnd = nullptr;
        m_pWndProc = nullptr;
        m_old_pWndProc = nullptr;

        m_pSwapChain = nullptr;
        m_pDevice = nullptr;
        m_pContext = nullptr;
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

    inline WNDPROC setWndProc(WNDPROC proc) {return m_old_pWndProc = (WNDPROC)SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)(m_pWndProc = proc));};
    inline HWND getHandle() const {return m_hWnd;}
    inline ID3D11Device* getDevice() const {return m_pDevice;}
    inline ID3D11DeviceContext* getContext() const {return m_pContext;}
    inline WNDPROC getWndProc() const {return m_pWndProc;}
    inline WNDPROC getOldWndProc() const {return m_old_pWndProc;}

protected:
    WNDCLASS                m_wc;
    HWND                    m_hWnd;
    IDXGISwapChain*         m_pSwapChain;
    ID3D11Device*			m_pDevice;
    ID3D11DeviceContext*	m_pContext;
    WNDPROC					m_pWndProc;
    WNDPROC                 m_old_pWndProc;

    bool m_registered;
    char m_title[256];
    char m_className[256];
};

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


#endif //ALPHA_RING_WINDOW_H
