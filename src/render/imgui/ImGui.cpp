#include "ImGui.h"

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include "input/Input.h"
#include "global/Global.h"
#include "filesystem/Filesystem.h"

#include "../D3d11/D3d11.h"
#include "./game/mcc/CMCCContext.h"
#include "./game/halo3/CHalo3Context.h"

#include "mcc/mcc.h"
#include "mcc/CGameGlobal.h"

static ICContext* pages[7] {
        nullptr,
        nullptr,
        g_pHalo3Context,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
};

namespace AlphaRing::Render::ImGui {
    bool Initialize() {
        ::ImGui::CreateContext();
        ImGui_ImplWin32_Init(Graphics()->hwnd);
        ImGui_ImplDX11_Init(Graphics()->pDevice, Graphics()->pContext);
        ::ImGui::StyleColorsDark();

        ImGuiIO &io = ::ImGui::GetIO();

        // config
        io.MouseDrawCursor = true;
        io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

        // ini
        io.IniFilename = "./alpha_ring/imgui.ini";
        ::ImGui::LoadIniSettingsFromDisk("../../../alpha_ring/imgui.ini");

        const float scale = GetDpiForWindow(Graphics()->hwnd) * 1.0f / 96.0f;

        auto font_path = R"(C:\Windows\Fonts\msyh.ttc)";

        io.Fonts->Clear();
        if (AlphaRing::Filesystem::Exist(font_path)) {
            io.Fonts->AddFontFromFileTTF(font_path, 16.0f * scale, nullptr, io.Fonts->GetGlyphRangesChineseFull());
        } else {
            ImFontConfig config;
            config.SizePixels = 16.0f * scale;
            io.Fonts->AddFontDefault(&config);
        }

        ::ImGui::GetStyle().ScaleAllSizes(scale);

        return true;
    }

    void Render() {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ::ImGui::NewFrame();

        bool inGame = MCC::IsInGame();
        auto pGameGlobal = GameGlobal();

        AlphaRing::Input::Update();

        if (!AlphaRing::Global::Global()->show_imgui || !AlphaRing::Global::Global()->show_imgui_mouse)
            ::ImGui::SetMouseCursor(ImGuiMouseCursor_None);

        if (!AlphaRing::Global::Global()->show_imgui)
            return;

        g_pMCCContext->render();


        if (inGame && pGameGlobal != nullptr) {
            auto context = pages[pGameGlobal->current_game];
            if (context != nullptr)
                context->render();
        }

        if (::ImGui::BeginMainMenuBar()) {
            if (inGame)
                ::ImGui::Separator();
            ::ImGui::Text("%.1f fps", ::ImGui::GetIO().Framerate);
            ::ImGui::EndMainMenuBar();
        }

        ::ImGui::Render();
        Graphics()->SetRenderTargetView();
        ImGui_ImplDX11_RenderDrawData(::ImGui::GetDrawData());
    }
}