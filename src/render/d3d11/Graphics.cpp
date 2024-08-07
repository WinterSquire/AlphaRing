#include "D3d11.h"

static Graphics_t graphics;

Graphics_t* p_graphics = &graphics;

void Graphics_t::SetRenderTargetView() {
    if (pView != nullptr)
        pContext->OMSetRenderTargets(1, &pView, nullptr);
}

void Graphics_t::RecreateRenderTargetView() {
    ID3D11Texture2D *pBackBuffer;
    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **) &pBackBuffer);
    pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pView);
    pBackBuffer->Release();
}

void Graphics_t::SetWireframe() {
    D3D11_RASTERIZER_DESC r_desc;
    ID3D11RasterizerState* r_state;
    
    pContext->RSGetState(&r_state);
    if (r_state != nullptr) {
        r_state->GetDesc(&r_desc);
        r_desc.FillMode = D3D11_FILL_WIREFRAME;
        pDevice->CreateRasterizerState(&r_desc, &r_state);
        pContext->RSSetState(r_state);
    }
}