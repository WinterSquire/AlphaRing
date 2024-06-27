#include "main_renderer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#include "imgui/main_context.h"

CMainRenderer CMainRenderer::instance;

void CMainRenderer::ImGui_Init() {
    CreateMainRenderTargetView();

    //todo: custom scaling
    float scale = 1.5f;
    ImGui::CreateContext();

    {
        ImGuiIO &io = ImGui::GetIO();

        // config
        io.MouseDrawCursor = true;
        io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

        // ini
        io.IniFilename = "./alpha_ring/imgui.ini";
        ImGui::LoadIniSettingsFromDisk("../../../alpha_ring/imgui.ini");

        // fonts
        io.Fonts->Clear();
        io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\msyh.ttc)", 16.0f * scale, nullptr, io.Fonts->GetGlyphRangesChineseFull());
    }

    ImGui::GetStyle().ScaleAllSizes(scale);

    ImGui_ImplWin32_Init(m_window->get_hwnd());
    ImGui_ImplDX11_Init(m_pDevice, m_pContext);
}

bool CMainRenderer::Render(int render_flag) {
    if (m_bNewFrame) return false;

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (m_bShowContext)
        MainContext()->render(render_flag);

    if (!m_bShowMouse || !m_bShowContext)
        ImGui::SetMouseCursor(ImGuiMouseCursor_None);

    return m_bNewFrame = true;
}

bool CMainRenderer::Present() {
    if (!m_bNewFrame) return false;

    ImGui::Render();
    m_pContext->OMSetRenderTargets(1, &m_pView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    m_bNewFrame = false;
    return true;
}
