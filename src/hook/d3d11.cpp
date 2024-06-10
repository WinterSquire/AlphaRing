#include "./d3d11.h"

#include "render/Renderer.h"
#include "render/Window.h"

#include <minhook/MinHook.h>

#include <d3d11.h>
#include <memory>

struct FunctionTable {
    typedef HRESULT(__stdcall* tPresent) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
    typedef HRESULT (__stdcall* tResizeBuffers) (IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

    void* functions[205];

    tPresent Present;
    tResizeBuffers ResizeBuffers;
    long(__stdcall* p_fD3D11CreateDeviceAndSwapChain)(IDXGIAdapter*,D3D_DRIVER_TYPE,HMODULE,UINT,const D3D_FEATURE_LEVEL*,UINT,UINT,const DXGI_SWAP_CHAIN_DESC*,IDXGISwapChain**,ID3D11Device**,D3D_FEATURE_LEVEL*,ID3D11DeviceContext**);

    bool Initialize();
} functionTable;

static bool bInitialized = false;

inline void CheckInit(IDXGISwapChain* pSwapChain) {
    ID3D11Device*			pDevice;
    ID3D11DeviceContext*	pContext;

    if (!bInitialized &&
        pSwapChain != nullptr &&
        SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)) &&
        pDevice != nullptr && (pDevice->GetImmediateContext(&pContext), pContext != nullptr)) {

        DXGI_SWAP_CHAIN_DESC sd;
        pSwapChain->GetDesc(&sd);

        MainWindow()->init(sd.OutputWindow, pSwapChain, pDevice, pContext);
        Renderer()->Init(sd.OutputWindow, pSwapChain, pDevice, pContext);
        bInitialized = true;
    }
}

static HRESULT __stdcall dPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    CheckInit(pSwapChain);

    if (bInitialized) Renderer()->Render();

    return functionTable.Present(pSwapChain, SyncInterval, Flags);
}

static HRESULT dResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
    CheckInit(pSwapChain);

    if (bInitialized) {
        Renderer()->ReleaseMainRenderTargetView();

        HRESULT hr = functionTable.ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

        Renderer()->CreateMainRenderTargetView();

        Renderer()->Resize(Width, Height);

        return hr;
    } else {
        return functionTable.ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
    }
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
    auto p_window = std::make_unique<CWindow>(
            100, 100, "Directx11 Hook", "Directx11 Hook");

    if (p_window->getHandle() == nullptr) return false;

    auto d3d11 = GetModuleHandle("d3d11.dll");

    if (d3d11 == nullptr) return false;

    p_fD3D11CreateDeviceAndSwapChain = (decltype(p_fD3D11CreateDeviceAndSwapChain))GetProcAddress(
            d3d11, "D3D11CreateDeviceAndSwapChain");

    if (p_fD3D11CreateDeviceAndSwapChain == nullptr) return false;

    IDXGISwapChain* swapChain;
    ID3D11Device* device;
    ID3D11DeviceContext* context;

    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0 };

    const DXGI_SWAP_CHAIN_DESC swapChainDesc {
            {
                    100,
                    100,
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
            p_window->getHandle(),
            1,
            DXGI_SWAP_EFFECT_DISCARD,
            DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
    };

    if (FAILED(p_fD3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, featureLevels, 2, D3D11_SDK_VERSION,
                                             &swapChainDesc, &swapChain, &device, &featureLevel, &context)))
        return false;


    memcpy(this, *(uintptr_t**)swapChain, 18 * sizeof(uintptr_t));
    memcpy(((uintptr_t*)this) + 18, *(uintptr_t**)device, 43 * sizeof(uintptr_t));
    memcpy(((uintptr_t*)this) + 18 + 43, *(uintptr_t**)context, 144 * sizeof(uintptr_t));

    swapChain->Release();
    device->Release();
    context->Release();

    return true;
}