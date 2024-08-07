#pragma once

#include <d3d11.h>

struct Graphics_t {
    ID3D11Device *pDevice;
    ID3D11DeviceContext *pContext;
    IDXGISwapChain *pSwapChain;
    ID3D11RenderTargetView *pView;
    IDXGIFactory *pIDXGIFactory;
    HWND hwnd;

    void SetRenderTargetView();
    void RecreateRenderTargetView();
    void SetWireframe();
};

extern Graphics_t* p_graphics;
inline Graphics_t* Graphics() {return p_graphics;}

