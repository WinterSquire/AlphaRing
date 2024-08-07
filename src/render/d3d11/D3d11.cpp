#include "D3d11.h"

#include <d3d11.h>

#include "common.h"

#include "imgui.h"

#include "../imgui/ImGui.h"
#include "../Window/Window.h"

namespace AlphaRing::Render::D3d11 {
    bool CreateHook();
    void InitMainRender(IDXGISwapChain *swapChain);

    void *functions[205];

    void *GetFunction(int index) { return functions[index]; }

    HMODULE hD3d11;

    long (__stdcall *p_fD3D11CreateDeviceAndSwapChain)(IDXGIAdapter *, D3D_DRIVER_TYPE, HMODULE, UINT,
                                                       const D3D_FEATURE_LEVEL *, UINT, UINT,
                                                       const DXGI_SWAP_CHAIN_DESC *, IDXGISwapChain **, ID3D11Device **,
                                                       D3D_FEATURE_LEVEL *, ID3D11DeviceContext **);

    Graphics_t graphics;

    DefDetourFunction(HRESULT, __stdcall, Present, IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
        if (graphics.pSwapChain != pSwapChain) {
            InitMainRender(pSwapChain);
        }

        ImGui::Render();

        return ppOriginal_Present(graphics.pSwapChain, SyncInterval, Flags);
    }

    DefDetourFunction(HRESULT, __stdcall, ResizeBuffers, IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
        if (graphics.pSwapChain != pSwapChain) {
            InitMainRender(pSwapChain);
        }

        graphics.pView->Release();

        auto result = ppOriginal_ResizeBuffers(graphics.pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

        graphics.RecreateRenderTargetView();

        return result;
    }
}

namespace AlphaRing::Render::D3d11 {
    void InitMainRender(IDXGISwapChain *swapChain) {
        static bool initialized = false;
        DXGI_SWAP_CHAIN_DESC sd;

        assert(initialized == false);

        // Get Device and Context
        graphics.pSwapChain = swapChain;
        graphics.pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&graphics.pDevice);
        graphics.pDevice->GetImmediateContext(&graphics.pContext);

        memcpy(functions + 18, *(void **) graphics.pDevice, 43 * sizeof(void *));
        memcpy(functions + 18 + 43, *(void **) graphics.pContext, 144 * sizeof(void *));

        bool result = CreateHook();

        assertm(result, "Failed to create hook");

        // Get Factory
        IDXGIDevice * pDXGIDevice = nullptr;
        graphics.pDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);

        IDXGIAdapter * pDXGIAdapter = nullptr;
        pDXGIDevice->GetAdapter( &pDXGIAdapter );

        pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&graphics.pIDXGIFactory);

        // Create Render Target View
        graphics.RecreateRenderTargetView();

        // Get Window HWND
        graphics.pSwapChain->GetDesc(&sd);
        graphics.hwnd = sd.OutputWindow;

        ImGui::Initialize();
        Window::Initialize();

        initialized = true;
    }

    bool Initialize() {
        const WNDCLASS wc {
                CS_HREDRAW | CS_VREDRAW,
                DefWindowProc,
                0,
                0,
                GetModuleHandle(nullptr),
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                "Default Window"
        };

        bool result;

        result = RegisterClass(&wc);

        assertm(result, "failed to register class");

        auto hwnd = CreateWindow(wc.lpszClassName, "Default Window", WS_OVERLAPPEDWINDOW, 0, 0,
                                     800, 600, nullptr, nullptr, wc.hInstance, nullptr);

        assertm(hwnd != nullptr, "failed to create window");

        hD3d11 = GetModuleHandle("d3d11.dll");

        assertm(hD3d11 != nullptr, "failed to find module \"d3d11.dll\"");

        p_fD3D11CreateDeviceAndSwapChain = (decltype(p_fD3D11CreateDeviceAndSwapChain)) GetProcAddress(
                hD3d11, "D3D11CreateDeviceAndSwapChain");

        assertm(p_fD3D11CreateDeviceAndSwapChain != nullptr, "failed to find function \"D3D11CreateDeviceAndSwapChain\"");

        IDXGISwapChain *swapChain;
        ID3D11Device *device;
        ID3D11DeviceContext *context;

        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0};
        const DXGI_SWAP_CHAIN_DESC swapChainDesc {
                {
                        0,
                        0,
                        {
                                60,
                                1
                        },
                        DXGI_FORMAT_R8G8B8A8_UNORM,
                        DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
                        DXGI_MODE_SCALING_UNSPECIFIED
                },
                {
                        1,
                        0
                },
                DXGI_USAGE_RENDER_TARGET_OUTPUT,
                1,
                hwnd,
                1,
                DXGI_SWAP_EFFECT_DISCARD,
                DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
        };

        result = SUCCEEDED(p_fD3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, featureLevels, 2, D3D11_SDK_VERSION,
                                                            &swapChainDesc, &swapChain, &device, &featureLevel, &context));

        assertm(result, "failed to create device and swapchain");

        memcpy(functions, *(void **) swapChain, 18 * sizeof(void *));

        swapChain->Release();
        device->Release();
        context->Release();

        DestroyWindow(hwnd);
        UnregisterClass(wc.lpszClassName, wc.hInstance);

        result = AlphaRing::Hook::Detour({
            {functions[8],  Present,       (void **) &ppOriginal_Present},
            {functions[13], ResizeBuffers, (void **) &ppOriginal_ResizeBuffers},
        });

        assertm(result, "failed to create d3d11 hook");

        return result;
    }
}
