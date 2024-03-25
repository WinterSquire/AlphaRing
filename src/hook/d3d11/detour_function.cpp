#include "detour_function.h"

#include "imgui_impl.h"
#include "function_table.h"

HRESULT __stdcall Detour::Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!ImmediateGUI::Initialized()) ImmediateGUI::Initialize(pSwapChain);

    ImmediateGUI::Update();

    return functionTable.Present(pSwapChain, SyncInterval, Flags);
}

HRESULT Detour::ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    ImmediateGUI::ReleaseMainRenderTargetView();

    HRESULT hr = functionTable.ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

    ImmediateGUI::CreateMainRenderTargetView();

    // Set up the viewport.
    D3D11_VIEWPORT vp{
        0,0,
        static_cast<FLOAT>(Width), static_cast<FLOAT>(Height),
        0.0f, 1.0f
    };

    ImmediateGUI::GetImmediateContext()->RSSetViewports(1, &vp);

    return hr;
}