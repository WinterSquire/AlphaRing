#include "Window.h"

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

void CWindow::set_renderer(CRenderer *renderer) {
    m_renderer = renderer;
    m_renderer->m_window = this;
}
