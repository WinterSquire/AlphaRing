#pragma once

#include <d3d11.h>

namespace AlphaRing::Render::D3d11 {
    bool Initialize();

    enum {None, Halo1, Halo2, Halo3, Halo3ODST, HaloReach, Halo4,};

    void* GetFunction(int index);

    extern struct Graphics_t {
        ID3D11Device *pDevice;
        ID3D11DeviceContext *pContext;
        IDXGISwapChain *pSwapChain;
        ID3D11RenderTargetView *pView;
        IDXGIFactory *pIDXGIFactory;
        HWND hwnd;

        void RecreateRenderTargetView() {
            ID3D11Texture2D *pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **) &pBackBuffer);
            pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pView);
            pBackBuffer->Release();
        }

        void SetRenderTargetView() {
            if (pView != nullptr) {
                pContext->OMSetRenderTargets(1, &pView, nullptr);
            }
        }
    } graphics;

    inline Graphics_t *Graphics() { return &graphics; }
}
