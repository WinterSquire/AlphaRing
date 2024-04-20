#include "imgui_impl.h"

#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"
#include <d3d11.h>

bool                    bInitialized;

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND					window;
WNDPROC					oWndProc;

IDXGISwapChain*         pSwapChain;
ID3D11Device*			pDevice;
ID3D11DeviceContext*	pContext;
ID3D11RenderTargetView*	mainRenderTargetView;

ImmediateGUI::IMGUIContextCallback_t pCallback;
IDXGISwapChain*      ImmediateGUI::GetSwapChain(){return pSwapChain;}
ID3D11Device*		 ImmediateGUI::GetDevice(){return pDevice;}
ID3D11DeviceContext* ImmediateGUI::GetImmediateContext() {return pContext;}
ID3D11RenderTargetView** ImmediateGUI::GetTargetView(){return &mainRenderTargetView;}

bool ImmediateGUI::Initialized() {return bInitialized;}

void ImmediateGUI::Initialize(IDXGISwapChain* swapChain)
{
    pSwapChain = swapChain;

    // 如果获取device失败则返回
    if (FAILED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        return;

    pDevice->GetImmediateContext(&pContext);

    DXGI_SWAP_CHAIN_DESC sd;
    pSwapChain->GetDesc(&sd);
    window = sd.OutputWindow;

    pSwapChain = pSwapChain;

    ImmediateGUI::CreateMainRenderTargetView();

    oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR) WndProc);

    // IMGUI初始化
    float scale = 2.0f;
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    io.MouseDrawCursor = true;
    io.IniFilename = nullptr;
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyh.ttc", 16.0f * scale);
    ImGui::GetStyle().ScaleAllSizes(scale);

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);
    bInitialized = true;
}

static bool bShowContext = true;
bool ImmediateGUI::isVisible() { return bShowContext; }

static bool bRender = false;

void ImmediateGUI::NewFrame() {
    if (bRender) return;
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    bRender = true;
}

void ImmediateGUI::Render() {
    bRender = false;
    ImGui::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

static void setStyle() {
    static bool bFirst = true;
    ImGuiStyle& style = ImGui::GetStyle();
    if (!bFirst) return;
    bFirst = false;
    ImGui::SetWindowSize({800, 600});
}

namespace MCC::IMGUI {extern void page_mcc();}

void ImmediateGUI::Update()
{
    if (!bInitialized) return;

    ImmediateGUI::NewFrame();

    if (bShowContext) {
        ImGui::Begin("Alpha Ring");
        setStyle();
        MCC::IMGUI::page_mcc();
        ImGui::End();
    }
    else ImGui::SetMouseCursor(ImGuiMouseCursor_None);

    ImmediateGUI::Render();
}

// release MainRenderTargetView
void ImmediateGUI::ReleaseMainRenderTargetView() {
    if (mainRenderTargetView == nullptr) return;

    pContext->OMSetRenderTargets(0, 0, 0);
    mainRenderTargetView->Release();
    mainRenderTargetView = nullptr;
}

void ImmediateGUI::CreateMainRenderTargetView() {
    pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice);
    pDevice->GetImmediateContext(&pContext);

    ID3D11Texture2D *pBackBuffer = NULL;
    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);//swap chain resize buffer
    pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
    pBackBuffer->Release();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
}

void ImmediateGUI::SetCallback(ImmediateGUI::IMGUIContextCallback_t callback) {
    pCallback = callback;
}

// forward declare
LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    switch (uMsg) {
        case WM_KEYDOWN:{
            switch (wParam) {
                case VK_F4:{
                    bShowContext = !bShowContext;
                    break;
                }
            }
            break;
        }
        case WM_KEYUP:{

        }
        default:
            break;
    }

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


