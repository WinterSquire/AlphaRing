#include "Window.h"
#include "Renderer.h"

#include "windows.h"

#include <mutex>
#include <condition_variable>

static std::mutex cv_m;
static std::condition_variable cv;
static bool b_shouldDestory = false;

void Window::waitForDestroy() {
    std::unique_lock<std::mutex> lk(cv_m);
    cv.wait(lk, []{return b_shouldDestory;});
}

void Window::signalDestroy() {
    std::lock_guard<std::mutex> lk(cv_m);
    b_shouldDestory = true;
    cv.notify_one();
}

LRESULT Window_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_KEYDOWN:{
            switch (wParam) {
                case VK_F4:{
                    bool& b = Renderer()->ShowContext();
                    b = !b;
                    break;
                }
            }
            break;
        }
        case WM_KEYUP:{
            break;
        }
        default:
            break;
    }
    return false;
}
