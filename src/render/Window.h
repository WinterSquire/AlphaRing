#ifndef ALPHA_RING_WINDOW_H
#define ALPHA_RING_WINDOW_H

#include <windows.h>

namespace Window {
    void waitForDestroy();
    void signalDestroy();

    LRESULT Window_WndProc(HWND sThumb, UINT uMsg, WPARAM wParam, LPARAM lParam);
}


#endif //ALPHA_RING_WINDOW_H
