#include "Render.h"

#include "D3d11/D3d11.h"
#include "ImGui/ImGui.h"

bool AlphaRing::Render::Initialize() {
    return AlphaRing::Render::D3d11::Initialize();
}

bool AlphaRing::Render::Render(int render_flag) {
    if (ImGui::BeginFrame()) {
        ImGui::Render(render_flag);
        return true;
    }
    return false;
}

void AlphaRing::Render::SetStateWireframe() {
    const D3D11_RASTERIZER_DESC desc {
            D3D11_FILL_WIREFRAME,D3D11_CULL_NONE,false,
            0,0.0f,0.0f,
            true, false, false, false
    };
    ID3D11RasterizerState *pRasterizerState;

    D3d11::Graphics()->pDevice->CreateRasterizerState(&desc, &pRasterizerState);
    D3d11::Graphics()->pContext->RSSetState(pRasterizerState);
}

void AlphaRing::Render::SetState(void *p_state) {
    D3d11::Graphics()->pContext->RSSetState((ID3D11RasterizerState*)p_state);
}
