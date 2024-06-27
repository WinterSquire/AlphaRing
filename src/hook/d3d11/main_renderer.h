#pragma once

#include "core/Renderer.h"

class CMainRenderer : public CRenderer {
public:
    CMainRenderer() : CRenderer(nullptr) {

    }

    enum {None, Halo1, Halo2, Halo3, Halo3ODST, HaloReach, Halo4,};

    void Init(IDXGISwapChain* p_swapChain, ID3D11Device* p_device, ID3D11DeviceContext* p_context) {
        m_pSwapChain = p_swapChain;
        m_pDevice = p_device;
        m_pContext = p_context;
        m_bNewFrame = false;
        m_bShowContext = true;
        m_bShowMouse = true;

        ImGui_Init();
    }

    void ImGui_Init();
    bool Render(int render_flag);

    bool Present() override;

    inline bool Render() override {
        return Render(None);
    }

    void CreateMainRenderTargetView() {
        ID3D11Texture2D *pBackBuffer = nullptr;
        m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
        m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pView);
        pBackBuffer->Release();
        m_pContext->OMSetRenderTargets(1, &m_pView, nullptr);
    }

    void ReleaseMainRenderTargetView() {
        if (m_pView == nullptr) return;

        m_pContext->OMSetRenderTargets(0, 0, 0);
        m_pView->Release();
        m_pView = nullptr;
    }

    inline void Resize(float width, float height) {
        D3D11_VIEWPORT vp{0,0,width, height,0.0f, 1.0f};
        m_pContext->RSSetViewports(1, &vp);
    }

    inline bool ShowContext() {
        return m_bShowContext;
    }

    inline void ToggleContext() {
        m_bShowContext = !m_bShowContext;
    }

    inline bool GetShowMouse() {
        return m_bShowMouse;
    }

    inline void SetShowMouse(bool b) {
        m_bShowMouse = b;
    }

    inline void SetState(ID3D11RasterizerState* p_state) {
        m_pContext->RSSetState(p_state);
    }

    inline void SetStateWireframe() {
        if (m_state_wireframe == nullptr)
            m_pDevice->CreateRasterizerState(&m_desc_wireframe, &m_state_wireframe);
        if (m_state_wireframe != nullptr)
            m_pContext->RSSetState(m_state_wireframe);
    }

    static CMainRenderer instance;

private:
    const D3D11_RASTERIZER_DESC m_desc_wireframe {
            D3D11_FILL_WIREFRAME,D3D11_CULL_NONE,false,
            0,0.0f,0.0f,
            true, false, false, false
    };

    ID3D11RasterizerState* m_state_wireframe;


    bool m_bShowContext;
    bool m_bNewFrame;
    bool m_bShowMouse;
    ID3D11RenderTargetView* m_pView;

};

inline CMainRenderer* MainRenderer() { return &CMainRenderer::instance; }