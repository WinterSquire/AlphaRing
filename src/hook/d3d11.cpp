#include "./d3d11.h"

#include "render/Renderer.h"
#include "render/Window.h"

#include "MinHook.h"

#include <d3d11.h>

HWND					window;
WNDPROC					oWndProc;

struct FunctionTable {
    typedef HRESULT(__stdcall* tPresent) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
    typedef HRESULT (__stdcall* tResizeBuffers) (IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

    void* functions[205];

    tPresent Present;
    tResizeBuffers ResizeBuffers;

    bool Initialize();
} functionTable;

static LRESULT __stdcall dWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT Window_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam) || Window_WndProc(hWnd, uMsg, wParam, lParam))
        return true;

    if (uMsg == WM_QUIT && hWnd == window) Window::signalDestroy();

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

static HRESULT __stdcall dPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    static bool bInitialized = false;
    ID3D11Device*			pDevice;
    ID3D11DeviceContext*	pContext;

    if (!bInitialized &&
        pSwapChain != nullptr &&
        SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)) &&
        pDevice != nullptr && (pDevice->GetImmediateContext(&pContext), pContext != nullptr)) {

        DXGI_SWAP_CHAIN_DESC sd;
        pSwapChain->GetDesc(&sd);
        window = sd.OutputWindow;
        oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR) dWndProc);

        Renderer()->Init(window, pSwapChain, pDevice, pContext);
        bInitialized = true;
    }
    else {
        Renderer()->Render();
    }

    return functionTable.Present(pSwapChain, SyncInterval, Flags);
}

static HRESULT dResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
    Renderer()->ReleaseMainRenderTargetView();

    HRESULT hr = functionTable.ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

    Renderer()->CreateMainRenderTargetView();

    Renderer()->Resize(Width, Height);

    return hr;
}

bool Directx11Hook::Initialize() {
    functionTable.Initialize();

    // [8]   Present
    if (MH_CreateHook(functionTable.functions[8], dPresent,(void **) &functionTable.Present) != MH_OK ||
        MH_EnableHook(functionTable.functions[8]) != MH_OK)
        return false;

    // [13]  ResizeBuffers
    if (MH_CreateHook(functionTable.functions[13], dResizeBuffers,(void **) &functionTable.ResizeBuffers) != MH_OK ||
        MH_EnableHook(functionTable.functions[13]) != MH_OK)
        return false;

    return true;
}

bool FunctionTable::Initialize() {
    WNDCLASS wc {
            CS_HREDRAW | CS_VREDRAW,
            DefWindowProc,
            0,
            0,
            GetModuleHandle(nullptr),
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            "Directx11 Hook",
    };

    if (!RegisterClass(&wc)) return false;

    HWND window = CreateWindow(wc.lpszClassName, "Directx11 Hook", WS_OVERLAPPEDWINDOW,
                               0, 0, 100, 100, nullptr, nullptr, wc.hInstance, nullptr);

    if (window == nullptr) return false;

    HMODULE d3d11 = GetModuleHandle("d3d11.dll");

    if (d3d11 == nullptr) {
        DestroyWindow(window);
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return false;
    }

    void *D3D11CreateDeviceAndSwapChain = GetProcAddress(d3d11, "D3D11CreateDeviceAndSwapChain");

    if (D3D11CreateDeviceAndSwapChain == nullptr) {
        DestroyWindow(window);
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return false;
    }

    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0 };

    DXGI_RATIONAL refreshRate;
    refreshRate.Numerator = 60;
    refreshRate.Denominator = 1;

    DXGI_MODE_DESC bufferDesc;
    bufferDesc.Width = 100;
    bufferDesc.Height = 100;
    bufferDesc.RefreshRate = refreshRate;
    bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    DXGI_SAMPLE_DESC sampleDesc;
    sampleDesc.Count = 1;
    sampleDesc.Quality = 0;

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    swapChainDesc.BufferDesc = bufferDesc;
    swapChainDesc.SampleDesc = sampleDesc;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.OutputWindow = window;
    swapChainDesc.Windowed = 1;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    IDXGISwapChain* swapChain;
    ID3D11Device* device;
    ID3D11DeviceContext* context;

    if (((long(__stdcall*)(
            IDXGIAdapter*,
            D3D_DRIVER_TYPE,
            HMODULE,
            UINT,
            const D3D_FEATURE_LEVEL*,
            UINT,
            UINT,
            const DXGI_SWAP_CHAIN_DESC*,
            IDXGISwapChain**,
            ID3D11Device**,
            D3D_FEATURE_LEVEL*,
            ID3D11DeviceContext**))(D3D11CreateDeviceAndSwapChain))(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, 2, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &featureLevel, &context) < 0)
    {
        ::DestroyWindow(window);
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return false;
    }

    memcpy(this, *(uintptr_t**)swapChain, 18 * sizeof(uintptr_t));
    memcpy(((uintptr_t*)this) + 18, *(uintptr_t**)device, 43 * sizeof(uintptr_t));
    memcpy(((uintptr_t*)this) + 18 + 43, *(uintptr_t**)context, 144 * sizeof(uintptr_t));

    swapChain->Release();
    swapChain = NULL;

    device->Release();
    device = NULL;

    context->Release();
    context = NULL;

    DestroyWindow(window);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return true;
}