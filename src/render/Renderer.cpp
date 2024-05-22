#include "Renderer.h"

#include <d3d11.h>
#include <dxgi.h>

#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"

#include "imgui/home_page.h"

class CRenderer : public ICRenderer {
public:
    void Init(void* oWindow, void *p_swapChain, void *p_device, void *p_context) override;

    void CreateMainRenderTargetView() override;
    void ReleaseMainRenderTargetView() override;

    bool NewFrame() override;
    void Render() override;
    void EndFrame() override;

    bool &ShowContext() override {return m_bShowContext;}
    void Resize(float width, float height) override {D3D11_VIEWPORT vp{0,0,width, height,0.0f, 1.0f}; pContext->RSSetViewports(1, &vp);}

    void SetState(void *p_state) override {pContext->RSSetState((ID3D11RasterizerState*)p_state);}
    void SetStateWireframe() override;

    static CRenderer Instance;

private:
    HWND					window;
    IDXGISwapChain*         pSwapChain;
    ID3D11Device*			pDevice;
    ID3D11DeviceContext*	pContext;
    ID3D11RenderTargetView*	mainRenderTargetView;

    ImGui::CustomWidget::HomePage home_page;

    bool m_bShowContext;
    bool m_bNewFrame;
};

CRenderer CRenderer::Instance;
ICRenderer *g_pRenderer = &CRenderer::Instance;

void CRenderer::Init(void* oWindow, void *p_swapChain, void *p_device, void *p_context) {
    pContext = (ID3D11DeviceContext*)p_context;
    pSwapChain = (IDXGISwapChain*)p_swapChain;
    pDevice = (ID3D11Device*)p_device;
    window = (HWND)oWindow;
    m_bNewFrame = false;
    m_bShowContext = true;

    CreateMainRenderTargetView();

    //todo: custom scaling
    float scale = 1.5f;
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.MouseDrawCursor = true;
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    io.Fonts->Clear();
    io.IniFilename = "./alpha_ring/imgui.ini";
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyh.ttc", 16.0f * scale);
    ImGui::LoadIniSettingsFromDisk("../../../alpha_ring/imgui.ini");
    ImGui::GetStyle().ScaleAllSizes(scale);

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);
}

void CRenderer::CreateMainRenderTargetView() {
    if (!pSwapChain || !pDevice || !pContext) return;

    pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice);
    pDevice->GetImmediateContext(&pContext);

    ID3D11Texture2D *pBackBuffer = nullptr;
    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);//swap chain resize buffer
    pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mainRenderTargetView);
    pBackBuffer->Release();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, nullptr);
}

void CRenderer::ReleaseMainRenderTargetView() {
    if (mainRenderTargetView == nullptr) return;

    pContext->OMSetRenderTargets(0, 0, 0);
    mainRenderTargetView->Release();
    mainRenderTargetView = nullptr;
}

bool CRenderer::NewFrame() {
    if (m_bNewFrame) return false;
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    return m_bNewFrame = true;
}

void CRenderer::Render() {
    NewFrame();

    if (m_bShowContext) {
        ImGui::Begin("Alpha Ring");
        home_page.render();
        ImGui::End();
    }
    else
        ImGui::SetMouseCursor(ImGuiMouseCursor_None);

    EndFrame();
}

void CRenderer::EndFrame() {
    if (!m_bNewFrame) return;
    m_bNewFrame = false;
    ImGui::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void CRenderer::SetStateWireframe() {
    const D3D11_RASTERIZER_DESC desc {
            D3D11_FILL_WIREFRAME,D3D11_CULL_NONE,false,
            0,0.0f,0.0f,
            true, false, false, false
    };
    ID3D11RasterizerState *pRasterizerState;

    pDevice->CreateRasterizerState(&desc, &pRasterizerState);
    pContext->RSSetState(pRasterizerState);
}
