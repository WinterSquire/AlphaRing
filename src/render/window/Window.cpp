#include <tchar.h>
#include "Window.h"

#include "common.h"

#include "global/Global.h"

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "../D3d11/D3d11.h"

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace AlphaRing::Render::Window {
    WNDPROC oldWndProc = nullptr;

    //todo: WM_IME_COMPOSITION Support
    static LRESULT dWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
            return true;

        switch (uMsg) {
            case WM_KEYDOWN: {
                switch (wParam) {
                    case VK_F4:
                        AlphaRing::Global::Global()->show_imgui = !AlphaRing::Global::Global()->show_imgui;
                        break;
                }
                break;
            }
        }

        auto& io = ImGui::GetIO();
        if (io.WantCaptureMouse)
            return true;

        return CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
    }

/*
    //CreateWindowExW()
    DefDetourFunction(HWND, __stdcall, dCreateWindowExW, DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
        auto hwnd = ppOriginal_dCreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);

        if (lpClassName && wcscmp(lpClassName, L"UnrealWindow") == 0) {
            ppOriginal_dCreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
        }
        return hwnd;
    }
*/
    auto class_name = L"AlphaRing";

    static LRESULT WndProc1(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

        return DefWindowProcW(hWnd, uMsg, wParam, lParam);
    }

    bool RegistWindowClass() {
        WNDCLASSW wc;
        ZeroMemory(&wc, sizeof(wc));
        wc.style = CS_DBLCLKS;
        wc.lpszClassName = class_name;
        wc.lpfnWndProc = WndProc1;
        wc.hInstance = GetModuleHandle(nullptr);
        return RegisterClassW(&wc);
    };

    HWND CreateAnotherWindow(const wchar_t* window_name) {
        auto exStyle = WS_EX_APPWINDOW;
        auto style = WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_GROUP|WS_TABSTOP;
        auto hInstance = GetModuleHandleA(nullptr);
        auto hParent = AlphaRing::Render::D3d11::Graphics()->hwnd;
        return CreateWindowExW(exStyle, class_name, window_name, style,
                        0, 0, 800, 600, hParent, nullptr, hInstance, nullptr);
    }

    bool Initialize() {
        auto hwnd = AlphaRing::Render::D3d11::Graphics()->hwnd;

        oldWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)dWndProc);

        return oldWndProc != nullptr;
    }
}
